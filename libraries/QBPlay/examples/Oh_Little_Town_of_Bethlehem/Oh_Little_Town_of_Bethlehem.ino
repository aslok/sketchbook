/*
 * Oh_Little_Town_of_Bethlehem.ino
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

const char Oh_Little_Town_of_Bethlehem[] PROGMEM = "MNT150L4O2BP64BP64BA+B>DC<EAGL8F+GL4ADL2B.P64L4BP64BP64B>EDP64DC<EAGL8F+GL4BAL2G.L4BP64BP64BAGL2F+P64L4F+P64F+EF+GAL2B.P64L4BP64BP64BA+B>DC<E>ED<GB.L8AL2G.P4L4BP64BP64BA+B>DC<EAGL8F+GL4ADL2B.P64L4BP64BP64B>EDP64DC<EAGL8F+GL4BAL2G.L4BP64BP64BAGL2F+P64L4F+P64F+EF+GAL2B.P64L4BP64BP64BA+B>DC<E>ED<GB.L8AL2G.P4L4BP64BP64BA+B>DC<EAGL8F+GL4ADL2B.P64L4BP64BP64B>EDP64DC<EAGL8F+GL4BAL2G.L4BP64BP64BAGL2F+P64L4F+P64F+EF+GAL2B.P64L4BP64BP64BA+B>DC<E>ED<GB.L8AL2G.P4L4BP64BP64BA+B>DC<EAGL8F+GL4ADL2B.P64L4BP64BP64B>EDP64DC<EAGL8F+GL4BAL2G.L4BP64BP64BAGL2F+P64L4F+P64F+EF+GAL2B.P64L4BP64BP64BA+B>DC<E>ED<GB.L8AL2G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Oh_Little_Town_of_Bethlehem);
}

void loop(){
    play->touch();
}
