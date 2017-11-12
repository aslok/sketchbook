/*
 * Spoonful_of_Sugar_Makes_the_Medicine_Go_Down_Mary_Poppins.ino
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

const char Spoonful_of_Sugar_Makes_the_Medicine_Go_Down_Mary_Poppins[] PROGMEM = "MNT255L4O2DEF+G.L8GL4GGGF+GAL8BBL2BL4BL2B.L4>CD.L8DL4DDD.L8<BL4GEL1F+P4L4F+FF+G.L8GL4F+GL2A+.L4A+B.L8BL4A+BL2>C+.L4C+DP2C+DP2C+DC+DC+DP4<GEL2F+L4F+.L8FF+L4>C.<B.L8ABBL4BP4DL2B.L4GL8F+F+L4F+P4FL2F+DL8EEL4EP4D+EP4GEL2F+L4F+.L8FF+L4>C.<B.L8ABBL4BP4DL1BL4BP8L8DL4C+DL2BAL1G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Spoonful_of_Sugar_Makes_the_Medicine_Go_Down_Mary_Poppins);
}

void loop(){
    play->touch();
}
