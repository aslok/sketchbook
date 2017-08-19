/*
 * lcd_7seg_x_4_cyr_artclib.ino
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
Sketch uses 12,644 bytes (88.2%) of program storage space. Maximum is 14,336 bytes.
Global variables use 555 bytes (54.2%) of dynamic memory, leaving 469 bytes for local variables. Maximum is 1,024 bytes.
 */
boolean debug = false;

#include "lcd7x4.h"
lcd7x4* lcd;

#include "Wire.h"
#include "RTClib.h"
#include "aRTClib.h"
ds1307* rtc;

char buffer[10];

byte brightness = 245;     // 0 - 255

byte    pinout[]           = {8,     9,     4,     6,     5,     7,     3,     2};
boolean pinout_anode[]     = {true,  true,  true,  true,  true,  true,  true,  true};
byte    dig_pinout[]       = {10,    11,    12,    13,    0};
boolean dig_pinout_anode[] = {true,  true,  true,  true};

unsigned long us;
unsigned long us_prev = 0;

// Переменные для ввода команд
char buffer_incom[21];
byte buffer_incom_pos = 0;
boolean buffer_incom_done = false;
// Mode: normal, set time, set adjust, set unixtime
enum mode_type {
  normal,
  set,
  adjust,
  unixtime
};

mode_type mode = normal;

void setup(){
  debug = true;

  Serial.begin(57600);

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc = new ds1307();
  lcd = new lcd7x4(pinout, dig_pinout, pinout_anode, dig_pinout_anode, brightness);

  sprintf(buffer_incom,
          "%02d.%02d.%04d %02d:%02d:%02d",
          rtc->date.day(), rtc->date.month(), rtc->date.year(),
          rtc->date.hour(), rtc->date.minute(), rtc->date.second());
  Serial.println(buffer_incom);
}

void loop(){
  us = micros();

  if (us - us_prev > 1000000){
    us_prev = us;
    rtc->update();

    byte hour = rtc->date.hour() % 12;
    sprintf(buffer, "%d%s%02d", hour ? hour : 12, rtc->date.second() % 2 ? "." : "", rtc->date.minute());
    lcd->print(buffer);
  }

  while (Serial.available() > 0){
    switch (char incom_byte = Serial.read()){
      case 10:
        break;
      case 13:
        buffer_incom[buffer_incom_pos] = '\0';
        buffer_incom_pos = 0;
        buffer_incom_done = true;
        if (debug){
          Serial.print(F("Received: "));
          Serial.println(buffer_incom);
        }
        break;
      default:
        buffer_incom[buffer_incom_pos++] = incom_byte;
    }
  }

  if (buffer_incom_done){
    if (mode == normal) {
      if (!strcmp(buffer_incom, "set")){
        mode = set;
        Serial.println(F("SET: Please enter"));
      }else if (!strcmp(buffer_incom, "adjust")){
        mode = adjust;
        Serial.println(F("ADJUST: Please enter"));
      }else if (!strcmp(buffer_incom, "unixtime")){
        mode = unixtime;
        Serial.println(F("UNIXTIME: Please enter"));
      }else if (!strcmp(buffer_incom, "read")){
        Serial.print(F("READ: Unixtime "));
        Serial.println(rtc->unixtime_read());
        Serial.print(F("READ: Adjust "));
        rtc->printFloat(rtc->adjust_read(), 2);
        Serial.println();
      }else if (!strcmp(buffer_incom, "last")){
        rtc->last_write(0);
        Serial.println(F("LAST ADJUST: 0"));
      }
    }else if (mode == set){
      mode = 0;
      char delim[] = " :.";
      byte day = atoi(strtok(buffer_incom, delim));
      byte month = atoi(strtok(NULL, delim));
      int year = atoi(strtok(NULL, delim));
      byte hour = atoi(strtok(NULL, delim));
      byte minute = atoi(strtok(NULL, delim));
      byte second = atoi(strtok(NULL, delim));
      // Правильное время:
      DateTime new_time = DateTime(year, month, day, hour, minute, second);
      unsigned long new_unixtime = new_time.unixtime();
      // Последний раз устанавливалось правильное время:
      unsigned long old_unixtime = rtc->unixtime_read();
      // Прошло столько секунд с момента последней коррекции (например 89349):
      unsigned long time_elapsed = new_unixtime - old_unixtime;
      // Учитываем существующую поправку (например -12.50)
      float adjust = rtc->adjust_read();
      // Такая разница в секундах с правильным временем (например -2):
      long time_diff = new_unixtime - rtc->date.unixtime();
      float new_adjust = (time_diff ? (3600.0 * 24 / (time_elapsed / time_diff)) : 0) + adjust;
      if (debug){
        Serial.print(F("SET: Old adjust value "));
        rtc->printFloat(adjust, 2);
        Serial.println();
        Serial.print(F("SET: Elapsed time "));
        Serial.println(time_elapsed);
        Serial.print(F("SET: Old timestamp "));
        Serial.println(rtc->date.unixtime());
        Serial.print(F("SET: New timestamp "));
        Serial.println(new_unixtime);
        Serial.print(F("SET: Time diff "));
        Serial.println(time_diff);
        Serial.print(F("SET: Adjust "));
        rtc->printFloat(new_adjust, 2);
        Serial.println();
      }
      rtc->unixtime_write(new_unixtime);
      rtc->adjust_write(new_adjust);
      rtc->set(new_time);
    }else if (mode == adjust){
      mode = 0;
      float new_adjust = atof(buffer_incom);
      rtc->adjust_write(new_adjust);
    }else if (mode == unixtime){
      mode = 0;
      unsigned long new_unixtime = atol(buffer_incom);
      rtc->unixtime_write(new_unixtime);
    }
    buffer_incom_done = false;
  }

  lcd->update();
}
