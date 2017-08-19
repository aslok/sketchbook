/*
 * artclib.h
 * Header file of library
 *
 * modified 19.08.2017
 * by Fust Vitaliy Vitaliy Fust <aslok.zp@gmail.com>
 * with Arduino 1.8.3 (tested on Arduino Pro Mini 168 5V)
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


#ifndef artclib_h
#define artclib_h

#include "Arduino.h"
#include "RTClib.h"

class ds1307{
  public:
    DateTime date;

    ds1307();
    DateTime update();
    void adjust();
    void set(DateTime);
    unsigned long unixtime_read();
    float adjust_read();
    unsigned long last_read();
    void unixtime_write(unsigned long);
    void adjust_write(float);
    void last_write(unsigned long);

    void printFloat(float value, int places);
  private:
    RTC_DS1307 rtc;
    unsigned long last_adjust;
};

#endif
