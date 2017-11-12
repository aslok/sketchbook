/*
 * Bach_I.ino
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

const char Bach_I[] PROGMEM = "MNT150L8O3AL16>C<AL8EL16AEL8CL16ECL4<AL16EA>C<ABABAG+B>D<B>C<B>C<AL8>AL16>C<AL8EL16AEL8CL16ECL4<AL16>C<BL8>CL16C<BL8>CAL16C.L32DL8C<BL16>ED+L8EL16ED+L8E>CL16<E.L32FL8ED+L16<B>EGEF+EF+ED+F+AF+GF+GF+EGED+EAED+EBED+E>C<ED+E>C<BABGF+EL8GL32F+GL16F+L4EL8AL16>C<AL8EL16AEL8CL16ECL4<AL16EA>C<ABABAG+B>D<B>C<B>C<AL8>AL16>C<AL8EL16AEL8CL16ECL4<AL16>C<BL8>CL16C<BL8>CAL16C.L32DL8C<BL16>ED+L8EL16ED+L8E>CL16<E.L32FL8ED+L16<B>EGEF+EF+ED+F+AF+GF+GF+EGED+EAED+EBED+E>C<ED+E>C<BABGF+EL8GL32F+GL16F+L4EL8EL16GEL8<BL16>E<BL8GL16BGL4EL8AG+>DC+GL16FEL8FDFL16AFL8DL16FDL8<BL16>D<BL4GL8>CL16ECDCDC<B>DFDEDEDCEC<B>CFC<B>CGC<B>CAC<B>CAGFGEDCL8EL32DEL16DL4CL16EDL8EL16EDL8E>C<EL64FL8EDL16DCL8DL16DCL8DBDL64EL8DCAL16>C<AGL4F.L16AFEL4D.L16FDCL4<A+L16A+AA+AL4G+L8FEAG+>DL16C<B>C<A>CEL8AEL16DC<B>CL4<AL8>EL16GEL8<BL16>E<BL8GL16BGL4EL8AG+>DC+GL16FEL8FDFL16AFL8DL16FDL8<BL16>D<BL4GL8>CL16ECDCDC<B>DFDEDEDCEC<B>CFC<B>CGC<B>CAC<B>CAGFGEDCL8EL32DEL16DL4CL16EDL8EL16EDL8E>C<EL64FL8EDL16DCL8DL16DCL8DBDL64EL8DCAL16>C<AGL4F.L16AFEL4D.L16FDCL4<A+L16A+AA+AL4G+L8FEAG+>DL16C<B>C<A>CEL8AEL16DC<B>CL4<A";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Bach_I);
}

void loop(){
    play->touch();
}