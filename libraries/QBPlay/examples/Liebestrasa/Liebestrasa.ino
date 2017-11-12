/*
 * Liebestrasa.ino
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

const char Liebestrasa[] PROGMEM = "MNT150L8O2DB>DGBGD<B>DGBGD<B>D+F+BF+D+<B>D+F+BL16<B.L32>F+L8D+<B>DG+BL16<B.L32>G+L8DCDG+>CL16O2B.L32>G+L8D<B>C+EAEC+<E>C+EAL16<E.L32>EL8C+<EL16>EC+L8<F+L16>F+C+L8<GL16>GC+L8<B>DF+BL16<A.L32>F+L8D<GB>DGD<BGB>DGL16<D.L32>DL8<BB>DGBGD<B>DGBGD<B>D+F+BF+D+<B>D+F+BL16<B.L32>F+L8D+<B>DG+BL16<B.L32>G+L8DCDG+>DL16O2B.L32>G+L8DEA>C+EC+<A<E>C+EAL16<E.L32>EL8C+<E>C+<F+>C+<G>C+<B>DF+BL16<A.L32>F+L8D<GB>DGD<BGB>DGD<BL2>G.L8<DB>DGBGD<B>DGBGD<B>D+F+BF+D+<B>D+F+BL16<B.L32>F+L8D+<B>DG+BL16<B.L32>G+L8DCDG+>CL16O2B.L32>G+L8D<B>C+EAEC+<E>C+EAL16<E.L32>EL8C+<EL16>EC+L8<F+L16>F+C+L8<GL16>GC+L8<B>DF+BL16<A.L32>F+L8D<GB>DGD<BGB>DGL16<D.L32>DL8<BB>DGBGD<B>DGBGD<B>D+F+BF+D+<B>D+F+BL16<B.L32>F+L8D+<B>DG+BL16<B.L32>G+L8DCDG+>DL16O2B.L32>G+L8DEA>C+EC+<A<E>C+EAL16<E.L32>EL8C+<E>C+<F+>C+<G>C+<B>DF+BL16<A.L32>F+L8D<GB>DGD<BGB>DGD<BL2>G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Liebestrasa);
}

void loop(){
    play->touch();
}
