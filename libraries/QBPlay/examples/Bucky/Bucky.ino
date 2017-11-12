/*
 * Bucky.ino
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

const char Bucky[] PROGMEM = "MNT255L2O2F.L4EL2GFA+.L4AL2>C<A+>DDDDL1DL2C.L4<BL2>CD<A+.L4>CL2DL4<A+A+L2AGAA+L1>CL4<AGF+L2F.L4EL2GFA+.L4AL2>C<A+>C<A+>CC+L1DD+L2<A+>CDD+FGL1DC<A+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bucky);
}

void loop(){
    play->touch();
}
