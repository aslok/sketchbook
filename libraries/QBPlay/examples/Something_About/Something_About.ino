/*
 * Something_About.ino
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

const char Something_About[] PROGMEM = "MNT150L4O3CL8<AL2EP4L8EA>C<BAL4BL8G+L2EP2L8AA+AGEDL2C+P8L4C+DEL8GFEL4GL2FP2L4>FL8DL2<A+P4L8FA+>FEDL4EL8CL2<AP2L4>CL8<AL2>D+P8L8CC<BAL2B";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Something_About);
}

void loop(){
    play->touch();
}
