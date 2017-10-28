/*
Cyrstal_i2c
Пример анимации, первая и вторая строки выводятся в одной позиции по очереди
Третья строка выводится один раз в начале программы

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Nano)

Sketch uses 6,736 bytes (21.9%) of program storage space. Maximum is 30,720 bytes.
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
  lcd->init(F("Arduino \rFunduino\r UNO\n     Ардуино Уно"));
  lcd->printn(0);
  lcd->printn(2);
}
void loop(){
  for (byte num = 0; num < 2; num++){
    lcd->go(0);
    lcd->printn(num);
    if (!num){
      delay(2500);
    }
  }
  delay(700);
}
