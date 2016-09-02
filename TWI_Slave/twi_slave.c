#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "common_define.h"



//configuring LAST_INTVECT_ADDRESS as per device selected
/*****************************************************************************/
#define LAST_INTVECT_ADDRESS 		TWI_vect // The start of the application code




/*****************************************************************************/
/*****************************************************************************/
#define TWI_SLAW_RECEIVED         	0x60	// Status slave address and write command received
#define TWI_SLAR_RECEIVED         	0xa8	// Status slave address and read command received
#define TWI_SLAVETX_NACK_RECEIVED 	0xc0	// Status slave transmit and no acknowledgement or last byte
#define TWI_SLAVERX_ACK_RETURNED  	0x80	// Status slave receive and acknowledgement returned
#define TWI_SLAVERX_NACK_RETURNED 	0x88	// Status slave receive and no acknowledgement or last byte


//
uint8_t state = 0;
// __no_init uint8_t pageBuffer[PAGE_SIZE];
uint16_t time_lapse_sec = 0;
uint8_t volatile gtimeout;
uint8_t statusCode = 0;

/***********************************************************************/

/***********************************************************************/
void InitTWI (void) {
    DDRC &= ~((1 << PORTC5) | (1 << PORTC4)); // Set SCL and SDA as input
    PORTC &= ~((1 << PORTC5) | (1 << PORTC4)); // Set SCL and SDA low
    // Note: PORTC4 and PORT5 commonly used for tiny48. tiny88, mega48 TWI based devices

    TWAR = SLAVE_ADDRESS;
    TWCR = (1 << TWEN);
    // Enable, but don't enable ACK until we are ready to receive packets.
}
/***********************************************************************/



/***********************************************************************/
//! Return non-zero if "Enter Bootloader" pin is held low externally.
uint8_t IsBootPinLow (void) {
    // Make sure "Enter Bootloader" pin is input with internal pull-up.

    DDRB &= ~(1 << PORTB0);  //making port pin as input
    PORTB |= (1 << PORTB0);
    // Let it settle.
    _delay_us (BOOT_SETTLE_DELAY);
    // Return non-zero if pin is low.
    return ((PINB & (1 << PORTB0)) == 0);

}
/***********************************************************************/



/***********************************************************************/
uint8_t GetStatusCode (void) {
    // Check if SPM operation is complete
    if ((SPMCSR & (1 << SELFPROGEN)) != 0)
        statusCode |= STATUSMASK_SPMBUSY;

    return statusCode;
}
/***********************************************************************/


/***********************************************************************/
void AbortTWI (void) {
    // Recover from error condition by releasing bus lines.
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
/***********************************************************************/


/***********************************************************************/
void ProcessSlaveTransmit (uint8_t data) {
    // Prepare data for transmission.
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);	// Send byte, NACK expected from master.
    // Wait for activity.
    do {} while ((TWCR & (1 << TWINT)) == 0);
    wdt_reset ();
    // Check TWI status code for SLAVETX_NACK.
    switch (TWSR) {
    case TWI_SLAVETX_NACK_RECEIVED:
        // End communication.
        TWCR = (1 << TWINT) | (1 << TWEN);
        break;

    default:
        AbortTWI ();
    }
}
/***********************************************************************/


/***********************************************************************/
uint8_t SlaveReceiveByteAndACK (uint8_t * data) {
    // Receive byte and return ACK.
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    // Wait for activity.
    do {} while ((TWCR & (1 << TWINT)) == 0);
    wdt_reset ();
    // Check TWI status code for SLAVERX_ACK.
    switch (TWSR) {
    case TWI_SLAVERX_ACK_RETURNED:
        // Get byte and return non-zero for success.
        *data = TWDR;
        return 1;

    default:
        AbortTWI ();
        return 0;
    }
}
/***********************************************************************/


/***********************************************************************/
uint8_t SlaveReceiveByteAndNACK (uint8_t * data) {
    // Receive byte and return NACK.
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for activity.
    do {} while ((TWCR & (1 << TWINT)) == 0);
    wdt_reset ();

    // Check TWI status code for SLAVERX_ACK.
    switch (TWSR) {
    case TWI_SLAVERX_NACK_RETURNED:
        // Get byte, end communication and return non-zero for success.
        *data = TWDR;
        TWCR = (1 << TWINT) | (1 << TWEN);
        return 1;

    default:
        AbortTWI ();
        return 0;
    }
}
/***********************************************************************/



/***********************************************************************/
void UpdatePage (uint16_t pageAddress) {
    // Mask out in-page address bits.
    pageAddress &= ~(PAGE_SIZE - 1);
    // Protect RESET vector if this is page 0.
    if (pageAddress == INTVECT_PAGE_ADDRESS) {
        // Load existing RESET vector contents into buffer.
        pageBuffer[0] = pgm_read_word(INTVECT_PAGE_ADDRESS + 0);
        pageBuffer[1] = pgm_read_word(INTVECT_PAGE_ADDRESS + 1);
    }

    // Ignore any attempt to update boot section.
    if (pageAddress < BOOT_PAGE_ADDRESS) {
        boot_page_erase_safe (pageAddress);

        // Load temporary page buffer.
        uint8_t *bufferPtr = pageBuffer;
        uint16_t tempAddress = pageAddress;
        for (uint8_t i = 0; i < PAGE_SIZE; i += 2) {
            uint16_t tempWord = ((bufferPtr[1] << 8) | bufferPtr[0]);
            boot_page_fill_safe (tempAddress, tempWord); // Fill the temporary buffer with the given data
            tempAddress += 2;
            bufferPtr += 2;
        }
        // Write page from temporary buffer to the given location in flasm memory
        boot_page_write_safe (pageAddress);

        wdt_reset (); // Reset the watchdog timer
    }
}


/***********************************************************************/

/***********************************************************************/

void ProcessPageUpdate (void) {
    // Check the SPM is ready, abort if not.
    if ((SPMCSR & (1 << SELFPROGEN)) != 0) {
        AbortTWI ();

    } else {
        uint8_t pageAddressLo;
        uint8_t pageAddressHi;
        uint8_t *bufferPtr = pageBuffer;


        // Receive two-byte page address.
        if (SlaveReceiveByteAndACK (&pageAddressLo) ) {
        if (SlaveReceiveByteAndACK (&pageAddressHi) ) {
        // Receive page data.
            for (uint8_t i = 0; i < (PAGE_SIZE - 1); ++i) {
                if (SlaveReceiveByteAndACK (bufferPtr) != 0) {
                    ++bufferPtr;
                } else {
                    return;
                }
            }

            if (SlaveReceiveByteAndNACK (bufferPtr) ) {
        // Now program if everything went well.
            UpdatePage ((pageAddressHi << 8) | pageAddressLo);
            }
        }
        }
    }
}

/***********************************************************************/

/***********************************************************************/

void CleanupAndRunApplication (void) {
    wdt_disable(); // After Reset the WDT state does not change
    // Set up function pointer to address after last interrupt vector.
//  void (*FuncPtr) (void) = (void (*)(void)) ((LAST_INTVECT_ADDRESS + 2) / 2);
// FuncPtr ();

    asm volatile ("rjmp __vectors - 4"); // jump to application reset vector at end of flash

    for (;;); // Make sure function does not return to help compiler optimize

}

/***********************************************************************/

/***********************************************************************/

void ProcessPageErase (void) {
    uint16_t addr = 0;
    uint8_t i;

    for (i = 0; i < PAGE_SIZE; ++i) {
        pageBuffer[i] = 0xFF;
    }

    UpdatePage (addr);		// To restore reset vector
    addr += PAGE_SIZE;

    for (i = 0; i < (LAST_PAGE_NO_TO_BE_ERASED - 1); i++, addr += PAGE_SIZE) {
        addr &= ~(PAGE_SIZE - 1);

        if (addr < BOOT_PAGE_ADDRESS)
            // Erase each page one by one until the bootloader section
            boot_page_erase_safe (addr);
    }
}


/***********************************************************************/

/***********************************************************************/
void ProcessSlaveReceive (void) {
    uint8_t commandCode;

    if (SlaveReceiveByteAndACK (&commandCode) != 0) {
        // Process command byte.
        switch (commandCode) {
        case TWI_CMD_PAGEUPDATE:
            ProcessPageUpdate ();
            break;

        case TWI_CMD_EXECUTEAPP:
            // Read dummy byte and NACK, just to be nice to our TWI master.
            SlaveReceiveByteAndNACK (&commandCode);
            gtimeout = WDT_TIMEOUT_min; // Set WDT min for cleanup using reset
            wdt_enable(gtimeout);     // Apply the changes
            while(1); // Wait for WDT reset

        case TWI_CMD_BVERSION:
            SlaveReceiveByteAndNACK (&commandCode);
            state = 1;
            break;
        case TWI_CMD_ERASEFLASH:
            SlaveReceiveByteAndNACK (&commandCode);
            ProcessPageErase ();
            break;

        default:
            AbortTWI ();
        }
    }
}
/***********************************************************************/

/***********************************************************************/
void ReadAndProcessPacket (void) {
    // Enable ACK and clear pending interrupts.
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

    // Wait for activity.
    do { } while ((TWCR & (1 << TWINT)) == 0);

    wdt_reset ();

    // Check TWI status code for SLA+W or SLA+R.
    switch (TWSR) {
    case TWI_SLAW_RECEIVED:
        ProcessSlaveReceive ();
        break;

    case TWI_SLAR_RECEIVED:
        if (state == 0)
            ProcessSlaveTransmit (GetStatusCode () & STATUSMASK_SPMBUSY);
        else if (state == 1) {
            state = 0;
            ProcessSlaveTransmit (BVERSION);
        }
        break;

    default:
        AbortTWI ();
    }
}
/***********************************************************************/

/***********************************************************************/
void Start_Timer (void) {
    TIFR1   = TIFR1;  // Clear flags
    TCNT1H  = 0;
    TCNT1L  = 0;
    OCR1A   = 7813;   // 7812.5 (one sec at 8 MHz clock operation)
    TCCR1B  = _BV (CS12) + _BV (CS10) + _BV (WGM12);	// mode4: CTC,
    // Prescaller:1024
}

// 10 s delay code for allowing ARM9 linux to boot
#define HOST_BOOT_DELAY_SEC 10

/***********************************************************************/

/***********************************************************************/
void Host_Boot_Delay () {
//  time_lapse_sec = 0;

    Start_Timer ();
    do {
        if (TIFR1 & _BV (OCF1A)) {
            time_lapse_sec++;
            TIFR1 = TIFR1;
        }
    } while (time_lapse_sec < HOST_BOOT_DELAY_SEC);
    TCCR1B = 0;
    // stop the timer NOW

}

/***********************************************************************/

/***********************************************************************/
// Main Starts from here
int main (void) {


    if (MCUSR & _BV (PORF)) {	// Only in case of Power On Reset
        MCUSR = 0;


// Select the LED0 and LED1 interfacing port pins

        DDRB |= (_BV (1) + _BV (3));	// otp LED iterface
        PORTB &= ~(_BV (1) + _BV (3));     // ON the LEDs
        Host_Boot_Delay ();
        PORTB |= (_BV (1) + _BV (3));     // OFF the LEDs



    }

    if (IsBootPinLow ()) {
        InitTWI();
        gtimeout = WDT_TIMEOUT_8s;
        wdt_enable(gtimeout);

        while (1) {
            // Process the TWI Commands
            ReadAndProcessPacket ();
        }
    } else {
        CleanupAndRunApplication ();
    }
}
