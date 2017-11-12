/*
 * The_Irish_Ball.ino
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

const char The_Irish_Ball[] PROGMEM = "MNT150L8O2AL4>DL8DDEFL4EL8DL4DL8<A>DEFGAA+L2AP8L8AL4>DL8DDC<A+L4AL8AL4AL8FL4AL8AGFEL4FL8DL4DL8EL4FL8FGAA+L4AL8AL4>DP8L8<DEFGFEDCL2DP8L8DL2EP8L8EFGFEDCL2DL8<AL4>DL8DDEFL4EL8DL4DL8<A>DEFGAA+L2AP8L8AL4>DL8DDC<A+L4AL8AL4AL8FL4AL8AGFEL4FL8DL4DL8EL4FL8FGAA+L4AL8AL4>DP8L8<DEFGFEDCL2DP8L8DL2EP8L8EFGFEDCL2DL1D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Irish_Ball);
}

void loop(){
    play->touch();
}
