/*
 * Cyr-lcd7x4.cpp
 * Main file of library
 *
 * modified 16.09.2016
 * by Fust Vitaliy Vitaliy Fust <aslok.zp@gmail.com>
 * with Arduino 1.6.5 (tested on Arduino Pro Mini 168 5V)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "Cyr-lcd7x4.h"

//                          0          1          2          3          4
const byte PROGMEM num[] = {B11111100, B01100000, B11011010, B11110010, B01100110,
//                          5          6          7          8          9
                            B10110110, B10111110, B11100000, B11111110, B11110110};
const Codes PROGMEM en[] = {
  {'a', B11111010},
  {'b', B00111110},
  {'c', B00011010},
  {'d', B01111010},
  {'e', B11011110},
  {'g', B11110110},
  {'h', B00101110},
  {'i', B00100000},
  {'n', B00101000},
  {'ñ', B10101010},
  {'o', B00111010},
  {'q', B11100110},
  {'r', B00001010},
  {'t', B00011110},
  {'u', B00111000},
  {0, 0}
};
const Codes PROGMEM en_big[] = {
  {'A', B11101110},
  {'B', B11111110},
  {'C', B10011100},
  {'E', B10011110},
  {'F', B10001110},
  {'G', B10111110},
  {'H', B01101110},
  {'I', B01100000},
  {'J', B01111000},
  {'L', B00011100},
  {'O', B11111100},
  {'P', B11001110},
  {'S', B10110110},
  {'U', B01111100},
  {'Y', B01110110},
  {'Z', B11011010},
  {0, 0}
};
const Codes PROGMEM ru[] = {
  {'г', B00001010},
  {'д', B11101110},
  {'е', B11011110},
  {'и', B00111000},
  {'й', B10111000},
  {'о', B00111010},
  {'п', B00101010},
  {'с', B00011010},
  {0, 0}
};
const Codes PROGMEM ru_big[] = {
  {'А', B11101110},
  {'Б', B10111110},
  {'В', B11111110},
  {'Г', B10001100},
  {'Е', B10011110},
  {'Н', B01101110},
  {'О', B11111100},
  {'П', B11101100},
  {'Р', B11001110},
  {'С', B10011100},
  {'У', B01110110},
  {'Ч', B01100110},
  {'Ь', B00111110},
  {'Э', B11110010},
  {0, 0}
};

cyr_lcd7x4::cyr_lcd7x4(byte* po, byte* d_po, boolean* po_a, boolean* d_po_a, byte b, boolean d){
  pinout = po;
  dig_pinout = d_po;
  pinout_anode = po_a;
  dig_pinout_anode = d_po_a;
  brightness = b;
  debug = d;
  for (byte f = 0; f < 8; f++){
    digitalWrite(pinout[f], !pinout_anode[f]);
    pinMode(pinout[f], OUTPUT);
  }
  for (digs = 0; dig_pinout[digs]; digs++);
  if (debug){
    Serial.print(F("digs = "));
    Serial.println(digs);
  }
  for (byte f = 0; f < digs; f++){
    digitalWrite(dig_pinout[f], !dig_pinout_anode[f]);
    pinMode(dig_pinout[f], OUTPUT);
  }
  str_code = new byte(digs);
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }
}

void cyr_lcd7x4::print(char* str){
  if (debug){
    Serial.print(F("str = "));
    Serial.println(str);
  }

  // Стираем старые коды для вывода
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }

  // Длина строки
  byte str_len;
  for (str_len = 0; str[str_len]; str_len++);
  if (debug){
    Serial.print(F("str_len = "));
    Serial.println(str_len);
  }

  // Пустая строка - выводить нечего
  if (!str_len){
    return;
  }

  // Флаг наличия точки
  boolean need_dot = false;
  // Обходим конец строки который помещается
  for (int8_t str_pos = str_len - 1, show_pos = 0; str_pos >= 0 && show_pos < digs; str_pos--){
    // Запоминаем точку до следующего раза
    if (str[str_pos] == '.'){
      need_dot = true;
      continue;
    }
    if (debug){
      Serial.print(F("str["));
      Serial.print(str_pos);
      Serial.print(F("] = "));
      Serial.print(str[str_pos]);
      Serial.print(F(" ("));
      Serial.print(str[str_pos], DEC);
      Serial.print(F(") > "));
      Serial.println(show_pos);
    }
    // Если выводим цифру
    if (str[str_pos] >= '0' && str[str_pos] <= '9'){
      if (debug){
        Serial.println(F("Is number"));
      }
      // Бинарный код цифры
      str_code[show_pos] = need_dot | pgm_read_byte_near(num + (str[str_pos] - '0'));
    }
    // Переходим к следующему разряду
    show_pos++;
    // Сбрасываем флаг точки
    need_dot = false;
  }
  update();
  //while (debug);
}

void cyr_lcd7x4::update(){
  if (brightness < 255){
    us = micros();
    if (us - us_show <= min_brightness - min_brightness / 256 * brightness){
      return;
    }
    us_show = us;
  }
  // Обходим коды символов для вывода
  for (int8_t show_pos = 0; show_pos < digs; show_pos++){
    if (debug){
      Serial.print(F("str_code["));
      Serial.print(show_pos);
      Serial.print(F("] = "));
      Serial.println(str_code[show_pos], BIN);
    }
    // Если есть код символа для вывода (иначе пробел)
    if (!str_code[show_pos]){
      continue;
    }
    if (debug){
      Serial.print(F("digitalWrite("));
      Serial.print(dig_pinout[show_pos]);
      Serial.print(F(", "));
      Serial.print(dig_pinout_anode[show_pos]);
      Serial.println(F(");"));
    }
    // Включаем вывод разряда (текущий разряд)
    digitalWrite(dig_pinout[show_pos], dig_pinout_anode[show_pos]);
    // Обходим сигменты разряда
    for (int8_t f = 7; f >= 0; f--){
      if (debug){
        Serial.print(F("digitalWrite("));
        Serial.print(pinout[7 - f]);
        Serial.print(F(", "));
        Serial.print(!(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
        Serial.println(F(");"));
      }
      // Включаем необходимый сигмент
      digitalWrite(pinout[7 - f], !(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
    }
    if (debug){
      delay(500);
    }
    // Выключаем сигменты
    for (byte f = 0; f < 8; f++){
      digitalWrite(pinout[f], !pinout_anode[f]);
      pinMode(pinout[f], OUTPUT);
    }
    // Выключаем разряд
    digitalWrite(dig_pinout[show_pos], !dig_pinout_anode[show_pos]);
    // Переходим к следующему разряду
  }
}

