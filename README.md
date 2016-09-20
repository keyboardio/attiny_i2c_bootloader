# ATtiny88 I2C Bootloader

The goal of this project is to provide a safe bootloader that fits within about ~1 KB of flash for the ATtiny88 (and presumably ATtiny48) chips.
It was originally designed for the [keyboard.io project](http://keyboard.io).

The `TWI_Slave` directory contains such a bootloader, which expects to act as an I2C slave, with an I2C address of `0x58` (which can be altered by setting two of of the pins.

The `TWI_Mater` directory contains sample code for the I2C master that will flash some sample firmware to the ATtiny88.

## Building TWI_Slave

1. Install an avr toolchain (if you're on OS X, try [CrossPack for AVR®](https://www.obdev.at/products/crosspack/))
2. `cd TWI_Slave`
3. `make`

## Bootloader Protocol

The bootloader loads itself to `0x1C00` (in the upper kilobyte) of the flash, and has a protocol for updating the lower 7 KB of flash.
It always ensures that the first two bytes at `0x0000` (the reset vector) are preserved so that the bootloader is always the first thing executed.
If the bootloader receives no I2C commands after a few seconds, it jumps to `0x0038`, which is after the vector table and the standard AVR initialization (which has already been done).

The protocol it speaks supports a few different commands.
Each command starts with a single byte indicating the command to be run, and they have different formats.

All two-byte values (addresses, lengths, CRCs, etc.) are sent in little-endian format.

| Opcode | Description       | Format |
| ------ |-------------------| ------ |
| 0x01   | Set page address | 01 aa bb |
| 0x02   | Send frame (16 bytes) | 02 (... 16 bytes ... ) CRC16_lo CRC16_hi 00 |
| 0x03   | Reset (start application) | 03 |
| 0x04   | Erase flash | 04 |
| 0x06   | Get version and CRC16 | 06 a0 a1 l0 l1 |

To write new firmware, you must, for each page (64 bytes):

* Set the page address to write.
* 4 times: Send a frame (`0x02`), a frame of 16 bytes (one quarter of a page) is sent and prepared to be written.

After the 4th frame is sent, the page is written.
Each frame is accompanied by the CRC16 of that frame, which is checked.

All commands return ACK (0) on success for the last byte, except for send frame (op 2).
Send frame requires an extra 0 byte to be sent, and will return a NAK (3) on success.

The get version and CRC16 (0x06) can be used to retrieve the CRC16 of any address (`a0 a1`) and length (`l0 l1`) of flash.
It transmits back 3 bytes: the program version, and the CRC16 of the requested region.

The recommended update procedure is:

* Erase flash (4)
* For each page: set the address (1), send frame (2) four times
* Get version and CRC16 (6), starting at address `0x0004` (since the first four bytes are always preserved by the bootloader) to verify the entire firmware was written correctly
* Reset (3)
