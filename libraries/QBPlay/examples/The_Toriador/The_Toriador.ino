/*
 * The_Toriador.ino
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

const char The_Toriador[] PROGMEM = "MNT150L4O3CL8D.L16CL8<AL16AP16L4AL8A.L16GL8A.L16A+L4AL8AP8L4A+L8G.L16>CL4<A.P8FL8D.L16GL4C.P8L2GL8G>DC<A+AGAA+L4A.P8EAAL8G+BL1>EL8EL16DEDL8C+D<GAA+P8L16AA+AL8F>DL4C.P8P8L16<FGFL8CA+L4AGF.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Toriador);
}

void loop(){
    play->touch();
}
