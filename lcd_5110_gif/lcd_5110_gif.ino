/*
Sketch uses 29 424 bytes (95%) of program storage space. Maximum is 30 720 bytes.
Global variables use 596 bytes (29%) of dynamic memory, leaving 1 452 bytes for local variables. Maximum is 2 048 bytes.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "utf8_cp1251.h"

// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

#include "imgs.c"

const byte ms = 75;
byte current = 0;

void setup() {
  display.begin();
  display.setContrast(51);
}

void say(const __FlashStringHelper* str){
  char cp1251[29];
  display.fillRect(0, 0, LCDWIDTH, 8, WHITE);
  utf8_to_cp1251(str, cp1251, 29);
  display.setCursor(0, 0);
  display.println(cp1251);
}

void loop() {
  if (current == imgs_cnt){
    current = 0;
  }
  display.drawBitmap(0, 8, imgs[current], 84, 40, BLACK, WHITE);
  if (      current > 2  && current < 7){
    say(F(" ЗДРАВСТВУЙТЕ!"));
  }else if (current > 8  && current < 12){
    say(F("     ПАРУ СЛОВ"));
  }else if (current > 12 && current < 16){
    say(F("    О ПОЛИТИКЕ"));
  }else if (current > 16 && current < 20){
    say(F("        БЛЯ   "));
  }else if (current > 20 && current < 26){
    say(F(" ЗАЦЕНИ ПРИКОЛ"));
  }else if (current > 27 && current < 31){
    say(F("      ПОЛИТИКА"));
  }else if (current > 33 && current < 39){
    say(F("     ПОЛИТИКА!"));
  }else if (current > 41 && current < 46){
    say(F(" ПОЙДЕМ ДАЛЬШЕ"));
  }else{
    say(F("              "));
  }
  display.display();
  delay(ms);
  current++;
}

