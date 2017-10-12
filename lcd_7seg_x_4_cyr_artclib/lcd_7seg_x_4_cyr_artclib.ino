/*
 * lcd_7seg_x_4_cyr_artclib.ino
 * Clock
 *
 * created 19.08.2017
 * modified 11.10.2017
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
Sketch uses 13,460 bytes (93.9%) of program storage space. Maximum is 14,336 bytes.
Global variables use 586 bytes (57.2%) of dynamic memory, leaving 438 bytes for local variables. Maximum is 1,024 bytes.
 */

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

// Также есть команды:
// read - чтение значений из памяти
// applied - сброс даты ежедневной поправки на 0
enum mode_type {
  // Вывод текущего времени
  normal,
  // Поправка времени на верное
  correct,
  // Ввод ежедневной поправки вручную
  amendment,
  // Ввод даты последней ручной поправки вручную
  corrected,
  // Ввод верной даты вручную
  adjust
};
mode_type mode = normal;

void setup(){
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

  if (us - us_prev > 1e6){
    us_prev = us;
    rtc->update();

    byte hour = rtc->date.hour() % 12;
    sprintf(buffer, "%d%s%02d", hour ? hour : 12, rtc->date.second() % 2 ? "." : "", rtc->date.minute());
    lcd->print(buffer);
    // Вывод текущего времени
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
        break;
      default:
        buffer_incom[buffer_incom_pos++] = incom_byte;
    }
  }

  if (buffer_incom_done){
    if (mode == normal) {
      // Поправка времени на верное
      if (!strcmp(buffer_incom, "correct")){
        mode = correct;
        Serial.println(F("CORRECT: Please enter"));
      // Ввод ежедневной поправки вручную
      }else if (!strcmp(buffer_incom, "amendment")){
        mode = amendment;
        Serial.println(F("AMENDMENT: Please enter"));
      // Ввод даты последней ручной поправки вручную
      }else if (!strcmp(buffer_incom, "corrected")){
        mode = corrected;
        Serial.println(F("CORRECTED: Please enter"));
      // Чтение значений из памяти
      }else if (!strcmp(buffer_incom, "read")){
        Serial.print(F("READ: Corrected "));
        Serial.println(rtc->corrected_read());
        Serial.print(F("READ: Amendment "));
        Serial.println(rtc->amendment_read(), 4);
        Serial.print(F("READ: Applied "));
        Serial.println(rtc->applied_read());
      // Сброс даты ежедневной поправки на 0
      }else if (!strcmp(buffer_incom, "applied")){
        rtc->applied_write(0);
        Serial.println(F("APPLIED: 0"));
      // Ввод верной даты вручную
      }else if (!strcmp(buffer_incom, "adjust")){
        mode = adjust;
        Serial.println(F("ADJUST: Please enter"));
      }
    // Поправка времени на верное
    }else if (mode == correct){
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
      rtc->correct(new_time);
    // Ввод ежедневной поправки вручную
    }else if (mode == amendment){
      mode = normal;
      float new_amendment = atof(buffer_incom);
      rtc->amendment_write(new_amendment);
    // Ввод даты последней ручной поправки вручную
    }else if (mode == corrected){
      mode = normal;
      unsigned long new_corrected = atol(buffer_incom);
      rtc->corrected_write(new_corrected);
    // Ввод верной даты вручную
    }else if (mode == adjust){
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
      rtc->adjust(new_time);
    }
    buffer_incom_done = false;
  }

  lcd->update();
}
