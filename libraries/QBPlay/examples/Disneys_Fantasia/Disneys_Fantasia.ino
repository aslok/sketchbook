/*
 * Disneys_Fantasia.ino
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

const char Disneys_Fantasia[] PROGMEM = "MNT150L16O4GD<B>DGP16GECEGP16GD<B>DGP16GC<A>CGP16GF+GD<B>DGF+GECEGF+GD<B>DGF+GC<A>CGF+GD<B>D<GAB>CDEF+EF+C<A>C<GAB>CDL32EF+L16GF+GD<B>D<GAB>CDEF+EF+C<A>C<GAB>CDL32EF+L16GD<B>DGP16GECEGP16GD<B>DGP16GC<A>CGP16GF+GD<B>DGF+GECEGF+GD<B>DGF+GC<A>CGF+GD<B>D<GAB>CDEFEFC<A>C<GAB>CDL32EFL16GFGD<B>D<GAB>CDEFEFC<A>C<GAB>CDL32EFL16EDEC<B>C<GAB>CDEDCD<BABGAB>CDL32EFL16EDEC<B>C<GAB>CDEDCD<BABGAB>CD<B>C<B>C<AF+ADEF+GAL32B>CL16<BABGF+GDEF+GAB>C<B>C<AF+ADEF+GAL32B>CL16<BABGF+GDEF+GABAGAF+CF+<AB>CDEF+GF+GDCD<B>CDEF+GAGAF+CF+<AB>CDEF+GF+GDCD<B>CDEF+GF+EF+C<A>C<GAB>CDL32EFL16GF+GD<B>D<GAB>CDEF+EF+C<A>C<GAB>CDL32EFL16GF+GD<B>D<GAB>CDL32EFL16GE<G>EGP16FD<G>DFP16EC<G>CEP16D<BGB>DP16GFGE<G>EFEFD<G>DEDEC<G>CDCD<BGB>C<B>C<AGA>C<B>C<AGA>C<B>C<AF+A>C<B>C<AF+ABABAGABABGF+GBABGEGBABGDGA+AA+GC+G>EDE<GC+GAGAGC+GA+AA+GC+GF+EF+DCDGF+GD<B>DAGAECEBABF+DF+>C<B>C<GEG>DCD<AF+A>EDE<BGB>F+EF+C<A>CGD<BGB>DGEC<G>CEGD<BGB>DF+C<AGA>CG<GB>DGAB<B>DGB>CD<DGB>DF+GF+GD<B>D<GF+G<GB>DGF+GD<B>D<GF+G<GB>DGF+GD<B>D<GAB>CDEF+EDEF+GAGF+GAB>C<GA>CDF+<GAB>CDEF+EDEF+GAGF+GAB>C<GA>CDF+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Disneys_Fantasia);
}

void loop(){
    play->touch();
}
