/*
Cyrstal
Использование символа "перенос строки"

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 5,228 bytes (16.2%) of program storage space. Maximum is 32,256 bytes.
Global variables use 81 bytes (4.0%) of dynamic memory, leaving 1,967 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("Arduino UNO\n     Ардуино Уно"));
  lcd->printn(0);
}
void loop(){
}
