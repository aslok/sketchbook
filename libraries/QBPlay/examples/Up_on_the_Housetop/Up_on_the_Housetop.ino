/*
 * Up_on_the_Housetop.ino
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

const char Up_on_the_Housetop[] PROGMEM = "MNT200L4O3CL8CDL4C<AFAL2>CL4DDC<AG>CL2CL4CL8CDL4C<AFAL2>CL4DDC<AG>CL2<FL4A+A+L2>DL4CL8CCL2<AL4GGL2A+L4AL8>CCL2<FL4>CL8CDL4C<AA+>CL2DL4CL8CDCCL4<AG>CL2<F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Up_on_the_Housetop);
}

void loop(){
    play->touch();
}
