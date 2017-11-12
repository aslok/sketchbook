/*
 * Chopin_1.ino
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

const char Chopin_1[] PROGMEM = "MNT100L1O1G+L16C+.>G+.>C+.E.C+.<G+.C+.G+.>C+.E.C+.<G+.C+.G+.>C+.E.C+.<G+.C+.G+.>C+.E.C+.<G+.C+>G+AG+GG+>C+ED+C+D+C+CC+EG+O2C+>G+AG+GG+>C+ED+C+D+C+CC+EG+P16<A>C+D+F+A>C+D+BAG+F+ED+F+C+CD+<AG+F+AED+F+C+CD+<AG+BA<C+>G+AG+GG+>C+ED+C+D+C+CC+EG+O2C+>G+AG+GG+>C+ED+C+D+C+CC+EG+D+ED+DD+BA+G+G>ED+C+<BA+G+GA+G+BDED+G+<A+>C+<B>D+<GA+G+GG+G+>G+CC+<F+>F+CC+<F>FCC+<F+>F+CC+<C+>C+<F+AD+>D+<F+AE>E<G+BG+>G+<B>E<G+>G+CC+<F+>F+CC+<F>FCC+<F+>F+CC+<F>F<B>D+<F+>F+<B>D+<A>A<B>E<G+>G+<B>E<G+>G+CC+<F+>F+CC+<F>FCC+<F+>F+CC+<C+>C+<F+AD+>D+<F+AE>E<G+BG+>G+<B>E<G+>G+CC+<F+>F+CC+D+>D+<F+AC+>C+<F+AC+>C+<D+F+C>C<D+F+C>C<D+F+C>C<D+F+C>C<D+F+<B>BD+F+<B>BD+F+<A+>A+D+F+<A+>A+D+F+<A>AD+F+<A>AD+F+<A>AD+F+C>C<D+F+<B>BD+F+<B>BD+F+<A+>A+D+F+<A+>A+D+F+<A>AD+F+<A>AD+F+<G+>G+D+F+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Chopin_1);
}

void loop(){
    play->touch();
}
