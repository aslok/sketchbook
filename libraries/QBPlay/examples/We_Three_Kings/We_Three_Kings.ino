/*
 * We_Three_Kings.ino
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

const char We_Three_Kings[] PROGMEM = "MNT150L4O2BL8AL4GL8EF+GF+L4EP8BL8AL4GL8EF+GF+L4EP8L8G.P16GA.P16AB.P16B>DC<BABAL4GL8F+L4EP8F+L2A.L8G.P16GP32L4GL8DL4GL8EL4GP8L8G.P16GP32L4GL8DL4GL8EL4GP8L8G.P16GL4AL8BL4>CL8<BL4AL8BG.P16GP32L4GL8DL4GL8EL4G.P4BL8AL4GL8EF+GF+L4EP8BL8AL4GL8EF+GF+L4EP8L8G.P16GA.P16AB.P16B>DC<BABAL4GL8F+L4EP8F+L2A.L8G.P16GP32L4GL8DL4GL8EL4GP8L8G.P16GP32L4GL8DL4GL8EL4GP8L8G.P16GL4AL8BL4>CL8<BL4AL8BG.P16GP32L4GL8DL4GL8EL4G.P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) We_Three_Kings);
}

void loop(){
    play->touch();
}
