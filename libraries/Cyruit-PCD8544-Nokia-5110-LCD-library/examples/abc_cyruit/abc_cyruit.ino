/*
 * abc_cyruit.ino
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
#include "Cyruit_PCD8544.h"

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// Cyruit_PCD8544 lcd = Cyruit_PCD8544(5, 6, 7);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

const byte start = 32;
const byte finish = 127;
const word utf8_start = 0x0400;
const word utf8_finish = 0x0491;
const byte scr_size = 84;
const word ms = 3000;
byte scr;

void setup(){
  // Инициализация дисплея
  lcd.begin();
  // Устанавливаем контраст
  lcd.setContrast(51);
  // Устанавливаем цвет текста
  lcd.setTextColor(BLACK);
  lcd.clearDisplay();
}

void next_page(){
  lcd.display();
  delay(ms);
  lcd.clearDisplay();
  lcd.setCursor(0, 0);
  scr++;
}

void print_utf8(word* utf8_num){
  word utf8_chr = (*utf8_num & 0x07C0) << 2 | *utf8_num & 0x003F | 0xC080;
  char* utf8 = (char*) &utf8_chr;
  for (byte i = 2; i--; ){
    lcd.print(*(utf8 + i));
  }
}

void loop() {
  scr = 1;
  // Распечатываем стандартную 7-битную таблицу символы 32-127
  for (char chr_num = start; chr_num > 0; chr_num++){
    if (chr_num == scr * scr_size + start){
      next_page();
    }
    lcd.print(chr_num);
  }
  next_page();
  scr = 1;
  // Распечатываем часть кирилической таблицы юникода 0400-0491
  // которую возможно перекодировать в cp1251 почти полностью
  for (word utf8_num = utf8_start; utf8_num <= utf8_finish; utf8_num++){
    if (utf8_num == scr * scr_size + utf8_start){
      next_page();
    }
    print_utf8(&utf8_num);
  }
  next_page();
}
