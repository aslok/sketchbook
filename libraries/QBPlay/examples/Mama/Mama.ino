/*
 * Mama.ino
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

const char Mama[] PROGMEM = "MNT255L8O3AGFEL2DL8AGFEL2DL4DL2A+.L4DL2A+.L8GFEDL2CL8GFEDL2CL4CL2A.L4CL2A.L8FEDCL2<A+L8>FEDCL2<A+L4A+L2>G.L4DL2A+.L4AL8GFL4GL8FEL4FL8EDL4EL8DC+L2D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Mama);
}

void loop(){
    play->touch();
}
