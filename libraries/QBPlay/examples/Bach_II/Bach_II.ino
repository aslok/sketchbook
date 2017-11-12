/*
 * Bach_II.ino
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

const char Bach_II[] PROGMEM = "MNT200L8O3FC<AGA>C<FA>CD+DCD<A+FEFA+DFA>C<A+AA+GEDEGCEGA+AGAGFEFACEFAGF<FD<BAB>D<GB>DFEDO3C<GEDEGCEGA+AG<GEC+<B>C+E<A>C+EGFEO3D<AFEFADFA>C<A+AA+GEDEGCEGA+AGAFDC+DF<B>DFAGFGEC+<B>C+E<A>C+EGFED<AFEFADFA>C<A+A>D<A+GF+GA+DGA+>DC+<B>C+<A+GFGA+DG>CEDC>D<AFEFADFA>C<A+A>FD<A+AA+>D<FA+>DFED<D<BG+F+G+BEG+B>DC+<BO3AEC+<B>C+E<A>C+EGF+E<C<AF+EF+ADF+A>C<BAO3GD<BAB>D<GB>DFD+DD+C<AGA>C<FA>CD+DCD<A+GF+GA+D+GA+>DC<A+>C<AF+EF+ADF+A>C<A+AGD<A+AA+>D<GA+>DFEDC<GEDEGCG>CEDCFC<AGA>C<F>CFAGFAAFEFADFA>C<A+AG>D<A+AA+>D<GA+>DFEDEGEDEGCEGA+AG>C<AFEFADFA>C<A+AA+GEDEGCEGA+AGAFC<A+>CF<A>CD+GFD+<FD<A+AA+>D<FA+>DFEDEC<A+AA+>E<GA+>EGFEAGFEFADFD<A+G>EF<A+AGAA+L2E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bach_II);
}

void loop(){
    play->touch();
}
