/*
 * When_Johnny_Comes_Marching_Home_Again.ino
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

const char When_Johnny_Comes_Marching_Home_Again[] PROGMEM = "MNT150L32O1DEFGL4AP4L32DEFGL4AP4L32DEFGL4AP4L32DEFGL4AP4L8O3EEAAL4AP64L8BL4>CL8<BL4>CL8<AL2GP8L8EL2GP16L8EEAAL4AP64L8BL4>CL8<BL4>CL8DL2EP16L8CL2EP16L8CL4EL8EEDCL4DL8DL4DP32L8<BL4>CL8CC<BAL4BL8BBP32>CDL4E.D.C.<B.L8EAAL4AL8GL2A.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) When_Johnny_Comes_Marching_Home_Again);
}

void loop(){
    play->touch();
}
