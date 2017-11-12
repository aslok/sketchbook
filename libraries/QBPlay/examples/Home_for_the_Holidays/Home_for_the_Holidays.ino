/*
 * Home_for_the_Holidays.ino
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

const char Home_for_the_Holidays[] PROGMEM = "MNT150L4O2EFL2GL4ECL2>CL4<BAGFL1EL4CDL2EL4D+EAGFED>C<BAGFEFL2GL4EC>DC<BA>C<EL1GL4>DC<BGAFGEFDL1CL4CFGA>CC<B>DCC.L8<BL4>DC<BAL2GL4EFGGF+GBAGFL1EL4CFGA>CC<B>DCC.L8<BL4>DC<BAL2GL4GAB>DDEDC<B.L8AL4GGGAGFEFL2GL4ECL2>CL4<BAGFL1EL4CDL2EL4D+EAGFED>C<BAGFEFL2GL4EC>DC<BA>C<EL1GL4>DC<BGAFGEFDCGGGL2GP4L4EFL2GL4ECL2>CL4<BAGFL1EL4CDL2EL4D+EAGFED>C<BAGFEFL2GL4EC>DC<BA>C<EL1GL4>DC<BGAFGEFDL1CL4CFGA>CC<B>DCC.L8<BL4>DC<BAL2GL4EFGGF+GBAGFL1EL4CFGA>CC<B>DCC.L8<BL4>DC<BAL2GL4GAB>DDEDC<B.L8AL4GGGAGFEFL2GL4ECL2>CL4<BAGFL1EL4CDL2EL4D+EAGFED>C<BAGFEFL2GL4EC>DC<BA>C<EL1GL4>DC<BGAFL2GEL1F>DC.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Home_for_the_Holidays);
}

void loop(){
    play->touch();
}
