/*
 * Solfe_by_Bach.ino
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

const char Solfe_by_Bach[] PROGMEM = "MNT150L16O2D+CD+G>CD+DC<BGB>DGFD+DD+CD+G>CD+DCDC<BAGFD+DD+CD+G>CD+DC<BGB>DGFD+DD+CD+G>CD+DCDC<BAGFD+DD+C<GD+CO5C<GD+G+O2FA>CFG+>CD+D<A+FD<A+O4A+FDGO2D+GA+>D+GA+>DC<AG+A>C<AG+A>D+C<GA>D+C<GA>DC<F+A>AC<F+A>F+C<DA>C<AF+DA+O1GA+>DGA+AGF+DF+A>DC<A+AA+GA+>DGA+AGAGF+EDC<A+AA+GA+>DGA+AGF+DF+A>DC<A+AA+GA+>DGA+AGAGF+EDC<A+AA+GA+>DGD<A+G<FO4GD<BGB>DGC<G>G<G>C<G>G<GBG>F<GBG>F<G>D+CD+G>C<GD+CO2A+O5C<GECEG>C<FC>C<CFC>C<CECA+CECA+CG+O1FG+>CFG+GFECEG>C<A+G+GG+FG+>CFG+GFGFEDC<A+G+GG+FG+>CFG+GFECEG>C<A+G+GG+FG+>CFG+GFGFEDC<A+G+GG+>FC<G+F>C<G+FCG+FC<G+>FC<G+L2C+L16O4G+FEFGFEFL2O2CL16>G+FEFGFEFL2O1BL16O5D<FGG+GFD+DD+G>C<GA+G+GFL4D+DL16C<G>G<G>C<G>G<GBG>F<GBG>G<GA+G>E<GA+G>E<GA>D+>C<D+<A>D+>C<D+<G+F>D<FG+F>D<FG>C+A+C+<G>C+A+C+<F+D+>C<D+F+D+>C<D+D+>C>C<C<D+>C>C<C<D+>CD+G>CGD+CGD+CO3G>FD<BFD+<CD+G>CD+DC<BGB>DGFD+DD+CD+G>CD+DCDC<BAGFD+DD+CD+G>CD+DC<BGB>DGFD+DD+CD+G>CD+D<B>C<GD+DC<GD+DC.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Solfe_by_Bach);
}

void loop(){
    play->touch();
}
