/*
Cyrstal_i2c
Использование символа "перенос строки"

Hardware:
LCD PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 28.10.2017
by Fust Vitaliy
with Arduino 1.8.3 (tested on Arduino Nano)

Sketch uses 6,384 bytes (20.8%) of program storage space. Maximum is 30,720 bytes.
Global variables use 279 bytes (13.6%) of dynamic memory, leaving 1,769 bytes for local variables. Maximum is 2,048 bytes.
*/

#include "Wire.h"

#include "LiquidCrystal_I2C.h"
#include "Cyrstal_core.h"
#include "Cyrstal_i2c.h"
Cyrstal_i2c* lcd;


void setup(){
  lcd = new Cyrstal_i2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino UNO\n     Ардуино Уно"));
  lcd->printn(0);
}
void loop(){
}
