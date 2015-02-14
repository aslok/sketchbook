/*
Sketch uses 30 386 bytes (98%) of program storage space. Maximum is 30 720 bytes.
Global variables use 575 bytes (28%) of dynamic memory, leaving 1 473 bytes for local variables. Maximum is 2 048 bytes.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit.h"

// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Cyruit lcd = Cyruit(3, 4, 5, 6, 7, 51);

#include "imgs.c"

const byte ms = 75;
byte current = 0;

void setup() {
}

void loop() {
  if (current == imgs_cnt){
    current = 0;
  }
  lcd.drawBitmap(0, 8, imgs[current], 84, 40, BLACK, WHITE);
  if (      current > 2  && current < 7){
    lcd.print(F("ЗДРАВСТВУЙТЕ!"), -1, 0);
  }else if (current > 8  && current < 12){
    lcd.print(F("ПАРУ СЛОВ"),     -1, 0);
  }else if (current > 12 && current < 16){
    lcd.print(F("О ПОЛИТИКЕ"),    -1, 0);
  }else if (current > 16 && current < 20){
    lcd.print(F("БЛЯ"),           -4, 0);
  }else if (current > 20 && current < 26){
    lcd.print(F("ЗАЦЕНИ ПРИКОЛ"), -1, 0);
  }else if (current > 27 && current < 31){
    lcd.print(F("ПОЛИТИКА"),      -1, 0);
  }else if (current > 33 && current < 39){
    lcd.print(F("ПОЛИТИКА!"),     -1, 0);
  }else if (current > 41 && current < 46){
    lcd.print(F("ПОЙДЕМ ДАЛЬШЕ"), -1, 0);
  }else{
    lcd.print(F("              "), 0, 0);
  }
  delay(ms);
  current++;
}

