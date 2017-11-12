/*
 * Exodus.ino
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

const char Exodus[] PROGMEM = "MNT100L8O1GL4>C.L8GL4F.L8CD+FD.L16<A+L4>C.L8GL4A+.L8AA+>C<A.L16FL2GP8L8GA+>DC.L16<GL4G.L8>C<G>CD.L16<GL2GL8FGG+A+G.L16D+L8FGD+.L16CL2D.P8L8GL4C.L8GL4F.L8CD+FD.L16<A+L4>C.L8GL4A+.L8AA+>C<A.L16FL2GP8L8GA+>DC.L16<GL4G.L8>C<G>CD.L16<GL2GL8FGG+A+G.L16FL8D+FDA+L2>CP4L4CL16<A+>C<A+GL2A+P8L8G>CDL4F.L8D+DCL16<A+>C<A+GL2A+P8L8G>CDL4G.L8FD.L16CL1D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Exodus);
}

void loop(){
    play->touch();
}
