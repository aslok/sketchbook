/*
 * Theme_from_ARTHUR.ino
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

const char Theme_from_ARTHUR[] PROGMEM = "MNT150L4O3FL8<AL4>DC<BL8GB>DL4GFE.C<BL8AL4>FEDCDL8<FL4A+AG+L8EG+B>D<BG+E>D<E>C+L2E.L4<B.>C+EL8>FFFL4FL8<AL4AL8BL4B<DGL8O4EEEL4ECFEDCL8DDDL4D<FL2E>DL4DL8C+L2E.P8L4O2B.>C+EL8>FFFL4F<AAB.L8<GD<GO4EEEEL4EL8CL4FL8FL4EC<AL8>DDDL4D<FL2E>DL8D<B>C+L2EL8EP8L4O2B.>C+EL8>AAAL4AL8AAAL4AG+G+F+E.L8C+L2C+L4O1AL8EP8EO4C+C+C+L4C+L2DL8<EL4EL2F+L8AB>C+O1AL4O3G+A>E.L8O2C+L4>G+A>E.L8AAAL4AL8AAAL4AG+G+F+L2EL4E.L8C+L2F+L64O2A+>EL4F+.L8>C+L4DL8DL4DEF+<F+L2DL8>C+L4DL8DL4DEL8F+L2O1BL8O4C+DC+<AAO1A>F+AL4>ED.C+.L8AL2O1C+L8O4FFFL4FL8<AL4AL8BL4B<DGL8O4EEEL4ECFEDCL8DDDL4D<FL2E>DL4DL8C+L2E.P8L4O2B.>C+EL8>FFFL4F<AAB.L8<GD<GO4EEEEL4EL8CL4FL8FL4EC<AL8>DDDL4D<FL2E>DL8D<B>C+L2EL8EP8L4O2B.>C+EL8>AAAL4AL8AAAL4AG+G+F+E.L8C+L2C+L4O1AL8EP8EO4C+C+C+L4C+L2DL8<EL4EL2F+L8AB>C+O1AL4O3G+A>E.L8O2C+L4>G+A>E.L8AAAL4AL8AAAL4AG+G+F+L2EL4E.L8C+L2F+L64O2A+>EL4F+.L8>C+L4DL8DL4DEF+<F+L2DL8>C+L4DL8DL4DEL8F+L2O1BL8O4C+DC+<AAO1A>F+AL4>ED.C+O1AEAL1A";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_ARTHUR);
}

void loop(){
    play->touch();
}
