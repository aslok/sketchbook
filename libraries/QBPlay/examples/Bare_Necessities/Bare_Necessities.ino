/*
 * Bare_Necessities.ino
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

const char Bare_Necessities[] PROGMEM = "MNT200L4O2CDFP4L2AL4G+AL8GL4F.FGFGFGL8FL4D.CF.L8CL4FA>DC<A+AL1GP4L4>CDCP4L2DL4CDL8CL4<A.FGFGF>DL8<FL4F.GA.L8>CL4<A>C<AFDCL1FP4L4FL8E.L16EL4DL2CG.L4GL8G.L16FL4EL1FP4L4FL8E.L16EL4DL2CG.L4GFGL1AP4L4AA+>CL8DDL2DL4<A+AGAA+>CDC<AGAA+>CL8DDL2DL4<A+AGFEL1F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bare_Necessities);
}

void loop(){
    play->touch();
}
