/*
 * Invention_14_by_Bach.ino
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

const char Invention_14_by_Bach[] PROGMEM = "MNT100L32O3A+>CDCL16<A+>FDA+FDL32FD+DD+L16F<A+>D<FG+GL32D+FGFL16D+A+G>D+<A+GL32A+G+GG+L16A+D+GCD+<AL32>CDD+DL16CAF>C<A>D+L32<FGAGL16F>C<A>FCL4DP4P16L32GFD+FL16GL8CP8P16L32FD+DD+L16FL8<A+P8P16L32D+DCDL16D+AL32>C<A+AA+L16>CL8<FP8>F<FA>CL4FP4P8L8<FA+>DL4FP4P8L8<GA+>CL4EP4P16L32<FGAGL16F>C<A>FCAL32D+DCDL16D+<A>C<F+AL8A+>D<A+GG+>F<AFL16GL32CDD+DL16CGD+>C<G>DL32<G+GFGL16G+DF<B>GL8D+P8P16L32CDD+DL16CL8>C.L16<A+G+L32FGG+GL16FL8>F.L16D+DL32<A+>CDCL16<A+L8>A+.L16G+GL32A+G+GG+L16A+D+L32GFD+FL16GCL32D+DCDL16D+<AL32>CDD+DL16CFL32<G+GFGL16G+GL32A+>CDCL16<A+>D+L32<GFD+FL16GFL32AA+>C<A+L16A>DL32<FD+DD+L16FD+L32GAA+AL16G>CL32<D+DCDL16D+DP8P16L32A+>CDCL16<A+>FDA+FDL32FD+DD+L16F<A+>D+<A+>D+<GL32D+FGFL16D+A+G>D+<A+GL32A+G+GG+L16A+L8D+>D+L16D+L32D+DCDL16D+L8<D+>D+L16D+L32CDD+DL16CFL32DC<A+>CL16D<FA+>C<G+L2A+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Invention_14_by_Bach);
}

void loop(){
    play->touch();
}
