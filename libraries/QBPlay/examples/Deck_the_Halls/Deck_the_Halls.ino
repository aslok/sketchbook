/*
 * Deck_the_Halls.ino
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

const char Deck_the_Halls[] PROGMEM = "MNT200L4O3A.L8GL4F+EDEF+DL8EF+GEL4F+.L8EL4DC+L2DL4A.L8GL4F+EDEF+DL8EF+GEL4F+.L8EL4DC+L2DL4E.L8F+L4GEF+.L8GL4AEL8F+GL4AL8B>C+L4DC+<BL2AL4A.L8GL4F+EDEF+DL8BBBBL4A.L8GL4F+EL2DL4A.L8GL4F+EDEF+DL8EF+GEL4F+.L8EL4DC+L2DL4A.L8GL4F+EDEF+DL8EF+GEL4F+.L8EL4DC+L2DL4E.L8F+L4GEF+.L8GL4AEL8F+GL4AL8B>C+L4DC+<BL2AL4A.L8GL4F+EDEF+DL8BBBBL4A.L8GL4F+EL2D";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Deck_the_Halls);
}

void loop(){
    play->touch();
}
