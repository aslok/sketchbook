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


void setup(){
  Serial.begin(9600);  
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  
  // lcd->init(F("Привет мир! Я Ардуино Уно =)"));
  lcd->init(F("Привет мир!\nЯ Ардуино Уно =)"));
  lcd->printn(0);
  //Serial.println(lcd->scr_h);
}
void loop(){
}


/*void setup(){
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("АБВГДЕЖЗИКЛМНОПРСТУФЧХЦШЬЫЭЮЯ"));
  lcd->printn(0);
}
void loop(){
}*/


/*void setup(){
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino UNO\n     Ардуино Уно"));
  lcd->printn(0);
}
void loop(){
}*/


/*void setup(){
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Привет мир!\rЯ Ардуино Уно =)"));
  lcd->printn(0);
  lcd->setCursor(0, 1);
  lcd->printn(1);
}
void loop(){
}*/


/*void setup(){
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino \rFunduino\r UNO\n     Ардуино Уно"));
  lcd->printn(0);
  lcd->printn(2);
}
void loop(){
  for (uint8_t num = 0; num < 2; num++){
    lcd->home();
    lcd->printn(num);
    if (!num){
      delay(2500);
    }
  }
  delay(700);
}*/


/*void setup(){
  Serial.begin(9600);  
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Привет мир!\nЯ Ардуино Уно =)"));
  lcd->printn(0);
  Serial.println(lcd->scr_h);
  // ПРИВЕТ МИР!Я АРДУИНО УНО =)
}
void loop(){
}*/


/*void setup(){
  lcd = new LcdI2cRu(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("ПРЕВЕТИЧЕГ!\rЙА ТУПО АРДУИНКО\rЙА УЧУ РУССКИЙ\rВЫХОДИТ ХРЕНОВО\rВИДИШЬ ЛАЖА\rНУ ТО ТАКОЕ\rМНОГО ТЕКСТА\rМАЛО ТОЛКУ\rПРОВЕРЯЕМ ДЛИНУ\rСКОЛЬКО ВЛЕЗЕТ\rПОКА ВЛАЗИТ\rДОКИНЕМ ИШО\rЧТОБ БЫЛО\rЧЕМ БОГАТЫ\rЛЕВ ТОЛСТОЙ\rВОЙНА "));
}
void loop(){
  for (uint8_t num = 0; num < lcd->c; num++){
    lcd->clear();
    lcd->printn(num);
    lcd->setCursor(0, 1);
    if (num + 1 < lcd->c){
      lcd->printn(num + 1);
    }else{
      lcd->printn(0);
    }
    delay(1000);
  }
}*/

