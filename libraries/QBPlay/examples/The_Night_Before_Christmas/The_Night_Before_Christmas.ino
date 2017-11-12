/*
 * The_Night_Before_Christmas.ino
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

const char The_Night_Before_Christmas[] PROGMEM = "MNT150L8O2GGL4>C.L8CCL4<BGBAFAL2GL8GGL4FDFECEDCDL2EL8GGL4>C.L8CL4C<BGBAFAL2GL8GGL4FDFECEDC<BL2>CL4CAG+A>C<BAG>C<EL2GL4GFEFAGFEGCL2EL4CAG+A>C<BAG>C<EL2GL4GF+ED>C<BAAGGL2GL8GGL4>C.L8CL4C<BGBAFAL2GL8GGL4FDFECEDC<BL2>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Night_Before_Christmas);
}

void loop(){
    play->touch();
}
