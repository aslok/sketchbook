/*
 * Star_Trek_TOS_Theme.ino
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

const char Star_Trek_TOS_Theme[] PROGMEM = "MNT255L1O4B.D.F.<A.P8L2GL8G>C.L2FFL4E.L8EL4C<A>DL2GP8L4GL1BP4L2CL8CF.L2A+A+L4A.L8AL4FDGL2>CP8L4CL1EP1L2O3G>F.L4EDC<BL2A+L1A+L2G>G.L4FEDCL2<BL1BL4A+L2A.L4B>C+DEF+GL2AL1A+.L2<A+.L4>CDD+FGG+L2A+L1BL2<G>F.L4EDC<BL2A+L1A+L4G+L2G>G.L4FEDCL2<BL1BL4A+L2A.L4B>CDEFEL2G.L4GL2A+.L4AL2GL1CL4D.F.A.L1>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Star_Trek_TOS_Theme);
}

void loop(){
    play->touch();
}
