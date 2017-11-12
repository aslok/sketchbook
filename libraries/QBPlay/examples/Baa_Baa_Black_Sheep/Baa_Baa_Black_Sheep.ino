/*
 * Baa_Baa_Black_Sheep.ino
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

const char Baa_Baa_Black_Sheep[] PROGMEM = "MNT150L4O2CCGGL8AAAAL2GL4FFEEDDL2CL4CL8CCL4GGAL8AAL4G.L8GL4FL8FFEEEEL4DL8DDL2C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Baa_Baa_Black_Sheep);
}

void loop(){
    play->touch();
}
