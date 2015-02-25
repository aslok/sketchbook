#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "utf8_cp1251.h"

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

void setup() {
  display.begin();
  display.setContrast(51);
  //display.setTextSize(2);
  char cp1251[29];
  utf8_to_cp1251(F("Привіт сонечко"), cp1251, 29);
  display.println(cp1251);
  utf8_to_cp1251(F("Доброго дня =)"), cp1251, 29);
  display.println(cp1251);
  display.println(F("\n    \xAB \xA4 \xBB"));
  display.display();
}


void loop() {
}
