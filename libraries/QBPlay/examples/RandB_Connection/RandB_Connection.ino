/*
 * RandB_Connection.ino
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

const char RandB_Connection[] PROGMEM = "MNT150L4O2CF.L8GL4GAA<A+.L8>FL4FFG<A+A>CEL2FL4CL1D.L4CF.L8GL4GAA<A+>C.L8FL4FG<A+A>CEL2FL4CL1D.L4DADADADADAD.L8FL4EEEGECL1E.L4<A+>DFDE.L8CL4CEGEF+.L8C<A+L4>D.FL8AL4A.GL1F.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) RandB_Connection);
}

void loop(){
    play->touch();
}
