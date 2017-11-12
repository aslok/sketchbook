/*
 * Oh_Come_All_Ye_Faithful.ino
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

const char Oh_Come_All_Ye_Faithful[] PROGMEM = "MNT150L8O2G.P16L2GL4DGL2ADL4BAB>CL2<BL4AL8G.P16L2GL4F+EF+GABL2F+L4E.L16D.P32L2D.>DL4C<BL2>C<BL4ABGAF+.L8EL4DL8G.P16L4GF+GAL2GL4DL8B.P16L4BAB>CL2<BL4AB>C<BAGL2F+L4G>CL2<BL4A.L16G.P32L2G.L8G.P16L2GL4DGL2ADL4BAB>CL2<BL4AL8G.P16L2GL4F+EF+GABL2F+L4E.L16D.P32L2D.>DL4C<BL2>C<BL4ABGAF+.L8EL4DL8G.P16L4GF+GAL2GL4DL8B.P16L4BAB>CL2<BL4AB>C<BAGL2F+L4G>CL2<BL4A.L16G.P32L2G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Oh_Come_All_Ye_Faithful);
}

void loop(){
    play->touch();
}
