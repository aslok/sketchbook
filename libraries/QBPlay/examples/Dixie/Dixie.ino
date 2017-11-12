/*
 * Dixie.ino
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

const char Dixie[] PROGMEM = "MNT150L16O3GEL8CCL16CDEFL8GGGEAAA.L16GL8A.L16GABCDL4E.L16C<GL4>C.L16<GEL4G.L16DEL4CP8L16GEL8CCL16CDEFL8GGGEAAA.L16GL8A.L16GAB>CDL4E.L16C<GL4>C.L16<GEL4G.L16DEL4C.L16GABL8>CED.L16CL8<AL4>CL8<AL4>D.L8<AL4>D.L16<GABL8>CED.L16CL8<ABC.L16AL8GE>C.L16<EL8EL4DL8EL4C.L8EL4D.L8AGE>C.L16EL8DL4CL8<EL4C.L8EL4D.L8AGEL4>E.L16CL8DL4C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Dixie);
}

void loop(){
    play->touch();
}
