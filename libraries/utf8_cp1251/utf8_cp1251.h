/*
 * utf8_cp1251.h
 * Header file of UTF-8 to CP1251 library
 *
 * modified 09.02.2015
 * by Fust Vitaliy Vitaliy Fust <aslok.zp@gmail.com>
 * with Arduino 1.5.8 (tested on Arduino Nano)
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
