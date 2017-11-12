/*
 * C_Minor_II.ino
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

const char C_Minor_II[] PROGMEM = "MNT255L8O3C<D+DD+CD+DD+>C<D+DD+CD+DD+G+FEFCFEFG+FEFCFEFBFD+FDFD+FBFD+FDFD+F>C<GFGD+GFG>C<GFGD+GFG>D+<G+GG+D+G+GG+>D+<G+GG+D+G+GG+>D<F+EF+DF+EF+>D<F+EF+DF+EF+>D<GF+GDGF+G>D<GF+GDGF+G>C<EDECEDE>C<EDECEDE>C<FEFCFEF>C<FEFCFEFA+FD+FDFD+FA+FD+FDFD+FA+GFGD+GFGA+GFGD+GFGG+GFGD+GFGG+GFGD+GFGG+DCD<A+>DCDG+DCD<A+>DCC+G<A+G+A+>D+<A+G+A+>G<A+G+A+>D+<A+G+A+>FC<A+>C<A>C<A+>CFC<A+>C<A>C<A+>CFDCD<B>DCDFDCD<B>DCDFDCD<B>DCDFDCD<B>DCC+D+C<B>C<G+>C<B>CD+C<B>C<G+>C<B>C<F>D+DD+FD+DD+<F>D+DD+FD+DD+<F+>C<B>CD+C<B>C<F+>C<B>CD+C<B>CEC<B>C<G>C<B>CEC<B>C<G>C<B>CF+C<B>C<A>C<B>CF+C<B>C<A>C<B>CGC<B>CDC<B>CGC<B>CDC<B>CG+C<B>CDC<B>CG+C<B>CDC<B>CO0GB>DFG+FEFBF>D<BG+FEF<G>CD+G>C<GF+G>D+CGD+C<G+GG+<GA>F+>CD+C<B>CF+CAF+D+C<B>CP8>DCDD+C<B>C<A>C<B>CD<BABGBAB>C<AGAF+AGABGF+GD>GFGG+FD+FDFD+FGD+DD+CD+DD+FDCD<B>DCDD+C<B>C<G>C<B>C<A>FD+F<G>D+DD+<F>DCD<D+>C<B>C<AFD+FGD+DD+FDCDL16CEL8CDEGG+A+>C<A+G+GL4FL8GL16FECFL8GFEFGG+GFD+DD+FDD+EL4<B.L8DFG+GFBF>D<FBG+GFE>C+<A+G>C<G+FG+GA+GEG+FDFEGECFD<B>DDEGA+GG+>CFDFG+>C<B>C<GFDL2EE";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) C_Minor_II);
}

void loop(){
    play->touch();
}
