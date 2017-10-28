/*
Cyrstal
Пример анимации, первая и вторая строки выводятся в одной позиции по очереди
Третья строка выводится один раз в начале программы

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 5,776 bytes (17.9%) of program storage space. Maximum is 32,256 bytes.
Global variables use 81 bytes (4.0%) of dynamic memory, leaving 1,967 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("Arduino \rFunduino\r UNO\n     Ардуино Уно"));
  lcd->printn(0);
  lcd->printn(2);
}
void loop(){
  for (byte num = 0; num < 2; num++){
    lcd->go(0);
    lcd->printn(num);
    if (!num){
      delay(2500);
    }
  }
  delay(700);
}
