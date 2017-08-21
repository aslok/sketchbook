/*
 * set_time.ino
 * Clock for arduino serial console
 * Clock with automatic daily time adjust
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
boolean debug = false;

#include "Wire.h"
#include "RTClib.h"
#include "aRTClib.h"
ds1307* rtc;

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
  unixtime,
  time
};
mode_type mode = normal;

void setup(){
  //debug = true;

  Serial.begin(57600);

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc = new ds1307();

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

    if (mode == normal){
      char buffer_tmp[21];
      sprintf(buffer_tmp,
              "%02d.%02d.%04d %02d:%02d:%02d",
              rtc->date.day(), rtc->date.month(), rtc->date.year(),
              rtc->date.hour(), rtc->date.minute(), rtc->date.second());
      Serial.println(buffer_tmp);
    }
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
        printFloat(rtc->adjust_read(), 4);
        Serial.println();
      }else if (!strcmp(buffer_incom, "last")){
        rtc->last_write(0);
        Serial.println(F("LAST ADJUST: 0"));
      }else if (!strcmp(buffer_incom, "time")){
        mode = time;
        Serial.println(F("TIME: Please enter"));
      }
    }else if (mode == set){
      mode = normal;
      char delim[] = " :.";
      byte day = atoi(strtok(buffer_incom, delim));
      byte month = atoi(strtok(NULL, delim));
      int year = atoi(strtok(NULL, delim));
      byte hour = atoi(strtok(NULL, delim));
      byte minute = atoi(strtok(NULL, delim));
      byte second = atoi(strtok(NULL, delim));
      // Правильное время:
      DateTime new_time = DateTime(year, month, day, hour, minute, second);
      // Прошло столько секунд с момента последней коррекции (например 89349):
      long time_elapsed = new_time.unixtime() - rtc->unixtime_read();
      // Такая разница в секундах с правильным временем (например -2):
      long time_diff = new_time.unixtime() - rtc->date.unixtime();
      // Новая поправка
      //     -12.9998                     86400           79755             -12                       0
      float new_adjust = (time_diff ? (3600.0 * 24 / (time_elapsed / (float) time_diff)) : 0) + rtc->adjust_read();
      if (debug){
        Serial.print(F("SET: Old adjust value "));
        printFloat(rtc->adjust_read(), 4);
        Serial.println();
        Serial.print(F("SET: Elapsed time "));
        Serial.println(time_elapsed);
        Serial.print(F("SET: Old timestamp "));
        Serial.println(rtc->date.unixtime());
        Serial.print(F("SET: New timestamp "));
        Serial.println(new_time.unixtime());
        Serial.print(F("SET: Time diff "));
        Serial.println(time_diff);
        Serial.print(F("SET: Adjust "));
        printFloat(new_adjust, 4);
        Serial.println();
      }
      rtc->unixtime_write(new_time.unixtime());
      rtc->adjust_write(new_adjust);
      rtc->set(new_time);
    }else if (mode == adjust){
      mode = normal;
      float new_adjust = atof(buffer_incom);
      rtc->adjust_write(new_adjust);
    }else if (mode == unixtime){
      mode = normal;
      unsigned long new_unixtime = atol(buffer_incom);
      rtc->unixtime_write(new_unixtime);
    }else if (mode == time){
      mode = normal;
      char delim[] = " :.";
      byte day = atoi(strtok(buffer_incom, delim));
      byte month = atoi(strtok(NULL, delim));
      int year = atoi(strtok(NULL, delim));
      byte hour = atoi(strtok(NULL, delim));
      byte minute = atoi(strtok(NULL, delim));
      byte second = atoi(strtok(NULL, delim));
      // Правильное время:
      DateTime new_time = DateTime(year, month, day, hour, minute, second);
      rtc->set(new_time);
    }
    buffer_incom_done = false;
  }
}

void printFloat(float value, int places){
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

