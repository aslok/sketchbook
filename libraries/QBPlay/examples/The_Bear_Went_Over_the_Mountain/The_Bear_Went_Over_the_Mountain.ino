/*
 * The_Bear_Went_Over_the_Mountain.ino
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

const char The_Bear_Went_Over_the_Mountain[] PROGMEM = "MNT150L8O2DL4F+L8F+F+EF+L4G.F+L8F+L4EL8EEDEL4F+.DL8DL4F+L8F+F+EF+L4G.BL8BL4AL8AL4GL8EL2DL8F+L4AL8AL4BL8BL2AL8DL4F+L8F+L4GL8GL2F+P8L8DL4F+L8F+F+EF+L4G.F+L8F+L4EL8EEDEL4F+.DL8DL4F+L8F+F+EF+L4G.B.L8BABAGF+EL2D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Bear_Went_Over_the_Mountain);
}

void loop(){
    play->touch();
}
