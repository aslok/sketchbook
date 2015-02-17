/*
 * Cyruit_PCD8544.h
 * This is header file for Cyruit-PCD8544 library which adds support
 * for cyrillic characters to Adafruit library for Arduino.
 * It's been originally developed by Vitaliy Fust.
 *
 * Copyright 2015 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#ifndef CYRUIT_PCD8544_H
#define CYRUIT_PCD8544_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
/* You'll need to write
 *    #include "SPI.h"
 *    #include "Adafruit_GFX.h"
 *    #include "Adafruit_PCD8544.h"
 * in your sketch.
 */

typedef struct ConvLetter {
  char cp1251;
  int  unicode;
} Letter;

class Cyruit_PCD8544: public Adafruit_PCD8544{
public:
  Cyruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST);
  Cyruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t RST);
  Cyruit_PCD8544(int8_t DC, int8_t CS, int8_t RST);

  virtual void
    drawChar(
      int16_t x, int16_t y, unsigned char c,
      uint16_t color, uint16_t bg, uint8_t size
    );

  #if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t data);
  #else
  virtual void write(uint8_t data);
  #endif
};

#endif // CYRUIT_PCD8544_H
