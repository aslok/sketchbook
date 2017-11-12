/*
 * Theme_From_Alred_Hitchcock_TV_Series.ino
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

const char Theme_From_Alred_Hitchcock_TV_Series[] PROGMEM = "MNT150L8O2DP8>DL32EL8DC+<B>C+P8DEP8<ADP8>DL32EL8DC+<B>C+P8DEP8<ADP8>FL4AL8GFP8AL4>CL8<A+AP8>CL4EL8DC+<A+AGFE<DP8>DL32EL8DC+<B>C+P8DEP8<ADP8>DL32EL8DC+<B>C+P8DEP4FP8AL4>CL8<A+AGFD+GA+DC+DEP8FL4E.L8D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_From_Alred_Hitchcock_TV_Series);
}

void loop(){
    play->touch();
}
