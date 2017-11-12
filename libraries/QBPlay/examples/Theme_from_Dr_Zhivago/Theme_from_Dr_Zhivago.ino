/*
 * Theme_from_Dr_Zhivago.ino
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

const char Theme_from_Dr_Zhivago[] PROGMEM = "MNT150L2O2AL4BL2>CL4EL2D.E.<AL4BL2>CL4EDL8GAL4FL2E.DL8DEL2DL4<AL2>C.C.<BL4>CL2<BL8GEL1A.L2>EL4GAEL8CDL4EC<GL2AL8>DCL4<B>FL8EDL4C<AL8>DC<B>FEDC<BL2BL8GBL2AL4BL2>CL4EL2D.E.<AL4BL2>CL4EDL8GAL4FL2E.DL8DEL2DL4<AL2>C.C.<BL4>CL2<BL8GEAB>CDEGL1AP8L8D.L16CL4<A+L8A+.L16AL4GL8A+.L16A+L4AL2D+L8>C.L16<A+L4AL8>D+.L16DL4DL8<A+.L16AL2G.L8>D.L16CL4<A+L8A+.L16AL4GL8>D.L16DL4D+L2<AL8F+.L16GL4AL8>C.L16CL4D+L8D.L16CL2D.L8C.L16CL2FL4C.L8D+L2D.L8<A.L16AL2>CL4<G.L8>CL2D.L8D.L16DL2GL4D.L8DL2D+L4<GL8A+.L16A+L2>DL4<GL8G.L16GL2A.L8>D.L16CL4<A+L8A+.L16AL4GL8A+.L16A+L4AL2D+L8>C.L16<A+L4AL8>D+.L16DL4DL8<A+.L16AL1GP8L8DA+AF+G>D+L4D.<A.L8G>D+DC<B>G+L2G.L8GG+GFD+<G>D+FD+DCC<B>DD+L4F.L8CDEL4F+.L8<DA+AGF+>D+L4D.<A.L8G>D+DC<B>G+L2G.L8GG+GFD+<G>D+FD+DCC<B>DD+L4F.L8CDEL4F+.<B.>DL8A+L2B.L8F+AGL4DL8C+L2C.L4C.DL8EL2F+.L8EDC+L4DL8>CL2<B.L4<B.>DL8A+L2B.L8F+AGL4DL8C+L2C.L4C.DL8EL2F+.L8EDC+L4DL8>CL2<B.L4E.L2G.L8AGF+L4G.E.L2D.L4D.L2FP8L8F+GF+GL4A.A+.L2>C.L4O2B.>DL8A+L2B.L8F+AGL4DL8C+L2C.L4C.DL8EL2F+.L8EDC+L4DL8>CL2<B.L4<B.>DL8A+L2B.L8F+AGL4DL8C+L2C.L4C.DL8EL2F+.L8EDC+L2C.L4F+.L1G.L4O1B.>DL8A+L2BP8L16<GGL1G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_Dr_Zhivago);
}

void loop(){
    play->touch();
}
