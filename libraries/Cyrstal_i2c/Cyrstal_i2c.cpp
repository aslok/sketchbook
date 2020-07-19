/*
 * Cyrstal_i2c.cpp
 * Основной файл библиотеки Cyrstal_i2c
 * Класс содержит методы вывода текста кирилицей на китайские экраны PCF8574
 * через интерфейс i2c
 *
 * created 19.01.2015
 * modified 28.10.2017
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

#include "Cyrstal_i2c.h"

// Конструктор
Cyrstal_i2c::Cyrstal_i2c(byte address, byte width, byte height) :
Cyrstal_core(width, height){
#ifdef debug
  Serial.println("lcd = new LiquidCrystal_I2C");
#endif
  lcd = new LiquidCrystal_I2C(address, width, height);
#ifdef debug
  Serial.println("lcd->init()");
#endif
  lcd->init();
#ifdef debug
  Serial.println("clear();");
#endif
  clear();
}

// Подсветка экрана
void Cyrstal_i2c::backlight(boolean state){
  (bl = state) ? lcd->backlight() : lcd->noBacklight();
}

// Подсветка экрана
void Cyrstal_i2c::backlight(){
  (bl = !bl) ? lcd->backlight() : lcd->noBacklight();
}
