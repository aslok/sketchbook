/*
 * POP_Goes_the_Weasel.ino
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

const char POP_Goes_the_Weasel[] PROGMEM = "MNT150L8O2C.L16CL8D.L16DE.G.E.L8C.L16<GL8>C.L16CL8D.L16DL4EL8C.L16<GL8>C.L16CL8D.L16DE.G.E.L4CP64AL8D.L16FL4ECL8>C.L16CL8<A.L16>C<B.>D.<B.L8GP8L16G>C.C.C.L8<A.L16>C<B.>D.<B.L4GF.L16EL8F.L16GL4A.L16BL4>C.AL8D.L16FL4EC";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) POP_Goes_the_Weasel);
}

void loop(){
    play->touch();
}
