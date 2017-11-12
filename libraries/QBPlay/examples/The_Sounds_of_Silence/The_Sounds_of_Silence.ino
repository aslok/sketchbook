/*
 * The_Sounds_of_Silence.ino
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

const char The_Sounds_of_Silence[] PROGMEM = "MNT180L8O3DDFFAAL1GP8L8CCCEEGGL1FP8L8FFFAA>CCL2DCP4L8<FFAA>CCL2DCP4L8<FF>DL2DL8DEFL4F.L8EL4D.L2C.L8DCL1<AP8L8FFFL2>C.P8L8<EFL2D.P8L8DDDFFAAL1GP8L8CCCEEGGL1FP4L8FFAA>CCL4D.L2CP4L8<FFFAA>CCL4DL8DL2CP4L8<FFL4>DL8DL4D.L8DEL4FL8FFEL4D.L2CL4CL8DCL1<AP8L8FFFL2>C.P8L8<EFL2D.P8L8DDDFFAAL1GP8L8CCCEEGGL1FP4L8FFAA>CCL4D.L2CP4L8<FFFAA>CCL4DL8DL2CP4L8<FFL4>DL8DL4D.L8DEL4FL8FFEL4D.L2CL4CL8DCL1<AP8L8FFFL2>C.P8L8<EFL2D.P4L8DDFFAAL1GP4L8CCEEGGL1FP4L8FFAA>CCL4D.L2CP4L8<FFAA>CCL4D.L2CP4L8<FFL2>D.EL8FL4F.L8EL4D.L2CP2L4<EL8FL2F.L16FFL2>C.P8L8<EFL2D.P4L8DDFFAAL1GP4L8CCEEGGL1FP4L8FFAA>CCL4D.L2CP4L8<FFAA>CCL4D.L2CP4L8<FFL4AL8>CCL4DL8DDDDL4EL8FFFFEL4D.L2CL8CL16DDL8CL2<A.P4L8EFL2FL8FFL2>C.P8L8<EFL2D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Sounds_of_Silence);
}

void loop(){
    play->touch();
}
