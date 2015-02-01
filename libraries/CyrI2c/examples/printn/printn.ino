/*
CyrLib
Test cyrillization of lcd display connected by i2c with CyrI2c library

Hardware:
LCD I2C PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
modified 01.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/
/*
Sketch uses 9 264 bytes (30%) of program storage space. Maximum is 30 720 bytes.
Global variables use 245 bytes (11%) of dynamic memory, leaving 1 803 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;


// Использование символа "перенос строки"
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino UNO\n     Ардуино Уно"));
  lcd->printn(0);
}
void loop(){
}


/*
// Использование символа "начало новой строки"
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Привет мир!\rЯ Ардуино Уно =)"));
  lcd->printn(0);
  lcd->go(0, 1);
  lcd->printn(1);
}
void loop(){
}*/


/*
// Пример анимации, первая и вторая строки выводятся в одной позиции по очереди
// Третья строка выводится один раз в начале программы
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
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
}*/


/*
// Пример анимации, первая и вторая строки выводятся в разных позициях
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
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
}*/


/*
// Проверка отображения символов русского алфавита
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  lcd->init(F("АБВГДЕЁЖЗИЙКЛМНОПРСУФХЦЧШЩЪЫЬЭЮЯ\r "));
}
void loop(){
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 0; num < 24; num++){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 32; num-- > 10; ){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
}*/


/*
// Проверка отображения символов украинского алфавита
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  lcd->init(F("АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСУФХЦЧШЩЬЮЯ\r "));
}
void loop(){
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 0; num < 24; num++){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
  lcd->go(0);
  lcd->printn(0);
  delay(1000);
  for (byte num = 32; num-- > 10; ){
    delay(2000);
    lcd->go(num);
    lcd->printn(1);
  }
  delay(2000);
}*/


/*
// Пример работы с большим количеством строк
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("ПРЕВЕТИЧЕГ!\rЯ ТУПО АРДУИНКО\rЙА УЧУ РУССКИЙ\rВЫХОДИТ ХРЕНОВО\rВИДИШЬ ЛАЖА\rНУ ТО ТАКОЕ\rМНОГО ТЕКСТА\rМАЛО ТОЛКУ\rПРОВЕРЯЕМ ДЛИНУ\rСКОЛЬКО ВЛЕЗЕТ\rПОКА ВЛАЗИТ\rДОКИНЕМ ИШО\rЧТОБ БЫЛО\rЧЕМ БОГАТЫ\rЛЕВ ТОЛСТОЙ\rВОЙНА "));
}
void loop(){
  for (byte num = 0; num < lcd->c; num++){
    lcd->clear();
    lcd->printn(num);
    lcd->go(0, 1);
    if (num + 1 < lcd->c){
      lcd->printn(num + 1);
    }else{
      lcd->printn(0);
    }
    delay(1000);
  }
}*/

