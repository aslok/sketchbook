/* This is the implementation of Cyruit-PCD8544 library which adds support
 * for cyrillic characters to Adafruit library for Arduino.
 * It's been originally developed by Vitaliy Fust.
 *
 * (C) 2015 Vitaliy Fust, aslok.zp@gmail.com
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 */

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"

//#noinclude
/*
Sketch uses 6 780 bytes (22%) of program storage space. Maximum is 30 720 bytes.
Global variables use 794 bytes (38%) of dynamic memory, leaving 1 254 bytes for local variables. Maximum is 2 048 bytes.
*/

// Это строка не нужна, если файл шрифта glcdfont.c в папке Adafruit-GFX
// был заменен на glcdfont.c.cp1251 (нужно переименовать) -
// экономия почти килобайт
#include "glcdfont_cp1251_min.c"
/*
Sketch uses 7 810 bytes (25%) of program storage space. Maximum is 30 720 bytes.
Global variables use 794 bytes (38%) of dynamic memory, leaving 1 254 bytes for local variables. Maximum is 2 048 bytes.
*/

const Letter PROGMEM g_letters[61] = {
  {0x82, 0x201A}, // SINGLE LOW-9 QUOTATION MARK
  {0x83, 0x0453}, // CYRILLIC SMALL LETTER GJE
  {0x84, 0x201E}, // DOUBLE LOW-9 QUOTATION MARK
  {0x85, 0x2026}, // HORIZONTAL ELLIPSIS
  {0x86, 0x2020}, // DAGGER
  {0x87, 0x2021}, // DOUBLE DAGGER
  {0x88, 0x20AC}, // EURO SIGN
  {0x89, 0x2030}, // PER MILLE SIGN
  {0x8A, 0x0409}, // CYRILLIC CAPITAL LETTER LJE
  {0x8B, 0x2039}, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
  {0x8C, 0x040A}, // CYRILLIC CAPITAL LETTER NJE
  {0x8D, 0x040C}, // CYRILLIC CAPITAL LETTER KJE
  {0x8E, 0x040B}, // CYRILLIC CAPITAL LETTER TSHE
  {0x8F, 0x040F}, // CYRILLIC CAPITAL LETTER DZHE
  {0x90, 0x0452}, // CYRILLIC SMALL LETTER DJE
  {0x91, 0x2018}, // LEFT SINGLE QUOTATION MARK
  {0x92, 0x2019}, // RIGHT SINGLE QUOTATION MARK
  {0x93, 0x201C}, // LEFT DOUBLE QUOTATION MARK
  {0x94, 0x201D}, // RIGHT DOUBLE QUOTATION MARK
  {0x95, 0x2022}, // BULLET
  {0x96, 0x2013}, // EN DASH
  {0x97, 0x2014}, // EM DASH
  {0x99, 0x2122}, // TRADE MARK SIGN
  {0x9A, 0x0459}, // CYRILLIC SMALL LETTER LJE
  {0x9B, 0x203A}, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
  {0x9C, 0x045A}, // CYRILLIC SMALL LETTER NJE
  {0x9D, 0x045C}, // CYRILLIC SMALL LETTER KJE
  {0x9E, 0x045B}, // CYRILLIC SMALL LETTER TSHE
  {0x9F, 0x045F}, // CYRILLIC SMALL LETTER DZHE
  {0xA0, 0x00A0}, // NO-BREAK SPACE
  {0xA1, 0x040E}, // CYRILLIC CAPITAL LETTER SHORT U
  {0xA2, 0x045E}, // CYRILLIC SMALL LETTER SHORT U
  {0xA3, 0x0408}, // CYRILLIC CAPITAL LETTER JE
  {0xA4, 0x00A4}, // CURRENCY SIGN
  {0xA5, 0x0490}, // CYRILLIC CAPITAL LETTER GHE WITH UPTURN
  {0xA6, 0x00A6}, // BROKEN BAR
  {0xA7, 0x00A7}, // SECTION SIGN
  {0xA8, 0x0401}, // CYRILLIC CAPITAL LETTER IO
  {0xA9, 0x00A9}, // COPYRIGHT SIGN
  {0xAA, 0x0404}, // CYRILLIC CAPITAL LETTER UKRAINIAN IE
  {0xAB, 0x00AB}, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
  {0xAC, 0x00AC}, // NOT SIGN
  {0xAD, 0x00AD}, // SOFT HYPHEN
  {0xAE, 0x00AE}, // REGISTERED SIGN
  {0xAF, 0x0407}, // CYRILLIC CAPITAL LETTER YI
  {0xB0, 0x00B0}, // DEGREE SIGN
  {0xB1, 0x00B1}, // PLUS-MINUS SIGN
  {0xB2, 0x0406}, // CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I
  {0xB3, 0x0456}, // CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
  {0xB4, 0x0491}, // CYRILLIC SMALL LETTER GHE WITH UPTURN
  {0xB5, 0x00B5}, // MICRO SIGN
  {0xB6, 0x00B6}, // PILCROW SIGN
  {0xB7, 0x00B7}, // MIDDLE DOT
  {0xB8, 0x0451}, // CYRILLIC SMALL LETTER IO
  {0xB9, 0x2116}, // NUMERO SIGN
  {0xBA, 0x0454}, // CYRILLIC SMALL LETTER UKRAINIAN IE
  {0xBB, 0x00BB}, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
  {0xBC, 0x0458}, // CYRILLIC SMALL LETTER JE
  {0xBD, 0x0405}, // CYRILLIC CAPITAL LETTER DZE
  {0xBE, 0x0455}, // CYRILLIC SMALL LETTER DZE
  {0xBF, 0x0457}  // CYRILLIC SMALL LETTER YI
};

Cyruit_PCD8544::Cyruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST):
  Adafruit_PCD8544(SCLK, DIN, DC, CS, RST){
}

Cyruit_PCD8544::Cyruit_PCD8544(int8_t SCLK, int8_t DIN, int8_t DC, int8_t RST):
  Adafruit_PCD8544(SCLK, DIN, DC, RST){
}

Cyruit_PCD8544::Cyruit_PCD8544(int8_t DC, int8_t CS, int8_t RST):
  Adafruit_PCD8544(DC, CS, RST){
}

#if defined(ARDUINO) && ARDUINO >= 100
size_t Cyruit_PCD8544::write(uint8_t c){
#else
void Cyruit_PCD8544::write(uint8_t c){
#endif
  static char prefix = 0;
  if (!prefix && c & 0x80){
    if ((~c) & 0x20){
      prefix = c;
    }
    #if ARDUINO >= 100
    return 0;
    #else
    return;
    #endif
  }else if (prefix){
    char suffix = c;
    int first5bit = prefix & 0x1F;
    first5bit <<= 6;
    int sec6bit = suffix & 0x3F;
    int unicode_char = first5bit + sec6bit;
    if ( unicode_char >= 0x410 && unicode_char <= 0x44F ) {
      c = (char)(unicode_char - 0x350);
    } else if (unicode_char >= 0x80 && unicode_char <= 0xFF) {
      c = (char)(unicode_char);
    } else if (unicode_char >= 0x402 && unicode_char <= 0x403) {
      c = (char)(unicode_char - 0x382);
    } else {
      int k = 0;
      for (; k < 61; k++) {
        if (unicode_char == pgm_read_word_near(&g_letters[k].unicode)) {
          c = pgm_read_byte_near(&g_letters[k].cp1251);
          break;
        }
      }
      if (k == 61){
        c = 127;
      }
    }
  }
  prefix = 0;

  if (c == '\n') {
    cursor_y += textsize*8;
    cursor_x  = 0;
  } else if (c == '\r') {
    // skip em
  } else {
    drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
    cursor_x += textsize*6;
    if (wrap && (cursor_x > (_width - textsize*6))) {
      cursor_y += textsize*8;
      cursor_x = 0;
    }
  }
  #if ARDUINO >= 100
  return 1;
  #endif
}

void Cyruit_PCD8544::drawChar(
  int16_t x, int16_t y, unsigned char c,
  uint16_t color, uint16_t bg, uint8_t size
){
  if((x >= _width)            || // Clip right
     (y >= _height)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5)
      line = 0x0;
  #if defined(CYRFONTMIN5X7_H)
    else if (c > 127)
      line = pgm_read_byte(cyrfont+((c-128)*5)+i);
  #endif
    else{
      Adafruit_PCD8544::drawChar(x, y, c, color, bg, size);
      return;
    }
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, color);
        else {  // big size
          fillRect(x+(i*size), y+(j*size), size, size, color);
        }
      } else if (bg != color) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, bg);
        else {  // big size
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}
