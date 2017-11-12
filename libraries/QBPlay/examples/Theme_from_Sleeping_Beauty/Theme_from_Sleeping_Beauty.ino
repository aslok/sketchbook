/*
 * Theme_from_Sleeping_Beauty.ino
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

const char Theme_from_Sleeping_Beauty[] PROGMEM = "MNT200L2O3C.<B.>CL4<AB>C<AL2BL4>DL2EL4C+L2D.D.G.F+.FL4DFEDL2AL4GL2FL4EEDC+DABL2>C.<B.>CL4<AB>C<AL2BL4>DL2DL4C+L2D.D.EFF+AGB>C<BAL4GL8F+GBAGEDED<BGP8L2>GAL4BL8>CP8<D+EFEGP8C+DEDEP8<B>CDCEDC<B>C<AGP8>F+GAGBAGF+GD+EP8L2GAL8B>CP8<D+EFEGP8C+DEDEP8<B>CDCEDC<BAGF+P8>FF+GF+BAGF+EDGFEDEDC<B>C<BAGL2>C.<B.>CL4<AB>C<AL2BL4>DL2EL4C+L2D.D.G.F+.FL4DFEDL2AL4GL2FL4EEDC+D<ABL2>C.<B.>CL4<AB>CC+L2DL4<AL2>EL4C+L8FP8O2A>C+DFAG+A>C+DFL2G+AB>DCEFEDL4CP4L8O3D+EF+GB>CL2EL32<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C<E>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_Sleeping_Beauty);
}

void loop(){
    play->touch();
}
