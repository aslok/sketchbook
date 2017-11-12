/*
 * Katiusha.ino
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

const char Katiusha[] PROGMEM = "MST255L2O2E.L4F+L2G.L4EGGF+EL2F+L4<BP4L2>F+.L4GL2A.L4F+AAGF+L1EL2B>EDL4EDCC<BAL2BEP4>CL4<AL2B.L4GF+<B>GF+L1EL2B>EDL4EDCC<BAL2BEP4>CL4<AL2B.L4GF+<B>GF+L1E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Katiusha);
}

void loop(){
    play->touch();
}
