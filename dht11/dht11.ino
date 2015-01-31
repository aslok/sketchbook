#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;

#include <dht.h>
dht DHT;

#define DHT11_PIN 2

void setup() {
  Serial.begin(57200);
  pinMode(13, OUTPUT);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->print(F("Температура\nВлажность"));
}

void loop() {
  digitalWrite(13, HIGH);

  char buffer[4];
  buffer[3] = 0;
  DHT.read11(DHT11_PIN);

  float2intchar(DHT.temperature, buffer);
  buffer[2] = 'C';
  lcd->print(buffer, -1, 0);

  float2intchar(DHT.humidity, buffer);
  buffer[2] = '%';
  lcd->print(buffer, -1, 1);

  Serial.println(DHT.temperature);
  digitalWrite(13, LOW);
  delay(2000);
}

void float2intchar(float num, char *str){
  sprintf(str, "%d", (uint8_t) num);
}
