/*
 * ButtonsTact.cpp
 * Основной файл библиотеки ButtonsTact
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

#include "ButtonsTact.h"

// Конструктор, можно задать номер пина кнопки
ButtonsTact::ButtonsTact(byte pin){
    if (pin == 255){
        return;
    }
    addButton(pin);
}

// Добавляем новую кнопку (кнопки) в массив кнопок
void ButtonsTact::addButton(byte pin){
    // Указатель на прошлую версию массива кнопок
    struct Button* buttons_old;
    // Количество элементов в прошлой версии массива кнопок
    byte buttons_cnt_old = buttons_cnt++;
    if (buttons_cnt_old){
        // buttons_old будет указывать на прошлую версию массива кнопок
        buttons_old = buttons;
    }
    // Указатель на новую версию массива кнопок
    buttons = (Button*) malloc(buttons_cnt * sizeof(Button));
    // Копируем кнопки из прошлой версии массива в новую
    for (byte num = 0; num < buttons_cnt_old; num++){
        buttons[num].pin = buttons_old[num].pin;
        buttons[num].levels = buttons_old[num].levels;
    }
    // Если в прошлой версии массива были кнопки
    if (buttons_cnt_old){
        // Освобождаем память выделенную для прошлой версии массива кнопок
        free(buttons_old);
    }
    buttons[buttons_cnt - 1].pin = pin;
    buttons[buttons_cnt - 1].levels = NULL;
    buttons[buttons_cnt - 1].state = ERROR;
    buttons[buttons_cnt - 1].current = ERROR;
    buttons[buttons_cnt - 1].ms_start = 0;
}

// Добавляем уровни срабатывания кнопки (кнопок)
void ButtonsTact::addLevels(...){
    va_list arguments;
    va_start(arguments, 255);
    // Количество уровней
    byte arg_cnt = 1;
    // Пересчитываем уровни
    for (; END != va_arg(arguments, int); ++arg_cnt);
    va_end(arguments);
    // Указатель на массив уровней
    int* levels = (int*) malloc(arg_cnt * sizeof(int));
    va_start(arguments, 255);
    // Уровень по-умолчанию
    int level_default;
    // Заполняем массив уровней (последний элемент END)
    for (byte num = 0; num <= arg_cnt; num++){
        levels[num] = va_arg(arguments, int);
        if (!num){
            level_default = levels[num];
        }
    }
    va_end(arguments);
    bubble_sort(levels);
    // Ассоциируем массив уровней с кнопками у которых нет уровней
    boolean levels_done = false;
    for (byte num = 0; num < buttons_cnt; num++){
        // Если у кнопки есть уровни - пропускаем ее
        if (NULL != buttons[num].levels){
            continue;
        }
        buttons[num].levels = levels;
        buttons[num].level_default = level_default;
        buttons[num].state = level_default;
        levels_done = true;
    }
    // Если нет кнопок без уровней, то перезаписываем уровни у последней кнопки
    if (!levels_done){
        // TODO: Память нельзя освобождать, если ее использует больше чем одна кнопка
        // Освобождаем память занятую прошлой версией массива уровней
        free(buttons[buttons_cnt - 1].levels);
        // Указатель будет указывать на новый массив уровней
        buttons[buttons_cnt - 1].levels = levels;
        buttons[buttons_cnt - 1].level_default = level_default;
        buttons[buttons_cnt - 1].state = level_default;
    }
}

// Возвращаем значение (текущий уровень) кнопки
int ButtonsTact::state(byte pin){
    for (byte num = 0; num < buttons_cnt; num++){
        if (buttons[num].pin != pin){
            continue;
        }
        int state = buttons[num].state;
        buttons[num].state = buttons[num].level_default;
        return state;
    }
    return ERROR;
}

// Обновляем состояние
unsigned long ButtonsTact::touch(unsigned long new_ms){
    ms = new_ms ? new_ms : millis();
    // Обходим каждую кнопку
    for (byte num = 0; num < buttons_cnt; num++){
        // Текущий уровень кнопки
        int current_raw = analogRead(buttons[num].pin);
        // Количество элементов в массиве уровней
        byte levels_cnt;
        for (levels_cnt = 0; END != buttons[num].levels[levels_cnt]; levels_cnt++);
        int current;
        // Обходим массив уровней
        for (byte num_from = 0; num_from < levels_cnt; num_from++){
            byte num_to = num_from + 1;
            // Каждая пара уровней проверяется на вхождение текущего уровня
            int level_from = buttons[num].levels[num_from];
            // Если это последняя итерация
            if (num_from == levels_cnt - 1 ||
                    // Или если текущий уровень меньше середины между парой уровней
                    current_raw < level_from + (buttons[num].levels[num_to] - level_from) / 2){
                // Значит текущее значение кнопки это текущий уровень
                current = level_from;
                break;
            }
        }
        // Если текущий уровень изменился на уровень по-умолчанию
        if (buttons[num].current != buttons[num].level_default &&
                current == buttons[num].level_default){
            // Сбрасываем время начала нажатия
            buttons[num].ms_start = 0;
            // Сохраняем текущий уровень
            buttons[num].current = current;
            // Устанавливаем значение кнопки на уровень по-умолчанию
            buttons[num].state = current;
        // Если текущий уровень изменился
        }else if (buttons[num].current != current){
            // Сохраняем время начала нажатия
            buttons[num].ms_start = ms;
            // Сохраняем текущий уровень
            buttons[num].current = current;
        }
        // Если кнопка нажата больше 50 милисекунд
        if (current != buttons[num].level_default &&
                (double) ms - buttons[num].ms_start > 50){
            // Игнорируем удерживание нажатия в течении 250 милисекунд
            buttons[num].ms_start = ms + 250;
            // Устанавливаем значение кнопки на текущий уровень
            buttons[num].state = current;
        }
    }
    return ms;
}

// Печать массива кнопок (для отладки)
void ButtonsTact::print(){
    for (byte button_num = 0; button_num < buttons_cnt; button_num++){
        Serial.print(buttons[button_num].pin);
        Serial.print(F(": "));
        for (byte level_num = 0; buttons[button_num].levels[level_num] != END; level_num++){
            if (level_num){
                Serial.print(F(", "));
            }
            Serial.print(buttons[button_num].levels[level_num]);
        }
        Serial.println();
    }
}

// Пузырьковая сортировка, для сортировки массива уровней
void ButtonsTact::bubble_sort(int* arr){
    byte levels_cnt;
    for (levels_cnt = 0; END != arr[levels_cnt]; levels_cnt++);
    for (byte pass = 1; pass < levels_cnt; pass++){
        boolean done = true;
        for (byte num_1 = 0, num_2 = 1; num_1 < levels_cnt - pass; num_1++, num_2++){
            if (arr[num_1] < arr[num_2]){
                continue;
            }
            int tmp = arr[num_1];
            arr[num_1] = arr[num_2];
            arr[num_2] = tmp;
            done = false;
        }
        if (done){
            return;
        }
    }
}
