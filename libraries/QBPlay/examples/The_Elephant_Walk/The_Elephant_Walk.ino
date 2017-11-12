/*
 * The_Elephant_Walk.ino
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

const char The_Elephant_Walk[] PROGMEM = "MNT150L8O2F.L16>AL8CFAGFD<B>CL4CL2CL8<F.L16AL8>CFAGFDL2C.L8D<G+L2G+.L8G+>D<G+FL2F.L8FL16AL8>CFAGFD<B>CL4CC.L8CL4GGL8ECCCL4FFL16D+FD+CL8<A+G+L4BBL16A+BA+G+L8FCD+FL4FL8F.L16>AL8CFAGFD<B>CL4CL2CL8<F.L16AL8>CFAGFDL2C.L8D<G+L2G+.L8G+>D<G+FL2F.L8FL16AL8>CFAGFD<B>CL4CC.L8CL4GGL8ECCCFL4FL16D+FD+CL8<A+G+L4BBL16A+BA+G+L8FCL4D+L8FL4F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Elephant_Walk);
}

void loop(){
    play->touch();
}
