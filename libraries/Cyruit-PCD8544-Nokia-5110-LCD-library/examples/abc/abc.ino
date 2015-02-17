/*
 * abc.ino
 * Демонстрация доступных для использования символов
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

// Software SPI (slower updates, more flexible pin options):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 lcd = Adafruit_PCD8544(3, 4, 5, 6, 7);

// Hardware SPI (faster, but must use certain hardware pins):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
//Adafruit_PCD8544 lcd = Adafruit_PCD8544(3, 4, 5);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

const byte start = 32;
const byte finish = 255;
const byte scr_size = 84;
const word ms = 2000;
byte scr;

void setup(){
  // Инициализация дисплея
  lcd.begin();
  // Устанавливаем контраст
  lcd.setContrast(51);
  // Устанавливаем цвет текста
  lcd.setTextColor(BLACK);
}

void next_page(){
  lcd.display();
  delay(ms);
  lcd.clearDisplay();
  lcd.setCursor(0, 0);
  scr++;
}

void loop() {
  scr = 1;
  for (word chr_num = start; chr_num <= finish; chr_num++){
    if (chr_num == (scr * scr_size + start)){
      next_page();
    }
    lcd.print((char) chr_num);
  }
  next_page();
}
