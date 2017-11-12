/*
 * Away_in_a_Manger.ino
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

const char Away_in_a_Manger[] PROGMEM = "MNT150L4O2DGGL8BAL4GGDEGEL2DL4DGGABB>DD<BGL2AL4DGGL8BAL4GGDEGEL2DL4DGGAB>D.P64C<DDF+L2GL8F+GL4AA>D<AAF+AGEL2DL8F+GL4AA>D<AAF+L8GF+GAB>C+L2DL4ED<BL8BAL4GGDE>C<EL2DL4DGGAB>D.C<DDF+L2GP16P4L4DGGL8BAL4GGDEGEL2DL4DGGABB>DD<BGL2AL4DGGL8BAL4GGDEGEL2DL4DGGAB>D.P64C<DDF+L2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Away_in_a_Manger);
}

void loop(){
    play->touch();
}
