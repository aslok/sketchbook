/*
Sketch uses 6 936 bytes (22%) of program storage space. Maximum is 30 720 bytes.
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
//Cyruit lcd = Cyruit(3, 4, 5);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

const byte start = 33;
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
  byte chr = start;
  scr = 1;
  while (chr < finish){
    lcd.print((char) chr);
    chr++;
    if (chr > (scr * scr_size + start)){
      next_page();
    }
  }
  next_page();
}
