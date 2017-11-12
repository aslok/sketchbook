/*
 * Beverly_Hillbillies_Theme_1st_verse.ino
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

const char Beverly_Hillbillies_Theme_1st_verse[] PROGMEM = "MNT150L8O2CCFCFGAAFFL4GP32GP32C.P16L8CL4EL8EFL4GL8FEFGFDL4C.P16L8CL4FFAL8GFA+AA+>CL4D.P16L8DL4CL8CCL4CL8CC<CDL4EF.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Beverly_Hillbillies_Theme_1st_verse);
}

void loop(){
    play->touch();
}
