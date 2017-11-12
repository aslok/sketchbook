/*
 * Here_Comes_Santa_Clause.ino
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

const char Here_Comes_Santa_Clause[] PROGMEM = "MNT200L4O2CAL8GGL4FCAL8GGL4FCA+L8A+A+L4AL1A+L4CL8A+A+L4AL8GGL4CA+AL8GGL4C>CC<BL1>CL4DFEDCEDC<A+A+L8>D.C.<A+.L1AL4>DFEL8DDL4CED<AL8>CCL4<A+AGL1FL4CAL8GGL4FCAL8GGL4FCA+L8A+A+L4AL1A+L4CL8A+A+L4AL8GGL4CA+AL8GGL4C>CC<BL1>CL4DFEDCEDC<A+A+L8>D.C.<A+.L1AL4>DFEL8DDL4CED<AL8>CCL4<A+AGL1F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Here_Comes_Santa_Clause);
}

void loop(){
    play->touch();
}
