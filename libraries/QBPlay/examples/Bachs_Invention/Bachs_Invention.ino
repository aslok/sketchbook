/*
 * Bachs_Invention.ino
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

const char Bachs_Invention[] PROGMEM = "MNT255L8O2FP8AP8FP8>CP8<FP8>FP8EDCDC<A+AA+AGFP8AP8>CP8<AP8>FP8CP8A>C<A+>C<A>C<A+>C<A>C<A+>C<FAGAFAGAFAGADFEFDFEFDFEF<BP8GP8>DP8<BP8>FP8DP8GAGFEFEDCDC<A+AP8>DC<B>C<BAGAGFEFEDCP8>C<B>CP8<EP8FP8>CP8<EP8>CP8<DP8BP8L2>CP2P4L8CP8EP8CP8GP8CP8>CP8<BAGAGFEFEDC<A+>CACA<A+>ACA<AP8A+P8GP8A+P8GP8>DP8<GP8>GP8FD+DD+DC<A+>C<A+AGP8A+P8>DP8<A+P8>GP8DP8A+P8C+P8A+P8C+P8A+P8C+P8DP8<AP8>FP8DP8AP8FP8GFGA+CA+DA+EA+CA+FEFA<B>AC+ADA<B>AEDEG<A>G<B>GC+G<A>GFP8DP8<A+P8>DP8<GP8L4>FL8EP8CP8<AP8>CP8<FP8L4>D+L8DFD+FDFD+FDFD+F<A+>DCD<A+>DCD<A+>DCD<GA+AA+GA+AA+GA+AA+EP8CP8GP8EP8A+P8GP8>CDC<A+AA+AGFGFD+DP8GFEFEDCDC<A+AA+AGFP8>FEFP8<AP8A+P8>FP8<AP8>FP8<GP8>EP8L1F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bachs_Invention);
}

void loop(){
    play->touch();
}
