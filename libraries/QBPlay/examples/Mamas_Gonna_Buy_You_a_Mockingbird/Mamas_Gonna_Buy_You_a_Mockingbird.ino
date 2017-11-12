/*
 * Mamas_Gonna_Buy_You_a_Mockingbird.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 *
 * created 10.11.2017
 * modified 12.11.2017
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

#include "QBPlay.h"
QBPlay* play;
const byte speaker_pin = A3;

const char Mamas_Gonna_Buy_You_a_Mockingbird[] PROGMEM = "MNT150L4O2CL8AAL4AA+AL8GGL2GL8CCGGL4GL8GAL4GFFP8L8CL4CAAA+AGL2GP16L4CA+AGL2F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Mamas_Gonna_Buy_You_a_Mockingbird);
}

void loop(){
    play->touch();
}
