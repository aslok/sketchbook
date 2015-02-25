/*
 * lcd_5110_gif.ino
 * Демонстрация работы библиотеки utf8_cp1251
 * Вывод анимации с русскими субтитрами
 *
 * created 10.02.2015
 * modified 16.02.2015
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

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "utf8_cp1251.h"

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

#include "imgs.c"

// Продолжительность анимации, мс
const word full_time = 9360;

typedef struct subtitle {
  char str[29];
  byte start;
  byte finish;
};

// Старт и финиш - область таймлайна для отображения, от 0 до 100
// Например - старт 4% от 9360 мс, финиш 13% от 9360 мс
const subtitle PROGMEM st[] = {
  { " ЗДРАВСТВУЙТЕ!",  4, 13 },
  { "     ПАРУ СЛОВ", 15, 23 },
  { "    О ПОЛИТИКЕ", 23, 31 },
  { "        БЛЯ   ", 31, 38 },
  { " ЗАЦЕНИ ПРИКОЛ", 38, 50 },
  { "      ПОЛИТИКА", 52, 58 },
  { "     ПОЛИТИКА!", 63, 75 },
  { " ПОЙДЕМ ДАЛЬШЕ", 79, 88 },
};
byte st_cnt = sizeof(st) / sizeof(subtitle);
byte cur_img = 0;
unsigned long mill;

void setup() {
  display.begin();
  display.setContrast(51);
  mill = millis();
}

inline void say(const __FlashStringHelper* str){
  char cp1251[29];
  display.fillRect(0, 0, LCDWIDTH, 8, WHITE);
  utf8_to_cp1251(str, cp1251, 29);
  display.setCursor(0, 0);
  display.print(cp1251);
}

void loop() {
  if (cur_img == imgs_cnt){
    cur_img = 0;
  }
  display.drawBitmap(0, 8, imgs[cur_img], 84, 40, BLACK, WHITE);
  byte st_num;
  for (st_num = 0; st_num < st_cnt; st_num++){
    if (
      cur_img > pgm_read_byte_near(&st[st_num].start)  * imgs_cnt / 100 &&
      cur_img < pgm_read_byte_near(&st[st_num].finish) * imgs_cnt / 100
    ){
      say((__FlashStringHelper*) &st[st_num].str);
      break;
    }
  }
  if (st_num == st_cnt){
    display.fillRect(0, 0, LCDWIDTH, 8, WHITE);
  }
  display.display();
  cur_img++;

  unsigned long cur_mil;
  while ((cur_mil = millis()) - mill < full_time / imgs_cnt);
  mill = cur_mil;
}
