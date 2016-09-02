/*****************************************************************************
*
* Atmel Corporation
*
* File              : flash.h
* Compiler          : IAR C 3.10C Kickstart
* Revision          : $Revision: 2.0 $
* Date              : $Date: Tuesday, November 29, $
* Updated by        : $Author: raapeland $
*
* Support mail      : avr@atmel.com
*
* Target platform   : All AVRs with bootloader support
*
* AppNote           : AVR109 - Self-programming
*
* Description       : Flash operations for AVR109 Self-programming
****************************************************************************/


#define _GET_LOCK_BITS() __AddrToZByteToSPMCR_LPM( (void __flash *) 0x0001, 0x09 )
#define _GET_LOW_FUSES() __AddrToZByteToSPMCR_LPM( (void __flash *) 0x0000, 0x09 )
#define _GET_HIGH_FUSES() __AddrToZByteToSPMCR_LPM( (void __flash *) 0x0003, 0x09 )
#define _GET_EXTENDED_FUSES() __AddrToZByteToSPMCR_LPM( (void __flash *) 0x0002, 0x09 )
#define _SET_LOCK_BITS(data) __DataToR0ByteToSPMCR_SPM( data, 0x09 )
#define _ENABLE_RWW_SECTION() __DataToR0ByteToSPMCR_SPM( 0x00, 0x11 )

#define _WAIT_FOR_SPM() while( SPMCR_REG & (1<<SPMEN) );

#ifndef LARGE_MEMORY
  #define _LOAD_PROGRAM_MEMORY(addr) __load_program_memory( (const unsigned char __flash *) (addr) )
  #define _FILL_TEMP_WORD(addr,data) __AddrToZWordToR1R0ByteToSPMCR_SPM( (void __flash *) (addr), data, 0x01 )
  #define _PAGE_ERASE(addr) __AddrToZByteToSPMCR_SPM( (void __flash *) (addr), 0x03 )
  #define _PAGE_WRITE(addr) __AddrToZByteToSPMCR_SPM( (void __flash *) (addr), 0x05 )
#else
  #define _LOAD_PROGRAM_MEMORY(addr) __extended_load_program_memory( (const unsigned char __farflash *) (addr) )
  #define _FILL_TEMP_WORD(addr,data) __AddrToZ24WordToR1R0ByteToSPMCR_SPM( (void __farflash *) (addr), data, 0x01 )
  #define _PAGE_ERASE(addr) __AddrToZ24ByteToSPMCR_SPM( (void __farflash *) (addr), 0x03 )
  #define _PAGE_WRITE(addr) __AddrToZ24ByteToSPMCR_SPM( (void __farflash *) (addr), 0x05 )
#endif
