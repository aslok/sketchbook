/*
 * Oh_My_Darling_Clementine.ino
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

const char Oh_My_Darling_Clementine[] PROGMEM = "MNT150L8O3C.L16CL4C<GP64L8>E.L16EL4ECL8C.L16EL4G.L16GL8F.L16EL2DP32L8D.L16EL4FFL8E.L16DL4ECL8C.L16EL4D<GL8B.L16>DL2CP8L8C.L16CL4C<GP64L8>E.L16EL4ECL8C.L16EL4G.L16GL8F.L16EL2DP32L8D.L16EL4FFL8E.L16DL4ECL8C.L16EL4D<GL8B.L16>DL2CP8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Oh_My_Darling_Clementine);
}

void loop(){
    play->touch();
}
