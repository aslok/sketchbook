/*
 * Santa_Clause_is_Coming_to_Town.ino
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

const char Santa_Clause_is_Coming_to_Town[] PROGMEM = "MNT150L4O2GL8EFL4GG.L8GABL4>CL2CL8<EFL4GGGL8AGL4FL2FL4EGCEDL2FL4<BL2>CL8GEFL4GG.L8GABL4>CL2CL8<EFL4GGGL8AGL4FL2FL4EGCEDL2FL4<BL1>CL4>CDC<B>C<AL2AL4>CDC<B>CL2<A.L4>DEDC+D<BBBL8B>CL4DC<BAGP4G.L8GEFL4GG.L8GABL4>CL2CL8<EFL4GGGL8AGL4FL2FL4EGCEDL2FL4>DL1C.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Santa_Clause_is_Coming_to_Town);
}

void loop(){
    play->touch();
}
