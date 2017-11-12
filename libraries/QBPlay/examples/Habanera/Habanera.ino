/*
 * Habanera.ino
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

const char Habanera[] PROGMEM = "MNT150L4O1D.L16A.L8>F.<A.L4D.L16A.L8>F.<A.L4D.L16A.L8>F.<A.L4D.L16A.L8O4D.C+.L4C.L16C.L8<B.A+.L4A.L16A.L8G+.G.L16FGFE.F.L8G.F.L32DL4E.L8>D.C+.L4C.L16C.L8<B.A+.L4A.L16A.L8G.F.L16EFED.E.L8F.E.L4D.L8>D.C+.L4C.L16C.L8<B.A+.L4A.L16A.L8G+.G.L16FGFE.F.L8G.F.L32DL4E.L8>D.C+.L4C.L16C.L8<B.A+.L4A.L16A.L8G.F.L16EFED.E.L8F.E.L4D.L16A.L8D.E.L4F+.L16A.L8F+.E.L4D.L16E.L8F+.G.L32F+L16A.L32F+L16A.L32F+L16A.L32F+L16A.L32GL8B.L32F+L8A.L32EL4G.L16B.L8E.F+.L32EL4G.L16B.L8G.F+.L4E.L16F+.L8G.A.L32GL16B.L32GL16B.L32GL16B.L32GL16B.L32AL8>C+.L32<GL8B.L32F+L4A.L16A.L8>D.E.L32DL4F+.L16<A.L8F+.E.L4D.L16E.L8F+.G.L32F+L16A.L32F+L16A.L32F+L16A.L32F+L16A.L32BL2>D.L16C+DC+L32<EL4G.L16B.L8>E.F+.L32EL4G.L16<B.L8G.F+.L4E.L16F+.L8G.A.L16>C+.<B.G+.A.L1>F+L16EF+EL8D.P8L16A.L8>D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Habanera);
}

void loop(){
    play->touch();
}
