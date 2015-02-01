/*
 Time v2
 Time and date on lcd display (used rtc timer) with control by keypad 4x4

 Hardware:
 Trickle-Charge Timekeeping Chip DS1302
 http://www.maximintegrated.com/en/products/digital/real-time-clocks/DS1302.html
 http://playground.arduino.cc/Main/DS1302RTC
 LCD I2C PCF8574
 http://habrahabr.ru/post/219137/
 http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514
 Keypad 4x4

 created 18.01.2015
 modifid 01.02.2015
 by Fust Vitaliy
 with Arduino 1.5.8 (tested on Arduino Nano)
*/
/*
Sketch uses 15 048 bytes (48%) of program storage space. Maximum is 30 720 bytes.
Global variables use 435 bytes (21%) of dynamic memory, leaving 1 613 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;


#include <Keypad.h>
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

#include <dht.h>
dht DHT;

#define DHT11_PIN 2

void setup() {
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  rtc.begin();
  DateTime now = rtc.now();

  hello(now.hour());
}

void loop() {
  DateTime now = rtc.now();
  DHT.read11(DHT11_PIN);

  char buffer[9];
  char suf[3]{223, 'C'};

  // День недели
  //lcd->init(F("Нд\rПн\rВт\rСр\rЧт\rПт\rСб"));
  //lcd->printn(now.dayOfWeek(), -1, 0);
  lcd->init(F("Неділя\rПонеділок\rВівторок\rСереда\rЧетвер\rП'ятниця\rСубота"));
  lcd->printn(now.dayOfWeek(), 0, 0);

  // Дата
  //sprintf(buffer, "%02d.%02d", now.day(), now.month());
  sprintf(buffer, "%d", now.day());
  lcd->print(buffer, -5, 0);

  // Месяц
  //lcd->init(F("січня\rлютого\rберезня\rквітня\rтравня\rчервня\rлипня\rсерпня\rвересня\rжовтня\rлистопада\rгрудня"));
  //lcd->printn(now.month() - 1, 3, 0);
  lcd->init(F("січ\rлют\rбер\rкві\rтра\rчер\rлип\rсер\rвер\rжов\rлис\rгру"));
  lcd->printn(now.month() - 1, -1, 0);

  // Время
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd->print(buffer, -1, 1);

  // Температура
  sprintf(buffer, "%d%s", (byte) DHT.temperature + 2, suf);
  lcd->print(buffer, 0, 1);

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

