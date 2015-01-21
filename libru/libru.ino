/*
LibRu
Test russification of lcd display connected by i2c with LcdI2cRu library

Hardware:
LCD I2C PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 6 450 bytes (19%) of program storage space. Maximum is 32 256 bytes.
Global variables use 614 bytes (29%) of dynamic memory, leaving 1 434 bytes for local variables. Maximum is 2 048 bytes.
Sketch uses 6 618 bytes (20%) of program storage space. Maximum is 32 256 bytes.
Global variables use 714 bytes (34%) of dynamic memory, leaving 1 334 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdI2cRu.h>
LcdI2cRu* ru;

void setup()
{
  Serial.begin(9600);
  
  ru = new LcdI2cRu(0x27, 16, 2);
  ru->backlight();
  
  // ru->init("");
  // ru->init(F(""));
  ru->init(F("Привет мир!\nЯ Ардуино Уно =)"));
  // ru->init(F("ПРЕВЕТИЧЕГ!\nЙА ТУПО АРДУИНКО\nЙА УЧУ РУССКИЙ\nВЫХОДИТ ХРЕНОВО\nВИДИШЬ ЛАЖА\nНУ ТО ТАКОЕ\nМНОГО ТЕКСТА\nМАЛО ТОЛКУ\nПРОВЕРЯЕМ ДЛИНУ\nСКОЛЬКО ВЛЕЗЕТ\nПОКА ВЛАЗИТ\nДОКИНЕМ ИШО\nЧТОБ БЫЛО\nЧЕМ БОГАТЫ\nЛЕВ ТОЛСТОЙ\nВОЙНА "));
}

void loop()
{
  int num;
  for (num = 0; num < (ru->c - 1); num++){
    ru->clear();
    ru->printn(num);
    ru->setCursor(0, 1);
    ru->printn(num + 1);
    delay(1000);
  }
  ru->clear();
  ru->printn(num);
  ru->setCursor(0, 1);
  ru->printn(0);
  delay(1000);
}

