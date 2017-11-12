/*
 * The_Theme_from_The_Sting_part_II.ino
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

const char The_Theme_from_The_Sting_part_II[] PROGMEM = "MNT255L8O2G+D+G+>CL4D+L8<GD+GA+L4>D+.P8L8<G+D+G+>CL4D+L8<GD+GA+L4>D+.P8L8<D+P8G+B>EP8D+P8D+P8<G+B>EP8D+P4O0G+G+B>G+<G+>G+B>G+<G+>G+B>G+<G+>G+B>G+L4G+G+G+L8G+L4G+L8D+FCD+L4F<G+L8A+BG+A+L4>CL8<G+>C<G+L4A+G+P4G+G+G+L8G+L4G+L8D+FCD+L4FL8<G+G+A+BG+A+L4>CL8<G+>C<G+L4A+G+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Theme_from_The_Sting_part_II);
}

void loop(){
    play->touch();
}
