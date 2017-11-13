/*
 * Eine_Kleine_Nachtmusik_1st_Movement.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 * https://github.com/Zannick/qbasic-programs/blob/master/SONG.BAS
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

const char Eine_Kleine_Nachtmusik_1st_Movement[] PROGMEM = "T120MSO3L4gp8d8gp8L8dgdgb>d4p4L4cp8<a8>cp8L8<a>c<af#ad4p4MSO3L8ggggggggaaaaMLa>c<f#aggggggggaaaaMLa>c<f#aMNO3L16ddddddddddddddddddddddddd4p4p1O2MLf#2g2MSL4>cc<adL8dp8>d8p8d8p8p4p1MLL8f#2g2MSc4cc<a4aaggggggggggggggggg>gggggaaggf#f#ggeeO3MNL16ddddddddeeeeeeeeddddddddeeeeeeeeMSL8f#gagf#gaf#bagabag#bO3MSL8aaaaaaaaa<aaaa4p4O3MSL8p2p4f#p8<bp8>gp8ep8c#p8p4e4dMLp8ep8d2c#4p4O3MSL8p4c#4MLdp8f#p8MS<bp8gp8ep8>ep8MLedp4p2O3MSL8ddeef#f#ddc#c#ddeec#c#ddeef#f#ddc#c#ddeec#c#O3MSL8ddf#ed#<b>c#d#egedc#<ab>c#d>dddddddMLdMS<aaaa4agO3MSL8f#deef#f#ddc#c#ddeec#c#ddeef#f#ddc#c#ddeec#c#O3MSL8ddf#ed#<b>c#d#egedc#<ab>c#d>dddddddMLdMS<aaaa4agO3MSL8f#<ab>c#ddeef#c#def#f#ggaaa#a#b4p4O3MLL8e2.dMSc#dp8dp8dp8p4MSO3L4gp8d8gp8L8dgdgb>d4p4L4cp8<a8>cp8L8<a>c<af#ad4p4MSO3L8ggggggggaaaaMLa>c<f#aggggggggaaaaMLa>c<f#aMNO3L16ddddddddddddddddddddddddd4p4p1O2MLf#2g2MSL4>cc<adL8dp8>d8p8d8p8p4p1O3MLL8f#2g2MSc4cc<a4aaggggggggggggggggg>gggggaaggf#f#ggeeO3MNL16ddddddddeeeeeeeeddddddddeeeeeeeeddddeeeeddddeeeeMSL8d<dddd4p4O2MSL8p2p4bp8ep8>cp8<ap8f#p8p4>a4gMLp8ap8g2f#4p4O3MSL8p4f#4MLgp8bp8MSep8cp8<a4p8>aMLagp4p2O2MSL8ggaabbggf#f#ggaaf#f#ggaabbggf#f#ggaaf#f#O2MSL8g>gbag#ef#g#a>c<agf#def#ggggggggMLgMSdddd4dcO2MSL8bgaabbggf#f#ggaaf#f#g>gaabbggf#f#ggaaf#f#O3MSL8ggbag#ef#g#a>c<agf#def#gggggggggb>dddddc<bdef#ggaaO3MSL8b<f#gabb>ccddd#d#e4p4O2MLL8a2.gMSf#g4p4p2MLa2.gMSf#L4gp4>gp4ep4dp4O2MSL16ggggggggggggggggggggggggggggaaaaggggggggggggggggggggggggggggaaaaL8gb>dgbg>d<bg4<g.g16g4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Eine_Kleine_Nachtmusik_1st_Movement);
}

void loop(){
    play->touch();
}
