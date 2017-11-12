/*
 * Hava.ino
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

const char Hava[] PROGMEM = "MST200L4O2DDP16L8F+D+DL4F+F+P16L8AGF+L4GGP16L8A+AGL4F+D+L2DL4DDP16L8F+D+DL4F+F+P16L8AGF+L4GGP16L8A+AGL4F+D+L2DP16L8F+L4F+L8D+DDL4DP16L8D+L4D+L8DCCL4CP16CD+CGF+D+L16D+L2DL8F+L4F+L8D+DDL4DP16L8D+L4D+L8DCCL4CP16CD+CGF+D+L16D+L2DP16GP16GP16L4GA+L2A+L8GGA+AGA+AGGGA+AGA+AGAA>C<A+A>C<A+AAA>C<A+A>C<A+AP8AL4>DL8<AAL4>DL8<A>C<A+AL2G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Hava);
}

void loop(){
    play->touch();
}
