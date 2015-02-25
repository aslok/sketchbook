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

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);

void setup(){
  lcd.begin();
  lcd.setContrast(51);
}
void loop(){
  display.clear();
  // Использование символа "начало новой строки"
  display.init(F("Привет мир!\rЯ Ардуино Уно =)"));
  display.printn(0);
  display.go(0, 1);
  display.printn(1);
  delay(2000);

  display.clear();
  // Использование символа "перенос строки"
  display.init(F("Arduino UNO\n   Ардуино Уно"));
  display.printn(0);
  delay(2000);
}
