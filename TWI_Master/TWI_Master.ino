// this is an Arduino sketch to upload a firmware image to the TWI_Slave bootloader.
// The example firmware is the compiled version of the following C code, which
// flashes two LEDs on PB0 and PB1.
//
// // Main Starts from here
// int main (void) {
//       DDRB |= ((1 << PB0) | (1 << PB1)); // PB0 and PB1 are output
//       while (1) {
//         PORTB &= ~(1 << PB0);
//         PORTB |= (1 << PB1);
//         _delay_ms(400);
//         PORTB |= (1 << PB0);
//         PORTB &= ~(1 << PB1);
//         _delay_ms(200);
//     }
// }


#include <util/crc16.h>
#include "Arduino.h"
#include "Wire.h"

void setup() {
  Wire.begin();
}

#define page_size 64
#define frame_size 16
#define blank 0xff
#define pages 3
#define firmware_length 192
#define DELAY 1
const uint16_t offsets[pages] = {0, 64, 128};
const byte firmware[firmware_length] PROGMEM = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x13, 0xc0, 0x1a, 0xc0, 0x19, 0xc0, 0x18, 0xc0, 0x17, 0xc0, 0x16, 0xc0, 0x15, 0xc0, 0x14, 0xc0, 0x13, 0xc0, 0x12, 0xc0, 0x11, 0xc0, 0x10, 0xc0, 0xf, 0xc0, 0xe, 0xc0, 0xd, 0xc0, 0xc, 0xc0, 0xb, 0xc0, 0xa, 0xc0, 0x9, 0xc0, 0x8, 0xc0, 0x11, 0x24, 0x1f, 0xbe, 0xcf, 0xef, 0xd2, 0xe0, 0xde, 0xbf, 0xcd, 0xbf, 0x2, 0xd0, 0x1b, 0xc0, 0xe3, 0xcf, 0x84, 0xb1, 0x83, 0x60, 0x84, 0xb9, 0x28, 0x98, 0x29, 0x9a, 0x2f, 0xef, 0x83, 0xec, 0x99, 0xe0, 0x21, 0x50, 0x80, 0x40, 0x90, 0x40, 0xe1, 0xf7, 0x0, 0xc0, 0x0, 0x0, 0x28, 0x9a, 0x29, 0x98, 0x2f, 0xef, 0x81, 0xee, 0x94, 0xe0, 0x21, 0x50, 0x80, 0x40, 0x90, 0x40, 0xe1, 0xf7, 0x0, 0xc0, 0x0, 0x0, 0xe9, 0xcf, 0xf8, 0x94, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

byte written = 0;
byte addr = 0x50;

byte read_crc16(byte *version, uint16_t *crc16, uint16_t offset, uint16_t length) {
  byte result = 2;

  Wire.beginTransmission(addr);
  Wire.write(0x06); // get version and CRC16
  Wire.write(offset & 0xff); // addr (lo)
  Wire.write(offset >> 8); // addr (hi)
  Wire.write(length & 0xff); // len (lo)
  Wire.write(length >> 8); // len (hi)
  result = Wire.endTransmission();
  if (result != 0) {
      return result;
  }
  Wire.requestFrom(addr, (uint8_t) 3);
  Serial.print("Available bytes: ");
  Serial.print(Wire.available());
  Serial.print("\n");
  if (Wire.available() == 0) {
  }
  byte v = Wire.read();
  *version = v;
  if (Wire.available() == 0) {
    return 0xFF;
  }
  byte crc16_lo = Wire.read();
  if (Wire.available() == 0) {
    return 0xFF;
  }
  byte crc16_hi = Wire.read();
  while (Wire.available()) {
    byte c = Wire.read();
  }
  *crc16 = (crc16_hi << 8) | crc16_lo;
  return result;
}

void loop() {
  if (written != 0) {
    // we're done
    return;
  }

  Serial.print("Communicating\n");

  byte result = 2;
  while (result != 0) {
    Serial.print("Reading CRC16\n");

    byte version;
    uint16_t crc16;
    result = read_crc16(&version, &crc16, 0, firmware_length);

    Serial.print("result ");
    Serial.print(result);
    Serial.print("\n");

    if (result != 0) {
      _delay_ms(100);
      continue;
    }
    Serial.print("Version: ");
    Serial.print(version);
    Serial.print("\n\nExisting CRC16 of 0000-1FFF: ");
    Serial.print(crc16, HEX);
    Serial.print("\n");
  }


  Serial.print("Erasing\n");
  Wire.beginTransmission(addr);
  Wire.write(0x04); // erase user space
  result = Wire.endTransmission();
  Serial.print("result = ");
  Serial.print(result);
  Serial.print("\n");
  if (result != 0) {
    _delay_ms(1000);
    return;
  }

  byte o = 0;

  for (uint16_t i = 0; i < firmware_length; i += page_size) {
    Serial.print("Setting addr\n");
    Wire.beginTransmission(addr);
    Wire.write(0x1); // write page addr
    Wire.write(offsets[o] & 0xff); // write page addr
    Wire.write(offsets[o] >> 8);
    result = Wire.endTransmission();
    Serial.print("result = ");
    Serial.print(result);
    Serial.print("\n");
    _delay_ms(DELAY);
    // got something other than ACK. Start over.
    if (result != 0) {
      return;
    }

    // transmit each frame separately
    for (uint8_t frame = 0; frame < page_size / frame_size; frame++) {
      Wire.beginTransmission(addr);
      Wire.write(0x2); // continue page
      uint16_t crc16 = 0xffff;
      for (uint8_t j = frame * frame_size; j < (frame + 1) * frame_size; j++) {
        if (i + j < firmware_length) {
          uint8_t b = pgm_read_byte(&firmware[i + j]);
          Wire.write(b);
          crc16 = _crc16_update(crc16, b);
        } else {
          Wire.write(blank);
          crc16 = _crc16_update(crc16, blank);
        }
      }
      // write the CRC16, little end first
      Wire.write(crc16 & 0xff);
      Wire.write(crc16 >> 8);
      Wire.write(0x00); // dummy end byte
      result = Wire.endTransmission();
      Serial.print("got ");
      Serial.print(result);
      Serial.print(" for page ");
      Serial.print(offsets[o]);
      Serial.print(" frame ");
      Serial.print(frame);
      Serial.print("\n");
      // got something other than NACK. Start over.
      if (result != 3) {
        return;
      }
      delay(DELAY);
    }
    o++;
  }

  // verify firmware
  while (result != 0) {
    Serial.print("Reading CRC16\n");

    byte version;
    uint16_t crc16;
    // skip the first 4 bytes, are they were probably overwritten by the reset vector preservation
    result = read_crc16(&version, &crc16, offsets[0] + 4, firmware_length - 4);

    Serial.print("result ");
    Serial.print(result);
    Serial.print("\n");

    if (result != 0) {
      _delay_ms(100);
      continue;
    }
    Serial.print("Version: ");
    Serial.print(version);
    Serial.print("\n\nCRC CRC16 of ");
    Serial.print(offsets[0] + 4, HEX);
    Serial.print("-");
    Serial.print(offsets[0] + firmware_length, HEX);
    Serial.print(": ");
    Serial.print(crc16, HEX);
    Serial.print("\n");

    // calculate our own CRC16
    uint16_t check_crc16 = 0xffff;
    for (uint16_t i = 4; i < firmware_length; i++) {
      check_crc16 = _crc16_update(check_crc16, pgm_read_byte(&firmware[i]));
    }
    if (crc16 != check_crc16) {
      Serial.print("CRC does not match ours: ");
      Serial.print(check_crc16, HEX);
      Serial.print("\n");
      return;
    }
    Serial.print("CRC check: OK\n");
  }

  written = 1; // firmware successfully rewritten

  Serial.print("resetting\n");
  Wire.beginTransmission(addr);
  Wire.write(0x03); // execute app
  result = Wire.endTransmission();
  Serial.print("result ");
  Serial.print(result);
  Serial.print("\n");

  Serial.print("done\n");
}
