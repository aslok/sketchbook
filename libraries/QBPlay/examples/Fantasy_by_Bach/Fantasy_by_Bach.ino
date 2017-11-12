/*
 * Fantasy_by_Bach.ino
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

const char Fantasy_by_Bach[] PROGMEM = "MNT100L16O4D<AFAFD>D<AFAFDEAEC+EC+<A>C+E<A+AGFA>D<A>DFDFAFA>DC+EDC+<BAGA+AGFEFAGFEDC<A+AA+>DGFEDCG<A+A>CFC<AF>DFEDC<A+AGF+GA+>EDC+<BA>E<GFA>D<AFD>D<A+AGF+G>D<AGFEF>D<GFED+E>D<FEDC+D<A+>C+D>D<F+G<A>C+D>D<EF<G>C+D>D<D+E<FA>DFA>D<A+AGFEDC+DE<A+AGFA>D<EG>C+L2D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Fantasy_by_Bach);
}

void loop(){
    play->touch();
}
