/*
 * Snow_White_and_the_Seven_Dwarves_Hi_Ho.ino
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

const char Snow_White_and_the_Seven_Dwarves_Hi_Ho[] PROGMEM = "MNT200L4O2CL2F.L4EL2D.L4FG.L8AL4GFL2E.L4CDFCCDEFA+L2A.L4FGCDEL2F.L4EL2D.L4FG.L8AL4GFL2E.L4CDFCCDEFA+L2A.L4GL2F.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Snow_White_and_the_Seven_Dwarves_Hi_Ho);
}

void loop(){
    play->touch();
}
