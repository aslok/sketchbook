/*
 * Love_Theme_from_Romeo_and_Juliet.ino
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

const char Love_Theme_from_Romeo_and_Juliet[] PROGMEM = "MNT200L2O4GL4G<B>CD<AGL2>CCL4<ABL2G+>EL4E<GAA+EFL2G+G+GL4DD+D+EL2A.L4EFA+A+AL2A.L4EFG+G+AL2B.L4F+G>CC<BL2B.L4F+GA+A+BL2>E.L4<B>CDD+EL2A.L4EFGG+AL2B.L4AL2G+GL4G<B>CD<AGL2>CCL4<ABL2G+>EL4E<GAA+EFL2G+G+G>DCP4L4<G>CEL1CCP1";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Love_Theme_from_Romeo_and_Juliet);
}

void loop(){
    play->touch();
}
