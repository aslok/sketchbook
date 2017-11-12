/*
 * Fiddler_On_The_Roof.ino
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

const char Fiddler_On_The_Roof[] PROGMEM = "MNT200L8O2GFGFL4ECP4L8EFGFGFEFGAA+AA+AL4GP4P2G+GF+FL8D+DCDL4D+P4L8D+DCDL4D+CGP4P2L8GFGFL4ECP4L8EFGFGFEFGAA+AA+AL4GP4P2G+GF+FL8D+DCDL4D+P4L8D+DCD+DC<B>DL4CEFGG+G+G+G+G+L8A+>CL4<A+G+GL8GGGGGGL4GP4P4GFFFFFL8GG+L4GFL1EP4L4EFGG+G+G+G+G+L8A+>CL4<A+G+GL8GGGGGGL4GP4P4GFFFFD+DCD+L1G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Fiddler_On_The_Roof);
}

void loop(){
    play->touch();
}
