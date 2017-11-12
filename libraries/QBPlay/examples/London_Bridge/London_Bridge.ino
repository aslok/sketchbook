/*
 * London_Bridge.ino
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

const char London_Bridge[] PROGMEM = "MNT150L8O2A.L16BL8AGF+GL4AL8EF+L4GL8F+GL4AL8A.L16BL8AGF+GL4AEAL8F+L4D.L8A.L16BL8AGF+GL4AL8EF+L4GL8F+GL4AL8A.L16BL8AGF+GL4AEAL8F+L4D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) London_Bridge);
}

void loop(){
    play->touch();
}
