/*
 * serial_show.ino
 * Файл с примером использования библиотеки ButtonsTact
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
 * created 18.10.2017
 * modifid 28.10.2017
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

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;

#include "ButtonsTact.h"
ButtonsTact* buttons;

const int RIGHT     = 0;
const int UP        = 130;
const int DOWN      = 300;
const int LEFT      = 475;
const int SELECT    = 720;
const int NONE      = 1023;

const byte PRINT_UP     = 0;
const byte PRINT_DOWN   = 1;
const byte PRINT_LEFT   = 2;
const byte PRINT_RIGHT  = 3;
const byte PRINT_SELECT = 4;
const byte PRINT_NONE   = 5;

void setup(){
    // Обработка нажатий на пине A0
    buttons = new ButtonsTact(A0);
    // На первом месте стоит уровень по-умолчанию, когда ничего не нажато
    buttons->addLevels(NONE, UP, DOWN, LEFT, RIGHT, SELECT, END);

    lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2, 10);
    lcd->backlight();
    lcd->init(F("Вверх\rВниз\rВлево\rВправо\rВыбрать\r"));
}

unsigned long ms_last = 0;

void loop(){
    unsigned long ms = buttons->touch();
    int button_A0 = buttons->state(A0);
    switch (button_A0){
        case UP:
            lcd->printn(PRINT_UP, 5, 0, 7);
            ms_last = ms;
            break;
        case DOWN:
            lcd->printn(PRINT_DOWN, 5, 0, 7);
            ms_last = ms;
            break;
        case LEFT:
            lcd->printn(PRINT_LEFT, 5, 0, 7);
            ms_last = ms;
            break;
        case RIGHT:
            lcd->printn(PRINT_RIGHT, 5, 0, 7);
            ms_last = ms;
            break;
        case SELECT:
            lcd->printn(PRINT_SELECT, 5, 0, 7);
            ms_last = ms;
            break;
        default:
            if (ms_last && ms - ms_last > 2000){
                ms_last = 0;
                lcd->printn(PRINT_NONE, 5, 0, 7);
            }
    }
}
