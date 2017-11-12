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

const char Eine_Kleine_Nachtmusik_1st_Movement[] PROGMEM = "T120 MS O3 L4 g p8 d8 g p8 L8 dgdgb>d4 p4 L4 c p8 <a8>c p8 L8 <a>c<af#ad4 p4 MS O3 L8 ggggggggaaaa ML a>c<f#a ggggggggaaaa ML a>c<f#a MN O3 L16 dddddddddddddddddddddddd d4 p4 p1 O2 ML f#2g2 MS L4 >cc<ad L8 d p8 >d8 p8 d8 p8 p4 p1 ML L8 f#2g2 MS c4cc<a4aa ggggggggggggggggg>gggggaaggf#f#ggee O3 MN L16 ddddddddeeeeeeeeddddddddeeeeeeee MS L8 f#gagf#gaf#bagabag#b O3 MS L8 aaaaaaaaa<aaaa4 p4 O3 MS L8 p2 p4 f# p8 <b p8 >g p8 e p8 c# p8 p4 e4 d ML p8 e p8 d2c#4 p4 O3 MS L8 p4 c#4 ML d p8 f# p8 MS <b p8 g p8 e p8>e p8 ML ed p4 p2 O3 MS L8 ddeef#f#dd c#c#ddeec#c# ddeef#f#dd c#c#ddeec#c# O3 MS L8 ddf#ed#<b>c#d# egedc#<ab>c# d>ddddddd ML d MS <aaaa4 ag O3 MS L8 f#deef#f#dd c#c#ddeec#c# ddeef#f#dd c#c#ddeec#c# O3 MS L8 ddf#ed#<b>c#d# egedc#<ab>c# d>ddddddd ML d MS <aaaa4 ag O3 MS L8 f#<ab>c#ddee f#c#def#f#gg aaa#a#b4 p4 O3 ML L8 e2. d MS c# d p8 d p8 d p8 p4 MS O3 L4 g p8 d8 g p8 L8 dgdgb>d4 p4 L4 c p8 <a8>c p8 L8 <a>c<af#ad4 p4 MS O3 L8 ggggggggaaaa ML a>c<f#a ggggggggaaaa ML a>c<f#a MN O3 L16 dddddddddddddddddddddddd d4 p4 p1 O2 ML f#2g2 MS L4 >cc<ad L8 d p8 >d8 p8 d8 p8 p4 p1 O3 ML L8 f#2g2 MS c4cc<a4aa ggggggggggggggggg>gggggaaggf#f#ggee O3 MN L16 ddddddddeeeeeeeeddddddddeeeeeeee ddddeeeeddddeeee MS L8 d<ddd d4 p4 O2 MS L8 p2 p4 b p8 e p8 >c p8 <a p8 f# p8 p4 >a4 g ML p8 a p8 g2f#4 p4 O3 MS L8 p4 f#4 ML g p8 b p8 MS e p8 c p8 <a4 p8 >a ML ag p4 p2 O2 MS L8 ggaabbgg f#f#ggaaf#f# ggaabbgg f#f#ggaaf#f# O2 MS L8 g>gbag#ef#g# a>c<agf#def# gggggggg ML g MS ddd d4 dc O2 MS L8 bgaabbgg f#f#ggaaf#f# g>gaabbgg f#f#ggaaf#f# O3 MS L8 ggbag#ef#g# a>c<agf#def# gggggggg gb>dddddc <bdef#ggaa O3 MS L8 b<f#gabb>cc ddd#d#e4 p4 O2 ML L8 a2. g MS f# g4 p4 p2 ML a2. g MS f# L4 g p4 >g p4 e p4 d p4 O2 MS L16 gggggggggggggggg  ggggggggggggaaaa gggggggggggggggg ggggggggggggaaaa L8 gb>dgbg>d<b g4<g.g16 g4";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Eine_Kleine_Nachtmusik_1st_Movement);
}

void loop(){
    play->touch();
}
