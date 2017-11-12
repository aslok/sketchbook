/*
 * Theme_from_Star_Wars.ino
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

const char Theme_from_Star_Wars[] PROGMEM = "MNT150L2O3CGP16L16FEDL2>C<GP16L16FEDL2>C<GP16L16FEFL2DP16L16<GGGL2>CGP32L16FEDL2>C<GP16L16FEDL2>C<GP16L16A+AA+L1GL2G.L8<G.L16GL4A.L8A>FEDCL16CDEDP16L8<AL4BL8G.L16GL4A.L8A>FEDCGP8L4D.P8L8<G.L16GL4A.L8A>FEDCL16CDEDP16L8<AL4BP16L8>G.L16GL8>C.L16<A+L8G+.L16GL8F.L16D+L8D.L16CL1GL2G.P16L16GGGL8>CP8L16<CCCL2C.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_Star_Wars);
}

void loop(){
    play->touch();
}
