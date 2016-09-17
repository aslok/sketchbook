/*
 * lcd7x4.cpp
 * Main file of library
 *
 * modified 17.09.2016
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

#include "lcd7x4.h"

//                          0          1          2          3          4
const byte PROGMEM num[] = {B11111100, B01100000, B11011010, B11110010, B01100110,
//                          5          6          7          8          9
                            B10110110, B10111110, B11100000, B11111110, B11110110};

lcd7x4::lcd7x4(const byte* po, const byte* d_po, const boolean* po_a, const boolean* d_po_a, const byte b){
  init((byte*) po, (byte*) d_po, (boolean*) po_a, (boolean*) d_po_a, (byte) b);
}

lcd7x4::lcd7x4(byte* po, byte* d_po, boolean* po_a, boolean* d_po_a, byte b){
  init(po, d_po, po_a, d_po_a, b);
}

void lcd7x4::init(byte* po, byte* d_po, boolean* po_a, boolean* d_po_a, byte b){
  pinout = po;
  dig_pinout = d_po;
  pinout_anode = po_a;
  dig_pinout_anode = d_po_a;
  brightness = b;
  for (byte f = 0; f < 8; f++){
    digitalWrite(pinout[f], !pinout_anode[f]);
    pinMode(pinout[f], OUTPUT);
  }
  for (digs = 0; dig_pinout[digs]; digs++);
  for (byte f = 0; f < digs; f++){
    digitalWrite(dig_pinout[f], !dig_pinout_anode[f]);
    pinMode(dig_pinout[f], OUTPUT);
  }
  str_code = new byte(digs);
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }
}

void lcd7x4::print(char* str){

  // Стираем старые коды для вывода
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }

  // Длина строки
  byte str_len;
  for (str_len = 0; str[str_len]; str_len++);

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
    // Если выводим цифру
    if (str[str_pos] >= '0' && str[str_pos] <= '9'){
      // Бинарный код цифры
      str_code[show_pos] = need_dot | pgm_read_byte_near(num + (str[str_pos] - '0'));
    }
    // Переходим к следующему разряду
    show_pos++;
    // Сбрасываем флаг точки
    need_dot = false;
  }
  update();
}

void lcd7x4::update(){
  if (brightness < 255){
    us = micros();
    if (us - us_show <= min_brightness - min_brightness / 256 * brightness){
      return;
    }
    us_show = us;
  }
  // Обходим коды символов для вывода
  for (int8_t show_pos = 0; show_pos < digs; show_pos++){
    // Если есть код символа для вывода (иначе пробел)
    if (!str_code[show_pos]){
      continue;
    }
    // Включаем вывод разряда (текущий разряд)
    digitalWrite(dig_pinout[show_pos], dig_pinout_anode[show_pos]);
    // Обходим сигменты разряда
    for (int8_t f = 7; f >= 0; f--){
      // Включаем необходимый сигмент
      digitalWrite(pinout[7 - f], !(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
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

