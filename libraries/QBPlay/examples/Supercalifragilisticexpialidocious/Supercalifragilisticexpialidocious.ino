/*
 * Supercalifragilisticexpialidocious.ino
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

const char Supercalifragilisticexpialidocious[] PROGMEM = "MNT255L4O2EGGGAGGEGGAGL2GFL4GGGGAGGDGGAGL2GEL4GGGGAGGG>CCDCL2C<AL4A>C<BA>C<GGEGG+ABL2>CL4CP4<GL8GGGGGGL4GL8GGL4GP4<GL8GGGGGGL4GL8GGL4G>GEGGGAGGEGGAGL2F.L4GGGGGAGGDGGAGL2E.L4GGGGGAGGG>CCDCL2<A.L4AAAAABAAA>DC<BAGP4L2GL4EGGGAGGEGGAGL2GFL4GGGGAGGDGGAGL2GEL4GGGGAGGG>CCDCL2C<AL4A>C<BA>C<GGEGG+ABL2>CC";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Supercalifragilisticexpialidocious);
}

void loop(){
    play->touch();
}
