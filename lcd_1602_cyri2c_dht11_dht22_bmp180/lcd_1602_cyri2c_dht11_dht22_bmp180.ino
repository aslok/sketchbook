#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

#include <SFE_BMP180.h>
SFE_BMP180 pressure;
#define ALTITUDE 100.0

#include "dht.h"
dht DHT11;
dht DHT22;

#define DHT22_PIN 2
#define DHT11_PIN 3

void setup() {
  pinMode(13, OUTPUT);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  pressure.begin();
}

word get_uptime(){
  return micros() / 1000000;
}

void loop() {
  word uptime = get_uptime();
  while(!(get_uptime() - uptime));

  if (uptime % 5){
    return;
  }

  digitalWrite(13, HIGH);

  char buffer[17];

  // BMP 180 temp
  byte wait;
  if((wait = pressure.startTemperature())){
    delay(wait);
  }

  double temp;
  pressure.getTemperature(temp);
  dtostrf(temp, 4, 1, buffer);
  sprintf(buffer, "%s\337C", buffer);
  lcd->print(buffer, 0, 0);

  // BMP 180 press
  if((wait = pressure.startPressure(3))){
    delay(wait);
  }

  double meas;
  pressure.getPressure(meas, temp);
  dtostrf(pressure.sealevel(meas, ALTITUDE) / 133.3 * 100, 6, 2, buffer);
  lcd->print(buffer, 0, 1);

  // DHT 11 temp
  DHT11.read11(DHT11_PIN);

  sprintf(buffer, "%d", (byte) DHT11.temperature);
  lcd->print(buffer, 7, 0);

  // DHT 11 humi
  sprintf(buffer, "%d%%", (byte) DHT11.humidity);
  lcd->print(buffer, 7, 1);

  // DHT 22 temp
  DHT22.read22(DHT22_PIN);

  dtostrf(DHT22.temperature, 4, 1, buffer);
  sprintf(buffer, "%s\337C", buffer);
  lcd->print(buffer, -1, 0);

  // DHT 22 humi
  dtostrf(DHT22.humidity, 4, 1, buffer);
  sprintf(buffer, "%s%%", buffer);
  lcd->print(buffer, -1, 1);

  digitalWrite(13, LOW);
}
