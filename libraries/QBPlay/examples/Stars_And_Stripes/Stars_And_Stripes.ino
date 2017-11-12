/*
 * Stars_And_Stripes.ino
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

const char Stars_And_Stripes[] PROGMEM = "MNT150L4O3CCL8<A+AL4AL8G+AL2A.L8G+AL4AL8G+AL4>CL8<A.L16>CL2<A+L4G.L8GL4GL8F+GL4GL8F+GL2A+.L8AGAL4>C.DDL2<G.L4>CCL8<A+AL4AL8G+AL2A.L8G+AL4AL8G+AA+AG.L16EL2GL4F.L8FL4FL8EFL4G+L8GFL2>FP8L8<FGA>C<FGA>C<CDAL2GL8FP8>FP8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Stars_And_Stripes);
}

void loop(){
    play->touch();
}
