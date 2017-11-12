/*
 * Let_It_Snow.ino
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

const char Let_It_Snow[] PROGMEM = "MNT200L8O2CC>CCL4<A+AGFL2CL8CCL4G.L8FL4G.L8FL4EL2CL4DL8>DDL4C<A+AL2G.L8>EDL4CL8C<A+L4AL8AGL2F.L4CL8>CCL4<A+AGFL2CL8CCL4G.L8FL4G.L8FL4EL2CL4DL8>DDL4C<A+AL2G.L8>EDL4CL8C<A+L4AL8AGL2F.L8EFGAL4GE>CL2<G.L8EGL4FL8FEL4DL8CDL2E.L8EFL4GL8AGL4E>CL1<GL8>C<BL4ABL8ABL2>C.L4<CL8>CCL4<A+AGFL2CL8CCL4G.L8FL4G.L8FL4EL2CL8DD>DDL4C<A+AL2G.L8>EDL4CL8C<A+L4AL8AGL2F.P8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Let_It_Snow);
}

void loop(){
    play->touch();
}
