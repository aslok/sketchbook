/*
 * time_ds1302_lcd_5110_v2.ino
 * Time v2.0
 * Time and date on lcd display (used rtc timer) with control by keypad 4x4
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1302
 * http://www.maximintegrated.com/en/products/digital/real-time-clocks/DS1302.html
 * http://playground.arduino.cc/Main/DS1302RTC
 * Monochrome Nokia 5110 LCD Display
 * Keypad 4x4
 *
 *
 * created 18.01.2015
 * modifid 18.02.2015
 * with Arduino 1.5.8 (tested on Arduino Uno)
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

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"
#include "Cyruit.h"

// D3 - LCD 1 - reset (RST)
// D4 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D6 - LCD 4 - Serial data out (DIN)
// D7 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);


#include "Time.h"
#include "DS1302RTC.h"
// Set pins:  CE, IO,CLK
DS1302RTC RTC(12, 11, 10);
#define DS1302_GND_PIN 9
#define DS1302_VCC_PIN 8

const char hello_str[] PROGMEM = "доброї ночі\rдоброго ранку\rдоброго дня\rдоброго вечора";

void setup() {
  lcd.begin();
  lcd.setContrast(51);

  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);
  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  tmElements_t tm;
  RTC.read(tm);

  display.init((__FlashStringHelper*) hello_str);
  display.printn((++tm.Hour % 24) / 6, 0, 1);
  display.print(F("я годинник :)"), -1, 3);
  delay(2000);
  display.clear();
}

void loop() {
  tmElements_t tm;
  RTC.read(tm);

  display.print(tm.Day, 0, 0);
  display.init(F("січня\rлютого\rберезня\rквітня\rтравня\rчервня\rлипня\rсерпня\rвересня\rжовтня\rлистопада\rгрудня"));
  display.printn(tm.Month - 1, 3, 0);

  display.init(F("неділя\rпонеділок\rвівторок\rсереда\rчетвер\rп'ятниця\rсубота"));
  display.printn(tm.Wday - 1, -1, 1);

  char buffer[9];
  buffer[8] = 0;
  sprintf(buffer, "%02d:%02d:%02d", tm.Hour, tm.Minute, tm.Second);
  display.print(buffer, 0, 3, display.scr_width);

  display.init((__FlashStringHelper*) hello_str);
  display.printn((++tm.Hour % 24) / 6, 0, 5, display.scr_width);

  unsigned long prevtime = RTC.get();
  while(prevtime == RTC.get());
}
