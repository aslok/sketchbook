/*
 * Real_Thing_Buy_the_World_a_Coke.ino
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

const char Real_Thing_Buy_the_World_a_Coke[] PROGMEM = "MNT150L8O2DL4CDFDCL8DL4F.FGAGL8AL2G.P8L4AGA>C<AGL8AL4>C.<AF.L8GL4FL8DL2C.P8L8DL4CDFDCL8DL4F.FGAGL8AL2G.P8L8AL4GA>C<AL8GL4A>C.<AF.L8GL4FL8DL2F.P8L8DL4CDFDCL8DL4F.FGAGL8AL2G.P8L8AL4GA>C<AG.L8AL4>C.<AF.L8GL4FL8DL4F.L8AL16AL8A+.L4AL1FP4L8FL16FL8F.L4EL8FL1G.P4L4AGA>C<AL8GL4A>C.<AF.L8GL4FL8DL1F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Real_Thing_Buy_the_World_a_Coke);
}

void loop(){
    play->touch();
}
