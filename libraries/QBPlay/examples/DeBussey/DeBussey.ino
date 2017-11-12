/*
 * DeBussey.ino
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

const char DeBussey[] PROGMEM = "MNT150L8O2G+L2>G+L4F.L8<G+>D+FL2D+.L8<G+>C+D+C+.L4F.L8C+.<F+>CC+L2C.L8<D+A+>C<A+>D+<A+G+A+G+DF+G+L4F+.F.L8<A+>FF+FA+FD+FD+<A+>C+D+L4C+.L8C.<G+.C+>G+>G+L4>G+.F.L8O2C+O4D+FL2D+.L8O2C+O4C+D+L4G+.F.L8O2C+O4D+FL4D+.C+.L8O2G+O4C+D+A+.L4G+.L8F.O2A+O4D+FD+.L4C+.L8<A+.L4O1D+.L8O5F.O3A+.O5D+P64D+P64D+C+P64C+P64C+CP64CP64C.C+.L4<A+.O1A+.L8O5F.O3A+P64O5F+FD+FD+C+D+C+C.L16D+L8C+.L4<A+.O2G+.L8O4F+.G+.>C.<A+.F+.L4O2A.L8O4F+P64F+P64F+P64F+G+L4F+.O2A+.L8O4F+.G+.>C+.<A+.F+.L4O2C.L8O4F+P64F+P64F+P64F+G+L4F+.O2D+.L8O4F+.G+.L4>D+.L8<A+.L4O2D+.P64L8O4A+P64A+P64A+P64A+>C<A+>C+D+L16<G+>C+L2G+.L32<G+>C+L4G+.L16<G+>C+L2G+.L32O3G+>C+L4G+.P4L2<G+.L4B.L8>C+L2<G+.L4B>C+L8D+L4F.C+L8FGFL4C+L8<FC+.<A+.L4>A+.>CL8FL4<A+.>CL8FL2F+L8F.D.D+.L2A+.L4G+.P64L2G+.L4BL8>C+L4<G+.BL8F+P4C+.L16<C+G+EL8>E.L16<E>C+<G+L8>G+.L16<G+>E<BL4>G+.L2F+.P64F+.L4AL16>C+<C+L2<F+.L4AL8>C+ED+C+<B.L4AL8G+F+ED+C+<BAG+G+F+EP4L2>D+.L4F+L8A+L2D+.L4F+A+L8>FEL4<A+.G+.L8A+>FD+L4<A+.G+.L2>D+.L4F+L8A+L2D+.L4F+L8A+L1>D+.L4C+.D+.P4L16O2FG+>CFG+>CL4G+.L2FL8D+FL1D+L8C+D+C+.L4F.L8C+.CC+L2C.P8L8<A+>C<A+>D+<A+G+A+L4G+L8F+G+L4F+.L2FP64L8FF+FA+FD+FD+D+C+D+L4C+.L8C.<F.P8<G+>G+>G+L4>G+.F.O2C+.L8O4D+FL2D+.L4O2G+.L8O4C+D+L4G+.F.L8O2A+O4D+FL4D+.C+.O1FL8O3C+D+L4A+.F.L8O1C+D+L4A+.F.D+L8O3F+G+L4>C+.<A+.L8O1G+.O3A+>CL4F.<G+.L16O1C+G+>C+FG+>C+O1F>CFG+>CFO1C+G+>C+FG+>C+O1F>CFG+>CFL4B.>C+.L16O2C+G+>A+FG+>C+O2F>CFG+>CFO2C+G+>C+FG+>C+O2F>CFG+>CFL4B.>C+.<B.>C+.F.L1G+L16<G+>C+FL2G+.P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) DeBussey);
}

void loop(){
    play->touch();
}
