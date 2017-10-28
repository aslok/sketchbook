/*
Cyrstal_i2c
Пример анимации, первая и вторая строки выводятся в разных позициях

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Nano)

Sketch uses 6,768 bytes (22.0%) of program storage space. Maximum is 30,720 bytes.
Global variables use 267 bytes (13.0%) of dynamic memory, leaving 1,781 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "Wire.h"

#include "LiquidCrystal_I2C.h"
#include "Cyrstal_core.h"
#include "Cyrstal_i2c.h"
Cyrstal_i2c* lcd;


void setup(){
  lcd = new Cyrstal_i2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino Nano\rАрдуино Нано"));
}
void loop(){
  for (byte num = 0; num < 4; num++){
    lcd->clear();
    switch (num){
      case (0):
        lcd->go(0, 0);
        break;
      case (1):
        lcd->go(4, 1);
        break;
      case (2):
        lcd->go(0, 1);
        break;
      case (3):
        lcd->go(4, 0);
        break;
    }
    lcd->printn(0);
    switch (num){
      case (0):
        lcd->go(4, 1);
        break;
      case (1):
        lcd->go(0, 0);
        break;
      case (2):
        lcd->go(4, 0);
        break;
      case (3):
        lcd->go(0, 1);
        break;
    }
    lcd->printn(1);
    delay(1700);
  }
}
