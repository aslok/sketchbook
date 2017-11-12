/*
 * Bach_III.ino
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

const char Bach_III[] PROGMEM = "MNT150L8O2DAFDAFDAFDAFDA+GDA+GDA+GDA+GC+GEC+GEC+A+GEAGFDFAFA>D<A>DFDFBFEDC<BAG+F+E>D<B>C<EC<A>EC<G>D+C<G>D+C>AD+DC<A+AGF+ED>C<AA+>D<A+G>GO1FEO3DC<A+AGA>C<AF>FO1EDO3C<A+AGFGA+AGFEFDFA>D<G>C+EC+<A>EC+<A>EC+<AA+AG>EC+<G>EC+<G>EC+<GAGF>D<A+F>D<A+F>D<A+F>D<A+F+>C<AF+>C<AF+>C<AF+>C<AA+GF+GDGA+GDA+GDD+GF+GA+GD+A+GD+A+GC+A+GC+A+GC+AGFAFDAFDAFDC+DEGE<A+>GE<A+>GEC+<A>GL16FDC<A+L8AL16GFEFADFA>DC<A+AGFEDFA>DFADFADFADFA>DFAFDFD<B>D<G+BAG+L8C+EC+<AL16>DC<A+AL8O3FEE.DDC<A>D<A+G>C<AF+A+GEAF+DGEC+L2F+.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bach_III);
}

void loop(){
    play->touch();
}
