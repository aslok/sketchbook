#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

#include "dht.h"
dht DHT;

#define DHT11_PIN 2

void setup() {
  pinMode(13, OUTPUT);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->print(F("Температура\nВлажность"));
}

void loop() {
  digitalWrite(13, HIGH);
  DHT.read11(DHT11_PIN);

  char buffer[5];

  char suf[3]{223, 'C'};
  sprintf(buffer, "%d%s", (byte) DHT.temperature, suf);
  lcd->print(buffer, -1, 0);

  sprintf(buffer, "%d%s", (byte) DHT.humidity, "%");
  lcd->print(buffer, -1, 1);

  digitalWrite(13, LOW);
  delay(2000);
}

