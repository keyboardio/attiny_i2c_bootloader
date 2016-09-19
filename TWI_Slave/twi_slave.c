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
#define TWI_SLAVE_TX_NACK_RECEIVED 	0xc0	// Status slave transmit and no acknowledgement or last byte
#define TWI_SLAVE_RX_ACK_RETURNED  	0x80	// Status slave receive and acknowledgement returned
#define TWI_SLAVE_RX_NACK_RETURNED 	0x88	// Status slave receive and no acknowledgement or last byte

#define ACK TWI_SLAVE_RX_ACK_RETURNED
#define NAK TWI_SLAVE_RX_NACK_RETURNED


void init_twi() {
    DDRC &= ~(_BV(0) | _BV(1)); // set the AD01 ports as inputs
    DDRC &= ~(_BV(PORTC5) | _BV(PORTC4)); // Set SCL and SDA as input
    PORTC &= ~(_BV(PORTC5) | _BV(PORTC4)); // Set SCL and SDA low
    // Note: PORTC4 and PORT5 commonly used for tiny48. tiny88, mega48 TWI based devices

    TWAR = (SLAVE_BASE_ADDRESS | AD01) << 1; // ignore the general call address
    TWCR = _BV(TWEN) | _BV(TWEA); // activate, ack our address
    // Enable, but don't enable ACK until we are ready to receive packets.
}

inline void wait_for_activity() {
    do {} while ((TWCR & _BV(TWINT)) == 0);
    wdt_reset ();
}

uint8_t get_status_code() {
    // Check if SPM operation is complete
    if ((SPMCSR & _BV(SELFPROGEN)) != 0) {
        return STATUSMASK_SPMBUSY;
    }

    return 0;
}

void abort_twi (void) {
    // Recover from error condition by releasing bus lines.
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void process_slave_transmit (uint8_t data) {
    // Prepare data for transmission.
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);	// Send byte, NACK expected from master.
    wait_for_activity();

    // Check TWI status code for SLAVE_TX_NACK.
    if (TWSR != TWI_SLAVE_TX_NACK_RECEIVED) {
        abort_twi ();
        return;
    }

    // End communication.
    TWCR = _BV(TWINT) | _BV(TWEN);
}

uint8_t slave_receive_byte(uint8_t *data, uint8_t ack) {
    // Receive byte and return ACK.
    TWCR = _BV(TWINT) | _BV(TWEN) | (ack == ACK  ? _BV(TWEA) : 0);

    wait_for_activity();

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

// don't call this, call update_page unless you need to bypass safety checks
void unsafe_update_page(uint16_t pageAddress) {
  for (uint8_t i = 0; i < PAGE_SIZE; i += 2) {
      uint16_t tempWord = ((pageBuffer[i+1] << 8) | pageBuffer[i]);
      boot_page_fill_safe(pageAddress + i, tempWord); // Fill the temporary buffer with the given data
  }

  // Write page from temporary buffer to the given location in flash memory
  boot_page_write_safe(pageAddress);
}

uint8_t update_page(uint16_t pageAddress) {
    // Mask out in-page address bits.
    pageAddress &= ~(PAGE_SIZE - 1);
    // Protect RESET vector if this is page 0.
    if (pageAddress == INTVECT_PAGE_ADDRESS) {
        // Load existing RESET vector contents into buffer.
        pageBuffer[0] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 0);
        pageBuffer[1] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 1);
        pageBuffer[2] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 2);
        pageBuffer[3] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 3);
    }

    // Ignore any attempt to update boot section.
    if (pageAddress >= BOOT_PAGE_ADDRESS) {
        return 0;
    }

    unsafe_update_page(pageAddress);

    wdt_reset(); // Reset the watchdog timer
    return 1;
}

uint8_t pageAddressLo;
uint8_t pageAddressHi;

// which frame of the page we are processing
uint8_t frame = 0;

uint8_t process_read_address() {
  frame = 0; // reset which frame we are reading

  // clear the page buffer
  for (uint8_t i = 0; i < PAGE_SIZE; ++i) {
      pageBuffer[i] = 0xFF;
  }

  // Receive two-byte page address.
  if (!slave_receive_byte(&pageAddressLo, ACK)) {
      return 0;
  }
  if (!slave_receive_byte(&pageAddressHi, ACK)) {
      return 0;
  }
  wdt_reset(); // Reset the watchdog timer
  return 1;
}

uint8_t process_read_frame() {
    uint16_t crc16 = 0xffff;

    // Check the SPM is ready, abort if not.
    if ((SPMCSR & _BV(SELFPROGEN)) != 0) {
        abort_twi();
        return 0;
    }
    uint8_t *bufferPtr = &pageBuffer[frame * FRAME_SIZE];

    // Receive page data in frame-sized chunks
    for (uint8_t i = 0; i < FRAME_SIZE; i++) {
        if (!slave_receive_byte(bufferPtr, ACK)) {
            return 0;
        }
        crc16 = _crc16_update(crc16, *bufferPtr);
        bufferPtr++;
    }
    // grab the CRC16 checksum, sent little end first.
    uint8_t c0, c1;
    if (!slave_receive_byte(&c0, ACK)) {
        return 0;
    }
    if (!slave_receive_byte(&c1, ACK)) {
        return 0;
    }
    // if the CRC16 doesn't match, reject the frame
    if (crc16 != (uint16_t) ((c1 << 8) | c0)) {
      return 0;
    }
    frame++;
    wdt_reset(); // Reset the watchdog timer
    return 1;
}

// Now program if everything went well.
uint8_t process_page_update (void) {
    if (!update_page((pageAddressHi << 8) | pageAddressLo)) {
        return 0;
    }
    return 1;
}

void cleanup_and_run_application() {
    MCUSR = 0; // clear resets
    wdt_disable(); // After Reset the WDT state does not change

    // TODO: this should be possible to do with rjmp and save 4 bytes
    asm volatile ("ldi r31, 0x00");
    asm volatile ("ldi r30, 0x38");
    asm volatile ("ijmp"); // jump to start of user code

    for (;;); // Make sure function does not return to help compiler optimize

}

void process_page_erase() {
    for (uint8_t i = 0; i < PAGE_SIZE; ++i) {
        pageBuffer[i] = 0xFF;
    }
    // read the reset vector
    pageBuffer[0] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 0);
    pageBuffer[1] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 1);
    pageBuffer[2] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 2);
    pageBuffer[3] = pgm_read_byte(INTVECT_PAGE_ADDRESS + 3);

    boot_page_erase_safe(0); // have to erase the first page or else it will not write correctly

    unsafe_update_page(0); // restore just the initial vector

    uint16_t addr = 0;
    addr += PAGE_SIZE;
    update_page(addr);

    for (uint8_t i = 0; i < (LAST_PAGE_NO_TO_BE_ERASED - 1); i++, addr += PAGE_SIZE) {
        addr &= ~(PAGE_SIZE - 1);

        if (addr < BOOT_PAGE_ADDRESS) {
            boot_page_erase_safe(addr);
        }
    }
}

void process_slave_receive() {
    uint8_t commandCode;

    if (!slave_receive_byte(&commandCode, ACK)) {
        return;
    }

    // Process command byte.
    switch (commandCode) {
    case TWI_CMD_PAGEUPDATE_ADDR:
        if (!process_read_address()) {
          // indicate an error
          slave_receive_byte(&commandCode, ACK);
          break;
        }
        // nack for a last dummy byte to say we read everything
        slave_receive_byte(&commandCode, NAK);
        break;
    case TWI_CMD_PAGEUPDATE_FRAME:
        if (!process_read_frame()) {
          // indicate an error
          slave_receive_byte(&commandCode, ACK);
          break;
        }
        if (frame == PAGE_SIZE / FRAME_SIZE) {
          if (!process_page_update()) {
            // indicate an error
            slave_receive_byte(&commandCode, ACK);
            break;
          }
        }
        // nack for a last dummy byte to say we read everything
        slave_receive_byte(&commandCode, NAK);
        break;

    case TWI_CMD_EXECUTEAPP:
        // nack for a last dummy byte to say we read everything
        slave_receive_byte(&commandCode, NAK);
        wdt_enable(WDTO_15MS);  // Set WDT min for cleanup using reset
        for (;;); // Wait for WDT reset

    case TWI_CMD_ERASEFLASH:
        process_page_erase();
        // nack for a last dummy byte to say we read everything
        slave_receive_byte(&commandCode, NAK);
        break;

    default:
        abort_twi();
    }
}

void read_and_process_packet() {
    // Enable ACK and clear pending interrupts.
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN);

    wait_for_activity();

    // Check TWI status code for SLA+W or SLA+R.
    switch (TWSR) {
    case TWI_SLAW_RECEIVED:
        process_slave_receive();
        break;

    case TWI_SLAR_RECEIVED:
        process_slave_transmit(get_status_code() & STATUSMASK_SPMBUSY);
        break;

    default:
        abort_twi();
    }
}

// Main Starts from here
int main() {
    if (MCUSR & _BV (PORF) || MCUSR & _BV(EXTRF)) {
        // Only in case of Power On Reset
        // Or external reset
        // We can toggle the left hand's extrf and the right hand's
        // power
        // rewrite the vector
        MCUSR = 0;
        init_twi();
        wdt_enable(WDTO_8S);

        while (1) {
            read_and_process_packet(); // Process the TWI Commands
        }
    } else {
        cleanup_and_run_application();
    }
}
