/*
 * Leave_it_to_Beaver.ino
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

const char Leave_it_to_Beaver[] PROGMEM = "MNT150L8O2CL4FL8A>C<AFL4GL8A+L4>DL8C<B>CFL4DL8<A+L4G.P16L8CL4FL8A>C<AFL4GL8A+L4>DL8C<B>CFD<GEL4F.P8>AL8AL4G.L8FGFL4D+L8EDD+EFGG+L4A.P8O1GL8GL4F.L8EFEL4C+L8DDEFG>G<G>C<A+AG.P16>CL4FL8A>C<AFL4GL8A+L4>DL8C<B>CFL4DL8<A+L4G.P16L8>CL4FL8A>C<AFL4GL8A+L4>DL8C<B>CFD<GEL4F.L8>F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Leave_it_to_Beaver);
}

void loop(){
    play->touch();
}
