/*
 * Take_5.ino
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

const char Take_5[] PROGMEM = "MNT200L8O2B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.P2P2P4L8<B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.P2P2P4L8>ED+ED+EL4GL8EL4CL8<AB>CC+DL4F+L8DL4<BL8GAA+B>CL4EL8CL4<AL8F+GAA+BA+B>CDDC+DD+EL4GL8EL4CL8<AB>CC+DL4F+L8DL4<BL8GAA+B>CL4EL8CL4<AL8F+A>DCL2<BP4L8<B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.L32D.E.D.L8<BL4AL2BP4L8B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.L32D.E.D.L8<BL4AL2B.BP4P4P4P4P4P4P4P4P4P4P4P4P4P4P4P2P4L8B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.P2P2P4L8<B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.P2P2P4L8>ED+ED+EL4GL8EL4CL8<AB>CC+DL4F+L8DL4<BL8GAA+B>CL4EL8CL4<AL8F+GAA+BA+B>CDDC+DD+EL4GL8EL4CL8<AB>CC+DL4F+L8DL4<BL8GAA+B>CL4EL8CL4<AL8F+A>DCL2<BP4L8<B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.L32D.E.D.L8<BL4AL2BP4L8B>EGAA+BA+AL4G<B>DL2E.L32F+.G.F+.L8EL4DL2E.L32D.E.D.L8<BL4AL2B.BP2P4L32>D.E.D.L8<BL4AL2B.BP2P4L32>D.E.D.L8<BL4AL2B.BP2P4L32>F+.G.F+.L8EL4DL2E.EE.EE.EL4E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Take_5);
}

void loop(){
    play->touch();
}
