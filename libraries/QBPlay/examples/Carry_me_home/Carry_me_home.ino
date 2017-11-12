/*
 * Carry_me_home.ino
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

const char Carry_me_home[] PROGMEM = "MNT150L8O3CP64L4CL8C+L4C.P32L8<A+L4G+.L8FL16D+L4G+.P8D+L8G+A+>CP64CC+CP64C<G+GG+L2A+P8L4>CL8C+.L16CP64L4CL8<A+G+L4A+L8G+.L16FD+L4G+.P8D+L8G+.L16A+L4>CL8C+CP64C<A+G+.L16GL2G+P8L4A+P64L8A+>CC+P64C+D+.L16C+L4CP64L8C.L16C+L8D+L4C.P8D+L8C+.L16CP64L4CL8<A+.L16G+P64L8G+P64G+GG+L2A+P8L4>CL8C+CL4CL8<A+.L16G+P64L4A+P64L8G+.L16FL8D+L4G+.P16D+L8G+.L16A+L8>CP64CC+CP64C<A+G+.L16GL1G+P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Carry_me_home);
}

void loop(){
    play->touch();
}
