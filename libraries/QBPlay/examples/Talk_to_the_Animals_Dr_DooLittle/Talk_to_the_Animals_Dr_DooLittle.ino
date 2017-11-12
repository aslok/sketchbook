/*
 * Talk_to_the_Animals_Dr_DooLittle.ino
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

const char Talk_to_the_Animals_Dr_DooLittle[] PROGMEM = "MNT150L8O2C+DEL4FL8FEFEL4DP8FL8GFEL4DL8EDEFGEG>CL2<GP8L8C+DEFEFEFL4D.L8GF+GF+GL4EL8GAAAB>CD<BAL2GP8L8DDEL4F.L8EFAGFL4EG.L8C+DEL4F.L8EFAG.L16F+L2GP8L8EEF+L4GGL8GBAGL16F+GL2AL8F+GF+L16AAL2AP8L4EL2AP8L8D+EF+L4GL8GF+GF+L4EP8GL8AGF+L4EL8F+EF+GAF+A>DL2<AP8L8D+EF+L4GL8GF+GF+L4EAL8AG+AGL4F+BB>C+C+DL8DC+DC+L4<B.P8EGBL2>DEL1D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Talk_to_the_Animals_Dr_DooLittle);
}

void loop(){
    play->touch();
}
