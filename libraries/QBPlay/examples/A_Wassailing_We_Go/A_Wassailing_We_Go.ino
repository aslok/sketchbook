/*
 * A_Wassailing_We_Go.ino
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

const char A_Wassailing_We_Go[] PROGMEM = "MNT150L4O3EL8F+L4G+L8F+L4EL8F+L4G+L8F+L4EL8BL4BL8BL2B.L4>C+L8C+L4<BL8G+L4BL8BL4AL8G+L4F+L8EL4F+L8G+L4A.G+AL2BL4>EC+L2<BL4G+ABB>EC+L2<BL4G+AL2BL4>C+<G+AF+ED+E.L8F+L4G+EL2AL4G+AL2BL4>C+<G+AF+ED+L2E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) A_Wassailing_We_Go);
}

void loop(){
    play->touch();
}
