/*
 * us_to_200k.ino
 * Example file of Cyr-lcd7x4 library
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
Sketch uses 4,700 bytes (32.8%) of program storage space. Maximum is 14,336 bytes.
Global variables use 51 bytes (5.0%) of dynamic memory, leaving 973 bytes for local variables. Maximum is 1,024 bytes.
 */

#include "lcd7x4.h"
lcd7x4* lcd;

byte brightness = 255;     // 0 - 255

byte    pinout[]           = {8,     9,     4,     6,     5,     7,     3,     2};
boolean pinout_anode[]     = {true,  true,  true,  true,  true,  true,  true,  true};
byte    dig_pinout[]       = {10,    11,    12,    13,    0};
boolean dig_pinout_anode[] = {true,  true,  true,  true};

unsigned long us_prev = 0;

void setup(){
  lcd = new lcd7x4(pinout, dig_pinout, pinout_anode, dig_pinout_anode, brightness);
}

void loop(){
  if (micros() - us_prev < 100){
    lcd->update();
    return;
  }
  char buffer[6];
  dtostrf(((micros() / 100000) % 2000) / 10.0, 0, 1, buffer);
  lcd->print(buffer);
  us_prev = micros();
}
