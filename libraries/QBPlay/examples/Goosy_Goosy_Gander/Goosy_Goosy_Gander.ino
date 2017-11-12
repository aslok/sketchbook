/*
 * Goosy_Goosy_Gander.ino
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

const char Goosy_Goosy_Gander[] PROGMEM = "MNT150L8O2DDDF+L4AAL8B>C+D<BL4AAGGF+F+L8EDEF+L4DDL8DDDF+L4AL8AAB>C+D<BL4AP8L8AGGGGL4F+L8F+F+EDEF+L2D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Goosy_Goosy_Gander);
}

void loop(){
    play->touch();
}
