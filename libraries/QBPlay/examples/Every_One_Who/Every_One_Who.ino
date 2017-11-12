/*
 * Every_One_Who.ino
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

const char Every_One_Who[] PROGMEM = "MNT150L4O2BL8BL4>DL8DL4<GL8GL4BL8BL4EL8EL4EL8EL4E.EP64L8EL4F+L8EL4DL8EL4F+L8GL4AL8A+L4B.B.B.P64D.BL8BL4>DL8DL4<GL8GL4BL8BL4EL8EL4EL8EL4E.EP64L8FL4F+L8EL4DL8EL4F+L8GL4AL8BL4G.P64G.P64G.GP64L8GL4F+L8F+L4AL8AL4>DL8DL4<AL8AL4F+L8F+L4AL8AL4>D.DP64L8DL4DL8DL4DL8DL4DL8DL4DL8DL4DL8CL4<AL8F+L4D.D.E.F+.G.F+.G.G+.A.GL8AL4BL8GL4AL8BL4AL8GL4E.E.EP64L8EL4D+L8EL4GL8F+L4F+L8FL4F+.FL8F+L4AL8GL4GL8F+L4G.F+L8GL4BL8AL4AL8G+L4AL8EL4F+L8GL4A.A.AP64L8DL4C+L8DL4G.G.G.GP64L8DL4E.F.G.GP64L8G+L4AL8AL4AL8BL4>C+L8C+L4<BL8AL4>D.D.DP64L8CL4<AL8F+L4D.E.F+.G.F+L8F+L4GL8GL4G+L8G+AG+AL4BL8>CL4DL8EL4<B.A.G.G.GD.E.F+.G.F+.G.G+.A.GL8AL4BL8GL4AL8BL4AL8GL4E.E.EP64L8EL4D+L8EL4GL8F+L4F+L8FL4F+.FL8F+L4AL8GL4GL8F+L4G.F+L8GL4BL8AL4AL8G+L4AL8EL4F+L8GL4A.A.AP64L8DL4C+L8DL4G.G.G.GP64L8DL4E.F.G.GP64L8G+L4AL8AL4AL8BL4>C+L8C+L4<BL8AL4>D.D.DP64L8CL4<AL8F+L4D.E.F+.G.F+L8F+L4GL8GL4G+L8G+AG+AL4BL8>CL4DL8EL4<B.A.G.G.G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Every_One_Who);
}

void loop(){
    play->touch();
}
