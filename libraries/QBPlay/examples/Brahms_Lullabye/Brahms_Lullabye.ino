/*
 * Brahms_Lullabye.ino
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

const char Brahms_Lullabye[] PROGMEM = "MNT150L8O3EEL2GL8EEL2GL8EGL4>C<BAAGL8DEL4FDL8DEL2FL8DFBAL4GBL2>CL8<CCL4>C.L8C<AFL2GL8CCL4FGAEGL8CCL2>CL8<AFL2GL8ECL4FEDL2C.P2L8EEL2GL8EEL2GL8EGL4>C<BAAGL8DEL4FDL8DEL2FL8DFBAL4GBL2>CL8<CCL4>C.L8C<AFL2GL8CCL4FGAEGL8CCL2>CL8<AFL2GL8ECL4FEDL2C.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Brahms_Lullabye);
}

void loop(){
    play->touch();
}
