#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

#include "dht.h"
dht DHT;

#define DHT22_PIN 2

void setup() {
  pinMode(13, OUTPUT);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->print(F("Температ.\nВлажность"));
}

void loop() {
  digitalWrite(13, HIGH);
  DHT.read22(DHT22_PIN);

  char buffer[5];

  char suf[3]{223, 'C'};
  dtostrf(DHT.temperature, 4, 1, buffer);
  sprintf(buffer, "%s%s", buffer, suf);
  lcd->print(buffer, -1, 0);

  dtostrf(DHT.humidity, 4, 1, buffer);
  sprintf(buffer, "%s%s", buffer, "%");
  lcd->print(buffer, -1, 1);

  digitalWrite(13, LOW);
  delay(2000);
}

