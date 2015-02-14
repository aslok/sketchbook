/*
Sketch uses 7 096 bytes (23%) of program storage space. Maximum is 30 720 bytes.
Global variables use 623 bytes (30%) of dynamic memory, leaving 1 425 bytes for local variables. Maximum is 2 048 bytes.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"

// Software SPI (slower updates, more flexible pin options):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);

// Hardware SPI (faster, but must use certain hardware pins):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
//Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5);
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
