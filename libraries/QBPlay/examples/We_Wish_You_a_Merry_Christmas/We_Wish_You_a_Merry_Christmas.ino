/*
 * We_Wish_You_a_Merry_Christmas.ino
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

const char We_Wish_You_a_Merry_Christmas[] PROGMEM = "MNT150L4O3CFL8FGFEL4DDDGL8GAGFL4ECCAL8AA+AGL4FDL8CCL4DGEL2FL4CFFFL2EL4EFEDL2CL4CAGF>C<CL8CCL4DGEL2FL4CFL8FGFEL4DDDGL8GAGFL4ECCAL8AA+AGL4FDL8CCL4DGEL2F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) We_Wish_You_a_Merry_Christmas);
}

void loop(){
    play->touch();
}
