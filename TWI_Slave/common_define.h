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


/*****************************************************************************/
/*****************************************************************************/
// Select the correct Bit name of to SELFPROGRAMming
#define SELFPROGEN     SELFPRGEN


uint8_t pageBuffer[PAGE_SIZE];
/*****************************************************************************/
/*****************************************************************************/

#define BVERSION 			0x01	// This bootloader revision identifier
