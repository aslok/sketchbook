/*
 * CyrI2c.h
 * Заголовочный файл библиотеки CyrI2c
 * Класс содержит методы вывода текста на экраны 1602
 * используется протокол I2C
 *
 * created 19.01.2015
 * modified 04.02.2015
 * with Arduino 1.5.8 (tested on Arduino Nano)
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

#ifndef CyrI2c_h
#define CyrI2c_h

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

class CyrI2c {
  public:
    CyrI2c(byte address, byte width, byte height);
    void print(const __FlashStringHelper*, int8_t = 127, byte = 255, byte = 255);
    void print(int chr, int8_t position = 127, byte go_ln = 255, byte space = 255);
    void print(double, int8_t = 127, byte = 255, byte width = 5, byte prec = 2);
    void print(char, int8_t = 127, byte = 255, byte = 255);
    void print(char*, int8_t = 127, byte = 255, byte = 255);
    void print_enc(char*, int8_t = 127, byte = 255, byte = 255);

    void backlight();
    void backlight(boolean);
    void power();
    void power(boolean);
    void cursor();
    void cursor(boolean);
    void blink();
    void blink(boolean);
    void clear();
    void go(byte col, byte row);
    void go(byte = 32);

    void init(const char*);
    void init(const __FlashStringHelper*);
    void printn(byte num, int8_t = 127, byte = 255, byte = 255);

    boolean bl = false;
    boolean pwr = true;
    boolean crsr = false;
    boolean blnk = false;


  private:
    void get_next_scr(char* str, char* next_scr);
    void write_str_enc(char* str, char* lcd);
    void get_str_enc(char* str, char* result);
    void create_char(byte cell, byte num);

    char read_pgm(char*);
    byte read_pgm(byte*);
    void clear_arr(byte*, byte count);
    void clear_arr(char*, int8_t count = -1);

    void printn_str(byte num, int8_t, byte, byte);
    void printn_flash(byte num, int8_t, byte, byte);

    LiquidCrystal_I2C* lcd;
    char*  abc;
    char*  en;
    byte*  en_num;
    byte*  ru;
    byte*  ru_num;

    char*  s;
    byte   f;
    char   scr[33];
    byte   scr_pos;
    byte   char_map[8];
};

#endif
