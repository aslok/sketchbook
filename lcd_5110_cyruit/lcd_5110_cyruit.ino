#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit.h"

// Software SPI (slower updates, more flexible pin options):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Cyruit lcd = Cyruit(3, 4, 5, 6, 7);

// Hardware SPI (faster, but must use certain hardware pins):
// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
//Cyruit lcd = Cyruit(3, 4, 5);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

void setup(){
  Serial.begin(57200);
}

void loop() {
  lcd.print(F("Привет, МИР!"), 0, 2, 14);
  delay(300);
  lcd.print(F("ривет, МИР! "), 0, 2, 14);
  delay(300);
  lcd.print(F("ивет, МИР! П"), 0, 2, 14);
  delay(300);
  lcd.print(F("вет, МИР! Пр"), 0, 2, 14);
  delay(300);
  lcd.print(F("ет, МИР! При"), 0, 2, 14);
  delay(300);
  lcd.print(F("т, МИР! Прив"), 0, 2, 14);
  delay(300);
  lcd.print(F(", МИР! Приве"), 0, 2, 14);
  delay(300);
  lcd.print(F(" МИР! Привет"), 0, 2, 14);
  delay(300);
  lcd.print(F("МИР! Привет,"), 0, 2, 14);
  delay(300);
  lcd.print(F("ИР! Привет, "), 0, 2, 14);
  delay(300);
  lcd.print(F("Р! Привет, М"), 0, 2, 14);
  delay(300);
  lcd.print(F("! Привет, МИ"), 0, 2, 14);
  delay(300);
}
