/*
Sketch uses 9 002 bytes (29%) of program storage space. Maximum is 30 720 bytes.
Global variables use 909 bytes (44%) of dynamic memory, leaving 1 139 bytes for local variables. Maximum is 2 048 bytes.
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
  //Serial.begin(57200);
  // Инициализация дисплея
  lcd.begin();
  // Устанавливаем контраст
  lcd.setContrast(51);
  // Устанавливаем цвет текста
  lcd.setTextColor(BLACK);
}

void loop() {
  display.print("Добрий день!", -1, 0);
  delay(1000);
  display.print("Як справи?", 0, 1);
  delay(1000);
  display.print("Поміркуй про щось смачне", -4, 3);
  delay(1000);
  display.print("банан", 0, 4, 14);
  delay(3000);
  display.clear();
  delay(1000);
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
