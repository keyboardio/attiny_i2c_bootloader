/*****************************************************************************/
#define TWI_CMD_PAGEUPDATE_ADDR         0x01	// TWI Command to program a flash page address to write
#define TWI_CMD_PAGEUPDATE_FRAME        0x02	// TWI Command to program the next frame of the page of flash
#define TWI_CMD_EXECUTEAPP            	0x03	// TWI Command to jump to the application program
#define TWI_CMD_ERASEFLASH              0x04	// TWI Command to erase the entire application section of flash memory
#define TWI_CMD_GETCRC16                0x06  // TWI Command to get application version and CRC16 of memory contents
#define TWI_CMD_GETERRCONDN             0x07    // TWI Command to get Error condition

/*****************************************************************************/


#define BOOT_SETTLE_DELAY         	100	// Debounce delay for the boot pin in MCU cycles
#define SLAVE_BASE_ADDRESS          0x50	// The base address identifier of this slave device on the TWI (I2C) bus
#define INTVECT_PAGE_ADDRESS      	0x000	// The location of the start of the interrupt vector table address


/***************************************************************/


// Page size selection for the controller with 8K flash
// The flash memory page size for these devices
#define PAGE_SIZE 64 // SPM_PAGESIZE is sometimes 32 for attiny88, which is incorrect
#define FRAME_SIZE 16 // how big of chunks of data we can write over TWI

// Page 112, the start of bootloader section
#define BOOT_PAGE_ADDRESS 0X1C00

#define FLASH_SIZE 8192

// 8KB of flash divided by pages of size 64 bytes
#define TOTAL_NO_OF_PAGES  (FLASH_SIZE / PAGE_SIZE)

// The number of pages being used for bootloader code
#define BOOTLOADER_PAGES          	(TOTAL_NO_OF_PAGES - BOOT_PAGE_ADDRESS/PAGE_SIZE)

// For bounds check during page write/erase operation to protect the bootloader code from being corrupted
#define LAST_PAGE_NO_TO_BE_ERASED 	(TOTAL_NO_OF_PAGES - BOOTLOADER_PAGES)


/*****************************************************************************/
/*****************************************************************************/
// Select the correct Bit name of to SELFPROGRAMming
#define SELFPROGEN     SELFPRGEN


uint8_t pageBuffer[PAGE_SIZE];
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/

#define STATUSMASK_SPMBUSY 		0x01	// The mask bit for SPM busy status code
#define STATUSMASK_BLSCERR              0x02    // The mask bit for attempt to override bootloader section
#define STATUSMASK_TWIABORT             0x04    // The mask bit for indicating TWI abort fn called
#define STATUSMASK_SLTR_BUSY            0x08    // The mask bit for slave transmit
#define STATUSMASK_SLRBAA_BUSY          0x10    // The mask bit for slave receive and ack
#define STATUSMASK_SLRBAN_BUSY          0x20    // The mask bit for slave receive and Nack
#define STATUSMASK_EEPROM_BUSY          0x40    // The mask bit for EEPROM busy
#define STATUSMASK_BOOTLOADER           0x80    // The mask bit for bootloader operations
/*****************************************************************************/
/*****************************************************************************/

#define BVERSION 			0x01	// This bootloader revision identifier
