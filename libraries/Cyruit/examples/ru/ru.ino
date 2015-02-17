/*
 * ru.ino
 * Проверка отображения символов русского алфавита
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
  display.init(F("АБВГДЕЁЖЗИЙКЛМНОПРСУФХЦЧШЩЪЫЬЭЮЯ\r "));
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
}
