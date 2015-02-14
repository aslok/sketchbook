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

void setup(){
  Serial.begin(57200);
  // Инициализация дисплея
  lcd.begin();
  // Устанавливаем контраст
  lcd.setContrast(51);
  // Устанавливаем цвет текста
  lcd.setTextColor(BLACK);
  lcd.print("є");
  lcd.display();
}

void loop() {
}

void printBits(byte myByte){
  for(byte mask = 0x80; mask; mask >>= 1){
    if(mask & myByte)
      Serial.print('1');
    else
      Serial.print('0');
  }
  Serial.print('\n');
}

void printBits(word myByte){
  for(word mask = 0x8000; mask; mask >>= 1){
    if (mask == 0x80){
      Serial.print(' ');
    }
    if(mask & myByte)
      Serial.print('1');
    else
      Serial.print('0');
  }
  Serial.print('\n');
}

void printBits(int myByte){
  printBits((word) myByte);
}
