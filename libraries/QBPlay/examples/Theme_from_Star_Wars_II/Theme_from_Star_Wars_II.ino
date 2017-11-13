/*
 * Theme_from_Star_Wars_II.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 * http://www.antonis.de/faq/progs/starwars.bas
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

const char Theme_from_Star_Wars_II[] PROGMEM = "t136mno3l8ddgfe-dco2b-ago3d2.l12dddl8g4p4p2p2t236l6o2dddl2mlgo3ddmnl6co2bal2o3mlgddmnl6co2bamll2o3gddmnl6co2bo3cl2mlo2a1a4p4mnt236l6o2dddl2mlgo3ddmnl6co2bal2o3mlgddmnl6co2bamll2o3gddmnl6co2bo3cl2mlo2a1a4p4mnt136mno3l8p4mno2l8d4e4.eo3co2bagl12gabl8a8.e16f+4d8.de4.eo3co2bago3d8.o2a16mla4a4mnd4e4.eO3co2bagl12gaba8.e16f+4o3d8.d16l16g8.fe-8.dc8.o2b-a8.go3d2t236l6o2dddl2mlgo3ddmnl6co2bal2o3mlgddmnl6co2bamll2o3gddmnl6co2bo3cl2mlo2a1a4p4mnt236l6o2dddl2mlgo3ddmnl6co2bal2o3mlgddmnl6co2bamll2o3gddmnl6co2bo3cl2mlo2a1a4p4mnl6o3mndddmll1gggg4p4p4mnl12dddg2";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Theme_from_Star_Wars_II);
}

void loop(){
    play->touch();
}
