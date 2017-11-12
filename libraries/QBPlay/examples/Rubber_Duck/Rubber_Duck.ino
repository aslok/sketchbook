/*
 * Rubber_Duck.ino
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

const char Rubber_Duck[] PROGMEM = "MNT255L4O3FF.L8DL4<A+L8GL4>D+D+.L8DL2C.P4P8L4FF.L8DL4<A+L8GL4>D+D+.L8DL2C.P4P8L4<DL8C+L4DL2FL4D+.A+L1AP4L4FL8EL4F.F+.G>D.L1CP4L4<A+L8AL4A+L8FL4D.D+L8FL4D+L2DL4C.L1FP2P8L4FF.L8F+L4GL8F+L2FP4L4DL8C+L4DL2FL4D+.A+L1AP4L4FL8EL4F.F+.G>D.L1CP4L4<A+L8AL4A+L8FL4D.D+L8FL4D+L2DL4F.L1A+.P8A.P4P8L4AL8G+L4AL8GL2F.L4GL8F+L4GL8FL4E.A.G+L1AP4P8L4A.A+.B.>C.<B>C.L8<A+L4A.A+.AA+.L8AL4G.>C.<BL2>C.P8L4<FL8GL4AL8FL4GL2F.P8L4DL8C+L4DL2FL4D+.A+L1AP4L4FL8EL4F.F+.G>D.L1CP4L4<A+L8AL4A+L8FL4D.D+L8FL4D+L2DL4C.P4P8A+L8AL4A+L8FL4D.D+L8FL4D+L2DL4C.P4P8A+L8AL4A+L8FL4D.D+L8FL4D+L2DL4F.L8A+P2P8A+P2P8A+P8L4A+.L8AA+P4<A+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Rubber_Duck);
}

void loop(){
    play->touch();
}
