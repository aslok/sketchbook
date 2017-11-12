/*
 * Dbnushka.ino
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

const char Dbnushka[] PROGMEM = "MNT150L8O3EGL4BL8B.L16BL4BL8A.L16GL4BL8B.L16BL4BL8E.L16EL4>CL8<A.L16AL4AL8G.L16AL4BB.P8L8B>CL4<AL8A.L16BL4GL8G.L16AL4F+L8F+.L16GL4EL8<B.L16BL4>F+L8D+.L16<BL4>F+L8G.L16DL2F+L8EF+GAL2B.L4GAGF+EL2GL4EP4L2BL4>DC<BAL8GAL4BBE>CL2<BL4E>CL2<BL4EEL1>EL4<EP4P2";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Dbnushka);
}

void loop(){
    play->touch();
}
