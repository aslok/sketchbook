/*
Cyrstal
Пример работы с большим количеством строк

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
  lcd->init(F("ПРЕВЕТИЧЕГ!\rЯ ТУПО АРДУИНКО\rЙА УЧУ РУССКИЙ\rВЫХОДИТ ХРЕНОВО\rВИДИШЬ ЛАЖА\rНУ ТО ТАКОЕ\rМНОГО ТЕКСТА\rМАЛО ТОЛКУ\rПРОВЕРЯЕМ ДЛИНУ\rСКОЛЬКО ВЛЕЗЕТ\rПОКА ВЛАЗИТ\rДОКИНЕМ ИШО\rЧТОБ БЫЛО\rЧЕМ БОГАТЫ\rЛЕВ ТОЛСТОЙ\rВОЙНА "));
}
void loop(){
  for (byte num = 0; num < lcd->f; num++){
    lcd->clear();
    lcd->printn(num);
    lcd->go(0, 1);
    if (num + 1 < lcd->f){
      lcd->printn(num + 1);
    }else{
      lcd->printn(0);
    }
    delay(1000);
  }
}
