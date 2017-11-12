/*
 * Joy_to_the_World.ino
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

const char Joy_to_the_World[] PROGMEM = "MNT150L4O3DL8C+.L16<BL4A.L8GL4F+ED.L8AL4B.L8BL4>C+.L8C+L2DP16L8DDC+<BAA.L16GL8F+>DDC+<BAA.L16GL8F+F+F+F+F+L16F+GL4A.L16GF+L8EEEL16EF+L4G.L16F+EL8DL4>DL8<BA.L16GL8F+GL4F+EL2DL4>DL8C+.L16<BL4A.L8GL4F+ED.L8AL4B.L8BL4>C+.L8C+L2DP16L8DDC+<BAA.L16GL8F+>DDC+<BAA.L16GL8F+F+F+F+F+L16F+GL4A.L16GF+L8EEEL16EF+L4G.L16F+EL8DL4>DL8<BA.L16GL8F+GL4F+EL2D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Joy_to_the_World);
}

void loop(){
    play->touch();
}
