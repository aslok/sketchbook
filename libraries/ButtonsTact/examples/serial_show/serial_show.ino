/*
 * serial_show.ino
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

    buttons = new ButtonsTact(0);
    // На первом месте стоит уровень по-умолчанию, когда ничего не нажато
    buttons->addLevels(NONE, UP, DOWN, LEFT, RIGHT, SELECT, END);
}

void loop(){
    buttons->touch();
    int button_0 = buttons->state(0);
    switch (button_0){
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
