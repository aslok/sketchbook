/*
 * Silent_Night.ino
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

const char Silent_Night[] PROGMEM = "MLT255L24O3GEGEGEGEGEGEGEGEGEGEGEGEAFAFAFAFGEGEGEGEGEGEGEGEECECECECECECECECECECECECECECECECECECECECECECECECGEGEGEGEGEGEGEGEGEGEGEGEAFAFAFAFGEGEGEGEGEGEGEGEECECECECECECECECECECECECECECECECECECECECECECECEC>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<FP8>D<F>D<F>D<F>D<F>D<F>D<F>D<F>D<FBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBG>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<EP8>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<EGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEGEAFAFAFAFAFAFAFAFAFAFAFAFAFAFAFP8AFAFAFAFAFAFAFAF>C<A>C<A>C<A>C<A>C<A>C<A>C<A>C<A>C<A>C<A>C<A>C<ABGBGBGBGAFAFAFAFAFAFAFAFGEGEGEGEGEGEGEGEGEGEGEGEAFAFAFAFGEGEGEGEGEGEGEGEECECECECECECECECECECECECECECECECECECECECECECECECAFAFAFAFAFAFAFAFAFAFAFAFAFAFAFP8AFAFAFL32A.F.A.F.A.F.A.F.A.F.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.B.G.B.G.B.G.B.G.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.P8>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>D.<B.>D.<B.>D.<B.>D.<B.B.F.B.F.B.F.B.F.B.F.B.F.B.F.B.F.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>F.<B.>F.<B.>F.<B.>F.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.P8>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.>D.<F.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.B.G.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.P8>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.P8A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.B.G.B.G.B.G.B.G.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.P8A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.>C.<A.B.G.B.G.B.G.B.G.A.F.A.F.A.F.A.F.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.A.F.A.F.A.F.A.F.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.P8>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>F.<B.>D.<B.>D.<B.>D.<B.>D.<B.B.F.B.F.B.F.B.F.B.F.B.F.B.F.B.F.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>E.<G.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.G.E.E.C.E.C.E.C.E.C.E.C.E.C.E.C.E.C.G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>G.<B.>F.<B.>F.<B.>F.<B.>F.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>D.<B.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.>C.<E.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Silent_Night);
}

void loop(){
    play->touch();
}
