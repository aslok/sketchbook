/*
 * Looney_Tunes_Theme.ino
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

const char Looney_Tunes_Theme[] PROGMEM = "MST200L8O3E.L16DL8CDED+ECDDDL2D.L8D.L16CL8<B>CDC+D<B>CCCL2C.L8<G.L16G+L8A.L16G+L8G.L16G+L8A.L16G+L8G>DDL2D.L8<AG+AL4>DEL2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Looney_Tunes_Theme);
}

void loop(){
    play->touch();
}
