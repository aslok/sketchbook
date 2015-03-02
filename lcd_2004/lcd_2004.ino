/*
 * lcd_2004.ino
 * Демонстрация доступных для использования символов
 *
 * Copyright 2015 Vitaliy Fust <aslok.zp@gmail.com>
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

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte start = 32;
const byte finish = 255;
const byte scr_size = 80;
const word ms = 2000;
byte scr;

void setup(){
  // Инициализация дисплея
  lcd.begin(20, 4);
  lcd.clear();
}

void next_page(){
  delay(ms);
  lcd.clear();
  lcd.setCursor(0, 0);
  scr++;
}

void loop() {
  scr = 1;
  for (word chr_num = start; chr_num <= finish; chr_num++){
    if (chr_num == (scr * scr_size + start)){
      next_page();
    }
    lcd.write((char) chr_num);
  }
  next_page();
}
