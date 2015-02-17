/*
 * en2ru.ino
 * Пример анимации, первая и вторая строки выводятся в разных позициях
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
}
