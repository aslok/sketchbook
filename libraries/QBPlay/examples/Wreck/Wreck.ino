/*
 * Wreck.ino
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

const char Wreck[] PROGMEM = "MNT200L4O3EL8DL4CL8CL4CL8DL4EL8EEDCDEDL4CL8<BL2>CL8CDL4EL8EL4EL8FL4GL8GL4GL8GL4GL8DL4DL8EL2DL8DGL4AL8FL4AL8FAL4>CL8C<BAL4GL8EL4GL8EL2GL4EL8DL4CL8CL4CL8DL4EL8EEDCDEDL4CL8<BL2>CL8C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Wreck);
}

void loop(){
    play->touch();
}
