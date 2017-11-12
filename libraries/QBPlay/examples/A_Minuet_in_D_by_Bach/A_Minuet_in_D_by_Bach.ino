/*
 * A_Minuet_in_D_by_Bach.ino
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

const char A_Minuet_in_D_by_Bach[] PROGMEM = "MNT150L4O3AL8>FEDC+L4D<AA+L8C+EGA+AGL4FL8EFL4DFL8A+A>DCL4FL8EDC<A+AL16A+>CL4<FEL2FL4AL8>FEDC+L4D<AA+L8C+EGA+AGL4FL8EFL4DFL8A+A>DCL4FL8EDC<A+AL16A+>CL4<FEL2FL4>AL8<F>AGFL16EFL8GL2CL4FL8<D>FEDL16C+DL8EL2<AL8AB>C+DEFGEC+A+AGL16FEL8DL4EC+L2D.L4AL8<F>AGFL16EFL8GL2CL4FL8<D>FEDL16C+DL8EL2<AL8AB>C+DEFGEC+A+AGL16FEL8DL4EC+L2D.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) A_Minuet_in_D_by_Bach);
}

void loop(){
    play->touch();
}
