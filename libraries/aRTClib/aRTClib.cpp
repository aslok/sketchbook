/*
 * aRTClib.cpp
 * Основной файл библиотеки aRTClib
 *
 * created 19.08.2017
 * modified 19.08.2017
 * with Arduino 1.8.3 (tested on Arduino Nano)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#include "aRTClib.h"

// Конструктор
ds1307::ds1307(){
  rtc.begin();
  last_adjust = last_read();
  update();
}

DateTime ds1307::update(){
  date = rtc.now();
  adjust();
  return date;
}

void ds1307::adjust(){
  if (date.hour() != 12 || date.minute() != 30 || date.second() != 30 || date.unixtime() <= last_adjust){
    return;
  }
  float adjust = adjust_read();
  if (!adjust){
    return;
  }
  last_adjust = date.unixtime() + 1;
  last_write(last_adjust);
  float adjust_dec = adjust - (long) adjust;
  delay(1000 * abs(adjust_dec));
  if (adjust < 0){
    adjust++;
  }

  DateTime new_time = DateTime(date.unixtime() + adjust);
  set(new_time);
}

void ds1307::set(DateTime new_time){
  rtc.adjust(new_time);
  date = rtc.now();
}

// unixtime - таймстамп последней ручной установки , хранится по адресу #0
unsigned long ds1307::unixtime_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 0);
  return *((unsigned long*) & read_arr);
}

// adjust - количество секунд для автоматической коррекции, хранится по адресу #4
float ds1307::adjust_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 4);
  return *((float*) & read_arr);
}

// last_adjust - таймстамп последней автоматической коррекции, хранится по адресу #8
unsigned long ds1307::last_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 8);
  return *((unsigned long*) & read_arr);
}

void ds1307::unixtime_write(unsigned long value){
  byte* value_arr = (byte*) &value;
  byte write_arr[] = {
    value_arr[0],
    value_arr[1],
    value_arr[2],
    value_arr[3]
  };
  rtc.writenvram(0, write_arr, 4);
}

void ds1307::adjust_write(float value){
  byte* value_arr = (byte*) &value;
  byte write_arr[] = {
    value_arr[0],
    value_arr[1],
    value_arr[2],
    value_arr[3]
  };
  rtc.writenvram(4, write_arr, 4);
}

void ds1307::last_write(unsigned long value){
  byte* value_arr = (byte*) &value;
  byte write_arr[] = {
    value_arr[0],
    value_arr[1],
    value_arr[2],
    value_arr[3]
  };
  rtc.writenvram(8, write_arr, 4);
}
