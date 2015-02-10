/*
created 10.02.2015
modified 10.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#ifndef Cyruit_h
#define Cyruit_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

typedef struct ConvLetter {
  char win1251;
  int  unicode;
} Letter;

class Cyruit {
  public:
    Cyruit(int8_t sclk, int8_t din, int8_t dc, int8_t cs, int8_t rst, byte contrast = 50);
    void
      print(const __FlashStringHelper*, int8_t = 127, byte = 255, byte = 255),
      print(int chr, int8_t position = 127, byte go_ln = 255, byte space = 255),
      print(double, int8_t = 127, byte = 255, byte width = 5, byte prec = 2),
      print(char, int8_t = 127, byte = 255, byte = 255),
      print(char*, int8_t = 127, byte = 255, byte = 255);

    void
      clear(),
      go(byte col, byte row),
      go(byte = 98);


  private:
    void
      write_str_enc(char*),
      write_bg();

    int utf8_to_cp1251(const char* utf8, char* windows1251, word n = 65535);
    char letter_cp1251(const Letter*);
    int  letter_utf8(const Letter*);

    Adafruit_PCD8544* lcd;
    byte scr_pos;
};

#endif
