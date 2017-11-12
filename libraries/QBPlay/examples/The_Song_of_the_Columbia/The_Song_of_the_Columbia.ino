/*
 * The_Song_of_the_Columbia.ino
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

const char The_Song_of_the_Columbia[] PROGMEM = "MNT150L8O2D.L16DL4GL8G.L16GL4AL8>D.L16CL8<BL4G.P8DEL8>EDC<BAGP64L2GL4F+P8L8AL4AL8AAL4AL8B>C+DL4<AP4>DL8C+<BAGF+EAC+L2DP8L8DF+L4AL8AAGF+EDP64DL4GP4L8GAL4BL8BB>C<BAGL2AP8L8GBL4>DL8DDC<BAGF+L4EP4L8>EDC<BAGL4F+L8EF+G.P8F+GL4AL8A.L16AL4AL8>DCL4<B.P4L8F+GL4AL8AAL4AL8>DCL4<B.P4L8GBL4>DL8DDC<BAGF+L4EP4L8>EDC<BAGL4F+L8EF+G.P8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Song_of_the_Columbia);
}

void loop(){
    play->touch();
}
