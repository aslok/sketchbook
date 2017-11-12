/*
 * Elise_Love_Story_Theme.ino
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

const char Elise_Love_Story_Theme[] PROGMEM = "MNT120L16O4E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.P32O4E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.>B.>C.D.E.O2G.>C.G.>F.E.D.O2G.B.>F.>E.D.C.O2E.A.>G.>D.C.<B.<E.>E.P64E.>E.<E.>E.P64E.>E.<D+.E.D+.E.D+.E.D+.E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.P32>B.>C.D.E.O2G.>C.G.>F.E.D.O2G.B.>F.>E.D.C.O2E.A.>E.>D.C.<B.<E.>E.>E.<E.>E.P64E.>E.<D+.E.D+.E.D+.E.D+.E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.P32L8O4C.P64C.P64C.L32<F.A.>C.L16O2A.>C.<A.O4F.E.P64E.D.A+.A.P64A.G.F.E.D.C.<A+.A.L32B.A.G.A.B.L16>C.O2A.>C.<A.O4D.D+.E.O2A.>C.>E.F.<A.>C.<E.>C.D.C.<B.>C.D.<B.>C.G.<B.>G.<A.>G.<B.>G.C.G.D.G.E.G.>C.<B.A.G.F.E.D.G.F.D.C.G.<B.>G.<C.A.>G.<B.>G.C.G.D.G.E.G.>C.<B.A.G.F.E.D.G.F.D.E.G.E.D+.E.<B.>E.D.E.<B.>E.D.E.<B.>E.D+.L8E.<B.>E.D+.E.D+.E.D+.E.P32L16E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.>B.>C.D.E.O2G.>C.G.>F.E.D.O2G.B.>F.>E.D.C.O2E.A.>E.>D.C.<B.<E.>E.>E.<E.>E.P64E.>E.<D+.E.D+.E.D+.E.D+.E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.O1A.A.A.A.A.L8O4C+.L16O1A.A.A.A.A.O4D.O1A.A.A.O4E.F.P64F.O1A.A.A.O4F.O1A.L8O4E.L16O1A.A.A.A.A.O4D.O1A.A.A.O4C.<B.A.O1A.A.A.O3A.O1A.O3A.O1A.O4C.O1A.O3B.O1G+.O3A.O1A.A.A.A.A.L8O4C+.L16O1A.A.A.A.A.O4D.O1A.A.A.O4E.F.P64F.O1A.A.A.O4F.O1A.L8O4F.L16O1A+.A+.A+.A+.A+.O4D+.O1A+.A+.A+.O4D.C.<A+.O1A+.A+.A+.O3A.O1A+.O3G+.O1B.B.B.O3G+.O1B.L4O3AP4L8BP8L16<A.>C.E.A.>C.E.D.C.<B.A.>C.E.A.>C.E.D.C.<B.A.>C.E.A.C.E.D.C.B.A+.A.G+.G.F+.F.E.D+.D.C+.C.<B.A+.A.G+.G.F+.F.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.<E.A.>B.>C.D.E.O2G.>C.G.>F.E.D.O2G.B.>F.>E.D.C.O2E.A.>E.>D.C.<B.<E.>E.>E.<E.>E.P64E.>E.<D+.E.D+.E.D+.E.D+.E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>E.G+.B.>C.O2E.A.>E.>E.D+.E.D+.E.<B.>D.C.<A.<E.A.>C.E.A.B.<E.G+.>D.>C.<B.A.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Elise_Love_Story_Theme);
}

void loop(){
    play->touch();
}
