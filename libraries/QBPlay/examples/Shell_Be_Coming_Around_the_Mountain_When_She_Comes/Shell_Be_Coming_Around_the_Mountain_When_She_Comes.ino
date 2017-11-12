/*
 * Shell_Be_Coming_Around_the_Mountain_When_She_Comes.ino
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

const char Shell_Be_Coming_Around_the_Mountain_When_She_Comes[] PROGMEM = "MNT150L8O2DEL16GL8G.G.L16GL8ED<B>DL4GP2L8GAL16BL8B.B.L16BL8>D<BAGL2AP2L8>D.L16C<BL8B.B.L16BL8AGGGL16EL8E.E.L16EL8AGF+EL16DL8D.G.L16AL8BAEF+L2GL8DEL16GL8G.G.L16GL8ED<B>DL4GP2L8GAL16BL8B.B.L16BL8>D<BAGL2AP2L8>D.L16C<BL8B.B.L16BL8AGGGL16EL8E.E.L16EL8AGF+EL16DL8D.G.L16AL8BAEF+L2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Shell_Be_Coming_Around_the_Mountain_When_She_Comes);
}

void loop(){
    play->touch();
}
