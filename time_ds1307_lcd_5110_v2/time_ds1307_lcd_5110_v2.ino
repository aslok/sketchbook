/*
 * time_ds1307_lcd_5110_v2.ino
 * Time v2.0
 * Time and date on lcd display (used rtc timer) with control by buttons
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 * Monochrome Nokia 5110 LCD Display
 * A momentary switches, buttons, or toggle switches
 *
 *
 * created 18.01.2015
 * modifid 28.02.2015
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

#define BUTTON_OK_PIN 2
#define BUTTON_NEXT_PIN 8
#define BUTTON_PREV_PIN 9

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;


const char hello_str[] PROGMEM = "доброї ночі\rдоброго ранку\rдоброго дня\rдоброго вечора";


enum scr { TIME, MENU, SETTINGS, CONTRAST, RESET };

scr cur_scr = TIME;
boolean scr_upd = false;

boolean ok_upd = false;
boolean next_upd = false;
#ifdef BUTTON_PREV_PIN
boolean prev_upd = false;
#endif


byte contrast_val = 60;


typedef struct menu {
  char str[29];
  void(* action)(void);
};

void cancel(){
  cur_scr = TIME;
  scr_upd = true;
}

void settings(){
  cur_scr = SETTINGS;
  scr_upd = true;
}

void reset(){
  cur_scr = RESET;
  scr_upd = true;
}

void back(){
  cur_scr = MENU;
  scr_upd = true;
}

void apply(){
  cur_scr = TIME;
  scr_upd = true;
}

void contrast(){
  cur_scr = CONTRAST;
  scr_upd = true;
}

void contrast_inc(){
  if (contrast_val < 75){
    contrast_val++;
  }
  lcd.setContrast(contrast_val);
}

void contrast_dec(){
  if (contrast_val > 48){
    contrast_val--;
  }
  lcd.setContrast(contrast_val);
}

const menu menu_items[] PROGMEM = {
  { "Скасувати", cancel },
  { "Параметри", settings },
  { "Скинути", reset },
  { "", NULL },
};

const menu submenu_items[] PROGMEM = {
  { "Скасувати", back },
  { "Підтвердити", apply },
  { "", NULL },
};

const menu settings_items[] PROGMEM = {
  { "Скасувати", back },
  { "Контраст", contrast },
  { "", NULL },
};

const menu contrast_items[] PROGMEM = {
  { "Більше", contrast_inc },
  { "Меньше", contrast_dec },
  { "Підтвердити", apply },
  { "", NULL },
};


void setup() {
  lcd.begin();
  lcd.setContrast(contrast_val);

  pinMode(BUTTON_OK_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  #ifdef BUTTON_PREV_PIN
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  #endif

  rtc.begin();
}

void show_time(boolean full_scr = true) {
  static unsigned long prev_time = 0;
  DateTime now = rtc.now();
  if (!scr_upd && prev_time == now.secondstime()){
    return;
  }
  prev_time = now.secondstime();
  if (scr_upd){
    display.clear();
  }
  display.print(now.day(), -13, 0, 2);
  display.init(F("січня    \rлютого   \rберезня  \rквітня   \rтравня   \rчервня   \rлипня    \rсерпня   \rвересня  \rжовтня   \rлистопада\rгрудня   "));
  display.printn(now.month() - 1, 3, 0);

  char buffer[9];
  buffer[8] = 0;

  display.init(F("неділя\rпонеділок\rвівторок\rсереда\rчетвер\rп'ятниця\rсубота"));
  if (full_scr){
    display.printn(now.dayOfWeek(), -1, 1, 9);
  }else{
    display.printn(now.dayOfWeek(), 0, 1);

    sprintf(buffer, "%d", now.year());
    display.print(buffer, -1, 1);
  }

  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  if (full_scr){
    display.print(buffer, 0, 3, display.scr_width);

    display.init((__FlashStringHelper*) hello_str);
    display.printn(((now.hour() + 1) % 24) / 6, 0, 5, display.scr_width);
    scr_upd = false;
  }else{
    display.print(buffer, -1, 2);
  }
}

void show_menu(const struct menu *cur_menu, boolean on_top = true){
  static byte cur_pos = 0;
  static byte cur_size = 0;

  if (ok_upd){
    ok_upd = false;
    // Выполняем пункт меню
    ((void (*)()) pgm_read_ptr_near(&cur_menu[cur_pos].action))();
    return;
  }

  if (
    !scr_upd &&
    #ifdef BUTTON_PREV_PIN
    !prev_upd &&
    #endif
    !next_upd
  ){
    return;
  }

  if (scr_upd){
    // Печатаем меню
    if (on_top){
      display.clear();
    }
    cur_pos = 0;
    for (
      cur_size = 0;
      (char) pgm_read_byte_near(&cur_menu[cur_size].str);
      cur_size++
    );
    for (
      byte pos = 0;
      pos < cur_size;
      pos++
    ){
      display.print(
        (__FlashStringHelper*) &cur_menu[pos].str,
        3,
        on_top ? pos : display.scr_height - cur_size + pos
      );
    }
  }

  if (        // Если нажата кнопка NEXT
    next_upd &&
    ++cur_pos == cur_size
  ){
    cur_pos = 0;
  #ifdef BUTTON_PREV_PIN
  }else if (  // Если нажата кнопка PREV
    prev_upd &&
    --cur_pos == 255
  ){
    cur_pos = cur_size - 1;
  #endif
  }

  if (
    !scr_upd &&
    #ifdef BUTTON_PREV_PIN
    !prev_upd &&
    #endif
    !next_upd
  ){
    return;
  }
  // Обновляем курсор меню
  for (byte pos = 0; pos < cur_size; pos++){
    display.print(
      pos == cur_pos ? F("=>\n") : F("  \n"),
      0,
      on_top ? pos : display.scr_height - cur_size + pos
    );
  }
  scr_upd = false;
  next_upd = false;
  #ifdef BUTTON_PREV_PIN
  prev_upd = false;
  #endif
}

void show_contrast(){
  static boolean prev_contrast = 0;
  if (!scr_upd && prev_contrast == contrast_val){
    return;
  }
  prev_contrast = contrast_val;
  char buffer[4];
  buffer[3] = 0;
  sprintf(buffer, "%d%%", contrast_val);
  display.print(buffer, 0, 2);
}

void loop(){
  static boolean btn_ok = false;
  static boolean btn_next = false;
  #ifdef BUTTON_PREV_PIN
  static boolean btn_prev = false;
  #endif
  // Текущий экран
  switch (cur_scr){
    case TIME:
      show_time();
      break;
    case MENU:
      show_menu(menu_items);
      break;
    case RESET:
      show_menu(submenu_items);
      break;
    case SETTINGS:
      show_menu(settings_items);
      break;
    case CONTRAST:
      show_time(false);
      show_contrast();
      show_menu(contrast_items, false);
      break;
  }
  // Если OK был keydown стал keyup
  if (!digitalRead(BUTTON_OK_PIN)){
    switch (cur_scr){
      case CONTRAST:
        ok_upd = true;
        delay(150);
        break;
      case TIME:
        break;
      default:
        btn_ok = true;
    }
  }else if (btn_ok && digitalRead(BUTTON_OK_PIN)){
    switch (cur_scr){
      default:
        ok_upd = true;
    }
    btn_ok = false;
  }
  // Если NEXT был keydown стал keyup
  if (!digitalRead(BUTTON_NEXT_PIN)){
    switch (cur_scr){
      default:
        btn_next = true;
    }
  }else if (btn_next && digitalRead(BUTTON_NEXT_PIN)){
    switch (cur_scr){
      case TIME:
        cur_scr = MENU;
        scr_upd = true;
        break;
      default:
        next_upd = true;
    }
    btn_next = false;
  }
  #ifdef BUTTON_PREV_PIN
  // Если PREV был keydown стал keyup
  if (!digitalRead(BUTTON_PREV_PIN)){
    switch (cur_scr){
      case TIME:
        break;
      default:
        btn_prev = true;
    }
  }else if (btn_prev && digitalRead(BUTTON_PREV_PIN)){
    switch (cur_scr){
      default:
        prev_upd = true;
    }
    btn_prev = false;
  }
  #endif
}
