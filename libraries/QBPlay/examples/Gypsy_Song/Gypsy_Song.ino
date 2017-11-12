/*
 * Gypsy_Song.ino
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

const char Gypsy_Song[] PROGMEM = "MNT100L16O1G>GA+>DL8EDL16O1F>FA>DL8EDL16O1E>FA>C+L8EC+L16DFED<AFED<G>GA+>DEDEDO1F>FA>DEDEDO1E>GA>C+EC+EC+L8D<AFDL16<G>GA+>DL8EDL16O1F>FA>DL8EDL16O1E>FA>C+L8EC+L16DFED<AFED<G>GA+>DEDEDO1F>FA>DEDEDO1E>GA>C+EC+EC+L8D<AFD>C<A+>C<A+A+AL4AL8AGAGGFL4FL8EE>C<A+A+AL4AL8AA>FC+EDL4D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Gypsy_Song);
}

void loop(){
    play->touch();
}
