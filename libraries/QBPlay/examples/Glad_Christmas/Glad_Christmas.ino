/*
 * Glad_Christmas.ino
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

const char Glad_Christmas[] PROGMEM = "MNT150L8O2FL4A+L8A+>D.L16CL8<A+L4AL8A+L4>CL8<FL4>CL8DD+.L16DL8CL2D.L8<FL4A+L8A+>D.L16CL8<A+L4AL8GL4>D+L8CL4<A+L8A+A.L16GL8AL2A+.L8FL4A+L8A+>D.L16CL8<A+L4AL8A+L4>CL8<FL4>CL8DD+.L16DL8CL2D.L8<FL4A+L8A+>D.L16CL8<A+L4AL8GL4>D+L8CL4<A+L8A+A.L16GL8AL2A+.L8FL4A+L8A+>D.L16CL8<A+L4AL8A+L4>CL8<FL4>CL8DD+.L16DL8CL2D.L8<FL4A+L8A+>D.L16CL8<A+L4AL8GL4>D+L8CL4<A+L8A+A.L16GL8AL2A+.L8FL4A+L8A+>D.L16CL8<A+L4AL8A+L4>CL8<FL4>CL8DD+.L16DL8CL2D.L8<FL4A+L8A+>D.L16CL8<A+L4AL8GL4>D+L8CL4<A+L8A+A.L16GL8AL2A+.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Glad_Christmas);
}

void loop(){
    play->touch();
}
