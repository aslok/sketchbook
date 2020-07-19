/*
 * Cyrstal_i2c.h
 * Заголовочный файл библиотеки Cyrstal_i2c
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

#ifndef Cyrstal_i2c_h
#define Cyrstal_i2c_h

//#define debug

#include "LiquidCrystal_I2C.h"
#include "Cyrstal_core.h"

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

class Cyrstal_i2c : public Cyrstal_core{
  public:
    Cyrstal_i2c(byte address, byte width, byte height);

    LiquidCrystal_I2C* lcd;

    void backlight();
    void backlight(boolean);

    void lcd_setCursor(byte col, byte row){     lcd->setCursor(col, row);
#ifdef debug
      delay(200);
#endif
    };
    void lcd_write(char chr){                   lcd->printByte(chr);
#ifdef debug
      delay(200);
#endif
    };
    void lcd_createChar(byte cell, byte* cur){  lcd->createChar(cell, cur);
#ifdef debug
      delay(200);
#endif
    };
    void lcd_display(){                         lcd->display();             };
    void lcd_noDisplay(){                       lcd->noDisplay();           };
    void lcd_cursor(){                          lcd->cursor();              };
    void lcd_noCursor(){                        lcd->noCursor();            };
    void lcd_blink(){                           lcd->blink();               };
    void lcd_noBlink(){                         lcd->noBlink();             };
    void lcd_clear(){                           lcd->home();
#ifdef debug
      delay(200);
#endif
    };
};

#endif
