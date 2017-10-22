/*
 * time_ds1307_lcd_1602_cyri2c_v3.ino
 * Time v3.0
 * Time and date on lcd display (used rtc timer) with control by keypad 1x3
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 * LCD I2C PCF8574
 *   http://habrahabr.ru/post/219137/
 *   http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514
 * Keys 1x3
 *
 *
 * created 05.05.2016
 * modifid 06.05.2016
 * with Arduino 1.6.5 (tested on Arduino Nano)
 *
 * Copyright 2016 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

#include "HMC5883L.h"
HMC5883L compass;
Vector compass_norm;

#include "RTClib.h"
RTC_DS1307 rtc;
DateTime now;
unsigned long prevtime;

#include "SFE_BMP180.h"
SFE_BMP180 pressure;
#define ALTITUDE 0

#define DHT22_PIN A3
#include "dht.h"
dht DHT22;

#include "SoftwareSerial.h"
SoftwareSerial ESPserial(2, 3); // RX | TX

const byte BUTTON1_PIN = 4;
const byte BUTTON2_PIN = 5;
const byte BUTTON3_PIN = 6;
boolean b1 = false;
boolean b2 = false;
boolean b3 = false;
boolean button1 = false;
boolean button2 = false;
boolean button3 = false;

boolean debug = false;

unsigned long ms;
enum display_enum{
  time,
  //comp,
  temp
};
byte display_max = 1; //2;
display_enum display = time;
display_enum prev_display = display;
boolean cmd_mode_1 = false;
boolean cmd_mode_2 = false;
boolean cmd_mode_3 = false;
unsigned long cmd_start_1 = 0;
unsigned long cmd_start_2 = 0;
unsigned long cmd_start_3 = 0;

void setup() {
  debug = false;

  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  digitalWrite(BUTTON1_PIN, LOW);
  digitalWrite(BUTTON2_PIN, LOW);
  digitalWrite(BUTTON3_PIN, LOW);
  pinMode (BUTTON1_PIN, INPUT_PULLUP);
  pinMode (BUTTON2_PIN, INPUT_PULLUP);
  pinMode (BUTTON3_PIN, INPUT_PULLUP);

  /*while (!compass.begin())
  {
    lcd->print("Нет соединения", 0, 0, 16);
    delay(500);
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_15HZ);
  compass.setSamples(HMC5883L_SAMPLES_1);*/
  
  if (debug){
    Serial.begin(9600);
  }

  Serial.begin(9600);
  // Start the software serial for communication with the ESP8266
  ESPserial.begin(9600);  
  
  pressure.begin();
  now = rtc.now();
  hello(now.hour());
}

void loop() {
  // listen for communication from the ESP8266 and then write it to the serial monitor
  if (ESPserial.available()){
    Serial.write(ESPserial.read());
  }

  // listen for user input and send it to the ESP8266
  if (Serial.available()){
    ESPserial.write(Serial.read());
  }

  ms = millis();

  read_buttons();

  if (button1){
    display = (display_enum) (display + 1);
  }
  if (button2){
    display = (display_enum) 0;
  }
  if (button3){
    display = (display_enum) (display - 1);
  }
  if (display > display_max){
    display = (display_enum) 0;
  }
  if (display < 0){
    display = (display_enum) display_max;
  }

  if (ms - prevtime > 1000 || prev_display != display){
    prevtime = ms;
    if (prev_display != display){
      prev_display = display;
      lcd->clear();
    }
    switch (display) {
        case time:
          show_time();
          break;
        /*case comp:
          show_compass();
          break;*/
        case temp:
          show_temp();
          break;
    }
  }
  if (debug){
    if (button1 || button2 || button3){
      Serial.print("Нажата копка ");
      if (button1) {
        Serial.print("один ");
      }
      if (button2) {
        Serial.print("два ");
      }
      if (button3) {
        Serial.print("три");
      }
      Serial.println();
    }
  }
}

void read_buttons(){
  b1 = digitalRead(BUTTON1_PIN) != 1;
  b2 = digitalRead(BUTTON2_PIN) != 1;
  b3 = digitalRead(BUTTON3_PIN) != 1;
  button1 = false;
  button2 = false;
  button3 = false;

  if (!b1){
    cmd_mode_1 = true;
  }
  if (!b2){
    cmd_mode_2 = true;
  } 
  if (!b3){
    cmd_mode_3 = true;
  }

  if (cmd_mode_1 && b1){
    cmd_mode_1 = false;
    cmd_start_1 = ms;
  }
  if (cmd_mode_2 && b2){
    cmd_mode_2 = false;
    cmd_start_2 = ms;
  }
  if (cmd_mode_3 && b3){
    cmd_mode_3 = false;
    cmd_start_3 = ms;
  }

  if (cmd_mode_1 && cmd_start_1 && ms - cmd_start_1 <= 50){
    cmd_start_1 = 0;
  } 
  if (cmd_mode_2 && cmd_start_2 && ms - cmd_start_2 <= 50){
    cmd_start_2 = 0;
  }
  if (cmd_mode_3 && cmd_start_3 && ms - cmd_start_3 <= 50){
    cmd_start_3 = 0;
  }

  if (!cmd_mode_1 && cmd_start_1 && (int) (ms - cmd_start_1) > 50 && b1){
    cmd_start_1 = cmd_start_1 + 1000;
    button1 = true;
  }
  if (!cmd_mode_2 && cmd_start_2 && (int) (ms - cmd_start_2) > 50 && b2){
    cmd_start_2 = cmd_start_2 + 1000;
    button2 = true;
  }
  if (!cmd_mode_3 && cmd_start_3 && (int) (ms - cmd_start_3) > 50 && b3){
    cmd_start_3 = cmd_start_3 + 1000;
    button3 = true;
  }
}

void show_time(){
  now = rtc.now();
  lcd->init(F("Нд\rПн\rВт\rСр\rЧт\rПт\rСб"));
  lcd->printn(now.dayOfWeek(), -1, 0);
  lcd->init(F("січня\rлютого\rберезня\rквітня\rтравня\rчервня\rлипня\rсерпня\rвересня\rжовтня\rлистопада\rгрудня"));
  lcd->printn(now.month() - 1, 3, 0);

  char buffer[9];
  buffer[8] = 0;
  sprintf(buffer, "%02d", now.day());
  lcd->print(buffer, 0, 0);
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd->print(buffer, 4, 1);
}

void show_compass(){
  /*
  http://magnetic-declination.com
    You clicked here:
    Latitude: 49° 29' 54.7" N
    Longitude: 24° 42' 55" E
    Magnetic declination: +6° 1' 
    Declination is POSITIVE (EAST)
    Inclination: 66° 10' 
    Magnetic field strength: 49615.4 nT
  */

  compass_norm = compass.readNormalize();
  float heading = atan2(compass_norm.YAxis, compass_norm.XAxis);
  float declinationAngle = (6.0 + (1.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  if (heading < 0){
    heading += 2 * PI;
  }
  if (heading > 2 * PI){
    heading -= 2 * PI;
  }
  float headingDegrees = heading * 180/M_PI; 

  lcd->init(F("X =\rY =\rZ =\rD =\r    "));

  lcd->printn(0, 0, 0);
  lcd->printn(4, 4, 0);
  lcd->print((int) compass_norm.XAxis, 4, 0);

  lcd->printn(1, -5, 0);
  lcd->printn(4, 12, 0, 4);
  lcd->print((int) compass_norm.YAxis, 12, 0, 4);

  lcd->printn(2, 0, 1);
  lcd->printn(4, 4, 1);
  lcd->print((int) compass_norm.ZAxis, 4, 1);

  lcd->printn(3, -5, 1);
  lcd->printn(4, 12, 1, 4);
  lcd->print((int) headingDegrees, 12, 1, 4);
}

void show_temp(){
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

  // DHT 22 temp
  DHT22.read22(DHT22_PIN);

  dtostrf(DHT22.temperature, 4, 1, buffer);
  sprintf(buffer, "%s\337C", buffer);
  lcd->print(buffer, -1, 0);

  // DHT 22 humi
  dtostrf(DHT22.humidity, 4, 1, buffer);
  sprintf(buffer, "%s%%", buffer);
  lcd->print(buffer, -1, 1);
}

void hello(uint8_t hour){
  lcd->clear();
  lcd->init(F("Доброї ночі!\rДоброго ранку!\rДоброго дня!\rДоброго вечора!\rЯ годинник :)"));
  lcd->printn((hour + 1) / 6, 0, 0);
  lcd->printn(4, 3, 1);
  delay(2000);
  lcd->clear();
}
