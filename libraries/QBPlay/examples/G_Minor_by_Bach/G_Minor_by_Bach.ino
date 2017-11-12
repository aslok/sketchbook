/*
 * G_Minor_by_Bach.ino
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

const char G_Minor_by_Bach[] PROGMEM = "MNT150L4O4A+AGADDGL8<GAA+>CL4DL8<DC<A+AL4O4D+L8FD+DCL4DL8D+DC<A+L4>CL8DC<A+>CL4<AL8DC<A+AL4O4A+AGADDGL8<GAA+>CL4DL8<DC<BAL4O4FL8GFD+DL4D+L8FD+DCL4DGCL1<A+L4>A+AGADDGL8<GAA+>CL4DL8<DC<A+AL4O4D+L8FD+DCL4DL8D+DC<A+L4>CL8DC<A+>CL4<AL8DC<A+AL4O4A+AGADDGL8<GAA+>CL4DL8<DC<BAL4O4FL8GFD+DL4D+L8FD+DCL4DGCL1<A+L4>DL8<A+>CDEL4FGAA+L8GAA+GL4AL8GAL4FL8<FGAA+>CDL4D+DCF<A+AA+DCGL8>DCL4D<GL8>D+DL4D+L8<G>D<F+>C<GA+L4AL8<AGF+E>DEF+GAA+L4>C<A+AL8A+L16>CDL4<GF+L1GL4>DL8<A+>CDEL4FGAA+L8GAA+GL4AL8GAL4FL8<FGAA+>CDL4D+DCF<A+AA+DCGL8>DCL4D<GL8>D+DL4D+L8<G>D<F+>C<GA+L4AL8<AGF+E>DEF+GAA+L4>C<A+AL8A+L16>CDL4<GF+L1G";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) G_Minor_by_Bach);
}

void loop(){
    play->touch();
}
