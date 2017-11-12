/*
 * Movin_On_Down_the_Road.ino
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

const char Movin_On_Down_the_Road[] PROGMEM = "MNT200L4O3CD+CL8<A+L4G.FD+FF+F+D+L2F+D+L4FGFD+L2GD+L4FGL8A+L4A+.GA+L2>C.L4CD+CL8<A+L4G.FD+FF+F+D+L2F+D+L4FGFD+L2GD+L4FGA+A+GA+L8GL4A+.L1>CP2L8<GD+FDL1D+P4L4D+GA+L2A+L4>CL1<GP4L4>CD+CL8<A+L4G.FD+FF+F+FL2D+P4L8GD+FDL1D+P4L4D+GA+L2A+L4>CL1<GP4L4>CD+CL8<A+L4G.FD+FF+F+FL1D+P4L4GL2A+>CD+L1<A+.P4L8GD+FDL1D+L8>D+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Movin_On_Down_the_Road);
}

void loop(){
    play->touch();
}
