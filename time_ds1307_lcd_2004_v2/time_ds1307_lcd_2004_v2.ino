/*
 * time_ds1307_lcd_2004_v2.ino
 * Time v2.0
 * Time and date on lcd display (used rtc timer) with control by buttons
 *
 * Hardware:
 * LCD PCF8574
 *   http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 * A momentary switches, buttons, or toggle switches
 * Humidity & Temperature Sensor DHT11
 *   http://electronics-lab.ru/blog/mcu/46.html
 *
 *
 * created 18.01.2015
 * modifid 02.03.2015
 * with Arduino 1.5.8 (tested on Arduino Pro Mini)
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

#include <LiquidCrystal.h>

LiquidCrystal display(12, 11, 5, 4, 3, 2);

#define BUTTON_OK_PIN 8
#define BUTTON_NEXT_PIN 7
#define BUTTON_PREV_PIN 6

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

#include "dht.h"
dht DHT;

#define DHT11_PIN 9


const char hello_str[] PROGMEM = "доброї ночі\rдоброго ранку\rдоброго дня\rдоброго вечора";

const char month[][4] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const char days[][4] = {
  "Sun", "Mon", "Tue", "Wed", "Wed", "Thu", "Fri", "Sat"
};

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
  //lcd.setContrast(contrast_val);
}

void contrast_dec(){
  if (contrast_val > 48){
    contrast_val--;
  }
  //lcd.setContrast(contrast_val);
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
  // Инициализация дисплея
  display.begin(20, 4);
  display.clear();

  // Инициализация кнопок
  pinMode(BUTTON_OK_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  #ifdef BUTTON_PREV_PIN
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  #endif

  // Инициализация календаря
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin();
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

  char suf[3]{223, 'C'};
  char buffer[12];
  buffer[11] = 0;

  sprintf(buffer, "%s", days[now.dayOfWeek()]);
  display.setCursor(0, 0);
  display.print(buffer);

  sprintf(buffer, "%02d %s %04d", now.day(), month[now.month() - 1], now.year());
  display.setCursor(9, 0);
  display.print(buffer);

  sprintf(buffer, " %02d:%02d:%02d", now.hour(), now.minute(), now.second());
  display.setCursor(5, 2);
  display.print(buffer);

  // Температура
  dtostrf(DHT.temperature, 2, 0, buffer);
  sprintf(buffer, "% 2s%s", buffer, suf);
  display.setCursor(0, 3);
  display.print(buffer);

  // Влажность
  dtostrf(DHT.humidity, 2, 0, buffer);
  sprintf(buffer, "% 2s%%", buffer);
  display.setCursor(17, 3);
  display.print(buffer);
}
/*
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
}*/

void loop(){
  DHT.read11(DHT11_PIN);

  static boolean btn_ok = false;
  static boolean btn_next = false;
  #ifdef BUTTON_PREV_PIN
  static boolean btn_prev = false;
  #endif

  show_time();

  // Текущий экран
  /*switch (cur_scr){
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
  #endif*/
}
