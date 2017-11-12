/*
 * NOM_6_in_E_by_Bach.ino
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

const char NOM_6_in_E_by_Bach[] PROGMEM = "MNT150L16O5ED+L8E<BG+BL16EF+ED+L8E<BG+BL16EBF+BG+BABG+BF+BE>ED+C+<B>ED+C+<BAG+F+EBF+BG+BABG+BF+BE>ED+C+<B>ED+C+<BAG+F+EF+G+AB>C+D+EF+G+AF+G+BEF+G+AB>C+D+EC+D+E<BABG+BABG+BF+BE>ED+C<BE>C+<EBEAEG+BF+BG+BABG+BF+BE>ED+C+<BE>C+<EBEAEG+EEED+EEEF+ED+EEEG+EF+EG+EAEF+EG+EEED+EEEF+ED+EEEG+EF+EG+EAEF+EG+EG+EG+EG+EG+EG+EG+EG+D+G+EG+D+G+EG+D+G+EG+DG+EG+DG+EG+DAEAC+AEAC+AEAC+AEA<B>AEA<B>AEA<B>G+EG+<B>G+EG+<B>G+EG+<B>G+EG+<A>G+EG+<A>G+EG+<A>F+EF+<A>F+EF+<A>F+EF+<A>F+EF+<G+>F+EF+<G+>F+EF+<G+>EEE<G+>EEE<G+>EEE<G+>EEE<F+>EEE<F+>EEE<F+>D+ED+<F+>D+ED+<F+>D+ED+<F+EF+EF+G+BEF+G+BEF+G+AG+AB>E<G+AB>E<G+AB>C+<B>C+DG+<B>C+DG<B>C+DBG+ED<BG+EDC+D<B>C+D+C+D+FG+C+D+FG+C+D+FF+FF+G+>C+<FF+G+>C+<FF+G+AG+AB>F<G+AB>F<G+AB>G+FC+BG+AF+FG+C+<BA>C+<AF+>F+D+EC+CD+<G+F+EG+EC+EG+>C+<G+>EC+G+C+CD+C<G+>G+GG+GG+D+EC+CD+C<G+>F+FF+FF+D+EC+CD+C<G+AG+AG+AD+EC+CF+C+F+D+F+C+F+CF+D+F+<G+>F+>D+<F+>C<F+>D<F+>C<F+>D+<F+<G+>E>C+<E>E<E>C+<E>E<E>C+<E<G+>F+>D+<F+>C<F+>D+<F+>C<F+>D+<F+<G+>E>C+<E>E<E>C+<E>E<E>C+<E<G+>G>C+<G>E<G>C+<G>E<G>C+<G<G+>G>C+<G>E<G>C+<G>E<G>C+<G<G+>G+>C+<G+>D+<G+>C+<G+>D+<G+>C+<G+<G+>F+>C<F+>D+<F+>C<F+>D+<F+>C<F+C+>C+<BAG+>C+<G+F+EG+ED+C+>C+<G+F+EG+ED+C+EC+<BA+>F+>C+<F+>E<F+>C+<F+>E<F+>C+<F+<A+>F+>E<F+>C+<F+>E<F+>C+<F+>E<F+<BO4BA+G+F+BF+ED+F+D+C+<B>BF+ED+F+D+C+<B>D+<BAG+>DEDG+DBDG+DED<G+>DED<G+>D<F+>D<G+>D<E>DC+EAG+AEDEC+E<B>E<A>AG+F+E<A>F+<A>E<A>D<A>C+E<B>EC+EDEC+E<B>E<A>AG+F+E<A>F+<A>E<A>D<A>C+<AAAG+AAABAG+AAA>C+<ABA>C+<A>D<ABA>C+<AAAG+AAABAG+AAA>C+<ABA>C+<A>D<ABA>C+<A>C+<A>C+<A>C+<A>C+<A>C+<A>C+<A>C+<G+>C+<A>C+<G+>C+<A>C+<G+>C+<A>C+<G>C+<A>C+<G>C+<A>C+<G>D<A>D<F+>D<A>D<F+>D<A>D<F+>D<A>D<E>D<A>D<E>D<A>D<E>C+<A>C+<E>C+<A>C+<E>C+<A>C+<E>C+<A>C+<D>C+<A>C+<D>C+<A>C+<DBABDBABDBABDBABC+BABC+BABC+AAAC+AAAC+AAAC+AAA<B>AAA<B>AAA<B>G+AG+<B>G+AG+<B>G+AG+<BABAB>C+E<AB>C+E<AB>C+DC+DEAC+DEAC+DEF+EF+G>C+<EF+G>C+<EF+G>EC+DEC+<A+B>C+<A+F+EDC+<B>C+DF+<B>C+DF+<B>C+DEDEF+BDEF+BDEF+G+F+G+A>D+<F+G+A>D+<F+G+A>F+D+EF+D+CC+D+C<G+F+F>BG+ABG+FF+G+FC+<BAO5C+<AB>C+<AF+G+AF+DC+<BO5D<B>C+D<BG+ABG+FG+C+D+C+D+FG+C+D+FG+C+D+FF+FF+G+BFF+G+BFF+G+AG+AB>D<G+AB>D<G+AB>D<BG+FBG+FC+BAG+F+G+AF+<B>AG+F+C+G+F+FDEF+D<G+>F+ED<A+>EDC+<B>C+D<BF>DC+<BF+>C+<BAG+ABAG+BABG+BF+BFF+G+ABF>D<F>C+<FBFF+AF+C+<A>C+F+C+AC+F+C+FG+FC+FG+>C+<G+>FC+G+<BA>C+<AF+A>C+F+C+AF+>C+<F+FG+FC+>C+CC+CC+<G+AF+FG+FC+BA+BA+BG+AF+FG+FC+DC+DC+D<G+AF+FG+>C+BBG+AF+FG+C+<BA>C+F+>C+C+<ABGF+ADC+<B>D<GF+FG+C+<BA>C+F+G+AF+BF+>C+<F+>D<F+C+F+G+FF+AG+AAAG+AF+AEAD+AEAF+AG+AAAF+AG+AG+F+E>ED+EC+E<B>E<A+>E<B>EC+ED+EEEC+ED+ED+C+<B>C+D+EF+G+AF+B<BABG+BF+BEBDBC+EF+G+AB>C+DEF+G+EA<AG+AF+AEAD+AC+A<B>D+EF+G+AB>C+D+EF+D+G+<EDEC+E<B>E<A>E<G+>E<A>E>C+<B>C+EAG+AF+C+EO2B>F+>D+C+D+F+AG+AF+D+F+O2B>G+BAB>EG+F+G+E<B>EO2B>A+>C+<B>C+EA+G+A+EC+ED+BA+G+F+BF+ED+F+D+C+<B>BAG+F+AF+ED+F+D+C+<B>AG+F+EG+ED+C+EC+<BA>G+F+ED+F+D+C+<B>D+<BAG+>EC+<BA>C+<AG+F+AF+ED+F+A>C+<B>D+F+G+AG+AF+G+EG+B>E<BG+E<B>E>ED+E<BG+EDEC+EDE<B>EC+EAEC+E<B>EC+E<A>E<B>EG+E<B>E<A>E<B>E<G+>E<A>EF+ED+EEEF+EG+EL4A.L8BL4G+L16O2AO4AG+L32AF+F+G+F+G+F+G+F+G+F+G+F+G+L8EL16E>ED+C+<B>E<A>E<G+>E<F+>E<EED+C+<B>E<A>E<G+>E<F+>E<EG+B>D+EG+B>D+L8E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) NOM_6_in_E_by_Bach);
}

void loop(){
    play->touch();
}
