/*
 * Star_Spangled_Banner.ino
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

const char Star_Spangled_Banner[] PROGMEM = "MNT150L8O3D+.L16CL4<G+>CD+L2G+L8>C.L16<A+L4G+CDL2D+L8D+D+L4>C.L8<A+L4G+L2GL8FGL4G+G+D+C<G+L8>D+.L16CL4<G+>CD+L2G+L8>C.L16<A+L4G+CDL2D+L8D+D+L4>C.L8<A+L4G+L2GL8FGL4G+G+D+C<G+L8O4CCL4CC+D+L2D+L8C+CL4<A+>CC+L2C+L8C+C+L4C.L8<A+L4G+L2GL8FL16G.L4G+CDL2D+L8D+D+L4G+G+L8G+GL4FFFA+L8>C+C<A+G+L4G+G.P8L8D+D+L4G+.L8A+>CC+L2D+L8<G+A+L4>C.L8C+L4<A+L2G+.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Star_Spangled_Banner);
}

void loop(){
    play->touch();
}
