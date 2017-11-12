/*
 * Billy_Boy_Charming_Billy.ino
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

const char Billy_Boy_Charming_Billy[] PROGMEM = "MNT150L8O2EFGGGGL4>CL8<EFL4GL8GAL4GL8EFL4GL8GGL4>CL8<FEEDP2DEFFFFL4FL8GFEDEFL4GL8>C<AL4GL8EEGFD<B>DL2C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Billy_Boy_Charming_Billy);
}

void loop(){
    play->touch();
}
