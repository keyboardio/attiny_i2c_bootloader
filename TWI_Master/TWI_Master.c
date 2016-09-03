#include <inavr.h>
#include "defines.h"
#include "serial.h"
#include "flash.h"
#include "stdint.h"

#define TWI_DDR_REG  DDRD
#define TWI_PORT_REG PORTD
#define TWI_SCL_PIN  PD0
#define TWI_SDA_PIN  PD1

#define BOOT_DDR_REG      DDRC
#define BOOT_PORT_REG     PORTC
#define BOOT_PIN          PC0

#define RESET_DDR_REG      DDRC
#define RESET_PORT_REG     PORTC
#define RESET_PIN          PC1




#define PAGE_SIZE 64      // 32 words = 64 Bytes
#define MAX__APP_ADDR 0X1800      // Maximum Application Address
// 0x1c00 means.. 1K bytes for Bootloader
// 0x1800 Means... 2K bytes for Bootloader

#define SLAVE_ADDRESS 0xb0

#define _BV( __THE_LOCATION_OF_PIN__ )    ( 1u << __THE_LOCATION_OF_PIN__ )

unsigned char block_load(unsigned int size, unsigned char mem);
/* BLOCKSIZE should be chosen so that the following holds: BLOCKSIZE*n = PAGESIZE,  where n=1,2,3... */

#define BLOCKSIZE PAGE_SIZE


void init_twi( void ) {
    TWI_DDR_REG &= ~(_BV(TWI_SCL_PIN) | _BV(TWI_SDA_PIN));
    TWI_PORT_REG &= ~(_BV(TWI_SCL_PIN) | _BV(TWI_SDA_PIN));

    // Init TWI as master.
    TWCR = _BV(TWEN);
    TWBR = 16; // 250bps @ 8MHz.
}


#define TWI_CMD_PAGEUPDATE        0x01
#define TWI_CMD_EXECUTEAPP        0x02
#define TWI_CMD_AVERSION          0x03
#define TWI_CMD_BVERSION          0x04
#define TWI_CMD_ERASEFLASH        0x05
#define TWI_CMD_CRCCHECK          0x06
#define TWI_CMD_GETERRCONDN       0x07

#define TWI_START_TRANSMITTED     0x08
#define TWI_SLAW_ACKED            0x18
#define TWI_TXDATA_ACKED          0x28
#define TWI_TXDATA_NACKED         0x30
#define TWI_SLAR_ACKED            0x40
#define TWI_RXDATA_ACKED          0x50
#define TWI_RXDATA_NACKED         0x58

uint8_t statusCode;
uint8_t success;
uint8_t over_size_flag=0;

void cycle_reset(void) {
    RESET_PORT_REG &= ~_BV(RESET_PIN);
    __delay_cycles( 10000 );
    RESET_PORT_REG |= _BV(RESET_PIN);
    __delay_cycles( 10000 );
}


uint8_t master_recieve( uint8_t address, uint8_t * data, uint16_t length ) {
    uint8_t error = 0;

    // START condition.
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    do {} while ((TWCR & _BV(TWINT)) == 0);
    error = (TWSR != TWI_START_TRANSMITTED);

    // Send SLA+R.
    if (!error) {
        TWDR = (address & ~0x01) | 0x01; // LSB set = Read.
        TWCR = _BV(TWINT) | _BV(TWEN);
        do {} while ((TWCR & _BV(TWINT)) == 0);
        error = (TWSR != TWI_SLAR_ACKED);
    }

    // Read data bytes minus the last one. Return ACK.
    uint8_t * bufferPtr = data;
    if (!error) {
        for (uint16_t i = 0; i < (length - 1); ++i) {
            TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN);
            do {} while ((TWCR & _BV(TWINT)) == 0);
            error = (TWSR != TWI_RXDATA_ACKED);
            if (!error) {
                *bufferPtr = TWDR;
                ++bufferPtr;
            } else {
                break;
            }
        }
    }

    // Read last data byte. Return NACK.
    if (!error) {
        TWCR = _BV(TWINT) | _BV(TWEN);
        do {} while ((TWCR & _BV(TWINT)) == 0);
        error = (TWSR != TWI_RXDATA_NACKED);
        if (!error) {
            *bufferPtr = TWDR;
            TWCR = _BV(TWSTO) | _BV(TWINT) | _BV(TWEN);
        }
    }

    // Abort communication if error.
    if (error) {
        TWCR = _BV(TWSTO) | _BV(TWINT) | _BV(TWEN);
    }

    return (!error);
}



void get_slave_status(void) {
    do {
        success = master_recieve( SLAVE_ADDRESS, &statusCode, 1 );
    } while ((statusCode != 0) || (!success));
}



uint8_t master_transmit( uint8_t address, uint8_t * data, uint16_t length ) {
    uint8_t error = 0;

    // START condition.
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    do {} while ((TWCR & _BV(TWINT)) == 0);
    error = (TWSR != TWI_START_TRANSMITTED);

    // Send SLA+W.
    if (!error) {
        TWDR = (address & ~0x01) | 0x00; // LSB cleared = Write.
        TWCR = _BV(TWINT) | _BV(TWEN);
        do {} while ((TWCR & _BV(TWINT)) == 0);
        error = (TWSR != TWI_SLAW_ACKED);
    }

    // Send data bytes minus the last one. Expect ACK.
    const uint8_t * bufferPtr = data;
    if (!error) {
        for (uint16_t i = 0; i < (length - 1); ++i) {
            TWDR = *bufferPtr;
            TWCR = _BV(TWINT) | _BV(TWEN);
            do {} while ((TWCR & _BV(TWINT)) == 0);
            error = (TWSR != TWI_TXDATA_ACKED);
            if (!error) {
                ++bufferPtr;
            } else {
                break;
            }
        }
    }

    // Send last data byte. Expect NACK.
    if (!error) {
        TWDR = *bufferPtr;
        TWCR = _BV(TWINT) | _BV(TWEN);
        do {} while ((TWCR & _BV(TWINT)) == 0);
        error = (TWSR != TWI_TXDATA_NACKED);
        if (!error) {
            TWCR = _BV(TWSTO) | _BV(TWINT) | _BV(TWEN);
        }
    }

    // Abort communication if error.
    if (error) {
        TWCR = _BV(TWSTO) | _BV(TWINT) | _BV(TWEN);
    }

    return (!error);
}



uint8_t pageBuffer[PAGE_SIZE+3];
uint16_t addr=0;


void first_time(void) {
    addr=0;
    init_twi();
    pageBuffer[0] = TWI_CMD_PAGEUPDATE;
    BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
    cycle_reset();
    get_slave_status();
}


uint8_t command_char=0, data_char=0, CRC_HI=0, CRC_LO=0;
uint8_t runApp[2];
uint8_t reps=0;

void read_from_slave(void) {
    if (success) {
        do {
            success = master_recieve( SLAVE_ADDRESS, &statusCode, 1 );
        } while ( !success );
    }
}



void read_and_send(uint8_t whichversion) {
    runApp[0]=whichversion;
    runApp[1]=whichversion;
    BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
    cycle_reset();
    get_slave_status();
    success = master_transmit( SLAVE_ADDRESS, runApp, 2 );
    read_from_slave();
    sendchar( statusCode );
}

void send_command(uint8_t command) {
    runApp[0] = command;
    runApp[1] = command;
    BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
    cycle_reset();
    get_slave_status();
    success = master_transmit( SLAVE_ADDRESS, runApp, 2 );
}


/*************************************************************************/
__C_task void main(void) {
    unsigned int temp_int;
    unsigned char val=0;


    init_twi();


    BOOT_DDR_REG |= _BV(BOOT_PIN);
    BOOT_PORT_REG &= ~_BV(BOOT_PIN);

    RESET_DDR_REG |= _BV(RESET_PIN);
    RESET_PORT_REG |= _BV(RESET_PIN);

    initbootuart(); // Initialize UART.
    /* Main loop */
    for(;;) {
        val=recchar(); // Wait for command character.

        if (( val ==  'P') || ( val == 'L')) {
            sendchar('\r');
        }

        else if (val == 'E') {
            sendchar('\r');
        }

        // Read lock byte -> execute command
        else if ( val == 'r') {
            if ( command_char == 'a') {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                read_and_send( TWI_CMD_AVERSION );
            } else if ( command_char == 'b' ) {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                read_and_send( TWI_CMD_BVERSION );
            } else if ( command_char == 'd' ) {
                // Read CRCHI
                sendchar(CRC_HI);
            } else if ( command_char == 'e' ) {
                // Read CRCLO
                sendchar(CRC_LO);
            } else if ( command_char == 'f' ) {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                // Status condition
                read_and_send(TWI_CMD_GETERRCONDN);
            } else
                sendchar(0xFF);

        }
        // Write lock byte -> load command
        else if ( val == 'l') {
            command_char = recchar();
            if ( command_char == 'c' ) {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                send_command( TWI_CMD_CRCCHECK );
                read_from_slave();
                CRC_HI= statusCode;
                read_from_slave();
                CRC_LO = statusCode;
            }
            sendchar('\r');
        }

        // Read high fuse bits -> BVERSION
        else if ( val == 'N' ) {
            BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
            read_and_send( TWI_CMD_BVERSION );
        }

        // Low Fuse Bits -> AVERSION
        else if ( val == 'F' ) {
            BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
            read_and_send( TWI_CMD_AVERSION );
        }

        else  if (val == 'a' ) {
            sendchar('Y'); // Yes, we do autoincrement.
        }

        else if (val=='A') { // Set address...
            // NOTE: Flash addresses are given in words, not bytes.
            addr =(recchar()<<8) | recchar(); // Read address high and low byte.
            addr = addr<<1;
            if (addr > MAX__APP_ADDR) over_size_flag =1;
            pageBuffer[1] = (uint8_t)(addr&0x00FF);
            addr = addr>>8;
            pageBuffer[2] = (uint8_t)(addr&0x00FF);
            sendchar('\r'); // Send OK back.

        }

        // Chip erase.
        else if (val == 'e' ) {
            runApp[0] =  TWI_CMD_ERASEFLASH;
            runApp[1] =  TWI_CMD_ERASEFLASH;
            BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
            cycle_reset();
            get_slave_status();
            success = master_transmit( SLAVE_ADDRESS, runApp, 2 );
            sendchar('\r'); // Send OK back.
        }

        // Check block load support.
        else if (val == 'b' ) {
            sendchar('Y'); // Report block load supported.
            sendchar((BLOCKSIZE>>8) & 0xFF); // MSB first.
            sendchar(BLOCKSIZE&0xFF); // Report BLOCKSIZE (bytes).
        }

        // Start block load.
        else  if (val == 'B' ) {

            temp_int = (recchar()<<8) | recchar(); // Get block size.
            val = recchar(); // Get memtype.
            sendchar( block_load(temp_int,val) ); // Block load.
            if (reps == 0)
                first_time();
            success = master_transmit( SLAVE_ADDRESS, pageBuffer, PAGE_SIZE+3 );
            if (success) {
                get_slave_status();
            }
            reps ++;
        }

        // Return programmer identifier.
        else if (val == 'S' ) {
            sendchar('A'); // Return 'AVRBOOT'.
            sendchar('V'); // Software identifier (aka programmer signature) is always 7 characters.
            sendchar('R');
            sendchar('B');
            sendchar('O');
            sendchar('O');
            sendchar('T');
            reps =0;
        }

        // Return software version.
        else if (val == 'V' ) {
            send_command(TWI_CMD_EXECUTEAPP);
            // Disable bootloader mode for slave
            BOOT_PORT_REG |= _BV(BOOT_PIN);
            sendchar('2');
            sendchar('0');
        }

        // Return signature bytes.
        else if (val == 's') {
            sendchar( SIGNATURE_BYTE_3 );
            sendchar( SIGNATURE_BYTE_2 );
            sendchar( SIGNATURE_BYTE_1 );
        }

        else if (val != 0x1b)                  // If not ESC, then it is unrecognized...
            sendchar('?');

    } // end: for(;;)
} // end: main

unsigned char block_load(unsigned int size, unsigned char mem) {
    // Flash memory type.
    if (!over_size_flag) { // Check for file size to be less than maximum pages that can be programmed
        if (mem=='F') {
            for (uint16_t i = 0; i < size; ++i) {
                pageBuffer[i+3] = recchar();
            }
            return '\r'; // Report programming OK
        }

        // Invalid memory type?
        else {
            return '?';
        }
    } else {
        over_size_flag=0;
        return '?';
    }
}
