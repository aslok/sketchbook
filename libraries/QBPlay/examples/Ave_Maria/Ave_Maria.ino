/*
 * Ave_Maria.ino
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

const char Ave_Maria[] PROGMEM = "MLT100L16O1A+.>D.F.<A+.>D.F.<A+.>D.F.<A+.>D.F.A+.D.F.<A+.>D.F.<A+.>D.E.A.D.A+.>D.<D.F.<F.A+.>D.<F.A.>D+.<F.A.O3C.<A+.<A+.>D.<G.A+.>D.<G.A+.>D.<G.A+.>D.>C.O1G.>C.<D+.G.>C.>DC<A+.C.A.G.C.A.A+.D.F.<A+.>D.F.<A+.>D.F.>D.<D.F.<A+.>D.F+.<A+.O3C.<A+.A.D.G.>D.<D.>E.D.<D.E.<A+.>D.E.>C+.<C+.G.<A.>C+.A.>C.<D+.F+.<A.>D+.A+.A.>C.D.D+.C.<A.A+.D.G.<A+.>D.G.<A+.>D.E.>D.<D.>C.O1A.>C.F.<A.>C.A.G.B.>D.F.D.<B.>C.<C.F.<A.>C.F.<A+.>G.A.A+.A.G.F.C.F.<A.>C.F.<A.>C.F.P64F.C.F.>C.O1A.>D+.<F.A.O3C.P64C.O1A.>B.>C.O1A.O3D.C.O1A+.O3D.<A+.<A+.>D.<F.A+.>D.<F.A+.>A+.>C.O1A.>D+.<F.A.O3C.P64C.<B.>C.D+.D.C.<A+.<A+.>D.<G.A+.>D.<G.A+.>D.A+.<A+.>D.>C.O1A.>C.<F.A.O3C.D.O1A.O3D.P64D.D+.D.C.D.F.<C.D+.>D+.<C.D+.<G.>C.D+.G.C.D+.>D.O1G.>C.>C.O1G.O3C.<A+.A.A+.>C+.C.<A+.>C.O1A.>C.<F.A.>C.<F.A.>D+.<F.A.>D+.A+.D.F.<A+.>D.F.<A+.>D.E.A.D.A+.>D.O1A+.>D.<F.A+.>D.<F.A.>D+.<F.A.O3C.<A+.D.F.<A+.>D.F.>D.<D.F.>F.<D.F.L2>A+P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Ave_Maria);
}

void loop(){
    play->touch();
}
