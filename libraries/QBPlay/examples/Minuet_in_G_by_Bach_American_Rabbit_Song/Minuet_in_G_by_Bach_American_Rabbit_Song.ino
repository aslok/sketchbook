/*
 * Minuet_in_G_by_Bach_American_Rabbit_Song.ino
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

const char Minuet_in_G_by_Bach_American_Rabbit_Song[] PROGMEM = "MNT150L4O4DL8<GAB>CL4D<GG>EL8CDEF+L4G<GG>CL8DC<BAL4BL8>C<BAGL4F+L8GABGL4BL2AL4>DL8<GAB>CL4D<GG>EL8CDEF+L4G<GG>CL8DC<BAL4BL8>C<BAGL4AL8BAGF+L1GL4>DL8<GAB>CL4D<GG>EL8CDEF+L4G<GG>CL8DC<BAL4BL8>C<BAGL4F+L8GABGL4BL2AL4>DL8<GAB>CL4D<GG>EL8CDEF+L4G<GG>CL8DC<BAL4BL8>C<BAGL4AL8BAGF+L1GL4>BL8GABGL4AL8DEF+DL4GL8EF+GDL4C+L8<B>C+L4<AL8AB>C+DEF+L4GF+EF+<A>C+L1DL4DL8<GF+L4G>EL8<GF+L4G>DC<BL8AGF+GL4AL8DEF+GABL4>C<BAL8B>DL4<GF+L1GL4>BL8GABGL4AL8DEF+DL4GL8EF+GDL4C+L8<B>C+L4<AL8AB>C+DEF+L4GF+EF+<A>C+L1DL4DL8<GF+L4G>EL8<GF+L4G>DC<BL8AGF+GL4AL8DEF+GABL4>C<BAL8B>DL4<GF+L1G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Minuet_in_G_by_Bach_American_Rabbit_Song);
}

void loop(){
    play->touch();
}
