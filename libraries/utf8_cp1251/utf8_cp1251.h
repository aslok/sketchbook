/*
modified 09.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#ifndef _UTF8_CP1251_H
#define _UTF8_CP1251_H

#include "Arduino.h"

typedef struct ConvLetter {
  char win1251;
  int  unicode;
} Letter;

int utf8_to_cp1251(const char* utf8, char* windows1251, int n);
int utf8_to_cp1251(const __FlashStringHelper* utf8_ptr, char* windows1251, int n);

#endif
