/*
Cyrstal
Равнение с очисткой старого содержимого

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 6,460 bytes (20.0%) of program storage space. Maximum is 32,256 bytes.
Global variables use 57 bytes (2.8%) of dynamic memory, leaving 1,991 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;


// Заполняем экран черточками для наглядного фона
void clear(){
  lcd->go(0);
  for (byte f = 0; f < 32; f++){
    lcd->printn(0);
  }
}
void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  //        №  0    1     2       3
  lcd->init(F("-\rСлева\rСправа\rВ центре"));
}
void loop(){
  clear();
  // Слева №1 с отступом 0
  lcd->printn(1, 0);
  delay(2000);

  clear();
  // Справа №2 с отступом 0
  lcd->printn(2, -1);
  delay(2000);

  clear();
  // В центре №3 с отступом 0, заменяя всю строку на строке №0
  lcd->printn(3, 0, 0, 16);
  delay(2000);

  clear();
  // Слева №1 с отступом 2 от левого края на строке №1
  lcd->printn(1, 2, 1);
  delay(2000);

  clear();
  // Справа №2 с отступом 2 от правого края на строке №1
  lcd->printn(2, -3, 1);
  delay(2000);

  clear();
  // В центре №3 с отступом 4 от левого края на строке №1
  lcd->printn(3, 4, 1);
  delay(2000);
}
