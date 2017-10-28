/*
Cyrstal
Пример анимации, первая и вторая строки выводятся в разных позициях

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 5,744 bytes (17.8%) of program storage space. Maximum is 32,256 bytes.
Global variables use 81 bytes (4.0%) of dynamic memory, leaving 1,967 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("Arduino Nano\rАрдуино Нано"));
}
void loop(){
  for (byte num = 0; num < 4; num++){
    lcd->clear();
    switch (num){
      case (0):
        lcd->go(0, 0);
        break;
      case (1):
        lcd->go(4, 1);
        break;
      case (2):
        lcd->go(0, 1);
        break;
      case (3):
        lcd->go(4, 0);
        break;
    }
    lcd->printn(0);
    switch (num){
      case (0):
        lcd->go(4, 1);
        break;
      case (1):
        lcd->go(0, 0);
        break;
      case (2):
        lcd->go(4, 0);
        break;
      case (3):
        lcd->go(0, 1);
        break;
    }
    lcd->printn(1);
    delay(1700);
  }
}
