#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "defines.h"
#include "serial.h"
#include "flash.h"
#include <Wire.h>

#include "stdint.h"

#define TWI_DDR_REG  DDRD
#define TWI_PORT_REG PORTD
#define TWI_SCL_PIN  PD0
#define TWI_SDA_PIN  PD1

#define BOOT_DDR_REG      DDRC
#define BOOT_PORT_REG     PORTC
#define BOOT_PIN          0

#define RESET_DDR_REG      DDRC
#define RESET_PORT_REG     PORTC
#define RESET_PIN          1




#define PAGE_SIZE 64      // 32 words = 64 Bytes
#define MAX__APP_ADDR 0X1800      // Maximum Application Address
// 0x1c00 means.. 1K bytes for Bootloader
// 0x1800 Means... 2K bytes for Bootloader

#define SLAVE_ADDRESS 0xb0


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
  //  RESET_PORT_REG &= ~_BV(RESET_PIN);
    delay( 10);
    //RESET_PORT_REG |= _BV(RESET_PIN);
    delay( 10 );
}


uint8_t master_recieve( uint8_t address, uint8_t * data, uint16_t length ) {
  Wire.requestFrom(address,length);
  for(uint16_t i=0;i<length;i++) {
    data[i] = Wire.read();
  }

  return 1;
  }



void get_slave_status(void) {
    do {
        success = master_recieve( SLAVE_ADDRESS, &statusCode, 1 );
    } while ((statusCode != 0) || (!success));
}



uint8_t master_transmit( uint8_t address, uint8_t * data, uint16_t length ) {
  Wire.beginTransmission(address);
  return Wire.write(data,length);

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
    Serial.write( statusCode );
}

void send_command(uint8_t command) {
    runApp[0] = command;
    runApp[1] = command;
  //  BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
    cycle_reset();
    get_slave_status();
    success = master_transmit( SLAVE_ADDRESS, runApp, 2 );
}


/*************************************************************************/
void setup (void) {


    Wire.begin();


    BOOT_DDR_REG |= _BV(BOOT_PIN);
    BOOT_PORT_REG &= ~_BV(BOOT_PIN);

    RESET_DDR_REG |= _BV(RESET_PIN);
    RESET_PORT_REG |= _BV(RESET_PIN);

    Serial.begin(9600); // Initialize UART.
}

void loop() {
     unsigned int temp_int;
    unsigned char val=0;

    /* Main loop */
    for(;;) {
        val=Serial.read(); // Wait for command character.

        if (( val ==  'P') || ( val == 'L')) {
            Serial.write('\r');
        }

        else if (val == 'E') {
            Serial.write('\r');
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
                Serial.write(CRC_HI);
            } else if ( command_char == 'e' ) {
                // Read CRCLO
                Serial.write(CRC_LO);
            } else if ( command_char == 'f' ) {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                // Status condition
                read_and_send(TWI_CMD_GETERRCONDN);
            } else
                Serial.write(0xFF);

        }
        // Write lock byte -> load command
        else if ( val == 'l') {
            command_char = Serial.read();
            if ( command_char == 'c' ) {
                BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
                send_command( TWI_CMD_CRCCHECK );
                read_from_slave();
                CRC_HI= statusCode;
                read_from_slave();
                CRC_LO = statusCode;
            }
            Serial.write('\r');
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
            Serial.write('Y'); // Yes, we do autoincrement.
        }

        else if (val=='A') { // Set address...
            // NOTE: Flash addresses are given in words, not bytes.
            addr =(Serial.read()<<8) | Serial.read(); // Read address high and low byte.
            addr = addr<<1;
            if (addr > MAX__APP_ADDR) over_size_flag =1;
            pageBuffer[1] = (uint8_t)(addr&0x00FF);
            addr = addr>>8;
            pageBuffer[2] = (uint8_t)(addr&0x00FF);
            Serial.write('\r'); // Send OK back.

        }

        // Chip erase.
        else if (val == 'e' ) {
            runApp[0] =  TWI_CMD_ERASEFLASH;
            runApp[1] =  TWI_CMD_ERASEFLASH;
            BOOT_PORT_REG &= ~( 1 << BOOT_PIN );
            cycle_reset();
            get_slave_status();
            success = master_transmit( SLAVE_ADDRESS, runApp, 2 );
            Serial.write('\r'); // Send OK back.
        }

        // Check block load support.
    //    else if (val == 'b' ) {
    //        Serial.write('Y'); // Report block load supported.
    //        Serial.write((BLOCKSIZE>>8) & 0xFF); // MSB first.
    //        Serial.write(BLOCKSIZE & 0xFF); // Report BLOCKSIZE (bytes).
    //    }

        // Start block load.
        else  if (val == 'B' ) {

            temp_int = (Serial.read()<<8) | Serial.read(); // Get block size.
            val = Serial.read(); // Get memtype.
            Serial.write( block_load(temp_int,val) ); // Block load.
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
            Serial.write('A'); // Return 'AVRBOOT'.
            Serial.write('V'); // Software identifier (aka programmer signature) is always 7 characters.
            Serial.write('R');
            Serial.write('B');
            Serial.write('O');
            Serial.write('O');
            Serial.write('T');
            reps =0;
        }

        // Return software version.
        else if (val == 'V' ) {
            send_command(TWI_CMD_EXECUTEAPP);
            // Disable bootloader mode for slave
            BOOT_PORT_REG |= _BV(BOOT_PIN);
            Serial.write('2');
            Serial.write('0');
        }

        // Return signature bytes.
        else if (val == 's') {
            Serial.write( SIGNATURE_BYTE_3 );
            Serial.write( SIGNATURE_BYTE_2 );
            Serial.write( SIGNATURE_BYTE_1 );
        }

        else if (val != 0x1b)                  // If not ESC, then it is unrecognized...
            Serial.write('?');

    } // end: for(;;)
} // end: main

unsigned char block_load(unsigned int size, unsigned char mem) {
    // Flash memory type.
    if (!over_size_flag) { // Check for file size to be less than maximum pages that can be programmed
        if (mem=='F') {
            for (uint16_t i = 0; i < size; ++i) {
                pageBuffer[i+3] = Serial.read();
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
