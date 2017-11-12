/*
 * Polo_Dancer.ino
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

const char Polo_Dancer[] PROGMEM = "MNT150L4O3GP8GL2>DP8L4DL8CDL4<A+L8AGAA+L1>CL4D<AL8GFL4DP8DL2GL4GAGL8FEFEL1DL4EFAGP8GL2>DP8L4DL8CDL4<A+L8AGAA+L1>CL4D<AL8GFL4DP8DL2GL4GAGL8FEL1FL4F<EFAGP8GL2A+L4A+>C<A+L8AGAA+L1>CL4C+C<AA+P8A+L2>FL4FGFL8D+C+L1CL4CL8AA+L4>CL8<A+AL4GP8GL2>DP8L4DL8CDL4<A+L8AGAA+L1>CL4D<AL8GFL4DP8DL2GL4GAGL8FEL1FL4FL2F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Polo_Dancer);
}

void loop(){
    play->touch();
}
