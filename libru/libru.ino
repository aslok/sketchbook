/*
LibRu
Test russification of lcd display connected by i2c with LcdI2cRu library

Hardware:
LCD I2C PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 21.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 6 192 bytes (19%) of program storage space. Maximum is 32 256 bytes.
Global variables use 516 bytes (25%) of dynamic memory, leaving 1 532 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdI2cRu.h>
LcdI2cRu* lcd;

void setup()
{
  Serial.begin(9600);
  
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  
  lcd->init(F("Привет мир!\nЯ Ардуино Уно =)"));
  // lcd->init(F("ПРЕВЕТИЧЕГ!\nЙА ТУПО АРДУИНКО\nЙА УЧУ РУССКИЙ\nВЫХОДИТ ХРЕНОВО\nВИДИШЬ ЛАЖА\nНУ ТО ТАКОЕ\nМНОГО ТЕКСТА\nМАЛО ТОЛКУ\nПРОВЕРЯЕМ ДЛИНУ\nСКОЛЬКО ВЛЕЗЕТ\nПОКА ВЛАЗИТ\nДОКИНЕМ ИШО\nЧТОБ БЫЛО\nЧЕМ БОГАТЫ\nЛЕВ ТОЛСТОЙ\nВОЙНА "));
  // lcd->init(F("АБВГДЕЖЗИКЛМНО\nПРСТУФЧХЦШЬЫЭЮЯ"));
}

void loop()
{
  uint8_t num;
  for (num = 0; num < (lcd->c - 1); num++){
    lcd->clear();
    lcd->printn(num);
    lcd->setCursor(0, 1);
    lcd->printn(num + 1);
    delay(1000);
  }
  lcd->clear();
  lcd->printn(num);
  lcd->setCursor(0, 1);
  lcd->printn(0);
  delay(1000);
}

