/*
 * Cyrstal.h
 * Заголовочный файл библиотеки Cyrstal
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

#ifndef Cyrstal_h
#define Cyrstal_h

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"

class Cyrstal : public Cyrstal_core {
  public:
    Cyrstal(byte rs, byte enable, byte d0, byte d1, byte d2, byte d3, byte width, byte height);

    LiquidCrystal* lcd;

    void lcd_setCursor(byte col, byte row){     lcd->setCursor(col, row);   };
    void lcd_write(char chr){                   lcd->write(chr);            };
    void lcd_createChar(byte cell, byte* cur){  lcd->createChar(cell, cur); };
    void lcd_display(){                         lcd->display();             };
    void lcd_noDisplay(){                       lcd->noDisplay();           };
    void lcd_cursor(){                          lcd->cursor();              };
    void lcd_noCursor(){                        lcd->noCursor();            };
    void lcd_blink(){                           lcd->blink();               };
    void lcd_noBlink(){                         lcd->noBlink();             };
    void lcd_clear(){                           lcd->clear();               };
};

#endif
