/*
 * Malguena.ino
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

const char Malguena[] PROGMEM = "MNT150L8O2G+AL4BL8G+AL4BAG+L8FF+L4G+L8FF+L4G+AG+L8G+AL4BL8G+AL4BAG+L8FF+L4G+L8FF+L4G+AG+L8G+AL4>C+L8<G+AL4>C+<BAL8F+G+L4AL8ABL4>C+D<BL8>FF+L4G+L8FF+L4G+AG+L8FF+L4G+L8FF+L4G+F+FL8G+AL4>C+L8<G+AL4>C+<BAL8F+G+L4AL8ABL4>C+DL2C+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Malguena);
}

void loop(){
    play->touch();
}
