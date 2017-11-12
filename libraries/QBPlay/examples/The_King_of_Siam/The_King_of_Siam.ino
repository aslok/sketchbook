/*
 * The_King_of_Siam.ino
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

const char The_King_of_Siam[] PROGMEM = "MNT150L8O3DEFGAFL4AL8G+EL4G+L8GD+L4GL8DEFGAFA>DC<AFAL2>CL8<DEFGAFL4AL8G+EL4G+L8GD+L4GL8DEFGAFA>D<AFA>DL2<DL8AB>C+DEC+L4EL8FC+L4FL8EC+L4EL8<AB>C+DECL4EL8FC+L4FL2EL8<AB>C+DEC+L4EL8FC+L4FL8EC+L4EL8<AB>C+DECL4EL8FC+L4FL2EL8<DEFGAFL4AL8G+EL4G+L8GD+L4GL8DEFGAFA>DC<AFAL2>CL8<DEFGAFL4AL8G+EL4G+L8GD+L4GL8DEFGAFA>D<AFA>DL2<D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_King_of_Siam);
}

void loop(){
    play->touch();
}
