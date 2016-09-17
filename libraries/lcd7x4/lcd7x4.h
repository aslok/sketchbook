/*
 * lcd7x4.h
 * Header file of library
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

#ifndef _LCD7X4_H
#define _LCD7X4_H

#include "Arduino.h"

class lcd7x4{
  private:
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

    void init(byte* po, byte* d_po, boolean* po_a, boolean* d_po_a, byte b);
  public:
    // Яркость
    byte brightness;
    // Количество разрядов дисплея
    byte digs;

    lcd7x4(byte*, byte*, boolean*, boolean*, byte b = 255);
    lcd7x4(const byte*, const byte*, const boolean*, const boolean*, const byte = 255);
    void print(char* str);
    void update();
};

#endif
