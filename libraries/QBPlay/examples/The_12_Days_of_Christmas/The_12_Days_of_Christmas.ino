/*
 * The_12_Days_of_Christmas.ino
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

const char The_12_Days_of_Christmas[] PROGMEM = "MNT150L8O2CCL4CL8FFL4FL8EFGAA+GL4A.L8A+L4>CL8D<A+AFL4GL2F.L8CCL4CL8FFL4FL8EFGAA+GL4A.>CL8<GAL4A+L8AA+L4>CL8D<A+AFL4GL2F.L8CCL4CL8FFL4FL8EFGAA+GL4A.>CL8<GAL4A+>CL8<GAL4A+L8AA+L4>CL8D<A+AFL4GL2F.L8CCL4CL8FFL4FL8EFGAA+GL4A.>CL8<GAL4A+>CL8<GAL4A+>CL8<GAL4A+L8AA+L4>CL8D<A+AFL4GL2F.L8CCL4CL8FFL4FL8EFGAA+GL4A.L2>CL4D<B.L1>CL8C<A+AGL4FA+DFL8GFEDL4CL8AA+L4>CL8D<A+AFL4GL2F.L8CCCCFFL4FL8EFGAA+GL2AL8>CC<GAA+GL2>CL4D<B.L1>CL8C<A+AGL4FA+DFL8GFEDL4CL8AA+L4>CL8D<A+AFL4GL2F.L8CCCCFFL4FL8EFGAA+GL2AL8>CC<GAA+G>CC<GAA+GL2>CL4D<B.L1>C";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_12_Days_of_Christmas);
}

void loop(){
    play->touch();
}
