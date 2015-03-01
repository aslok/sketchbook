#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

void setup(){
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
}
void loop(){
}
