/*
 * It_Came_Upon_A_Midnight_Clear.ino
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

const char It_Came_Upon_A_Midnight_Clear[] PROGMEM = "MNT150L8O2FL4>DL8CC<A+GL4FL8GL4FL8FGAA+A+>CDL2CL8<FL4>DL8CC<A+GL4FL8GL4FL8FL4GL8GAGFL2A+L8>DL4DL8<DDEF+L4GL8AL4A+L8>DC<A+AGAGL2FL8FL4>DL8CC<A+GL4FL8GL4FL8FL4GL8GAGFL2A+P8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) It_Came_Upon_A_Midnight_Clear);
}

void loop(){
    play->touch();
}
