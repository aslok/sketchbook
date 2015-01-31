// Sketch uses 8 988 bytes (29%) of program storage space. Maximum is 30 720 bytes.
// Global variables use 245 bytes (11%) of dynamic memory, leaving 1 803 bytes for local variables. Maximum is 2 048 bytes.


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;

// Пример анимации, первая и вторая строки выводятся в разных позициях
void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
}
void loop(){
  for (uint8_t num = 0; num < 4; num++){
    lcd->clear();
    switch (num){
      case (0):
        lcd->setCursor(0, 0);
        break;
      case (1):
        lcd->setCursor(4, 1);
        break;
      case (2):
        lcd->setCursor(0, 1);
        break;
      case (3):
        lcd->setCursor(4, 0);
        break;
    }
    lcd->print(F("Arduino Nano"));
    switch (num){
      case (0):
        lcd->setCursor(4, 1);
        break;
      case (1):
        lcd->setCursor(0, 0);
        break;
      case (2):
        lcd->setCursor(4, 0);
        break;
      case (3):
        lcd->setCursor(0, 1);
        break;
    }
    lcd->print(F("Ардуино Нано"));
    delay(1700);
  }
}
