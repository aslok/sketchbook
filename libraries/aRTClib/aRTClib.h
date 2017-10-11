/*
 * artclib.h
 * Header file of library
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
 */


#ifndef artclib_h
#define artclib_h

#include "Arduino.h"
#include "RTClib.h"

class ds1307{
  public:
    // Текущее значение даты
    DateTime date;

    // Конструктор
    ds1307();
    // Обновление текущего значения даты
    DateTime update();
    // Автоматическая коррекция
    void amendment_apply();
    // Поправка времени на верное и расчет коррекции
    void correct(DateTime);
    // Просто установка верной даты
    void adjust(DateTime);
    // Таймстамп последней ручной установки
    unsigned long corrected_read();
    // Количество секунд для автоматической коррекции
    float amendment_read();
    // Таймстамп последней автоматической коррекции
    unsigned long applied_read();
    void corrected_write(unsigned long);
    void amendment_write(float);
    void applied_write(unsigned long);
  private:
    RTC_DS1307 rtc;
    // Таймстамп последней автоматической коррекции
    unsigned long applied;
    // Количество секунд для автоматической коррекции
    float amendment;
};

#endif
