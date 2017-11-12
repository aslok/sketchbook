/*
 * Whistle_While_You_Work.ino
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

const char Whistle_While_You_Work[] PROGMEM = "MNT150L8O3C<A+AA+L4>C.L16CDL8C<A+AA+L4>C.L8CC<A+AG>C<A+AG>C<A+AA+L4>C.L8CC<A+AA+L4>C.L16CDL8C<A+AA+L4>C.L8CC<A+AG>C<A+AG>C<A+AGL4F.L8>FFD+DD+L4F.L8FFD+C+D+L4F.L8FFD+C+D+FFD+C+CDCDCDCDC<A+AA+L4>C.L16CDL8C<A+AA+L4>C.L8CC<A+AG>C<A+AG>C<A+AGL2F.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Whistle_While_You_Work);
}

void loop(){
    play->touch();
}
