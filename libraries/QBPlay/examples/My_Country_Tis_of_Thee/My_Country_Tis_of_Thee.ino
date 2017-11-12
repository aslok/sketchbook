/*
 * My_Country_Tis_of_Thee.ino
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

const char My_Country_Tis_of_Thee[] PROGMEM = "MNT150L4O2GGAF+.L8GL4ABB>C<B.L8AL4GAGF+L2GP4L4>DDDD.L8CL4<B>CCCC.L8<BL4ABL8>C<BAGL4B.L8>CL4DL8EL16DCL4<BAL2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) My_Country_Tis_of_Thee);
}

void loop(){
    play->touch();
}
