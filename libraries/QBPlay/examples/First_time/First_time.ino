/*
 * First_time.ino
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

const char First_time[] PROGMEM = "MNT200L4O1A+>D+L2D+L4DD+L2>CL4<A+D+L2FL4D+L2F.L4<A+>D+L2D+L4DD+L2>CL4<A+FL2A+L4FL2A+.L4D+>CL2CL4<B>CL2FL4D<A+L2>DL4<A+L2G.L4DD+L2D+L4DD+L2>CL4<DL1D+.L4GA+L1>FP4L4ED+DC+.L8CL2C.L4<FGG+L8A+L2>DP8L8<A+GL2A+L4GG+G.L8FL1FP4P8L4<A+>D+L2D+L4DD+L2>CL4<A+D+L2FL4D+L2F.L4<A+>D+L2D+L4DD+L2>CL4<A+FL2A+L4FL2A+.L4D+>CL2CL4<B>CL2FL4D<A+L2>DL4<A+L2G.L4DD+L2D+L4DD+L2>CL4<DL1D+.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) First_time);
}

void loop(){
    play->touch();
}
