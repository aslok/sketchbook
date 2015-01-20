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
Sketch uses 6 660 bytes (20%) of program storage space. Maximum is 32 256 bytes.
Global variables use 614 bytes (29%) of dynamic memory, leaving 1 434 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdI2cRu.h>
LcdI2cRu* ru;

void setup()
{
  Serial.begin(9600);
  
  ru = new LcdI2cRu(0x27, 16, 2);
  // Bytes -  386
  // Chars -  218  
  // String - 236
  ru->init(F("ПРЕВЕТИЧЕГ!\nЙА ТУПО АРДУИНКО\nЙА УЧУ РУССКИЙ\nВЫХОДИТ ХРЕНОВО\nВИДИШЬ ЛАЖА\nНУ ТО ТАКОЕ\nМНОГО ТЕКСТА\nМАЛО ТОЛКУ\nПРОВЕРЯЕМ ДЛИНУ\nСКОЛЬКО ВЛЕЗЕТ\nПОКА ВЛАЗИТ\nДОКИНЕМ ИШО\nЧТОБ БЫЛО\nЧЕМ БОГАТЫ\nЛЕВ ТОЛСТОЙ\nВОЙНА "));
}

void loop()
{
  for (int num = 0; num < ru->c; num++){
    ru->printn(num);
    delay(500);
    if (num & 1){
      delay(250);
      ru->clear();
    }else{
      ru->setCursor(0, 1);
    }
  }
}

