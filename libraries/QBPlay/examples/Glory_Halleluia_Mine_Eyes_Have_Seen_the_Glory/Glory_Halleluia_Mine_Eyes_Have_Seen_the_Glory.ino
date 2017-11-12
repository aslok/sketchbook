/*
 * Glory_Halleluia_Mine_Eyes_Have_Seen_the_Glory.ino
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

const char Glory_Halleluia_Mine_Eyes_Have_Seen_the_Glory[] PROGMEM = "MNT120L8O3DD.L16DL8D.L16CL8<B.L16>DL8G.L16AL8B.L16BL8B.L16AL4GP8L8GE.L16EL8E.L16F+L8G.L16F+L8G.L16EL8D.L16EL8D.L16<BL4>DP8L8DD.L16DL8D.L16CL8<B.L16>DL8G.L16AL8B.L16BL8B.L16AL4GGAAGF+L2G.P4L4D.L8C<B.L16>DL8G.L16AL2BGL4E.L8F+G.L16F+L8G.L16EL2D<BL4>DCL8<B.L16>DL8G.L16AL2BL4GGAAGF+L2G.P8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Glory_Halleluia_Mine_Eyes_Have_Seen_the_Glory);
}

void loop(){
    play->touch();
}
