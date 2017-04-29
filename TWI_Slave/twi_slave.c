#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/crc16.h>
#include "common_define.h"

// AD01: lower two bits of device address
#define AD01 ((PINB & _BV(0)) | (PINB & _BV(1)))

//configuring LAST_INTVECT_ADDRESS as per device selected
/*****************************************************************************/
#define LAST_INTVECT_ADDRESS 		TWI_vect // The start of the application code


/*****************************************************************************/
#define TWI_SLAW_RECEIVED         	0x60	// Status slave address and write command received
#define TWI_SLAR_RECEIVED         	0xa8	// Status slave address and read command received
#define TWI_SLAVE_TX_ACK_RECEIVED 	0xb8	// Status slave transmit and acknowledgement returned
#define TWI_SLAVE_TX_NACK_RECEIVED 	0xc0	// Status slave transmit and no acknowledgement of last byte
#define TWI_SLAVE_RX_ACK_RETURNED  	0x80	// Status slave receive and acknowledgement returned
#define TWI_SLAVE_RX_NACK_RETURNED 	0x88	// Status slave receive and no acknowledgement of last byte

#define ACK TWI_SLAVE_RX_ACK_RETURNED
#define NAK TWI_SLAVE_RX_NACK_RETURNED


// globals

// reuse pageAddr variable for CRC16 to save space
uint16_t pageAddr;
#define sendCrc16 pageAddr
// which frame of the page we are processing
uint8_t frame = 0;

void setup_pins() {
    DDRC |= _BV(7); // C7 is COMM_EN - this turns on the PCA9614 that does differential i2c between hands
    PORTC |= _BV(7); // Without it, the right hand can't talk to the world.

    
    // DDRB &= ~(_BV(0) | _BV(1) ); // set the AD01 ports as inputs

    // DDRB |= _BV(5)|_BV(3)|_BV(2); /* Set MOSI, SCK, SS all to outputs so we can use them to clear out the LEDs*/
    // TODO: Replace the last two lines with otentially sketchy optimization
    DDRB = _BV(5)|_BV(3)|_BV(2); //0b00101100; 
    PORTB &= ~(_BV(5)|_BV(3)|_BV(2)); // Drive MOSI/SCK/SS low
}

void init_twi() {
    TWAR = (SLAVE_BASE_ADDRESS | AD01) << 1; // ignore the general call address
    TWCR = _BV(TWEN) | _BV(TWEA); // activate, ack our address
    // Enable, but don't enable ACK until we are ready to receive packets.
}

inline void wait_for_activity(uint8_t ack) {
    // possibly Enable ACK and clear pending interrupts.
    TWCR = _BV(TWINT) | _BV(TWEN) | (ack == ACK  ? _BV(TWEA) : 0);

    do {} while ((TWCR & _BV(TWINT)) == 0);
    wdt_reset();
}

void __attribute__ ((noinline)) abort_twi() {
    // Recover from error condition by releasing bus lines.
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void process_slave_transmit(uint8_t data) {
     // Prepare data for transmission.
    TWDR = data;

    wait_for_activity(ACK);

    // Check TWI status code for SLAVE_TX_NACK.
    if (TWSR != TWI_SLAVE_TX_ACK_RECEIVED) {
        abort_twi();
        return;
    }
}

uint8_t slave_receive_byte(uint8_t *data, uint8_t ack) {
    // Receive byte and return ACK.
    wait_for_activity(ack);

    // Check TWI status code for SLAVE_RX_ACK. or SLAVE_RX_NACK
    // Basically, if the status register has the same value as
    // the type of packet we're looking for, then proceeed

    if (TWSR != ack) {
        abort_twi();
        return 0;
    }

    // Get byte
    *data = TWDR;
    if (ack == TWI_SLAVE_RX_NACK_RETURNED) {
        // If we're doing a NACK, then twiddle TWCR
        TWCR = _BV(TWINT) | _BV(TWEN);
    }
    return 1;
}

// receive two-byte word (little endian) over TWI
uint16_t slave_receive_word() {
    uint8_t lo, hi;
    slave_receive_byte(&lo, ACK);
    slave_receive_byte(&hi, ACK);
    return (hi << 8) | lo;
}

// don't call this, call update_page unless you need to bypass safety checks
void unsafe_update_page(uint16_t pageAddress) {
  for (uint8_t i = 0; i < PAGE_SIZE; i += 2) {
      uint16_t tempWord = ((pageBuffer[i+1] << 8) | pageBuffer[i]);
      boot_spm_busy_wait();
      boot_page_fill(pageAddress + i, tempWord); // Fill the temporary buffer with the given data
  }

  // Write page from temporary buffer to the given location in flash memory
  boot_spm_busy_wait();
  boot_page_write(pageAddress);
}

void buffer_reset_vector() {
    // Load existing RESET vector contents into buffer.
    for(uint8_t i = 4; i != 0; i--) {
        pageBuffer[i - 1] = pgm_read_byte(INTVECT_PAGE_ADDRESS + i - 1);
    }
}

void update_page(uint16_t pageAddress) {
    // Mask out in-page address bits.
    pageAddress &= ~(PAGE_SIZE - 1);
    // Protect RESET vector if this is page 0.
    if (pageAddress == INTVECT_PAGE_ADDRESS) {
	buffer_reset_vector();
    }

    // Ignore any attempt to update boot section.
    if (pageAddress >= BOOT_PAGE_ADDRESS) {
        return;
    }

    unsafe_update_page(pageAddress);
}

void __attribute__ ((noinline)) erase_page_buffer() {
    // clear the page buffer
    for (uint8_t i = 0; i < PAGE_SIZE; i++) {
        pageBuffer[i] = 0xFF;
    }
}


void process_read_address() {
  frame = 0; // reset which frame we are reading

  erase_page_buffer();

  // Receive two-byte page address.
  pageAddr = slave_receive_word();
}

uint8_t process_read_frame() {
    // check disabled for space reasons
    // Check the SPM is ready, abort if not.
     if ((SPMCSR & _BV(SELFPROGEN)) != 0) {
        abort_twi();
        return 0;
     }
 
    uint8_t *bufferPtr = &pageBuffer[frame * FRAME_SIZE];

    // Receive page data in frame-sized chunks
    uint16_t crc16 = 0xffff;
    for (uint8_t i = 0; i < FRAME_SIZE; i++) {
        if (!slave_receive_byte(bufferPtr, ACK)) {
            return 0;
        }
        crc16 = _crc16_update(crc16, *bufferPtr);
        bufferPtr++;
    }
    // check received CRC16
    if (crc16 != slave_receive_word()) {
      return 0;
    }
    frame++;
    return 1;
}

// Now program if everything went well.
void process_page_update() {
    update_page(pageAddr);
}

void cleanup_and_run_application(void) {
    wdt_disable(); // After Reset the WDT state does not change

    asm volatile ("rjmp __vectors-0x1bc8");  // jump to start of user code at 0x38
    
    for (;;); // Make sure function does not return to help compiler optimize
}


void process_page_erase() {
    erase_page_buffer();

    // read the reset vector
    buffer_reset_vector();

    boot_spm_busy_wait();
    boot_page_erase(0); // have to erase the first page or else it will not write correctly

    unsafe_update_page(0); // restore just the initial vector

    uint16_t addr = PAGE_SIZE;
    update_page(addr);

    while (addr < BOOT_PAGE_ADDRESS) {
        boot_spm_busy_wait();
        boot_page_erase(addr);
        addr += PAGE_SIZE;
    }
}

void process_getcrc16() {
    // get program memory address and length to calcaulate CRC16 of
    uint16_t addr = slave_receive_word();
    uint16_t len = slave_receive_word();
    uint16_t max = addr + len;

    // bail if it overflows
    // disable sanity check for space
    // it's actually a duplicate of the condition on the while loop
    // so it's safe to leave disabled
    // if (max < addr) {
    //   return;
    // }
    // bail if it exceeds flash capacity
    // if (  max >= FLASH_SIZE) {
    //   return;
    // }

    sendCrc16 = 0xffff;
    while (addr < max) {
      sendCrc16 = _crc16_update(sendCrc16, pgm_read_byte(addr));
      addr++;
    }
}

void transmit_crc16_and_version() {
    // write the version, then crc16, lo first, then hi
    process_slave_transmit(BVERSION);
    process_slave_transmit(sendCrc16 & 0xff);
    process_slave_transmit(sendCrc16 >> 8);
}

inline void send_transmit_success() {
    uint8_t _;
    // nack for a last dummy byte to say we read everything
    slave_receive_byte(&_, NAK);
}

void send_transmit_error() {
    uint8_t _;
    // AC for a last dummy byte to say we had an error
    slave_receive_byte(&_, ACK);
}


void process_slave_receive() {
    uint8_t commandCode;

    if (!slave_receive_byte(&commandCode, ACK)) {
        return;
    }

    // Process command byte.
    switch (commandCode) {
    case TWI_CMD_PAGEUPDATE_ADDR:
        process_read_address();
        break;
    case TWI_CMD_PAGEUPDATE_FRAME:
        if (!process_read_frame(&pageAddr)) {
          send_transmit_error();
          break;
        }
        if (frame == PAGE_SIZE / FRAME_SIZE) {
          process_page_update();
        }
        send_transmit_success();
        break;

    case TWI_CMD_EXECUTEAPP:
	wdt_enable(WDTO_15MS);  // Set WDT min for cleanup using reset
        asm volatile ("HERE:rjmp HERE");//Yes it's an infinite loop
	//for (;;); // Wait for WDT reset

    case TWI_CMD_ERASEFLASH:
        process_page_erase();
        break;

    case TWI_CMD_GETCRC16:
        process_getcrc16();
        break;

    default:
        abort_twi();
    }

    return;
}

void read_and_process_packet() {

    wait_for_activity(ACK);
    wdt_enable(WDTO_8S);  // Set WDT min for cleanup using reset

    // Check TWI status code for SLA+W or SLA+R.
    switch (TWSR) {
    case TWI_SLAW_RECEIVED:
        process_slave_receive();
        break;
    case TWI_SLAR_RECEIVED:
        transmit_crc16_and_version();
        init_twi();
        break;

    default:
        abort_twi();
    }
}


void init_spi_for_led_control() {
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPIE) | _BV(SPR0);
    //   SPSR = _BV(SPI2X);

}
ISR(SPI_STC_vect) {
    // Technically, we should be writing out a start frame, 
    // followed by 32 LEDs worth of data frames
    // followed by an end frame.
    // But all of those would be zeros.
    //
    // Hopefully, doing this won't cause the LEDs to get into a bad state
    // when we load the user program
   
    SPDR=0;
}

// Main Starts from here
int main() {

    // Turn on the interhand controllers and get the LEDs turned off
    // before deciding what to do next.
    
    setup_pins();
    init_spi_for_led_control();

    uint8_t sr_temp = MCUSR;
    MCUSR=0;

    // If this isn't a power-on reset or an external reset 
    // then we should skip the bootloader
    // We can toggle the left hand's extrf and the right hand's power
    if (sr_temp ^ (_BV(PORF)|_BV(EXTRF))) { 
        cleanup_and_run_application();
    }

    init_twi();
    // TODO - I'm not sure it's safe to not set this short little watchdog here./

    wdt_enable(WDTO_60MS);
    while (1) {
        read_and_process_packet(); // Process the TWI Commands
    }
}
