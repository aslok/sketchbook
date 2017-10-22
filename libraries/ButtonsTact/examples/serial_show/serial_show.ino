/*
 * serial_show.ino
 *
 * created 12.10.2017
 * modifid 12.10.2017
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

unsigned long ms_prev = 0;

void setup(){
    Serial.begin(57600);

    buttons = new ButtonsTact(0);
    buttons->addLevels(1023, 0, 130, 300, 475, 720, END);
    buttons->print();
}

void loop(){
    buttons->touch();
    /*unsigned long ms = millis();
    if (ms - ms_prev > 1000){
        ms_prev = ms;
    }*/
    int button_0 = buttons->state(0);
    if (button_0 < 1023){
        Serial.print(F("Level = "));
        Serial.println(button_0);
    }
}
