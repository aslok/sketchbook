/*
 * The_Odd_Couple_TV_Series_Theme.ino
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

const char The_Odd_Couple_TV_Series_Theme[] PROGMEM = "MNT150L16O2AL8>D.L16AL8A.L16GL2AL4AL8G.L16FL4GL8F.L16EL2FDD.P8L16DL8G.L16>DL8D.L16CL2DL4DL8C.L16<A+L4>CL8<A+.L16AL2A+GL1GP4L4AL8A.L16FL8G.L16DL2FGP4L4AL8A.L16FL8G.L16AL4>CL8C.L16<AL4FDP4AL8A.L16FG.A.>C.L4DL8D.L16CL8<A.L16GL4FL1GL2G.P8L16<AL8>D.L16AL8A.L16GL2AL4AL8G.L16FL4GL8F.L16EL2FDD.P8L16DL8G.L16>DL8D.L16CL2DL4DL8C.L16<A+L4>CL8<A+.L16AL2A+GL1GP4L4AL8A.L16FL8G.L16DL2FGP4L4AL8A.L16FG.A.>C.L4DCL8<A.L16GL8F.L16DL2FL8F.L16DL8F.L16DL2FL8F.L16DL8F.L16DL1FFL8D.L16AL8A.L16GL2AAP8L8DFDL1F";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Odd_Couple_TV_Series_Theme);
}

void loop(){
    play->touch();
}
