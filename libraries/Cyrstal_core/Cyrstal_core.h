/*
 * Cyrstal_core.h
 * Заголовочный файл библиотеки Cyrstal_core
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

#ifndef Cyrstal_core_h
#define Cyrstal_core_h

#include "Arduino.h"

class Cyrstal_core {
  public:
    Cyrstal_core(byte width, byte height);

    virtual void lcd_setCursor(byte col, byte row)    = 0;
    virtual void lcd_write(char)                      = 0;
    virtual void lcd_createChar(byte cell, byte* cur) = 0;
    virtual void lcd_display()                        = 0;
    virtual void lcd_noDisplay()                      = 0;
    virtual void lcd_cursor()                         = 0;
    virtual void lcd_noCursor()                       = 0;
    virtual void lcd_blink()                          = 0;
    virtual void lcd_noBlink()                        = 0;
    virtual void lcd_clear()                          = 0;

    // Ф-ия печати строк переданных с помощью F()
    void print(const __FlashStringHelper*, int8_t = 127, byte = 255, byte = 255);
    // Ф-ия печати целых чисел
    void print(int chr, int8_t position = 127, byte go_ln = 255, byte space = 255);
    // Печать чисел с плавающей точкой
    void print(double, int8_t = 127, byte = 255, byte width = 5, byte prec = 2);
    // Печать отдельного символа
    void print(char, int8_t = 127, byte = 255, byte = 255);
    // Печать массива символов по указателю
    void print(char*, int8_t = 127, byte = 255, byte = 255);
    // Печать массива символов во внутренней кодировке
    void print_enc(char*, int8_t = 127, byte = 255, byte = 255);

    // Символы
    void power();
    void power(boolean);
    // Курсор _
    void cursor();
    void cursor(boolean);
    // Курсор []
    void blink();
    void blink(boolean);
    // Очистка экрана и установка курсора на ноль
    void clear();
    // Установка курсора в выбранные столбец-строка
    void go(byte col, byte row);
    // Установка курсора в выбранную позицию справа-налево сверху-вниз
    void go(byte = 32);

    // Инициализация массива строк разделенных символом \r переданного через F()
    void init(const __FlashStringHelper*);
    // Инициализация массива строк разделенных символом \r переданного через указатель
    void init(const char*);
    // Печать строки из ранее переданного массива по её номеру
    void printn(byte num, int8_t = 127, byte = 255, byte = 255);

    boolean bl = false;
    boolean pwr = true;
    boolean crsr = false;
    boolean blnk = false;

    byte   f;

  private:
    // Получаем массив символов, которые будут отображаться после вывода строки
    void get_next_scr(char* str, char* next_scr);
    // Печатаем строку сгенерированную для экрана по строке во внутренней кодировке
    void write_str_enc(char* str, char* lcd);
    // Конвертируем строку во внутреннюю кодировку
    void get_str_enc(char* str, char* result);
    // Создание кастомного символа по номеру в указанной ячейке
    void create_char(byte cell, byte num);

    char read_pgm(char*);
    byte read_pgm(byte*);
    void clear_arr(byte*, byte count);
    void clear_arr(char*, int8_t count = -1);

    // Печать строки из ранее переданного массива символов по её номеру
    void printn_str(byte num, int8_t, byte, byte);
    // Печать строки из ранее переданного внутри F() массива по её номеру
    void printn_flash(byte num, int8_t, byte, byte);

    char*  abc;
    char*  en;
    byte*  en_num;
    byte*  ru;
    byte*  ru_num;

    char*  s;
    char   scr[33];
    byte   scr_pos;
    byte   char_map[8];
};

#endif