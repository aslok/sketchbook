/*
 * lcd_7seg_x_4_cyr_ds1307_fixed.ino
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
Sketch uses 12,582 bytes (87.8%) of program storage space. Maximum is 14,336 bytes.
Global variables use 558 bytes (54.5%) of dynamic memory, leaving 466 bytes for local variables. Maximum is 1,024 bytes.
 */
boolean debug = false;
boolean debug_display = false;
// Переменная для вывода отладки раз в секунду
unsigned long us_status = 0;

#include "lcd7x4.h"
lcd7x4* lcd;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

// For sprintf() function
char buffer[10];

byte brightness = 245;     // 0 - 255

byte    pinout[]           = {8,     9,     4,     6,     5,     7,     3,     2};
boolean pinout_anode[]     = {true,  true,  true,  true,  true,  true,  true,  true};
byte    dig_pinout[]       = {10,    11,    12,    13,    0};
boolean dig_pinout_anode[] = {true,  true,  true,  true};

unsigned long us;
unsigned long us_prev = 0;

// unixtime - таймстамп последней ручной установки , хранится по адресу #0
// adjust - количество секунд для автоматической коррекции, хранится по адресу #4
// last_adjust - таймстамп последней автоматической коррекции, хранится по адресу #8
unsigned long last_adjust = 0;
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
  //debug = true;
  //debug_display = true;

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  lcd = new lcd7x4(pinout, dig_pinout, pinout_anode, dig_pinout_anode, brightness);

  //if (debug || debug_display){
    Serial.begin(57600);
  //}

  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 8);
  last_adjust = *((unsigned long*) & read_arr);
  if (debug){
    Serial.print(F("Adjusted last time: "));
    Serial.println(last_adjust);
  }

  DateTime now = rtc.now();
  sprintf(buffer,
          "%02d.%02d.%04d %02d:%02d:%02d",
          now.day(), now.month(), now.year(),
          now.hour(), now.minute(), now.second());
  Serial.println(buffer);
}

void loop(){
  us = micros();

  if (us - us_prev > 1000000){
    us_prev = us;
    DateTime now = rtc.now();
    byte hour = now.hour() % 12;
    sprintf(buffer, "%d%s%02d", hour ? hour : 12, now.second() % 2 ? "." : "", now.minute());
    lcd->print(buffer);

    if (now.hour() == 12 && now.minute() == 30 && now.second() == 30 && now.unixtime() > last_adjust){
      byte read_arr[4];
      rtc.readnvram(read_arr, 4, 4);
      float adjust = *((float*) & read_arr);
      if (adjust){
        last_adjust = now.unixtime() + 1;
        byte* adjust_arr = (byte*) &last_adjust;
        byte write_arr[] = {
          adjust_arr[0],
          adjust_arr[1],
          adjust_arr[2],
          adjust_arr[3]
        };
        rtc.writenvram(8, write_arr, 4);

        float adjust_dec = adjust - (long) adjust;
        delay(1000 / (adjust_dec * -1));
        if (adjust < 0){
          adjust++;
        }

        DateTime new_time = DateTime(now.unixtime() + adjust);
        rtc.adjust(new_time);
      }
      if (debug){
        Serial.print(F("Adjusted time: "));
        Serial.println(adjust);
      }
    }
  }

  if (debug && mode == normal && us - us_status > 1000000){
    us_status = us;
    DateTime now = rtc.now();
    sprintf(buffer,
            "%02d.%02d.%04d %02d:%02d:%02d",
            now.day(), now.month(), now.year(),
            now.hour(), now.minute(), now.second());
    Serial.println(buffer);
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
        Serial.println(F("SET: Please enter date and time"));
      }else if (!strcmp(buffer_incom, "adjust")){
        mode = adjust;
        Serial.println(F("ADJUST: Please enter adjust"));
      }else if (!strcmp(buffer_incom, "unixtime")){
        mode = unixtime;
        Serial.println(F("UNIXTIME: Please enter unixtime"));
      }else if (!strcmp(buffer_incom, "read")){
        byte read_arr[8];
        rtc.readnvram(read_arr, 8, 0);
        unsigned long unixtime = *((unsigned long*) & read_arr);
        Serial.print(F("READ UNIXTIME: "));
        Serial.println(unixtime);
        float adjust = *((float*) & read_arr[4]);
        Serial.print(F("READ ADJUST: "));
        printFloat(adjust, 2);
        Serial.println();
      }else if (!strcmp(buffer_incom, "last")){
        byte write_arr[] = {0, 0, 0, 0};
        rtc.writenvram(8, write_arr, 4);
        Serial.println(F("LAST ADJUST: Set null done "));
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
      byte read_arr[8];
      rtc.readnvram(read_arr, 8, 0);
      // Последний раз устанавливалось правильное время:
      unsigned long old_unixtime = *((unsigned long*) & read_arr);
      // Учитываем существующую поправку (например -12.50)
      float adjust = *((float*) & read_arr[4]);
      // Прошло столько секунд с момента последней коррекции (например 88916):
      float time_elapsed = new_unixtime - old_unixtime;
      DateTime now = rtc.now();
      // Делим прошедшие секунды на разницу в секундах
      // Например, если час назад мы переводили часы на 5 сек, тогда 3600 / 5 = 720
      // Это значит часы отстают на 1 секунду за 720 секунд, запоминаем 720
      // Такая разница в секундах с последней установки времени (например -2):
      long time_diff = new_unixtime - now.unixtime();
      // Напрмер 86400 / (89349 / -2) + (-12.50)
      float new_adjust = (time_diff ? (3600.0 * 24 / (time_elapsed / time_diff)) : 0) + adjust;
      if (debug){
        Serial.print(F("SET: New time "));
        sprintf(buffer,
                "%02d.%02d.%04d %02d:%02d:%02d",
                new_time.day(), new_time.month(), new_time.year(),
                new_time.hour(), new_time.minute(), new_time.second());
        Serial.println(buffer);
        Serial.print(F("SET: Old adjust value "));
        printFloat(adjust, 2);
        Serial.println();
        Serial.print(F("SET: Elapsed time "));
        printFloat(time_elapsed, 2);
        Serial.println();
        Serial.print(F("SET: Old timestamp "));
        Serial.print(now.unixtime());
        Serial.println();
        Serial.print(F("SET: New timestamp "));
        Serial.println(new_unixtime);
        Serial.print(F("SET: Time diff "));
        Serial.println(time_diff);
        Serial.print(F("SET: Adjust "));
        printFloat(new_adjust, 2);
        Serial.println();
      }
      byte* unixtime_arr = (byte*) &new_unixtime;
      byte* adjust_arr = (byte*) &new_adjust;
      byte write_arr[] = {
        unixtime_arr[0],
        unixtime_arr[1],
        unixtime_arr[2],
        unixtime_arr[3],
        adjust_arr[0],
        adjust_arr[1],
        adjust_arr[2],
        adjust_arr[3]
      };
      rtc.adjust(new_time);
      rtc.writenvram(0, write_arr, 8);
      Serial.println(F("SET: Done"));
    }else if (mode == adjust){
      mode = 0;
      float new_adjust = atof(buffer_incom);
      byte* adjust_arr = (byte*) &new_adjust;
      byte write_arr[] = {
        adjust_arr[0],
        adjust_arr[1],
        adjust_arr[2],
        adjust_arr[3]
      };
      rtc.writenvram(4, write_arr, 4);
      Serial.print(F("ADJUST: Set "));
      printFloat(new_adjust, 2);
      Serial.println(F(" done "));
    }else if (mode == unixtime){
      mode = 0;
      unsigned long new_unixtime = atol(buffer_incom);
      byte* new_unixtime_arr = (byte*) &new_unixtime;
      byte write_arr[] = {
        new_unixtime_arr[0],
        new_unixtime_arr[1],
        new_unixtime_arr[2],
        new_unixtime_arr[3]
      };
      rtc.writenvram(0, write_arr, 4);
      Serial.print(F("UNIXTIME: Set "));
      Serial.print(new_unixtime);
      Serial.println(F(" done "));
    }
    buffer_incom_done = false;
  }

  lcd->update();
}

void printFloat(float value, int places) {
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;
  float d = 0.5;
  if (value < 0){
    d *= -1.0;
  }
  for (i = 0; i < places; i++){
    d /= 10.0;
  }
  tempfloat += d;
  if (value < 0){
    tempfloat *= -1.0;
  }
  while ((tens * 10.0) <= tempfloat){
    tens *= 10.0;
    tenscount += 1;
  }
  if (value < 0){
    Serial.print('-');
  }
  if (tenscount == 0){
    Serial.print(0, DEC);
  }
  for (i = 0; i < tenscount; i++){
    digit = (int) (tempfloat / tens);
    Serial.print(digit, DEC);
    tempfloat = tempfloat - ((float) digit * tens);
    tens /= 10.0;
  }
  if (places <= 0){
    return;
  }
  Serial.print('.');
  for (i = 0; i < places; i++){
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    Serial.print(digit, DEC);
    tempfloat = tempfloat - (float) digit;
  }
}
