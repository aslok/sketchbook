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
 * created 12.10.2017
 * modifid 22.10.2017
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
ButtonsTact* buttons;

const int RIGHT     = 0;
const int UP        = 130;
const int DOWN      = 300;
const int LEFT      = 475;
const int SELECT    = 720;
const int NONE      = 1023;

void setup(){
    Serial.begin(57600);

    // Обработка нажатий на пине A0
    buttons = new ButtonsTact(A0);
    // На первом месте стоит уровень по-умолчанию, когда ничего не нажато
    buttons->addLevels(NONE, UP, DOWN, LEFT, RIGHT, SELECT, END);
}

void loop(){
    buttons->touch();
    int button_A0 = buttons->state(A0);
    switch (button_A0){
        case UP:
            Serial.println(F("UP"));
            break;
        case DOWN:
            Serial.println(F("DOWN"));
            break;
        case LEFT:
            Serial.println(F("LEFT"));
            break;
        case RIGHT:
            Serial.println(F("RIGHT"));
            break;
        case SELECT:
            Serial.println(F("SELECT"));
            break;
    }
}
