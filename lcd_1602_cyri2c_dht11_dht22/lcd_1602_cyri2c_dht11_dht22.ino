#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

#include "dht.h"
dht DHT;

#define DHT22_PIN 2
#define DHT11_PIN 3

void setup() {
  pinMode(13, OUTPUT);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
}

void loop() {
  digitalWrite(13, HIGH);

  char buffer[6];

  DHT.read22(DHT22_PIN);

  dtostrf(DHT.temperature, 4, 1, buffer);
  sprintf(buffer, "%s\337C", buffer);
  lcd->print(buffer, 0, 0);

  dtostrf(DHT.humidity, 4, 1, buffer);
  sprintf(buffer, "%s%%", buffer);
  lcd->print(buffer, 0, 1);

  DHT.read11(DHT11_PIN);

  sprintf(buffer, "%d\337C", (byte) DHT.temperature);
  lcd->print(buffer, -1, 0);

  sprintf(buffer, "%d%%", (byte) DHT.humidity);
  lcd->print(buffer, -1, 1);

  digitalWrite(13, LOW);
  delay(2000);
}
