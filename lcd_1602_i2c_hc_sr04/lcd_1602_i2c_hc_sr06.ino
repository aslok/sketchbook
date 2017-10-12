#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "NewPing.h"
const byte trigger_pin = 12;
const byte echo_pin    = 11;
const byte max_distance = 150;
NewPing sonar(trigger_pin, echo_pin, max_distance);

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void loop() {
  delay(400);                      // Wait 400ms between pings
  
  unsigned int uS = sonar.ping();  // Send ping, get ping time in microseconds (uS).
  
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(3, 0);             // set cursor to column 3, line 0 (first row)
  lcd.print("Ping: ");
  lcd.print(uS / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
  lcd.print("cm");
}
