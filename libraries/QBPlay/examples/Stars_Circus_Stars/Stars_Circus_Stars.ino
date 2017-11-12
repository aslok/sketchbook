/*
 * Stars_Circus_Stars.ino
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

const char Stars_Circus_Stars[] PROGMEM = "MST255L2O3D+L4D.L8D+CP8L2D+P16L4FF+GG+AA+P4L2<A+L4>GP8L8GL4GGGP8L8GL4G+G+L8FEFGL4FD+L16D+L4DCD<A+>A+P8L8A+L4A+A+A+P8L8A+L4BBL8>C<B>CD+L4DCL2<B.L4BA+P8L8A+L4>D+P8L8CL4<A+AA+GFP16L8<A+AA+AL4A+>FP16L8<A+AA+AL4A+>A+P8L8A+L4>D+P8L8CL4<A+AA+F+FP16L8<AGAGL4AA+P4>A+.L8G+L2GL4>C.L8<A+L2DC<A+>G+GL4F.L8GG+P8L2>CL4D+L2FD+P32L1<GL2FP32L4A+.L8G+L2GL4>C.L8<A+L2DC<A+>G+GL4F.L8GL4G+>CF.P32L8D+L4<GA+D+.P32L8GL1FL4D+P4L2D+L4C+CL2CL4<B>CL1C.L4<B>CL2CL4<B>CL2D+L4C.L8D+L1C+L2<A+A+A+L4AA+L2A+L4AA+L1>C+.L4C<A+>CL2D+.F.L4FL1<A+.L2>D+D+L4C+CL2CL4<B>CL1C.L4<B>CL2CL4<B>CC+C<A+.L8GL1A+L2G+G+G+L4GG+L2BL4A+G+L1>G+.L4<G+A+>CL8D+P8L4<G+A+>CL8D+P8L4<D+F>CL1<A+L4G+P4<G+G+G+L8GP8L4GL8FP8L4FEO3FEO1FEO3FGL2EL4<CCCL8<A+P8L4A+L8G+P8L4G+GO3G+GO1G+GO3G+A+L2GL8<D+GA+>C+L4E.L8EL4EEED+DC+C<BA+AG+F+L8FA>CD+L4F+.L8F+L4F+F+F+FED+DC+C<BA+G+L8GA+>D+GL4A+.L8A+L4A+A+A+A+L8<GA+>D+GL4A+.L8A+L4A+A+A+A+L8<GA+>D+GL4A+.L8A+L4A.L8AL4G+.L8G+L4G.L8GL4F+.L8F+L4F.L8FL4ED+FD+L2D+L4C+CL2CL4<B>CL1C.L4<B>CL2CL4<B>CL2D+L4C.L8D+L1C+L2<A+A+A+L4AA+L2A+L4AA+L1>C+.L4C<A+L8>CP8L2D+.F.L4FL1<A+.L2>D+D+L4C+CL2CL4<B>CL1C.L4<B>CL2CL4<B>CC+C<A+.L8GL1A+L2G+G+G+L4GG+L2BL4A+G+L1>G+.L4<G+A+>CL8D+P8L4<G+A+>CL8D+P8L4<D+F>CL1<A+L4G+P4L32A+B>CC+DD+EFF+GL16G+P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Stars_Circus_Stars);
}

void loop(){
    play->touch();
}
