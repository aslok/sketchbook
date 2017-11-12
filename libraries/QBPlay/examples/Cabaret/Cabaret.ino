/*
 * Cabaret.ino
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

const char Cabaret[] PROGMEM = "MNT200L4O2A+L2>CL4D+GL2A+L4B>C<A+GL1A+P4L4>CL2<A+L4GL2A+>CL1<G.P4L4>CL2D+L4CL2D+CL4DL2<A+L1GP4L4GL2A+L4GL2A+CL1G.P4L4<A+L2>CL4D+GL2A+L4B>C<A+GL1A+P4L4>CL2<A+L4GL2A+>CL1<G.P4L4>CL2D+L4CL2D+CL4DL2<A+L1GP4L4GL2A+L4GL2A+CL1D+P4L4D+D.L8D+L1BP4L4D+D.L8D+L1A+P4L4GF+GL2>D+D+L4D+CDD+DD+FD+D<A+G+F<A+L2>CL4D+GL2A+L4B>C<A+GL1A+L4B>CL2<A+L4GL2A+>CL1C+.P4L4C.L2D+L4CL2D+CL4D.L2FL1<A+L4>CL2D+L4CL2D+L4D+L1D+P2L4<D+D.L8D+L1BP4L4D+D.L8D+L1A+P4L4GF+GL2>D+D+L4D+CDD+DD+FD+D<A+G+F<A+L2>CL4D+GL2A+L4B>C<A+GL1A+L4B>CL2<A+L4GL2A+>CL1C+.P4L4C.L2D+L4CL2D+CL4D.L2<A+L1GL4>CL2D+L4CL2D+CL4DL2F<A+.B>CL1D+L2CL1D+D+D+.P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Cabaret);
}

void loop(){
    play->touch();
}
