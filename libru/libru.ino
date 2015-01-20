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
Sketch uses 3 508 bytes (10%) of program storage space. Maximum is 32 256 bytes.
Global variables use 309 bytes (15%) of dynamic memory, leaving 1 739 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdI2cRu.h>
LcdI2cRu* ru;

void setup()
{
  Serial.begin(9600);
  
  const char str[] PROGMEM = "ПРЕВЕТИЧЕГ!\nЙА ТУПО АРДУИНКО\nЙА УЧУ РУССКИЙ\nВЫХОДИТ ХРЕНОВО\nВИДИШЬ ЛАЖА\nНУ ТО ТАКОЕ\nМНОГО ТЕКСТА\nМАЛО ТОЛКУ\nПРОВЕРЯЕМ ДЛИНУ\nСКОЛЬКО ВЛЕЗЕТ\nПОКА ВЛАЗИТ\nДОКИНЕМ\n";
  // set the LCD address to 0x27 for a 16 chars and 2 line display
  ru = new LcdI2cRu(0x27, 16, 2);
  ru->init(str);
}

void loop()
{
  for (int num = 0; num < ru->c; num++){
    ru->printn(num);
    delay(1000);
    if (num & 1){
      delay(500);
      ru->clear();
    }else{
      ru->setCursor(0, 1);
    }
  }
}

