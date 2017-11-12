/*
 * Clavier_by_Bach.ino
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

const char Clavier_by_Bach[] PROGMEM = "MNT100L16O2CEG>CE<G>CE<CEG>CE<G>CE<CDA>DF<A>DF<CDA>DF<A>DFO1B>DG>DF<G>DFO1B>DG>DF<G>DF<CEG>CE<G>CE<CEG>CE<G>CE<CEA>EA<A>EA<CEA>EA<A>EA<CDF+A>D<F+A>D<CDF+A>D<F+A>DO1B>DG>DG<G>DGO1B>DG>DG<G>DGO1B>CEG>C<EG>CO1B>CEG>C<EG>CO1A>CEG>C<EG>CO1A>CEG>C<EG>CO1DA>DF+>C<DF+>CO1DA>DF+>C<DF+>CO1GB>DGBDGB<GB>DGBDGB<GA+>EG>C+<EG>C+O1GA+>EG>C+<EG>C+O1FA>DA>D<DA>DO1FA>DA>D<DA>DO1FG+>DFBDFB<FG+>DFBDFB<EG>CG>C<CG>CO1EG>CG>C<CG>CO1EFA>CF<A>CF<EFA>CF<A>CF<DFA>CF<A>CF<DFA>CF<A>CFG<DGB>F<GB>FG<DGB>F<GB>F<CEG>CE<G>CE<CEG>CE<G>CE<CGA+>CE<A+>CE<CGA+>CE<A+>CEF<FA>CE<A>CEF<FA>CE<A>CEF+<CA>CD+<A>CD+F+<CA>CD+<A>CD+G<D+B>CD+<B>CD+G<D+B>CD+<B>CD+G+<FB>CD<B>CDG+<FB>CD<B>CDG<FGB>D<GB>DG<FGB>D<GB>DG<EG>CE<G>CEG<EG>CE<G>CEG<DG>CF<G>CFG<DG>CF<G>CFG<DGB>F<GB>FG<DGB>F<GB>FG<D+A>CF+<A>CF+G<D+A>CF+<A>CF+G<EG>CG<G>CGG<EG>CG<G>CGG<DG>CF<G>CFG<DG>CF<G>CFG<DGB>F<GB>FG<DGB>F<GB>FC<CGA+>E<GA+>EC<CGA+>E<GA+>EC<CFA>CFC<A>C<AFAFDFDCB>GB>DFD<B>D<BGBDFEDL1C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Clavier_by_Bach);
}

void loop(){
    play->touch();
}
