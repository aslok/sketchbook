/*
 * Finnegans_March.ino
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

const char Finnegans_March[] PROGMEM = "MNT150L8O3DGL16GGL8GGB>DL16<BAL8GAAAAF+AL16F+EDDL8GGGGB>DL16<BAL8GAADF+L16GGGGGGL8G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Finnegans_March);
}

void loop(){
    play->touch();
}
