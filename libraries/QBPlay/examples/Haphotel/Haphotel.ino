/*
 * Haphotel.ino
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

const char Haphotel[] PROGMEM = "MNT255L4O3CCCCCDC<AFFF>FFGFL2D.L4DE.L8EL4DDCCC<BA+A+AGL2AP8L16>CL8C.L16CL4CCDC<AFFF>FFGFDFFDL2C.L4<AA+>DC<A+L1AP4L2>FL4FL1DP4L4FGFL1C.P4L4DF.L8FL4FFFDEFGFEDCCCCCCDC<AFFF>FFGFL2D.L8D.L16DL4EEDDC+C+CL8C.L16CL4<A+A+AGL2AL4>C.L8CL4CCDC<AFFF>FFGFDFFDL2C.L4<AA+>CDEL1FP4L4FFDL1C.L2<AA+>CDEL1F.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Haphotel);
}

void loop(){
    play->touch();
}
