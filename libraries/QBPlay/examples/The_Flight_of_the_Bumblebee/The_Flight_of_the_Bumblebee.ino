/*
 * The_Flight_of_the_Bumblebee.ino
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

const char The_Flight_of_the_Bumblebee[] PROGMEM = "MLT255L4O4ED+DC+DC+C<B>C<BA+AG+GF+FED+DC+DC+C<B>C<BA+AG+GF+FED+DC+DC+C<B>ED+DC+DC+C<B>ED+DC+CFED+ED+DC+CC+DD+ED+DC+CFED+ED+DC+CC+DD+ED+DC+DC+C<B>CC+DD+EFEDED+DC+DC+C<B>CC+DD+EF+GG+AG+GF+FA+AG+AG+GF+FF+GG+AG+GF+FA+AG+AG+GF+FF+GG+AG+GF+GF+FEFF+GG+AA+AGAG+GF+GF+FEFF+GG+AA+AGL8<FL16AAAAAAABG+BG+BG+BG+AAAAAAAABG+BG+BG+BG+>AA+AG+ABABAA+AG+ABAG+AA+B>CC+C<BA+AA+B>CC+C<BA+<F+>DDDDDDDD+C+D+C+D+C+D+C+DDDDDDDDD+C+D+C+D+C+D+C+>DD+DC+DEDCDD+DC+DEDCDD+EFF+FED+DD+EFF+FD+EDC+C<BA+>D+DC+DC+C<BA+B>CC+>C+C<B>C<BA+AA+B>CC+CC+DD+ED+DC+DC+C<B>C<BA+AG+GF+FEFED+EFEDEFED+EFEDEFED+<EFED+EFED+EFEDED+DC+DC+C<B>C<BA+AG+GF+FEFED+EFEDEFED+EFEDEFED+EFEDEFED+EFEDEFF+GG+AA+B>CC+DD+EFF+GG+AA+B>CC+DD+EFED+EFEDED+DC+CFED+ED+DC+CC+DD+ED+DC+CC+DD+ED+DC+CC+DD+ED+DC+DC+C<B>CC+DD+EFEDED+DC+DC+C<B>CC+DD+EF+GG+AG+GF+FA+AG+AG+GF+FF+GG+AG+GF+FA+AG+AG+GF+FF+GG+AG+GF+GF+FEFF+GG+AA+AGAG+GF+FF+GG+AB>CDEFED+ED+DC+CFEDED+DC+CC+DD+ED+DC+CFED+ED+DC+CC+DD+L8EL16<G+AA+B>CC+DC+C<B>C<BA+AGAA+B>CC+DD+EFED+EFEDL8EL16G+AA+B>CC+DC+C<B>C<BA+AG+AA+B>CC+DD+<EFED+EF+GG+AG+GF+GF+FEFED+DC+C<BA+AG+GF+GF+FEFED+DC+C<BA+AA+AG+BGBGAB>CDEFED+FDFDL8EF+GG+L32A.<C.D.P8L16<EFF+GG+AA+BCC+DD+EFF+GG+AA+B>CC+DD+EF+GG+L32A.<C.D.P8P4L64AECAP8P4L32A.A.B.";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) The_Flight_of_the_Bumblebee);
}

void loop(){
    play->touch();
}
