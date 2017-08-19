/*
 * set_time.ino
 * Clock
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

#include "Wire.h"
#include "RTClib.h"
#include "aRTClib.h"
ds1307* rtc;

// For sprintf() function
char buffer[10];

void setup(){
  Serial.begin(57600);

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc = new ds1307(true);

  sprintf(buffer,
          "%02d.%02d.%04d %02d:%02d:%02d",
          rtc->date.day(), rtc->date.month(), rtc->date.year(),
          rtc->date.hour(), rtc->date.minute(), rtc->date.second());
  Serial.println(buffer);
}

void loop(){
}