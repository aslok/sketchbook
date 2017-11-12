/*
 * Andre.ino
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

const char Andre[] PROGMEM = "MST255L2O2GBD.L8>C+DEDC<B>C<BAGL4GL16GF+AGL8F+P8P4L2F+AD.L8B>CDC<BAGF+>EDL4CL16C<B>DCL8<BP8P4L4G.L8BL4>DDL2D<F+L4GAB>CL2<BL4AP4L2GBD.L8>C+DEDC<B>C<BAGL4GL16GF+AGL8F+P8P4L2F+AD.L8B>CDC<BAGF+>EDL4CL16C<B>DCL8<BP8P4L4G.L8BL4>DDL2D<F+L4GAB>CL2<BL4AP4L2F+AD+.L8A+B>C<BA+BL4>F+<BB.L8>EL4GP4L2<EGC+.L8G+ABAG+AL4>E<A>F+.L8DL4<AL8G+ABAG+AL4>E<AL8>F+DAF+DP8P4L4F+P4EP4L2DL8DD+EDC<BAGL4F+A>C.L8<AL4F+P4A.L8F+DDEF+L2GBD.L8>C+DEDC<B>C<BAGL4GL16GF+AGL8F+P8P4L4AL16AG+BAL8GP8P4P8EF+G+AB>CDL4D+EF+G<B.L8>DL4C.L8<AL2GL4>G.L8DL4<B.L8>DL4C.L8<AL2BL4B.L8>GL4D.L8<BL4>C.L8<AL4GP4L8>EDEDL4GP4L8C<B>C<AL4GP4BP4L2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Andre);
}

void loop(){
    play->touch();
}
