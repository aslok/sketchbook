/*
 * Oh_Christmas_Tree.ino
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

const char Oh_Christmas_Tree[] PROGMEM = "MNT150L4O2CL8F.L16FL8F.P64G.A.L16AL4A.P64L8AGAL4A+EGFL8>CC<AL4>D.L8CC<A+L4A+.L8A+A+GL4>C.L8<A+A+AL4AP16CL8F.L16FL4F.L8GA.L16AL4A.L8AGAL4A+EGF";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Oh_Christmas_Tree);
}

void loop(){
    play->touch();
}
