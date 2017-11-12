/*
 * Jingle_Bells.ino
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

const char Jingle_Bells[] PROGMEM = "MNT255L4O2DBAGL2D.L8DDL4DBAGL2E.L4EE>C<BAL1F+L4>DDC<AL1BL4DBAGL2D.L8DDL4DBAGL2E.L4EE>C<BA>DDDDEDC<AL2G.P4L4BBL2BL4BBL2BL4B>D<G.L8AL1BL4>CCC.L8CL4C<BBL8BBL4BAABL2A>DL4<BBL2BL4BBL2BL4B>D<G.L8AL1BL4>CCC.L8CL4C<BBL8BBL4>DDC<AL1G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Jingle_Bells);
}

void loop(){
    play->touch();
}
