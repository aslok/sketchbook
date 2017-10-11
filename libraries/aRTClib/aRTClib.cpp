/*
 * aRTClib.cpp
 * Основной файл библиотеки aRTClib
 *
 * created 19.08.2017
 * modified 11.10.2017
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
  // Таймстамп последней автоматической коррекции
  applied = applied_read();
  // Количество секунд для автоматической коррекции
  amendment = amendment_read();
  update();
}

// Обновление значения текущей даты
DateTime ds1307::update(){
  unsigned long unixtime = rtc.now().unixtime();
  unsigned long adjusted_time = unixtime + (long) amendment * (long) (unixtime - applied) / 86400L;
  date = DateTime(adjusted_time);

  // Запуск автоматической коррекции в 12:30:30
  if (date.hour() == 12 && date.minute() == 30 && date.second() == 30 && date.unixtime() > applied){
    amendment_apply();
  }
  return date;
}

// Автоматическая коррекция
void ds1307::amendment_apply(){
  if (!amendment){
    return;
  }
  unsigned long elapsed = date.unixtime() - corrected_read();
  float amendment_tmp = elapsed < 86400L ?
                          amendment * elapsed / 86400L :
                          amendment;
  applied_write(date.unixtime() + 1);
  delay(1000 * abs(amendment_tmp - (long) amendment_tmp));
  if (amendment_tmp < 0){
    amendment_tmp++;
  }

  DateTime new_time = DateTime(date.unixtime() + amendment_tmp);
  adjust(new_time);
}

// Поправка времени на верное и расчет коррекции
void ds1307::correct(DateTime new_time){
  // Прошло столько секунд с момента последней коррекции (например 79755):
  long time_elapsed = new_time.unixtime() - corrected_read();
  // Такая разница в секундах с правильным временем (например -12):
  long time_diff = new_time.unixtime() - date.unixtime();
  // Новая поправка
  //     -12.9998                     86400           79755             -12                       0
  float new_amendment = (time_diff ? (3600.0 * 24 / (time_elapsed / (float) time_diff)) : 0) + amendment_read();
  corrected_write(new_time.unixtime());
  applied_write(new_time.unixtime());
  amendment_write(new_amendment);
  adjust(new_time);
}

// Просто установка верной даты
void ds1307::adjust(DateTime new_time){
  rtc.adjust(new_time);
  date = rtc.now();
}

// corrected - читаем таймстамп последней ручной установки, хранится по адресу #0
unsigned long ds1307::corrected_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 0);
  return *(unsigned long*) &read_arr;
}

// amendment - читаем количество секунд для автоматической коррекции, хранится по адресу #4
float ds1307::amendment_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 4);
  return *(float*) &read_arr;
}

// applied - читаем таймстамп последней автоматической коррекции, хранится по адресу #8
unsigned long ds1307::applied_read(){
  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 8);
  return *(unsigned long*) &read_arr;
}

// corrected - пишем таймстамп последней ручной установки , хранится по адресу #0
void ds1307::corrected_write(unsigned long value){
  rtc.writenvram(0, (byte*) &value, 4);
}

// amendment - пишем количество секунд для автоматической коррекции, хранится по адресу #4
void ds1307::amendment_write(float value){
  amendment = value;
  rtc.writenvram(4, (byte*) &value, 4);
}

// applied - пишем таймстамп последней автоматической коррекции, хранится по адресу #8
void ds1307::applied_write(unsigned long value){
  applied = value;
  rtc.writenvram(8, (byte*) &value, 4);
}
