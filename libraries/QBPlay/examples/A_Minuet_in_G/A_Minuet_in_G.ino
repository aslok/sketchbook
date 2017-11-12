/*
 * A_Minuet_in_G.ino
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

const char A_Minuet_in_G[] PROGMEM = "MST200L4O3DGP8GP8GP8GL8DGBGL4AP8AP8AP8AL8DA>C<AL4B>DP8DP8L8DGF+EL4DP8DC<BP8BADGP8GP8GP8GL8DGBGL4AP8AP8AP8AL8DA>C<AL4B>DP8DP8L8DGF+EL4DP8DC<BP8BADP8>DP8DP8DP8DL8<EG+B>DL4CP8CP8CP8CL8<DF+A>CL4<B>DP8DP8L8DGF+EL4DL16E.D.C.L4<BAL2GL4DP8>DP8DP8DP8DL8<EG+B>DL4CP8CP8CP8CL8<DF+A>CL4<B>DP8DP8L8DGF+EL4DL16E.D.C.L4<BAL2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) A_Minuet_in_G);
}

void loop(){
    play->touch();
}
