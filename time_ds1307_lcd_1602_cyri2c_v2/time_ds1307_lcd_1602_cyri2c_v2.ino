/*
 * time_ds1307_lcd_1602_cyri2c_v2.ino
 * Time v2.0
 * Time and date on lcd display (used rtc timer) with control by keypad 4x5
 *
 * Hardware:
 * LCD I2C PCF8574
 *   http://habrahabr.ru/post/219137/
 *   http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 * 4x5 20 Key Matrix Membrane Switch Keypad Keyboard Super Slim
 *   http://i00.i.aliimg.com/img/pb/237/100/706/706100237_585.jpg
 * Humidity & Temperature Sensor DHT11
 *   http://electronics-lab.ru/blog/mcu/46.html
 *
 *
 * created 18.01.2015
 * modifid 04.02.2015
 * with Arduino 1.5.8 (tested on Arduino Nano)
 *
 * Copyright 2015 Vitaliy Fust <aslok.zp@gmail.com>
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


#include "Keypad.h"
const byte numRows = 5;
const byte numCols = 4;
char keymap[numRows][numCols] = {
  {'+', '-', '#', '*'},
  {'1', '2', '3', 'W'},
  {'4', '5', '6', 'S'},
  {'7', '8', '9', 'B'},
  {'A', '0', 'D', 'E'}
};
byte rowPins[numRows] = {4, 5, 6, 7, 8};
byte colPins[numCols] = {12, 11, 10, 9};
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

#include "RTClib.h"
RTC_DS1307 rtc;

#include "dht.h"
dht DHT;

#define DHT11_PIN 2

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  rtc.begin();
  DateTime now = rtc.now();

  hello(now.hour());
}

void loop() {
  DateTime now = rtc.now();
  DHT.read11(DHT11_PIN);

  // День недели
  lcd->init(F("Неділя\rПонеділок\rВівторок\rСереда\rЧетвер\rП'ятниця\rСубота"));
  lcd->printn(now.dayOfWeek(), 0, 0, now.day() < 10 ? 10 : 9);

  // Дата
  lcd->print(now.day(), -5, 0);

  // Месяц
  lcd->init(F("січ\rлют\rбер\rкві\rтра\rчер\rлип\rсер\rвер\rжов\rлис\rгру"));
  lcd->printn(now.month() - 1, -1, 0);

  // Время
  char buffer[9];
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd->print(buffer, 6, 1, 10);

  // Температура
  lcd->print(DHT.temperature + 2, 0, 1, 2, 0);
  char suf[3]{223, 'C'};
  lcd->print(suf);

  // Ждем до конца секунды, проверяем клавиатуру
  unsigned long prevtime = now.unixtime();
  while(prevtime == rtc.now().unixtime()){
    char keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY){
      switch (keypressed) {
        case '+':
          lcd->backlight();
          break;
        default:
          hello(now.hour());
      }
    }
  }
}

// Приветствие
void hello(uint8_t hour){
  lcd->clear();
  lcd->init(F("Доброї ночі!\rДоброго ранку!\rДоброго дня!\rДоброго вечора!\rЯ годинник :)"));
  lcd->printn((hour + 1) / 6, 0, 0);
  lcd->printn(4, 3, 1);
  delay(2000);
  lcd->clear();
}
