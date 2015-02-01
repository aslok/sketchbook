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
}
