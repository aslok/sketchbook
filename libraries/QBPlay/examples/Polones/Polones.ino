/*
 * Polones.ino
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

const char Polones[] PROGMEM = "MNT255L8O4G+AL4BL2AG+L4F+D+L2E.P4L4<BL8>DP8L4DL8C+P8L4C+L8<BP8BAG+F+L2G+L4EP4L8>G+AL4BL2AG+L4<A+>C+L2F+.P4L4<F+L8G+A+L4BL8>C+D+L4EL8D+C+F+ED+C+L2<BL4BP4L8>G+AL4BL2AG+L4F+D+L2E.P4L4<BL8>DP8L4DL8C+P8L4C+L8<BP8BAG+F+L2G+L4EP4L8>G+AL4BL2AG+L4<A+>C+L2F+.P4L4<F+L8G+A+L4BL8>C+D+L4EL8D+C+F+ED+C+L2<BL4BP4L8>D+EL4F+L2ED+L4AF+L16AG+AG+L2G+P4L4CL8F+P8L4F+L8EP8L4EL8D+P8D+C+CC+L2D+L4<G+P4L8>DC+CC+DC+CC+L4BP4L8DC+CC+DC+CC+L4AP4<G+L8A+>CL4C+L8D+EL4D+L8C+CL16D+C+D+C+D+C+C+P16L2C+.P4L8<G+AL4BL2AG+L4>D<BL2>C+.P4L4<A+L8B>C+L4<BA+G+F+L8>ED+C+EL2D+<BP8L8>C+D+EF+ED+EL2<AP8L8>C+D+EF+ED+EL2<G+P4L8A+B>C+<BA+BL4F+L8>D+P8D+EF+L16D+P16L2D+L4E.P4L8D+EL4F+L2ED+L4AF+L16AG+AG+L2G+P4L4CL8F+P8L4F+L8EP8L4EL8D+P8D+C+CC+L2D+L4<G+P4L8>DC+CC+DC+CC+L4BP4L8DC+CC+DC+CC+L4AP4<G+L8A+>CL4C+L8D+EL4D+L8C+CL16D+C+D+C+D+C+C+P16L2C+.P4L8<G+AL4BL2AG+L4>D<BL2>C+.P4L4<A+L8B>C+L4<BA+G+F+L8>ED+C+EL2D+<BP8L8>C+D+EF+ED+EL2<AP8L8>C+D+EF+ED+EL2<G+P4L8A+B>C+<BA+BL4F+L8>D+P8D+EF+L16D+P16L2D+E";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Polones);
}

void loop(){
    play->touch();
}
