/*
created 10.02.2015
modified 16.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#ifndef Cyruit_h
#define Cyruit_h

#include "Arduino.h"
#include "Cyruit_PCD8544.h"

enum display_type{
  Cyruit_PCD8544_lib
};

const int8_t
  def_position = 127;
const byte
  max_num_length = 16,
  def_go_ln = 255,
  def_space = 255,
  def_go = 255,
  def_float_width = 5,
  def_float_prec = 2;

class Cyruit {
  public:
    Cyruit(void*, display_type, byte width, byte height, byte f_width, byte f_height);
    Cyruit(Cyruit_PCD8544*, byte width, byte height, byte f_width, byte f_height);
    void
      print(const __FlashStringHelper*,
        int8_t position = def_position, byte go_ln = def_go_ln, byte space = def_space),
      print(int chr,
        int8_t = def_position, byte = def_go_ln, byte = def_space),
      print(double,
        int8_t = def_position, byte = def_go_ln,
        byte width = def_float_width, byte prec = def_float_prec),
      print(word utf8_num,
        int8_t = def_position, byte = def_go_ln,byte = def_space),
      print(char,
        int8_t = def_position, byte = def_go_ln,byte = def_space),
      print(char,
        word count),
      print(char*,
        int8_t = def_position, byte = def_go_ln, byte = def_space);
    void
      clear(),
      go(byte col, byte row),
      go(byte = def_go);
    word utf8_strlen(char*);


  private:
    void print_lcd(char*);
    byte
      font_width,
      font_height,
      scr_width,
      scr_height,
      scr_length,
      scr_pos;
    void* lcd;
    display_type lcd_type;
};

#endif
