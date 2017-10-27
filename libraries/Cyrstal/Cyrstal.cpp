/*
 * Cyrstal.cpp
 * Основной файл библиотеки Cyrstal
 * Класс содержит методы вывода текста кирилицей на китайские экраны PCF8574
 *
 * created 19.01.2015
 * modified 27.10.2017
 * with Arduino 1.8.3 (tested on Arduino Uno)
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

#include "Cyrstal.h"

// Конструктор
Cyrstal::Cyrstal(byte rs, byte enable, byte d0, byte d1, byte d2, byte d3, byte width, byte height) :
Cyrstal_core(width, height){
  lcd = new LiquidCrystal(rs, enable, d0, d1, d2, d3);
  lcd->begin(width, height);
  clear();
}
