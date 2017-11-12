/*
 * Sunset.ino
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

const char Sunset[] PROGMEM = "MNT150L4O3DGA+L8AGL4F+AL2G.D.L4DGA+L8AGL4F+AL1GP2L4G>CD+L8DCL4<B>DL2C.<G.A.A.L1A+.L4G>CD+L8DCL4<B>DL2C.C+.L1D.P4L4<A+L2>CL4<A+AP4A+L2>CL4<A+AP4A+L2>CL4<A+>CL1D.L4D+D+D+L8D+DL4CD+L2D.<A+.L4>CCCL8C<A+L4A>CL1<A+.L4>D+D+D+L8D+DL4CD+L2D.<A+.L4>CCCL8C<A+L4AA+L1G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Sunset);
}

void loop(){
    play->touch();
}
