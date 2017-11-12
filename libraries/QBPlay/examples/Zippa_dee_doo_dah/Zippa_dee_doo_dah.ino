/*
 * Zippa_dee_doo_dah.ino
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

const char Zippa_dee_doo_dah[] PROGMEM = "MNT150L8O2E.L16EL8FL4G>C.L8<A.L16FL8AL2GP8L4>CCL8<AGECECEL2DP8L8E.L16EL8FL4G>C.L8<A.L16FL8AL2GP8L8A.L16BL8>CL4EC.L8D.L16<AL8BL4>C.L8C<AL4BAFDAG.L8AB>CL4D.L8ECL4D.P8L16<B>CL8<BAGFEDE.L16EL8FL4G>C.L8<A.L16FL8AL2GP8L8AB>CL4EC.L8D<ABL2>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Zippa_dee_doo_dah);
}

void loop(){
    play->touch();
}
