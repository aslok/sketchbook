/*
 * Chopin_2.ino
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

const char Chopin_2[] PROGMEM = "MNT200L8O2G+.L16G.G+.>C.<A+.G.G+.A+.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.A+.>C.C+.D+.F.F+.L8A+.P32L16G+.F+.F.P64F.D+.P64D+FD+D.L8D+.A+.P32L16G+.F+.F.P64F.D+FD+D.D+.F.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.A+.>C.C+.D+.F.F+.L8A+.P32L16G+.F+.F.P64F.D+.P64D+FD+D.L8D+.A+.P8L16G+.F+.F.D+.F.L32D+.F.D+.L16D.D+.E.P16F.F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8>C+P32L16C.<A+.G+.F+.F.D+.C+.C.<A+.G+.F+.F.D+.C+.C.D+.A+.G+.G.G+.A+.>C.C+.D+.P32F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8>FP32L16D+.C+.C.<A+.G+.F+.F.D+.C+.C.<A+.G+.A.>C.<A+.F.F+.C.L8C+.P8P8G+.D+.L2G+L8E.L4G+.L8F.L4>F.P8F.L8<A+.L4>F.L8C.L4D+.L8C+.C.D+C+<A+L4G+.L8D+.L4G+.L8E.L4G+.L8F.>F.P32L16CC+CC+L8<B.>C.G+.<A+.>G.<A.>F+.<G+.>F.<F.A+.L4G+.L8D+.L16>G+L4<G+.L8E.L16>G+L4<G+.L8F.L16>G+L4F.P8L8F.L16G+L4F.L8<A+.L16>G+L4F.L8C.L16G+L8D+.C+.C.L16G+L8D+.C+.L16<A+.>G+L4<G+.L8D+.L16>G+L4<G+.L8E.L16>G+L4<G+.L8F.>F.P8L4F.L8<A+.L4>E.L8<A.>D+.<G+.>D.F.D+.G+.P8P8L16<G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G+A+G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.A+.>C.C+.D+.F.F+.L8A+.P32L16G+.F+.F.P64F.D+.P64D+FD+D.L8D+.A+.P32L16G+.F+.F.P64F.D+FD+D.D+.F.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.>C.<A+.G.G+.A+.>C.C+.D+.F.F+.L8A+.P32L16G+.F+.F.P64F.D+.P64D+FD+D.L8D+.P32A+.L16G+.F+.F.D+.F.L32D+F.D+.F.L16D.D+.E.P8F.F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8>C+P32L16C.<A+.G+.F+.F.D+.C+.C.<A+.G+.F+.F.D+.C+.C.D+.A+.G+.G.G+.A+.>C.C+.D+.P32F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8>FP32L16D+.C+.C.<A+.G+.F+.F.D+.C+.C.<A+.G+.A.>C.<A+.F.F+.C.L8C+.P8>F.L16F.F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8>C+P32L16C.<A+.G+.F+.F.D+.C+.C.<A+.G+.F+.F.D+.C+.C.D+.A+.G+.G.G+.A+.>C.C+.D+.P32F+.F.E.F.G+.F+.F.F+.F.E.F.A+.P32G+.A+.G+.G.G+.>C.<A+.G+.A+.G+.G.G+.L8O5FP8D+L16C+.C<A+G+F+FD+C+C<A+G+F+FD+C+C<A+A>C<A+.F.F+.C.L8C+.P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Chopin_2);
}

void loop(){
    play->touch();
}
