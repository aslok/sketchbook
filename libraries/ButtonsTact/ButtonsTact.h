/*
 * ButtonsTact.h
 * Заголовочный файл библиотеки ButtonsTact
 * Библиотека предназначена для управления кнопками,
 * которые подключены через различные резисторы на один и тот же пин
 * Возможности:
 * 1. Максимальное количество кнопок на одном пине - 255
 * 2. Максимальное количество используемых пинов - 255
 * 3. Определение нажатия при расхождениях по уровню напряжения
 * 4. Срабатывание нажатия только через 50 милисекунд удержания
 * 5. Очистка флага нажатия после передачи этого флага в скетч
 * 6. Повторное срабатывание нажатия только через 250 милисекунд
 *
 * created 12.10.2017
 * modified 22.10.2017
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

#ifndef ButtonsTact_h
#define ButtonsTact_h

#include "Arduino.h"

// Флаг "конец массива"
#define END -1
// Флаг "ошибка"
#define ERROR -1

struct Button {
  byte pin;
  int* levels;
  int current;
  unsigned long ms_start;
  int state;
  int level_default;
};

class ButtonsTact{
    public:
        // Конструктор, можно задать номер пина кнопки
        ButtonsTact(byte pin = 255);
        // Добавляем новую кнопку (кнопки) в массив кнопок
        void addButton(byte pin);
        // Добавляем уровни срабатывания кнопки (кнопок). int, int, int...
        void addLevels(...);
        // Возвращаем значение (текущий уровень) кнопки
        int state(byte pin);
        // Обновляем состояние
        unsigned long touch(unsigned long ms = 0);
        // Печать массива кнопок (для отладки)
        void print();
    private:
        // Массив кнопок и их уровней
        struct Button* buttons;
        // Количество кнопок
        byte buttons_cnt = 0;
        // uptime (обновляется в процессе выполнения touch)
        unsigned long ms = 0;
        // Пузырьковая сортировка, для сортировки массива уровней
        void bubble_sort(int* arr);
};

#endif
