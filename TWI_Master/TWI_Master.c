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
uint16_t offsets[pages] = {0, 64, 128};
byte firmware[firmware_length] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x13, 0xc0, 0x1a, 0xc0, 0x19, 0xc0, 0x18, 0xc0, 0x17, 0xc0, 0x16, 0xc0, 0x15, 0xc0, 0x14, 0xc0, 0x13, 0xc0, 0x12, 0xc0, 0x11, 0xc0, 0x10, 0xc0, 0xf, 0xc0, 0xe, 0xc0, 0xd, 0xc0, 0xc, 0xc0, 0xb, 0xc0, 0xa, 0xc0, 0x9, 0xc0, 0x8, 0xc0, 0x11, 0x24, 0x1f, 0xbe, 0xcf, 0xef, 0xd2, 0xe0, 0xde, 0xbf, 0xcd, 0xbf, 0x2, 0xd0, 0x1b, 0xc0, 0xe3, 0xcf, 0x84, 0xb1, 0x83, 0x60, 0x84, 0xb9, 0x28, 0x98, 0x29, 0x9a, 0x2f, 0xef, 0x83, 0xec, 0x99, 0xe0, 0x21, 0x50, 0x80, 0x40, 0x90, 0x40, 0xe1, 0xf7, 0x0, 0xc0, 0x0, 0x0, 0x28, 0x9a, 0x29, 0x98, 0x2f, 0xef, 0x81, 0xee, 0x94, 0xe0, 0x21, 0x50, 0x80, 0x40, 0x90, 0x40, 0xe1, 0xf7, 0x0, 0xc0, 0x0, 0x0, 0xe9, 0xcf, 0xf8, 0x94, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

byte written = 0;

void loop() {
  if (written != 0) {
    // we're done
    return;
  }

  Serial.print("Communicating\n");
  byte addr = 0x58;

  byte result = 2;
  while (result != 3) {
    Serial.print("Erasing\n");
    Wire.beginTransmission(addr);
    Wire.write(0x04); // erase user space
    Wire.write(0x00); // dummy end byte
    result = Wire.endTransmission();
    Serial.print("result = ");
    Serial.print(result);
    Serial.print("\n");

    _delay_ms(100);
  }

  byte o = 0;

  for (uint16_t i = 0; i < firmware_length; i += page_size) {
    Serial.print("Setting addr\n");
    Wire.beginTransmission(addr);
    Wire.write(0x1); // write page addr
    Wire.write(offsets[o] & 0xff); // write page addr
    Wire.write(offsets[o] >> 8);
    Wire.write(0x00); // dummy end byte
    result = Wire.endTransmission();
    Serial.print("result = ");
    Serial.print(result);
    Serial.print("\n");
    _delay_ms(DELAY);
    // got something other than NACK. Start over.
    if (result != 3) {
      return;
    }

    // transmit each frame separately
    for (uint8_t frame = 0; frame < page_size / frame_size; frame++) {
      Wire.beginTransmission(addr);
      Wire.write(0x2); // continue page
      uint16_t crc16 = 0xffff;
      for (uint8_t j = frame * frame_size; j < (frame + 1) * frame_size; j++) {
        if (i + j < firmware_length) {
          Wire.write(firmware[i + j]);
          crc16 = _crc16_update(crc16, firmware[i + j]);
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
  written = 1; // firmware successfully rewritten

  Serial.print("resetting\n");
  Wire.beginTransmission(addr);
  Wire.write(0x03); // execute app
  Wire.write(0x00); // dummy end byte
  result = Wire.endTransmission();
  Serial.print("result ");
  Serial.print(result);
  Serial.print("\n");

  Serial.print("done\n");
}
