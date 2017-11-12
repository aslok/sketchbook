/*
 * Schuman.ino
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

const char Schuman[] PROGMEM = "MNT255L8O2EAEA>C<A>CECFEC<ABE>C<BG+EAE>C<BP8EAEA>C<A>CECFEC<ABE>C<BG+EAEG+AP8G>C<G>CECEGEAGECD<G>ED<BG>C<G>EDP8<G>C<G>CECEGEAGECD<G>ED<BG>C<GB>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Schuman);
}

void loop(){
    play->touch();
}
