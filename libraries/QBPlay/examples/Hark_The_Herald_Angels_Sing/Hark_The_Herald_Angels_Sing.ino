/*
 * Hark_The_Herald_Angels_Sing.ino
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

const char Hark_The_Herald_Angels_Sing[] PROGMEM = "MNT150L4O3CFF.L8EL4FAAG>CCC.L8<A+L4AGL2AL4CFF.L8EL4FAAG>C<GG.L8EL4EDL2CL4>CCC<FA+AAG>CCC<FA+AAG>D.L8DL4DC<A+AL2A+L4GL8AA+L4>C.L8<FL4FGL2AL4>D.L8DL4DC<A+AL2A+L4GL8AA+L4>C.L8<FL4FGL2F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Hark_The_Herald_Angels_Sing);
}

void loop(){
    play->touch();
}
