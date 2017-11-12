/*
 * Petrov.ino
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

const char Petrov[] PROGMEM = "MNT150L4O3EL8D+L4EP4FL8CL4EP4L8D+EFEDC<BAL4>C.<BP4>DL8C+L4DP4FL8<BL4>DP4L2F.L8ED<BL2>CP4L4EL8D+L4EP4FL8CL4EP4L8EFGAL4A+.L8AL4GL8AGL4FP4L8EDC+DL4FP4L8DC<B>CL4EP4L8C<BA+B>DCFEL2<BA";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Petrov);
}

void loop(){
    play->touch();
}
