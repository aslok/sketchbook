/*
 * Bachs_Prelude.ino
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

const char Bachs_Prelude[] PROGMEM = "MNT150L16O4C<B>C<G>C<B>C<EC<B>C<G>C<B>C<GO4C<B>C<G>C<B>C<AFEFCFEFD>DCD<A>DCD<BGF+GDGF+GE>EDE<B>EDEC<AG+AEAG+A>C<F+EF+>C<F+EF+BGFGBGFGBEDEBEDEAF+EF+AF+EF+ADCDADCDGEDEGEDEGC+<B>C+GC+<B>C+F+DC+DFDC+DGF+GDAGADBABD>C<B>C<D>D<F+GAB>DEGDGCG<B>G<AGF+EL8F+BL16>CD<BCL32ABL8AL16G.L4GP2L16>C<B>C<G>C<B>C<A<FEFCFEFF>BABFBABG+<EDE<B>EDE>AEDEAEDEG+DCDG+DCDAEDEAEDEBG+F+G+BG+F+G+>C<EBE>C<E>D<DBDADBD>C<CACG+CACB<B>GEL8>CL16<AL8BAG+.L16AA<AG+AEAG+A>E>EDE<B>EDECO2AG+AEAG+A>D>GFGDGFGEC<B>C<G>C<B>C<EC<B>C<G>C<B>CC>C<B>C<G>C<B>C<AFEFAFEFD>DCD<A>DCD<BGF+GBGF+GE>EDE<B>EDEC<AG+A>C<AG+AG>GFGDGFGEGEGFAFADFDFEGEGCECEDFDF<BGAB>C<EDCDG>C<GDL4BL8FL32E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bachs_Prelude);
}

void loop(){
    play->touch();
}
