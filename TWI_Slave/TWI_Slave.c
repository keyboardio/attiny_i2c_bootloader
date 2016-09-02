#include <ioavr.h>
#include "stdint.h"
#include <inavr.h>
#include "Common_Define.h"

#ifdef __USI__
    #include "USI_TWI_Slave.c"
    #include "USI_TWI_Slave.h"
#endif


//configuring LAST_INTVECT_ADDRESS as per device selected
/*****************************************************************************/
#ifdef __TWI__
  #if  defined(__ATMEGA48__) | \
       defined(__ATMEGA48A__) | defined(__ATMEGA48PA__)
       #define LAST_INTVECT_ADDRESS 		SPM_READY_vect  // The start of the application code
  #endif

  /*****************************************************************************/
  #if defined(__ATTINY48__) | defined(__ATTINY88__)
     #define LAST_INTVECT_ADDRESS 		TWI_vect// The start of the application code
  #endif
  /*****************************************************************************/
#endif



#ifdef __USI__
 /*****************************************************************************/
    #if defined(__ATTINY167__) 
       #define LAST_INTVECT_ADDRESS 	USI_START_vect// The start of the application code
    #endif

    #if defined(__ATTINY85__) 
       #define LAST_INTVECT_ADDRESS 	USI_OVF_vect// The start of the application code
    #endif
 /*****************************************************************************/

 /*****************************************************************************/
 /*****************************************************************************/
 /*****************************************************************************/
 /*****************************************************************************/
 /*****************************************************************************/
 /*****************************************************************************/
#endif



/*****************************************************************************/
/*****************************************************************************/
#ifdef __TWI__
#define TWI_SLAW_RECEIVED         	0x60	// Status slave address and write command received
#define TWI_SLAR_RECEIVED         	0xa8	// Status slave address and read command received
#define TWI_SLAVETX_NACK_RECEIVED 	0xc0	// Status slave transmit and no acknowledgement or last byte
#define TWI_SLAVERX_ACK_RETURNED  	0x80	// Status slave receive and acknowledgement returned
#define TWI_SLAVERX_NACK_RETURNED 	0x88	// Status slave receive and no acknowledgement or last byte

#endif

//
uint8_t state = 0;
// __no_init uint8_t pageBuffer[PAGE_SIZE];
uint16_t time_lapse_sec = 0; 
uint8_t volatile gtimeout;
uint8_t statusCode = 0;

/***********************************************************************/

/***********************************************************************/
#ifdef __TWI__
void InitTWI (void)
{
  
  DDRC &= ~((1 << PORTC5) | (1 << PORTC4)); // Set SCL and SDA as input
  PORTC &= ~((1 << PORTC5) | (1 << PORTC4)); // Set SCL and SDA low
  // Note: PORTC4 and PORT5 commonly used for tiny48. tiny88, mega48 TWI based devices
  
  TWAR = SLAVE_ADDRESS;
  TWCR = (1 << TWEN);		
  // Enable, but don't enable ACK until we are ready to receive packets.

}
#endif
/***********************************************************************/



/***********************************************************************/
//! Return non-zero if "Enter Bootloader" pin is held low externally.
uint8_t IsBootPinLow (void)
{
  // Make sure "Enter Bootloader" pin is input with internal pull-up.
#if defined(__ATTINY24__)   | defined(__ATTINY24A__) | \
    defined(__ATTINY44__)   | defined(__ATTINY44A__) | \
    defined(__ATTINY84__)   | defined(__ATTINY84A__) | \
    defined(__ATTINY2313__) | defined(__ATTINY2313A__) | \
    defined(__ATTINY4313__) | defined(__ATTINY4313A__) | \
    defined(__ATTINY43U__)  | \
    defined(__ATTINY87__) | defined(__ATTINY167__) | \
    defined(__ATTINY48__)   | defined(__ATTINY88__) | \
    defined(__ATMEGA48__) | \
    defined(__ATMEGA48A__) | defined(__ATMEGA48PA__)
    
     DDRB &= ~(1 << PORTB0);  //making port pin as input
    PORTB |= (1 << PORTB0);   
    // Let it settle.
  __delay_cycles (BOOT_SETTLE_DELAY);
  // Return non-zero if pin is low.
  return ((PINB & (1 << PORTB0)) == 0);
#endif
  
#if defined(__ATTINY261__)  | defined(__ATTINY261A__) | \
    defined(__ATTINY461__)  | defined(__ATTINY461A__) | \
    defined(__ATTINY861__)  | defined(__ATTINY861A__) | \
    defined(__ATTINY25__)   | defined(__ATTINY25V__) | \
    defined(__ATTINY45__)   | defined(__ATTINY45V__) | \
    defined(__ATTINY85__)   | defined(__ATTINY85V__)    
    
    DDRB &= ~(1 << PORTB4);   //making port pin as input
    PORTB |= (1 << PORTB4); 
    // Let it settle.
  __delay_cycles (BOOT_SETTLE_DELAY);
  // Return non-zero if pin is low.
  return ((PINB & (1 << PORTB4)) == 0);
#endif
}
/***********************************************************************/



/***********************************************************************/
uint8_t GetStatusCode (void)
{
  // Check if SPM operation is complete  
  if ((SPMCSR & (1 << SELFPROGEN)) != 0) 
    statusCode |= STATUSMASK_SPMBUSY;
 
  return statusCode;
}
/***********************************************************************/


/***********************************************************************/
#ifdef __TWI__
void AbortTWI (void)
{
  // Recover from error condition by releasing bus lines.
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
#endif
/***********************************************************************/


/***********************************************************************/
#ifdef __TWI__
void ProcessSlaveTransmit (uint8_t data)
{
  // Prepare data for transmission.
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);	// Send byte, NACK expected from master.
  // Wait for activity.
  do{} while ((TWCR & (1 << TWINT)) == 0);
  __watchdog_reset ();
  // Check TWI status code for SLAVETX_NACK.
  switch (TWSR)
  {
    case TWI_SLAVETX_NACK_RECEIVED:
      // End communication.
      TWCR = (1 << TWINT) | (1 << TWEN);
      break;

    default:
      AbortTWI ();
  }
}
#endif
/***********************************************************************/


/***********************************************************************/
#ifdef __TWI__
uint8_t SlaveReceiveByteAndACK (uint8_t * data)
{
   // Receive byte and return ACK.
  TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
  // Wait for activity.
  do{} while ((TWCR & (1 << TWINT)) == 0);
  __watchdog_reset ();
  // Check TWI status code for SLAVERX_ACK.
  switch (TWSR)
  {
    case TWI_SLAVERX_ACK_RETURNED:
      // Get byte and return non-zero for success.
      *data = TWDR;	  
      return 1;

    default:	
      AbortTWI ();
      return 0;
  }
}
#endif
/***********************************************************************/


/***********************************************************************/
#ifdef __TWI__
uint8_t SlaveReceiveByteAndNACK (uint8_t * data)
{
  // Receive byte and return NACK.
  TWCR = (1 << TWINT) | (1 << TWEN);
  // Wait for activity.
  do{} while ((TWCR & (1 << TWINT)) == 0);
  __watchdog_reset ();
  
  // Check TWI status code for SLAVERX_ACK.
  switch (TWSR)
  {
    case TWI_SLAVERX_NACK_RETURNED:
      // Get byte, end communication and return non-zero for success.
      *data = TWDR;
      TWCR = (1 << TWINT) | (1 << TWEN);
      return 1;

    default:
	// Reset the SLRBAN busy LED
      AbortTWI ();
      return 0;
  }
}
#endif
/***********************************************************************/


/***********************************************************************/
/*  Absolute Unconditional Page Erase  Check bounds elsewhere    */
void Erase_One_Page (uint16_t addr) 
{
  // Erase page at the given address
  _SPM_ERASE (addr);

  do{} while ((SPMCSR & (1 << SELFPROGEN)) != 0);
  __DataToR0ByteToSPMCR_SPM (0, ((1 << 4) | (1 << SELFPROGEN)));
  do{} while ((SPMCSR & (1 << SELFPROGEN)) != 0);

  
}
/***********************************************************************/



/***********************************************************************/
void UpdatePage (uint16_t pageAddress)
{
  // Mask out in-page address bits.
  pageAddress &= ~(PAGE_SIZE - 1);
  // Protect RESET vector if this is page 0.
  if (pageAddress == INTVECT_PAGE_ADDRESS)
  {
    // Load existing RESET vector contents into buffer.
    pageBuffer[0] =
    __load_program_memory ((void __flash *) (INTVECT_PAGE_ADDRESS + 0));
    pageBuffer[1] =
    __load_program_memory ((void __flash *) (INTVECT_PAGE_ADDRESS + 1));
  }

  // Ignore any attempt to update boot section.
  if (pageAddress < BOOT_PAGE_ADDRESS)
  {
    Erase_One_Page (pageAddress);

    // Load temporary page buffer.
    uint8_t *bufferPtr = pageBuffer;
    uint16_t tempAddress = pageAddress;
    for (uint8_t i = 0; i < PAGE_SIZE; i += 2)
    {
      uint16_t tempWord = ((bufferPtr[1] << 8) | bufferPtr[0]);
      _SPM_FILLTEMP (tempAddress, tempWord); // Fill the temporary buffer with the given data
      tempAddress += 2;
      bufferPtr += 2;
    }
    // Write page from temporary buffer to the given location in flasm memory
    _SPM_PAGEWRITE (pageAddress);

//SPMEN//SELFPROGEN
    
    do{} while ((SPMCSR & (1 << SELFPROGEN)) != 0); // Wait for the SPM operation to complete 
    __DataToR0ByteToSPMCR_SPM (0, ((1 << 4) | (1 << SELFPROGEN))); // Clear Temporary Buffer
    do{} while ((SPMCSR & (1 << SELFPROGEN)) != 0); // Wait for the SPM operation to complete

    
    __watchdog_reset (); // Reset the watchdog timer
  }
}


/***********************************************************************/

/***********************************************************************/

void ProcessPageUpdate (void)
{
  // Check the SPM is ready, abort if not.
  if ((SPMCSR & (1 << SELFPROGEN)) != 0)
  {
    #ifdef __TWI__
      AbortTWI ();
    #endif
      
      #ifdef __USI__
       USI_TWI_SLAVE_Abort ();
    #endif 
      
  }
  else
  {
    #ifdef __TWI__
    uint8_t error = 0;
    uint8_t pageAddressLo;
    uint8_t pageAddressHi;
    uint8_t *bufferPtr = pageBuffer;
    
    
    // Receive two-byte page address.
    error = SlaveReceiveByteAndACK (&pageAddressLo) == 0;
    if (!error)
    {
      error = SlaveReceiveByteAndACK (&pageAddressHi) == 0;
    }
    // Receive page data.
     if (!error)
    {
      for (uint8_t i = 0; i < (PAGE_SIZE - 1); ++i)
      {
	if (SlaveReceiveByteAndACK (bufferPtr) != 0)
	{
          ++bufferPtr;
	}
	else
	{
	  error = 1;
	  break;
	}
      }
    }

    if (!error)
    {
      error = SlaveReceiveByteAndNACK (bufferPtr) == 0;
    }
   
    
    // Now program if everything went well.
    if (!error)
    {
      UpdatePage ((pageAddressHi << 8) | pageAddressLo);
    }
     #endif
  }
}


/***********************************************************************/

/***********************************************************************/
void Disable_WatchDogTimer (void)
{
/*  
     Timed sequence
     Interrupts are already disabled else additional code may go in to avoid
     the servicing of interrupt in between the timed sequence
*/
  asm (" push r24         \n"	
       " push r0          \n" 
       " eor r0, r0       \n"	/*  r0 = 0 */
       " ldi r24, 0x18    \n"   /* WDE and WDCE bits set    */
       " wdr              \n"   /* Reset the watchdog timer */
       " sts 0x0060, r24  \n"	/* WDCE, WDE set in WDTCSR  */
       " sts 0x0054, r0   \n"	/* WDRF in MCUSR = 0        */
       " sts 0x0060, r0   \n"	/* WDE in WDTCSR = 0        */
       " pop r0           \n" 
       " pop r24            ");
}

/***********************************************************************/

/***********************************************************************/

void CleanupAndRunApplication (void)
{
  Disable_WatchDogTimer(); // After Reset the WDT state does not change
  void (*FuncPtr) (void) = (void (*)(void)) ((LAST_INTVECT_ADDRESS + 2) / 2);	// Set up function pointer to address after last interrupt vector. 
  FuncPtr ();
}

/***********************************************************************/

/***********************************************************************/

void ProcessPageErase (void)
{
  uint16_t addr = 0;
  uint8_t i;

  for (i = 0; i < PAGE_SIZE; ++i)
  {
    pageBuffer[i] = 0xFF;
  }

  UpdatePage (addr);		// To restore reset vector
  addr += PAGE_SIZE;

  for (i = 0; i < (LAST_PAGE_NO_TO_BE_ERASED - 1); i++, addr += PAGE_SIZE)
  {
    addr &= ~(PAGE_SIZE - 1);
    
    if (addr < BOOT_PAGE_ADDRESS)
	Erase_One_Page (addr); // Erase each page one by one until the bootloader section
  }
}

/***********************************************************************/

/***********************************************************************/

void Init_WatchDogTimer (void)
{
/*
	Timed sequence to initialize watchdog timer
	for the given mode set in gtimeout variable
	Cross calls during maximum optimization can
	cause more than 4 cycles delay between change
	enable for WDT and setting values
*/
  asm ("push r0           \n" 
       "push r24          \n" 
       "lds r0, gtimeout  \n"   /* load the given settings    */
       "ldi r24, 0x18     \n"	/* WDE, WCE                   */
       "or r0, r24        \n"   /* set WDE and WCE            */
       "wdr               \n"   /* reset the watchdog timer   */
       "sts 0x0060, r24   \n"   /* change enable              */
       "sts 0x0060, r0    \n"   /* make the change            */ 
       "pop r24           \n" 
       "pop r0            \n");
}
/*
// LO = 4C, HI = DE
const uint16_t index_calc[16] = {
  0, 52225, 55297, 5120, 61441, 15360, 10240, 58369,
  40961, 27648, 30720 , 46081, 20480, 39937, 34817, 17408 };
#define MODULO_TWO_SUM( arg1, arg2, arg3)   ( arg1 ^ arg2 ^ arg3 )
void ProcessCRCCheck(void)
{
  //
  //CRC_LO <<= ((1 << 2) -1);
  //CRC_HI += 0x5a;
  //
  uint16_t crc_sum=0;
  uint16_t j=0;
  unsigned char const __flash * i = ( unsigned char const __flash * ) 2; // Leave out the reset vector for CRC
  uint8_t data;
  while (i < (unsigned char const __flash *) BOOT_PAGE_ADDRESS )
  {
    data = __load_program_memory(i);
    j=index_calc[crc_sum & 0xF];
    crc_sum = (crc_sum >> 4) & 0x0FFF;
    crc_sum = MODULO_TWO_SUM(crc_sum, j, index_calc[data & 0xF]);
    
    j= index_calc[crc_sum & 0xF];
    crc_sum = (crc_sum >> 4) & 0x0FFF;
    crc_sum = MODULO_TWO_SUM( crc_sum, j, index_calc[(data >> 4) & 0xF]);
          
    i++;
  }
  
    CRC_HI = 0x00FF & (crc_sum >> 8);
    CRC_LO = crc_sum & 0x00FF;  
}
*/


/***********************************************************************/

/***********************************************************************/
#ifdef __TWI__
void ProcessSlaveReceive (void)
{
  uint8_t commandCode;
 
  if (SlaveReceiveByteAndACK (&commandCode) != 0)
  {
    // Process command byte.
    switch (commandCode)
    {
	case TWI_CMD_PAGEUPDATE:
	  ProcessPageUpdate ();
	break;

	case TWI_CMD_EXECUTEAPP:
	  // Read dummy byte and NACK, just to be nice to our TWI master.
	  SlaveReceiveByteAndNACK (&commandCode);
          gtimeout = WDT_TIMEOUT_min; // Set WDT min for cleanup using reset
          Init_WatchDogTimer();     // Apply the changes
        while(1); // Wait for WDT reset
          
	case TWI_CMD_AVERSION:
	  SlaveReceiveByteAndNACK (&commandCode);
	  state = 2;
	break;

	case TWI_CMD_BVERSION:
	  SlaveReceiveByteAndNACK (&commandCode);
	  state = 1;
	break;
        /*
        case TWI_CMD_CRCCHECK:
          SlaveReceiveByteAndNACK (&commandCode);
          ProcessCRCCheck();
          state = 3;
        break;
*/
	case TWI_CMD_ERASEFLASH:
	  SlaveReceiveByteAndNACK (&commandCode);
	  ProcessPageErase ();
	break;
        
        case TWI_CMD_GETERRCONDN: // except TWI failure because that is the medium
          SlaveReceiveByteAndNACK (&commandCode);
          state = 4;
        break;

	default:
	  AbortTWI ();
    }
  }
}
#endif
/***********************************************************************/

/***********************************************************************/
void Read_EEPROM_byte (uint8_t addr, unsigned char *cValue)
{
#ifdef __TWI__
  while (EECR & (1 << EEPE));	// Wait until EEWE becomes zero
  EEAR = addr;			// load eeprom adress
  EECR = (1 << EERE);		// read enable
  *cValue = EEDR;		// return eeprom data
#endif
  
#ifdef __USI__
  while (EECR & (1 << EEWE));	// Wait until EEWE becomes zero
  EEAR = addr;			// load eeprom adress
  EECR = (1 << EERE);		// read enable
  *cValue = EEDR;		// return eeprom data
#endif
}

/***********************************************************************/

/***********************************************************************/
#ifdef __TWI__
void ReadAndProcessPacket (void)
{
  unsigned char temp;
  
  // Enable ACK and clear pending interrupts.
  TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
  
  // Wait for activity.
  do{ } while ((TWCR & (1 << TWINT)) == 0);

  __watchdog_reset ();

  // Check TWI status code for SLA+W or SLA+R.
  switch (TWSR)
  {
    case TWI_SLAW_RECEIVED:
      ProcessSlaveReceive ();
    break;

    case TWI_SLAR_RECEIVED:
      if (state == 0)
	ProcessSlaveTransmit (GetStatusCode () & STATUSMASK_SPMBUSY);
      else if (state == 1)
      {
	state = 0;
	ProcessSlaveTransmit (BVERSION);
      }
      else if (state == 2)
      {
	state = 0;
	Read_EEPROM_byte (EEMEM_ADDR_AVERSION, &temp);
	ProcessSlaveTransmit (temp);
      }
     break;

    default:
      AbortTWI ();
  }
}
#endif
/***********************************************************************/

/***********************************************************************/
void Start_Timer (void)
{
    #ifdef __TWI__
      TIFR1   = TIFR1;  // Clear flags
      TCNT1H  = 0;
      TCNT1L  = 0;
      OCR1A   = 7813;   // 7812.5 (one sec at 8 MHz clock operation)
      TCCR1B  = _BV (CS12) + _BV (CS10) + _BV (WGM12);	// mode4: CTC,
                                                  // Prescaller:1024
    #endif
      
     #ifdef __USI__
      TIFR   = TIFR;  // Clear flags // 
      // TCNT1H  = 0;
      TCNT1  = 0;
      //OCR1A   = 7813;   // 7812.5 (one sec at 8 MHz clock operation)//
      OCR1A   = 255;   // 7812.5 (one sec at 8 MHz clock operation) // 
      TCCR0A  = _BV (WGM01);	// mode4: CTC
      TCCR0B  = _BV (CS02) + _BV (CS00);	// prescaller: 1024
      
    #endif

}

// 10 s delay code for allowing ARM9 linux to boot  
#ifdef __TWI__
#define HOST_BOOT_DELAY_SEC 10
#endif

#ifdef __USI__
#define HOST_BOOT_DELAY_SEC 500
#endif

/***********************************************************************/

/***********************************************************************/
void Host_Boot_Delay ()
{
//  time_lapse_sec = 0;

  Start_Timer ();
#ifdef __TWI__
  do{
    if (TIFR1 & _BV (OCF1A))
    {
      time_lapse_sec++;
      TIFR1 = TIFR1;
    }
  }
  while (time_lapse_sec < HOST_BOOT_DELAY_SEC);
  TCCR1B = 0;			
  // stop the timer NOW
#endif
  
  // check this one later
 #ifdef __USI__
 do{
    if (TIFR & _BV (OCF0A))
    {
      time_lapse_sec++;
      TIFR = TIFR;
        
    }
    
  }
  while (time_lapse_sec < HOST_BOOT_DELAY_SEC);
  TCCR0B = 0;	
  TCCR0A =0; 
  // stop the timer NOW 
#endif  
}

/***********************************************************************/

/***********************************************************************/
// Main Starts from here
void main (void)
{
  
     
  if (MCUSR & _BV (PORF))	// Only in case of Power On Reset
  {
    MCUSR = 0;


// Select the LED0 and LED1 interfacing port pins
#if defined(__ATTINY25__)   | defined(__ATTINY25V__) | \
    defined(__ATTINY45__)   | defined(__ATTINY45V__) | \
    defined(__ATTINY85__)   | defined(__ATTINY85V__) | \
    defined(__ATTINY2313__) | defined(__ATTINY2313A__) | \
    defined(__ATTINY4313__) | defined(__ATTINY4313A__) | \
    defined(__ATTINY261__)  | defined(__ATTINY261A__) | \
    defined(__ATTINY461__)  | defined(__ATTINY461A__) | \
    defined(__ATTINY861__)  | defined(__ATTINY861A__) | \
    defined(__ATTINY43U__)  | \
    defined(__ATTINY87__)   | \
    defined(__ATTINY167__) | \
    defined(__ATTINY48__) | defined(__ATTINY88__) | \
    defined(__ATMEGA48__) | \
    defined(__ATMEGA48A__) | defined(__ATMEGA48PA__)
      
    DDRB |= (_BV (1) + _BV (3));	// otp LED iterface
    PORTB &= ~(_BV (1) + _BV (3));     // ON the LEDs
    Host_Boot_Delay ();
    PORTB |= (_BV (1) + _BV (3));     // OFF the LEDs
    
    
      
#endif
    
    
#if defined(__ATTINY24__)   | defined(__ATTINY24A__) | \
    defined(__ATTINY44__)   | defined(__ATTINY44A__) | \
    defined(__ATTINY84__)   | defined(__ATTINY84A__)
      
    DDRB |= (_BV (1) + _BV (2));	// otp LED iterface
    PORTB &= ~(_BV (1) + _BV (2));     // ON the LEDs
    Host_Boot_Delay ();
    
    
    PORTB |= (_BV (1) + _BV (2));     // OFF the LEDs
    
    
    

#endif          
  }
  
  if (IsBootPinLow ())
  {     
      #ifdef __TWI__
          InitTWI();
      #endif
    
          
      #ifdef __USI__
           USI_TWI_SLAVE_Init( SLAVE_ADDRESS );
           //__enable_interrupt();
      #endif

    
    
    gtimeout = WDT_TIMEOUT_8s;
    Init_WatchDogTimer ();
    
    while (1)
    {
          #ifdef __TWI__
              // Process the TWI Commands
              ReadAndProcessPacket ();
           #endif
              
           #ifdef __USI__
              // Process the USI based TWI Commands
              USI_TWI_SLAVE_ReadAndProcessPacket ();
           #endif
    }
  }
  else
  {
    CleanupAndRunApplication ();
  }
}
