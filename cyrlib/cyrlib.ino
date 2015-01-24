/*
CyrLib
Test cyrillization of lcd display connected by i2c with CyrI2c library

Hardware:
LCD I2C PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 23.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 9 248 bytes (28%) of program storage space. Maximum is 32 256 bytes.
Global variables use 245 bytes (11%) of dynamic memory, leaving 1 803 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;

void setup(){
  Serial.begin(9600);  
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  
  lcd->init(F("Arduino \rFunduino\r UNO\n     Ардуино Уно"));
  lcd->printn(0);
  lcd->printn(2);
  //lcd->printn(0);
  //for (uint8_t num = 0; lcd->scr[num]; num++){
  //  Serial.println((unsigned char) lcd->scr[num]);
  //}
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
}

