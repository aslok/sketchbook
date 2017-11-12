/*
 * Sleigh_Bells_Ring.ino
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

const char Sleigh_Bells_Ring[] PROGMEM = "MNT150L4O3DDDDEL8D<BL4GABL8AF+L4EL1DL4EF+A>DEL8D<BAGL4AL8ABAGL4EL1GL4>DDDDEL8D<BL4GABL8AF+L4EL1DL4EF+A>DEL8D<BAGL4AL8ABAGL4EL1GL8D+EL4BL8D+EL4BL8DEL4B>C+L1<A+L4BL8A+F+L4D+L1G+L4A+L8G+EC+EL4G+BA+>C+L1<F+.L8C+DL4AL8C+DL4AL8CDL4ABL2G+L4AL8G+EL4C+L1F+L4>AL8EDL4<A>DL8EAL4EL8D<A>DEL4A>D<ADDDDDEL8D<GL4GABL8AF+L4EL1DL4DF+A>DEL8D<BAGL4AL8ABAGL4EL1GL4>DDDDEL8D<BL4GABL8AF+L4EL1DL4EF+A>DEL8D<BAGL4AL8ABAGL4EL1G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Sleigh_Bells_Ring);
}

void loop(){
    play->touch();
}
