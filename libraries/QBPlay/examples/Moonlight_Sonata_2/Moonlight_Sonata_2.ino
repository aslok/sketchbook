/*
 * Moonlight_Sonata_2.ino
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

const char Moonlight_Sonata_2[] PROGMEM = "MNT200L4O4C+L2CL4<A+>D+P4C+CP4<A+G+P4F+L2FL4D+G+P4F+FP4D+>C+P4L2C+L4CL2<A+L4>D+L2C+L4CL2<A+L4G+L2>F+L4FL2D+L4G+L2F+L4FL2D+L4C+C+L2C+L4C+C+C<BL2BL4BBA+A+L2>CL4C+L2D+<F+L4FL8A+F+L4FD+>C+L2CL4<A+>D+P4L2C+L4CL2<A+L4G+>F+L2FL4D+G+P4L2F+L4FD+G+P4L2F+L4D+L2A+L4G+P4L2<CL8D+C+L4C+P4>C+L2C+L4C+C+C<BL2BL4BBA+A+L2>CL4C+L2D+<F+L4FL8A+F+L4FD+>C+L2CL4<A+>D+P4L2C+L4CL2<A+L4G+>F+L2FL4D+G+P4L2F+L4FD+G+P4L2F+L4D+L2A+L4G+P4L2<CL8D+C+L4C+P4L2F.F+.>D+L4C<G+>C+FL2<F.F+.>F+L4A+CD+C+L2<F.F+.>D+L4C<G+>C+FL2<F.F+.>F+L4A+CD+C+L2F.<A+.>D+.<G+.>C+.<F+.FL4G+L2BL4A+L2>D+.<F+.F.E.F.F+.FL4F+CC+P4L2>F.<A+.>D+.<G+.>C+.<F+.FL4G+L2BL4A+L2>D+.<F+.F.E.F.F+.FL4F+CC+P4>C+L2CL4<A+>D+P4C+CP4<A+G+P4>F+L2FL4D+G+P4F+FP4D+C+P4L2C+L4CL2<A+L4>D+L2C+L4CL2<A+L4G+L2>F+L4FL2D+L4G+L2F+L4FL2D+L4C+C+L2C+L4C+C+C<BL2BL4BBA+A+L2>CL4C+L2D+<F+L4FL8A+F+L4FD+>C+L2CL4<A+>D+P4L2C+L4CL2<A+L4G+>F+L2FL4D+G+P4L2F+L4FD+G+P4L2F+L4FL2A+L4G+P4L2<CL8D+C+L4C+P4P4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Moonlight_Sonata_2);
}

void loop(){
    play->touch();
}
