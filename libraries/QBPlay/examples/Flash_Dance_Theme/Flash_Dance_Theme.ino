/*
 * Flash_Dance_Theme.ino
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

const char Flash_Dance_Theme[] PROGMEM = "MNT150L2O3E.L8DCL2D.L8DEL2F.L8EEEDL2CL8DCL2A.L8GFL2G.L8FGFEL2DL4CL2D.L8CDL2E.L8DCL2D.L8DEL2F.L8EEEDL4CP4L8DCL2A.L8GFL2G.L8FGFEL4DL8>DCL4CL8DDL2D.P4L4CL8CCP4DDL4DP4L8<CDL2E.L8DCL4DL2<GL8>DDL2F.L8EDEDL2CL8DCL2A.L8>C<AL2G.L8FEFEL4DL8>DCL4CP4CDP8L8<GBL4>CCL8C<BL4BL8BAL4AGL8GBL4>CCL8C<BL4BL8BAL4AGL8GB>CL4CDL8CL4<BL8>CL4C.L8DL4<GG.P4L8GB>CCL4<AL8>C<BL4BL8BAAAL4>DCL8CCL4<AL8>C<BL4BL8BAL4AL8GB>CL4C.L8DCL4<BL8>CL4C.L8D<GL4GG>C<BL8BBAAL4AGL8GBL4>CCL8C<BL4BL8BAL4AGL8GBL4>CCL8C<BL4BL8BAL4AGL8GBL4>CCL8C<BL4BL8BAL4AGL8GBL1C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Flash_Dance_Theme);
}

void loop(){
    play->touch();
}
