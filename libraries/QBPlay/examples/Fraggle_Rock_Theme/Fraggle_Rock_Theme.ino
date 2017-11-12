/*
 * Fraggle_Rock_Theme.ino
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

const char Fraggle_Rock_Theme[] PROGMEM = "MNT255L4O2GA>C<AL8>D+L4DC.<A>FFFL8D+L1FP8L4DEF+DL8AL4F+E.DGL8GL4AL8AL1BP4P8L4CL8CL4CL8DL1<AP4P8L4BBAG>EL8DL4CL8<AL4G>CL8CL4CL8DL1<AP4P8L4BL8BL4AL8BL1>CP4P8L4CL8CL4CL8DL1<AP4P8L4BBAG>EL8DL4CL8<AL4G>CL8CL4CL8DL1<AP4P8L4BL8BL4AL8BL1>CP4P8L4<BL8BL4AL8BL1>CP4P8L4<BL8BL4AL8BL2>CP4L8>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Fraggle_Rock_Theme);
}

void loop(){
    play->touch();
}
