/*
 * Cyr-lcd7x4.h
 * Header file of library
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

#ifndef _CYR_LCD7X4_H
#define _CYR_LCD7X4_H

#include "Arduino.h"

typedef struct ConvCode {
  int unicode;
  char code;
} Codes;


class cyr_lcd7x4{
  private:
    boolean debug;
    byte* pinout;
    byte* dig_pinout;
    boolean* pinout_anode;
    boolean* dig_pinout_anode;

    // Коды для повторного вывода на дисплей
    byte* str_code;
    // Переменные таймеров
    unsigned long us;
    unsigned long us_show = 0;
    unsigned long us_prev = 0;
    // Минимальная яркость индикатора (при brightness == 0)
    const unsigned int min_brightness = 25000;
  public:
    // Яркость
    byte brightness;
    // Количество разрядов дисплея
    byte digs;

    cyr_lcd7x4(byte* po, byte* d_po, boolean* po_a, boolean* d_po_a, byte b = 255, boolean d = false);
    void print(char* str);
    void update();
};

#endif
