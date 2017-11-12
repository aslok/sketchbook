/*
 * Here_We_Go_Round_The_Mulberry_Bush.ino
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

const char Here_We_Go_Round_The_Mulberry_Bush[] PROGMEM = "MNT150L8O2GGGL4GL8B>DD<BL4GL8GAAAL4AL8BAAF+L4D.L8GGGL4GL8B>DD<BL4GL8GL4AL8ADEF+L4G.G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Here_We_Go_Round_The_Mulberry_Bush);
}

void loop(){
    play->touch();
}
