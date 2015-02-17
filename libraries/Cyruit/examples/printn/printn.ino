/*
 * printn.ino
 * Демонстрация работы метода вывода printn()
 *
 * Copyright 2015 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"
#include "Cyruit.h"

// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);

/*
// Использование символа "перенос строки"
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("Arduino UNO\n   Ардуино Уно"));
  display.printn(0);
}
void loop(){
}
*/

/*
// Использование символа "начало новой строки"
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("Привет мир!\rЯ Ардуино Уно =)"));
  display.printn(0);
  display.go(0, 1);
  display.printn(1);
}
void loop(){
}*/



// Пример анимации, первая и вторая строки выводятся в одной позиции по очереди
// Третья строка выводится один раз в начале программы
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("Arduino \rFunduino\r UNO\n   Ардуино Уно"));
  display.printn(0);
  display.printn(2);
}
void loop(){
  for (byte num = 0; num < 2; num++){
    display.go(0);
    display.printn(num);
    if (!num){
      delay(2500);
    }
  }
  delay(700);
}


/*
// Пример анимации, первая и вторая строки выводятся в разных позициях
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("Arduino Nano\rАрдуино Нано"));
}
void loop(){
  for (byte num = 0; num < 4; num++){
    display.clear();
    switch (num){
      case (0):
        display.printn(0,  0, 0);
        display.printn(1, -1, 1);
        break;
      case (1):
        display.printn(0, -1, 1);
        display.printn(1,  0, 0);
        break;
      case (2):
        display.printn(0,  0, 1);
        display.printn(1, -1, 0);
        break;
      case (3):
        display.printn(0, -1, 0);
        display.printn(1,  0, 1);
        break;
    }
    delay(1700);
  }
}*/


/*
// Проверка отображения символов украинского алфавита
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСУФХЦЧШЩЬЮЯ\r "));
}
void loop(){
  display.go(0);
  display.printn(0);
  delay(1000);
  for (byte num = 0; num < 24; num++){
    delay(2000);
    display.go(num);
    display.printn(1);
  }
  delay(2000);
  display.go(0);
  display.printn(0);
  delay(1000);
  for (byte num = 32; num-- > 10; ){
    delay(2000);
    display.go(num);
    display.printn(1);
  }
  delay(2000);
}*/


/*
// Пример работы с большим количеством строк
void setup(){
  lcd.begin();
  lcd.setContrast(51);
  display.init(F("ПРЕВЕТИЧЕГ!\rЯ АРДУИНКО!!\rЙА УЧУ РУССКИЙ\rВЫХОДИТ ПЛОХО\rВИДИШЬ ЛАЖА\rНУ ТО ТАКОЕ\rМНОГО ТЕКСТА\rМАЛО ТОЛКУ\rСМОТРИМ ДЛИНУ\rСКОЛЬКО ВЛЕЗЕТ\r"));
}
void loop(){
  for (byte num = 0; num < display.n_count(); num++){
    display.clear();
    for (byte pos = 0; pos < display.scr_height; pos++){
      display.printn((num + pos) % display.n_count(), 0, pos);
    }
    delay(1000);
  }
}*/
