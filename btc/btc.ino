#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"
#include "Cyruit.h"

Cyruit_PCD8544 lcd = Cyruit_PCD8544(A4, A5, 10, 11, 12);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);

const byte lcd_contrast = 51;
const byte lcd_backlight = 100;
const byte lcd_backlight_r = 0;
const byte lcd_backlight_g = 0;
const byte lcd_backlight_w = 0;
// D9 - LCD 7 - Light (PWM)
const byte lcd_backlight_pin = 9;
const byte lcd_backlight_pin_r = 6;
const byte lcd_backlight_pin_g = 5;
const byte lcd_backlight_pin_w = 3;
const byte buttons_pin = A7;
const byte in_1_pin = 2;
const byte in_2_pin = 4;
const byte in_3_pin = 7;
const byte in_4_pin = 8;
const byte out_1_pin = A0;
const byte out_2_pin = A1;
const byte out_3_pin = A2;
const byte out_4_pin = A3;

void setup(){
  Serial.begin(57600);

  analogWrite(lcd_backlight_pin, 255 - lcd_backlight);
  pinMode(lcd_backlight_pin, OUTPUT);
  analogWrite(lcd_backlight_pin_r, lcd_backlight_r);
  pinMode(lcd_backlight_pin_r, OUTPUT);
  analogWrite(lcd_backlight_pin_g, lcd_backlight_g);
  pinMode(lcd_backlight_pin_g, OUTPUT);
  analogWrite(lcd_backlight_pin_w, lcd_backlight_w);
  pinMode(lcd_backlight_pin_w, OUTPUT);
  pinMode(buttons_pin, INPUT);
  pinMode(out_1_pin, INPUT);
  pinMode(out_2_pin, INPUT);
  pinMode(out_3_pin, INPUT);
  pinMode(out_4_pin, INPUT);
  digitalWrite(in_1_pin, HIGH); // 4
  pinMode(in_1_pin, OUTPUT);
  digitalWrite(in_2_pin, HIGH);
  pinMode(in_2_pin, OUTPUT);
  digitalWrite(in_3_pin, HIGH); // 2
  pinMode(in_3_pin, OUTPUT);
  digitalWrite(in_4_pin, HIGH);
  pinMode(in_4_pin, OUTPUT);

  lcd.begin();
  // Переворачиваем
  lcd.setRotation(2);
  lcd.setContrast(lcd_contrast);
}


void loop(){
  display.clear();
  display.print(analogRead(buttons_pin), 0, 0, 14);
  display.print(analogRead(out_1_pin), 0, 1, 14);
  display.print(analogRead(out_2_pin), 0, 2, 14);
  display.print(analogRead(out_3_pin), 0, 3, 14);
  display.print(analogRead(out_4_pin), 0, 4, 14);
  
  delay(1000);
}

/*
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
*/

