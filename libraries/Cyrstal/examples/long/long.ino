/*
Cyrstal
Пример работы с большим количеством строк

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Uno)

Sketch uses 7,228 bytes (22.4%) of program storage space. Maximum is 32,256 bytes.
Global variables use 58 bytes (2.8%) of dynamic memory, leaving 1,990 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;

byte count;
void setup(){
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2);
  lcd->init(F("Каждый раз при\rинициализации\rуказателя\rиспользовался\rадрес той или\rиной переменной.\rЭто было связано\rс тем, что\rкомпилятор\rязыка С++\rавтоматически\rвыделяет память\rдля хранения\rпеременных\rи с помощью\rуказателя можно\rбез последствий\rработать с этой\rвыделенной\rобластью.\rВместе с тем\rсуществуют\rфункции\rmalloc и free,\rпозволяющие\rвыделять и\rосвобождать\rпамять по мере\rнеобходимости\rИспользование\rуказателей\rдосталось в\r\"наследство\" от\rязыка С.\rЧтобы упростить\rпроцесс\rизменения\rпараметров в С++\rвводится такое\rпонятие как\rссылка. Ссылка\rпредставляет\rсобой псевдоним\r(или второе\rимя), который\rпрограммы могут\rиспользовать для\rобращения к\rпеременной. Для\rобъявления\rссылки в\rпрограмме\rиспользуется\rзнак & перед ее\rименем."));
  count = lcd->count();
}
void loop(){
  for (byte num = 0; num < count; num++){
    lcd->clear();
    lcd->printn(num);
    delay(400);
    lcd->go(0, 1);
    if (num + 1 < count){
      lcd->printn(num + 1);
    }else{
      lcd->printn(0);
    }
    delay(400);
  }
}
