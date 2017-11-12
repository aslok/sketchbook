/*
 * Theme_from_The_Muppet_Movie.ino
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

const char Theme_from_The_Muppet_Movie[] PROGMEM = "MNT200L4O3CC<ABL8AL4BG.P4>CC<ABL8AL2GP4P8L4EEGFL8EL4FL8>C<CDL4EL8EL4EL8FL1GP4P8L4>CC<ABL8AL4BG.P4>CC<ABL8AL2GP4P8L4EEGFL8EL4FL8>C<CDL4EL8EL4DL8DL1CL4>CDC<B>DCL2<GL4>CDC<B>DL2CL4CCDC<B>DEL2<GL4GAL8AL4BL8>CL1DP4P8L4CC<ABL8AL4BG.P4>CC<ABL8AL2GP4P8L4EEGFL8EL4FL8>C<CDL4EL8EL4EL8CL4EAL8AL4AL8EL4A>CL8CL4CL8<AL4>CFL8FL4FL8CL4FL2<AB>CDEEEEL1G.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_The_Muppet_Movie);
}

void loop(){
    play->touch();
}
