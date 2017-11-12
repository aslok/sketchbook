/*
 * Expanse.ino
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

const char Expanse[] PROGMEM = "MNT150L8O3DDDED.L16<BL8>DL4DDL8<DDF+A>DD.L16CL4<B.BL8B>E<B.L16AL8GF+EL4AL8>CL4EL8C<BB.L16BL8AGF+L4E.EL8B>E<B.L16AL8GF+EL4AL8>CL4EL8C<BB.L16BL8AGF+L2E.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Expanse);
}

void loop(){
    play->touch();
}
