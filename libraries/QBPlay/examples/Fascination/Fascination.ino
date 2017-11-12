/*
 * Fascination.ino
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

const char Fascination[] PROGMEM = "MNT150L8O1B>CEGL2>C.<BL4>CL1<BL8<B>CEGL4>C<B>C<BA.L8BL1AL8C+DFAL1>DL8<C+DFAL1>CL8<C+DFAL4>DC<BAF.L8DL2C<BL8B>CEGL2>C.<BL4>CL1<BL8<B>CEGL4>C<B>C<BA.L8BL1AL8C+DFAL4>FEDC<A.L8FL2EDL8C+DEFL2A.B.L1>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Fascination);
}

void loop(){
    play->touch();
}
