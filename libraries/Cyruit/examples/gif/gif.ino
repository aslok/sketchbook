/*
 * gif.ino
 * Пример синхронного вывода графики и русского текста
 * (анимации с субтитрами)
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
  { "ЗДРАВСТВУЙТЕ!",  4, 13 },
  { "ПАРУ СЛОВ",     15, 23 },
  { "О ПОЛИТИКЕ",    23, 31 },
  { "БЛЯ   ",        31, 38 },
  { "ЗАЦЕНИ ПРИКОЛ", 38, 50 },
  { "ПОЛИТИКА",      52, 58 },
  { "ПОЛИТИКА!",     63, 75 },
  { "ПОЙДЕМ ДАЛЬШЕ", 79, 88 },
};
byte st_cnt = sizeof(st) / sizeof(subtitle);
byte cur_img = 0;
unsigned long mill;

void setup() {
  lcd.begin();
  lcd.setContrast(51);
  mill = millis();
}

void loop() {
  if (cur_img == imgs_cnt){
    cur_img = 0;
  }
  lcd.drawBitmap(0, 8, imgs[cur_img], 84, 40, BLACK, WHITE);
  byte st_num;
  for (st_num = 0; st_num < st_cnt; st_num++){
    if (
      cur_img > pgm_read_byte_near(&st[st_num].start)  * imgs_cnt / 100 &&
      cur_img < pgm_read_byte_near(&st[st_num].finish) * imgs_cnt / 100
    ){
      display.print((__FlashStringHelper*) &st[st_num].str, -1, 0);
      break;
    }
  }
  if (st_num == st_cnt){
    lcd.fillRect(0, 0, LCDWIDTH, 8, WHITE);
    lcd.display();
  }
  cur_img++;

  unsigned long cur_mil;
  while ((cur_mil = millis()) - mill < full_time / imgs_cnt);
  mill = cur_mil;
}
