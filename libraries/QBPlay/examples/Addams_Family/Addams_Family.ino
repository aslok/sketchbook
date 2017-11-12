/*
 * Addams_Family.ino
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

const char Addams_Family[] PROGMEM = "MNT200L8O3CDEFP4L4FP8FP8L8DEF+GP4L4O1GP8GP8L8O3DEF+GP4DEF+GP4CDEFP4L4O1FP8FP8P4L8O3CF.AF.D<A+.>GP4FE.GE.C<A.>FP4CF.AF.D<A+.>GP4FL64EFL8E.CD.EFP4CDEFP4L4FP8FP8L8DEF+GP4L4O1GP8GP8L8O3DEF+GP4DEF+GP4CDEFP4L4O1FP8FP8P4L8O3CF.AF.D<A+.>GP4FE.GE.C<A.>FP4CF.AF.D<A+.>GP4FL64EFL8E.CD.EFP4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Addams_Family);
}

void loop(){
    play->touch();
}
