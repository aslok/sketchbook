/*
 * time_ds1307_lcd_5110_v2.ino
 * Time v2.0
 * Time and date on lcd display (used rtc timer) with control by keypad 4x4
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
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

// Vcc = 3.3V
// GND and Light on GND pin

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);


#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

const char hello_str[] PROGMEM = "доброї ночі\rдоброго ранку\rдоброго дня\rдоброго вечора";

void setup() {
  lcd.begin();
  lcd.setContrast(60);

  rtc.begin();
  DateTime now = rtc.now();

  display.init((__FlashStringHelper*) hello_str);
  display.printn(((now.hour() + 1) % 24) / 6, 0, 1);
  display.print(F("я годинник :)"), -1, 3);
  delay(2000);
  display.clear();
}

void loop() {
  DateTime now = rtc.now();

  display.print(now.day(), 0, 0, 2);
  display.init(F("січня\rлютого\rберезня\rквітня\rтравня\rчервня\rлипня\rсерпня\rвересня\rжовтня\rлистопада\rгрудня"));
  display.printn(now.month() - 1, 3, 0, 9);

  display.init(F("неділя\rпонеділок\rвівторок\rсереда\rчетвер\rп'ятниця\rсубота"));
  display.printn(now.dayOfWeek(), -1, 1, 9);

  char buffer[9];
  buffer[8] = 0;
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  display.print(buffer, 0, 3, display.scr_width);

  display.init((__FlashStringHelper*) hello_str);
  display.printn(((now.hour() + 1) % 24) / 6, 0, 5, display.scr_width);

  unsigned long prevtime = rtc.now().secondstime();
  while(prevtime == rtc.now().secondstime());
}
