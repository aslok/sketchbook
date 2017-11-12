/*
 * The_Ghostbusters_Theme.ino
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

const char The_Ghostbusters_Theme[] PROGMEM = "MNT150L8O3CCL16D+EL8GL4A+AL8CCL16D+EL8GL4A+AP8L16CCL8ECD<A+P2>CL16CCL8<A+>CL4<AP4L16>CCL8D+CD<A+P8L4A+L8A+>CP2L16CCL8D+CL4D+P4P8L16C<A+L8>CCL4CP2L16D+CD+CL4D+P4<A+L8A+>CP2P8L16CCL8D+CL4D+P4P8L16C<A+L8>CCL4CP2L16D+CD+CL4D+P4<A+L8A+>CP2P4L4D+L8CL4D+L8CL4D+L8CL4D+L8CD+CL16<A+BL8>CL4D+L8CL4D+L8CL4D+L8CL4D+L8CD+CL16<A+BL8>CL4GL8D+L4GL8D+L4GL8D+L4GL8D+GD+L16C+DL8D+L4GL8D+L4GL8D+L4GL8D+L4GL8D+GD+L16C+DL8D+CCL16D+EL8GL4A+AL8CCL16D+EL8GL4A+AP8L16CCL8ECD<A+P2>CL16CCL8<A+>CL4<AP4L16>CCL8D+CD<A+P8L4A+L8A+>CP2L16CCL8D+CL4D+P4P8L16C<A+L8>CCL4CP2L16D+CD+CL4D+P4<A+L8A+>CP2P8L16CCL8D+CL4D+P4P8L16C<A+L8>CCL4CP2L16D+CD+CL4D+P4<A+L8A+>CP2P4L16D+CD+CL4D+P4<A+L8A+>CL16D+EL8GL4>CP4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Ghostbusters_Theme);
}

void loop(){
    play->touch();
}
