/*
 * Fugue_in_D_by_Bach.ino
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

const char Fugue_in_D_by_Bach[] PROGMEM = "MNT150L16O4AGL2AP8L16GFEDL8C+L4D.P2L16<AGL2AP16L8EFC+L4D.P2L16<AGL2AP16L16GFEDL8C+L4D.P2L8<D>C+EGA+>C+EL64<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DGA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DEA>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D<DF+A>D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Fugue_in_D_by_Bach);
}

void loop(){
    play->touch();
}
