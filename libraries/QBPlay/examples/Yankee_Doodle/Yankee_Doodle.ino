/*
 * Yankee_Doodle.ino
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

const char Yankee_Doodle[] PROGMEM = "MNT150L8O2GGABGBADGGABL4GL8F+DGGAB>C<BAGF+DEF+L4GGL8E.L16F+L8EDEF+L4GL8D.L16EL8DCL4<B>DL8E.L16F+L8EDEF+GEDGF+AL4GGP8P8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Yankee_Doodle);
}

void loop(){
    play->touch();
}
