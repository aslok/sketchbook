/*
 * Shes_a_Grand_Ole_Flag.ino
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

const char Shes_a_Grand_Ole_Flag[] PROGMEM = "MNT200L8O4D+GL4A+A+A+A+L8F.L16GL8G+AA+P8A+GL4D+D+D+L8C<A+>D+L4FL8DL4D+L8C<A+L4>D+L8C<A+L4>D+L8C<A+L2>DP4L8A+GL4D+D+D+L8C<A+>D+L4FL8DL4D+L8DC+L4CL8EGL4>C<A+L2G+P4L4<A+>D+.L8DL4D+GF.L8D+L4FL8A+B>CL4D+L8CL4D+DL2D+.P2L8<A+GL4D+D+D+L8C<A+>D+L4FL8DL4D+L8C<A+L4>D+L8C<A+L4>D+L8C<A+L2>DP4L8A+GL4D+D+D+L8C<A+>D+L4FL8DL4D+L8DC+L4CL8EGL4>C<A+L2G+P4L4<A+>D+.L8DL4D+GF.L8D+L4FL8A+B>CL4D+L8CL4D+DL2D+.P16L32D+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Shes_a_Grand_Ole_Flag);
}

void loop(){
    play->touch();
}
