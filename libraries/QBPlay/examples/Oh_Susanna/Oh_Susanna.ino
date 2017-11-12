/*
 * Oh_Susanna.ino
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

const char Oh_Susanna[] PROGMEM = "MNT150L16O2DEL8F+AA.L16BL8AF+D.L16EL8F+F+EDL4EP8L16DEL8F+AA.L16BL8AF+D.L16EL8F+F+EEL4DP8L16DEL8F+AA.L16BL8AF+D.L16EL8F+F+EDL4EP4L16DEL8F+AA.L16BL8AF+D.L16EL8F+F+EEL4DP4GGL8BL4BL8BAAF+DL4EP8L16DEL8F+AA.L16BL8AF+D.L16EL8F+F+EEL4DP4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Oh_Susanna);
}

void loop(){
    play->touch();
}
