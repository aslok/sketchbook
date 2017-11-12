/*
 * Sonatina.ino
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

const char Sonatina[] PROGMEM = "MST200L8O2B>CDL4<GL8GAGAL4BL8GB>CDL4<GL8GGF+GL4AP8L8B>CDL4<GL8GGABL4>CL8EGECL4<BL8>DC<A>DL4<GP8L8B>CDL4<GL8GAGAL4BL8GB>CDL4<GL8GGF+GL4AP8L8B>CDL4<GL8GGABL4>CL8EGECL4<BL8>DC<A>DL4<GP8L8GF+GAB>C+DEF+L4AL8GF+EDC+<BA>EC+<GL4F+L8A>DDDL4<BL8G>DDDL4<BL8G>DDD<BGEF+GEL4DP8L8F+EDL4AP8L8AGF+L4>CP8L8C<BAL4>EL8DC<BAGF+EDEF+GAA+B>CDL4<GL8GAGAL4BL8GB>CDL4<GL8GGF+GL4AP8L8B>CDL4<GL8GGABL4>CL8EGECL4<BL8>DC<A>DL4<GP8L8GF+GAB>C+DEF+L4AL8GF+EDC+<BA>EC+<GL4F+L8A>DDDL4<BL8G>DDDL4<BL8G>DDD<BGEF+GEL4DP8L8F+EDL4AP8L8AGF+L4>CP8L8C<BAL4>EL8DC<BAGF+EDEF+GAA+B>CDL4<GL8GAGAL4BL8GB>CDL4<GL8GGF+GL4AP8L8B>CDL4<GL8GGABL4>CL8EGECL4<BL8>DC<A>DL4<GP8L8B>CDL4<AL8A>C<BAL4GL8GGF+GEF+GABAL4AL8DB>CDL4<AL8A>C<BAL4G.>GL8EL4DL8<BL4AL8>DL4<B.>GL8EL4DL8<B>C<A>DL4<GP8BP8G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Sonatina);
}

void loop(){
    play->touch();
}
