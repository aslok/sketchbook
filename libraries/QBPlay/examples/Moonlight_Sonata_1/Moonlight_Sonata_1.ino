/*
 * Moonlight_Sonata_1.ino
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

const char Moonlight_Sonata_1[] PROGMEM = "MLT100L8O1C+O4C+E<G+>C+E<G+>C+E<G+>C+EO1BO4C+E<G+>C+E<G+>C+E<G+>C+EO1AO4C+E<A>C+EO1F+O4DF+<A>DF+O1G+O4CF+<G+>C+EO1G+O4C+D+<F+>CD+O1C+O3G+>C+<G+>C+E<G+>C+EG+C+L16EG+P64L8G+D+F+<G+>D+F+<G+>D+F+G+D+L16F+G+P64L8G+C+E<G+>C+EAC+F+<A>C+F+G+<B>E<G+B>EF+<B>D+B<B>D+E<B>E<G+B>E<G+B>E<G+B>EO2E>B>E<GB>E<GB>EG<BL16>EGP64L8G<B>F<GB>F<GB>FG<BL16>FGP64L8GCE<GB>E<G>C+EF+C+EF+<B>D<F+B>DG<B>C+E<B>C+F+<B>D<F+B>DF+<A+>E<F+A+>C+O1BO4DF+<B>DF+<B>D+F+BD+F+>C<EG<E>EG<G>EGA+EGBD+F+<B>D+F+<B>D+F+BD+F+>C<EG<E>EG<G>EGA+EGBD+F+<B>D+F+BDF<B>DFBC+G+<B>C+G+AC+F+<A>C+F+G<B>D<GB>DF+<A>D+<F+A>D+C+<F+AC+F+A>C+<F+G+C+FG+F+A>C+<A>C+F+C+F+A>C+<F+L16A>C+P64L8C+<G+BC+G+BC+G+B>C+<G+L16B>C+P64L8C+<F+AC+F+A>C<F+A>C+<F+A>D+<F+G+D+F+G+D+F+G+>D+<F+G+>E<G+>C+<EG+>C+D+<F+A>C+<EA+>C<CD+G+CD+ACD+F+CD+O1G+O4CD+<G+>CD+<A>CD+<F+>CD+O1G+O4EG+>C+<EG+>E<EG+>C+<EG+O1G+O3EG+>C+<EG+>E<EG+>C+<EG+<G+>AF+>C<A>D+CF+D+AF+>CO3E>C+<G+>EC+G+E>C+<G+>EC+<G+C+GEA+G>C+<A+>EC+GEA+<F+>C<A>D+CF+D+AF+CAD+CF+AD+F+CD+<A>C<F+AD+F+CD+<A>C<F+AD+F+C+F+A<G+>F+G+AG+F+D+F+AC+F+A<G+>F+G+AG+F+DF+AC+F+A<G+>F+G+AG+F+DF+AC+F+ACF+G+AG+F+C+E>C+<C+D>C+<D+A>C+<D+A>C+<D+G+>C<D+F+>C<EG+>C+<G+>C+E<G+>C+EG+C+L16EG+P64L8G+D+F+<G+>D+F+<G+>D+F+G+D+L16F+G+P64L8G+C+E<G+>C+EAC+F+<A>C+F+G+<B>E<G+B>EF+<B>D+B<B>D+E<B>E<B>EG+<B>EG+BEL16G+BP64L8BF+A<B>F+A<B>F+ABF+L16ABP64L8BEG+<B>EG+>C<F+G+>C+<EG+F+G+>C+<EG+>D+<F+G+D+F+G+>E<G+>C+<EG+>C+D<F+ADF+A>C<F+G+<B>F+G+>C+<EG+C+EG+C+FG+>C+<FG+>D<F+AC+F+AC+F+A>C<F+A>C+<FG+C+FG+C+FG+>C+<FG+>D<F+AC+F+AC+F+A>C<F+A>C+<FG+C+FG+>C+<F+AC+F+ABF+A<B>F+A<B>F+ABEG+AEG+AD+F+G+D+F+G+C+EF+C+D+<G+>C+D+G+C+D+AC+D+G+C+E<G+>C+EG+CD+<G+>CD+C+<G+>C+<G+>C+E<G+>C+EO2G+O4C+L16EO2G+L8CO4D+F+<G+>D+F+<G+>D+F+O2G+O4D+L16F+O2G+L8C+O4EC+G+E>C+<G+>EC+O2G+O5EL16C+O2G+L8<G+O5D+<A<C>F+AD+F+<A<G+>G+L16F+<G+L8C+O4EC+G+E>C+<G+>EC+O2G+O5EL16C+O2G+L8<GO5CD+<A>C<F+AD+F+<A<G+>G+L16F+<G+L8C+>G+>C+EC+<G+C+EG+>C+<G+E<C+>C+EG+EC+<G+>C+<G+EG+EL2C+P64C+P64L1C+P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Moonlight_Sonata_1);
}

void loop(){
    play->touch();
}
