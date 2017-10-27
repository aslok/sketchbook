/*
Cyrstal
Проверка отображения символов русского алфавита

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 27.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("АБВГДЕЁЖЗИЙКЛМНОПРСУФХЦЧШЩЪЫЬЭЮЯ\r "));
}
void loop(){
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 0; num < 24; num++){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 32; num-- > 10; ){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
}
