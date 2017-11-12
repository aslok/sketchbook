/*
 * Capricci.ino
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

const char Capricci[] PROGMEM = "MLT150L4O4GF+L8GL16F+GL8<G>EDGL64DC+DC+L16DL8CL64<BA+BA+L16BABL8G>EDGL64DC+DC+L16DL8CL64<BA+BA+L16BABL8G>BA<AG>GL64F+FF+FL16F+EF+L8DGF+DL64ED+ED+L16EDC+L8DL16C+D<A>AG+A<A>GF+G<A>F+EF+<A>EDE<A>AG+A<A>GF+G<A>F+EF+<A>EDEL4<AP8L8>EADC+DL4EP8L8EAD<A>GL16F+DGEADGEF+DEC+L8D<AF+>F+EC+<G>GF+D<A>A<B>BGEL64C+CC+CL16C+<B>C+L8<A>AL16A+DC+DL8F+GL16ADC+DL8EFL16GDC+DL8EGL16F<AG+AL8>DFL16D+<GF+GL8>EDGAF+EL4F+EDP4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Capricci);
}

void loop(){
    play->touch();
}
