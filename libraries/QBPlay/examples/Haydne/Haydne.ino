/*
 * Haydne.ino
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

const char Haydne[] PROGMEM = "MNT200L8O3EC<A>CEC<AP8>EC<A>CEC<AP8>EA<A>DFL4<BP8L8>DG<G>CEL4<AP8L8>CFDB>DL4<G+P8L8G+B<B>D<BL4>FP8L8<B>DFG+B>DL4FP8L8<G+AEBE>C<EL4F.L8EAL4DL8EC<B>C.L16DL8<B.L16AL4A";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Haydne);
}

void loop(){
    play->touch();
}
