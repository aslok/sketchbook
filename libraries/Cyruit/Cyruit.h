/*
 * Cyruit.h
 * Заголовочный файл библиотеки Cyruit
 * Класс содержит методы вывода текста на экраны
 *
 * created 10.02.2015
 * modified 17.02.2015
 * with Arduino 1.5.8 (tested on Arduino Nano)
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

#ifndef Cyruit_h
#define Cyruit_h

#include "Arduino.h"
#include "Cyruit_PCD8544.h"

// Поддерживаемые типы экранов
enum display_type{
  Cyruit_PCD8544_lib
};

// Типы массивов строк
enum string_type{
  NoString,
  FlashStringHelper,
  ASCIZString
};

// Магические числа
const int8_t
  def_position = 127;
const byte
  max_num_length = 16,
  def_go_ln = 255,
  def_space = 255,
  def_go = 255,
// Стандартные размеры дробей - общая длина и длина дробной части, 00.00
  def_float_width = 5,
  def_float_prec = 2;

class Cyruit {
  public:
    // Конструктор
    Cyruit(void*, display_type, byte width, byte height, byte f_width, byte f_height);
    Cyruit(Cyruit_PCD8544*, byte width, byte height, byte f_width, byte f_height);
    void
    // Ф-ия печати строк переданных с помощью F()
      print(const __FlashStringHelper*,
        int8_t position = def_position, byte go_ln = def_go_ln, byte space = def_space),
    // Ф-ия печати целых чисел
      print(int chr,
        int8_t = def_position, byte = def_go_ln, byte = def_space),
    // Печать чисел с плавающей точкой
      print(double,
        int8_t = def_position, byte = def_go_ln,
        byte width = def_float_width, byte prec = def_float_prec),
    // Печать отдельного utf символа по номеру
      print(word utf8_num,
        int8_t = def_position, byte = def_go_ln,byte = def_space),
    // Печать отдельного символа несколько раз
      print(char,
        int count),
    // Печать массива символов по указателю
      print(char*,
        int8_t = def_position, byte = def_go_ln, byte = def_space);
    inline void
    // Печать отдельного символа
      print(char,
        int8_t = def_position, byte = def_go_ln,byte = def_space),
    // Печать отдельного символа несколько раз
      print(char,
        word count);
    void
    // Очистка экрана и установка курсора на ноль
      clear(),
    // Установка курсора в выбранные столбец-строка
      go(byte col, byte row),
    // Установка курсора в выбранную позицию справа-налево сверху-вниз
      go(byte = def_go);
    // Возвращает длину строки закодированной в utf-8
    word utf8_strlen(char*);

    void
    // Инициализация массива строк разделенных символом \r
      init(const char*),
      init(const __FlashStringHelper*),
    // Печать строки из ранее переданного массива по её номеру
      printn(byte num, int8_t = 127, byte = 255, byte = 255);
    // Возвращает кол-во строк в ранее переданном массиве
    byte n_count();
    byte
    // Ширина символа
      font_width,
    // Высота символа
      font_height,
    // Кол-во символов по ширине экрана
      scr_width,
    // Кол-во символов по высоте экрана
      scr_height,
    // Кол-во символов которое вмещает экрана
      scr_length,
    // Позиция курсора от нуля слева направо сверху вниз
      scr_pos;


  private:
    // Ф-ия печати строк без параметров
    void print_lcd(char*);
    void
    // Печать строки из ранее переданного массива по её номеру
      printn_str(byte num, int8_t, byte, byte),
      printn_flash(byte num, int8_t, byte, byte);
    // Указатель на объект управления экраном
    void* lcd;
    // Тип экрана
    display_type lcd_type;
    // Указатель на строку-массив
    char* s;
    // Тип массива, FlashStringHelper или ASCIZString (char[])
    string_type s_type;
};

#endif
