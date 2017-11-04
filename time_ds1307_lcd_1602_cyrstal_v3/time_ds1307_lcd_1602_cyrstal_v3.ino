/*
 * time_ds1307_lcd_1602_cyrstal_v3.ino
 * Time v3.0
 * Time and date on lcd display (used rtc timer) with control by buttons
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 *
 *
 * created 01.11.2017
 * modifid 03.11.2017
 * with Arduino 1.8.3 (tested on Arduino Uno)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
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

#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;

#include "ButtonsTact.h"
ButtonsTact* buttons;

const int RIGHT     = 0;
const int UP        = 130;
const int DOWN      = 300;
const int LEFT      = 475;
const int SELECT    = 720;
const int NONE      = 1023;

#include "OneWire.h"
// Шина OneWire подключена к 12-му пину
OneWire ds(12);

// Количество подключенных датчиков ds_cnt
const byte ds_cnt = 2;

// Массив из ds_cnt групп по 8 байт
byte addr[ds_cnt][8];
// Массив для id найденных устройств
int addr_id[ds_cnt];

// Поиск 1-Wire устройств
// Если устройство найдено, то в 8 байтный массив addr[ds_num]
// записывается его ROM код
void ds_search(){
    // Предпологаем, что все устройства уже найдены
    boolean search_done = true;
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        // Если устройство найдено переходим к следующему
        if (addr_id[ds_num]){
            continue;
        }
        // Устройство номер ds_num не было найдено
        search_done = false;
        break;
    }
    search:
    // Повторяем поиск до тех пор, пока не найдем все устройства
    while (!search_done){
        // Выполняет новый поиск с первого устройства.
        ds.reset_search();
        delay(250);
        for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
            // Если устройство не найдено или CRC код не верный
            if (!ds.search(addr[ds_num]) ||
                    OneWire::crc8(addr[ds_num], 7) != addr[ds_num][7]){
                // Начинаем поиск с начала
                goto search;
            }
            // Присваиваем id новому устройству
            addr_id[ds_num] = ds_id_get(addr[ds_num]);
            //Serial.println(addr_id[ds_num]);
        }
        // Все устройства успешно найдены
        search_done = true;
    }
    return;
}

// Присваиваем id новому устройству
int ds_id_get(byte* addr){
    int ds_id = 0;
    for (byte byte_num = 0; byte_num < 8; byte_num++){
        ds_id += addr[byte_num];
    }
    return ds_id;
}

// Провести измерение температуры и записать данные в оперативную память
void ds_raw_create(byte* addr){
    // Выполняет сброс шины, необходимо перед связью с датчиком.
    ds.reset();
    // Выполняет выбор устройства после сброса, передается ROM Код устройства.
    ds.select(addr);
    // Передает информационный байт на устройство, работающее в паразитном режиме питания
    ds.write(0x44, 1);
}

// Считать последовательно 9 байт оперативной памяти
void ds_raw_read(byte* addr, byte* data){
    // Выполняет сброс шины, необходимо перед связью с датчиком.
    ds.reset();
    // Выполняет выбор устройства после сброса, передается ROM Код устройства.
    ds.select(addr);
    // Передает информационный байт на устройство
    ds.write(0xBE);
    // Смотрим 9 байтов
    for (byte i = 0; i < 9; i++){
        // Считывает информационный байт с устройства
        data[i] = ds.read();
    }
}

// Преобразуем получненный данные в температуру
float ds_raw_to_celsius(byte* addr, byte* data){
    int16_t raw = (data[1] << 8) | data[0];
    switch (addr[0]){
        // Old DS18S20
        case 0x10:
            raw = raw << 3;
            if (data[7] == 0x10){
                raw = (raw & 0xFFF0) + 12 - data[6];
            }
            break;
        // DS18B20
        case 0x28:
        // DS1822
        case 0x22:
            switch (data[4] & 0x60){
                case 0x00:
                    raw = raw & ~7;
                    break;
                case 0x20:
                    raw = raw & ~3;
                    break;
                case 0x40:
                    raw = raw & ~1;
            }
    }
    return (float) raw / 16.0;
}

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

// const char hello_str[] PROGMEM = "доброї ночі\rдоброго ранку\rдоброго дня\rдоброго вечора";

/*const char month[][4] PROGMEM = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const char days[][4] PROGMEM = {
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};*/

const char month[][7] PROGMEM = {
  "янв", "фев", "мар", "апр", "мая", "июн", "июл", "авг", "сен", "окт", "ноя", "дек"
};

const char days[][9] PROGMEM = {
  "вскр", "пнд", "вт", "ср", "чтв", "птн", "сб"
};

enum scr { TIME, MENU, SETTINGS, SET_TIME, SET_DATE, SET_TEMP, SET_TEMP_SENSOR, SET_TEMP_INFO };

scr cur_scr = TIME;
boolean scr_upd = true;

boolean ok_upd = false;
boolean next_upd = false;
boolean prev_upd = false;

typedef struct menu_item {
  char str[64];
  void(* action)(void);
};

typedef struct path_item {
  scr scr_name;
  byte pos;
};

path_item path[8];
byte path_pos = 0;
byte cur_pos = 0;

void back(){
  path_pos--;
  cur_scr = path[path_pos].scr_name;
  cur_pos = path[path_pos].pos;
  scr_upd = true;
}

void back2(){
  back();
  back();
}

void apply(){
  cur_scr = MENU;
  scr_upd = true;
}

void time(){
  cur_scr = TIME;
  scr_upd = true;
}

void menu(){
  path_pos = 0;
  cur_pos = 0;
  cur_scr = MENU;
  scr_upd = true;
}

void settings(){
  cur_scr = SETTINGS;
  scr_upd = true;
}

void set_time(){
  cur_scr = SET_TIME;
  scr_upd = true;
}

void set_date(){
  cur_scr = SET_DATE;
  scr_upd = true;
}

void set_temp(){
  cur_scr = SET_TEMP;
  scr_upd = true;
}

void set_temp_sensor(){
  cur_scr = SET_TEMP_SENSOR;
  scr_upd = true;
}

void set_temp_info(){
  cur_scr = SET_TEMP_INFO;
  scr_upd = true;
}

const menu_item menu_items[] PROGMEM = {
  { "Час", set_time },
  { "Дата", set_date },
  { "Температура", set_temp },
  { "", NULL },
};

const menu_item set_temp_items[] PROGMEM = {
  { "Датчік #1", set_temp_sensor },
  { "Датчік #2", set_temp_sensor },
  { "Інфо", set_temp_info },
  { "", NULL },
};

const menu_item set_temp_sensor_items[] PROGMEM = {
  { "Увімкнути", back2 },
  { "Вимкнути", back2 },
  { "", NULL },
};

const menu_item submenu_items[] PROGMEM = {
  { "Підтвердити", apply },
  { "", NULL },
};

void show_time(boolean full_scr = true) {
  static unsigned long prev_time = 0;
  DateTime now = rtc.now();
  if (!scr_upd && prev_time == now.secondstime()){
    return;
  }
  prev_time = now.secondstime();
  if (scr_upd){
    lcd->clear();
    lcd->print(F("\337C"), -1, 0);
  }

  lcd->print((__FlashStringHelper*) days[now.dayOfWeek()], 0, 0);

  char mon[16];
  strcpy_P(mon, month[now.month() - 1]);
  char buffer[16];
  sprintf(buffer, "%d %s", now.day(), mon);
  lcd->print(buffer, -6, 0, 6);

  /*dtostrf(readVcc(), 4, 2, buffer);
  sprintf(buffer, "%sV", buffer);
  lcd->print(buffer, -1, 0);*/

  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd->print(buffer, 0, 1, 16);

  if (scr_upd || !(now.second() % 5)) {
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        if (addr_id[ds_num] != 773){
          continue;
        }
        ds_raw_create(addr[ds_num]);

        delay(250);

        byte data[9];
        ds_raw_read(addr[ds_num], data);

        // Выводим температуру с устройства
        lcd->print(ds_raw_to_celsius(addr[ds_num], data), -3, 0, 3, 0);
    }
  }
  scr_upd = false;
}

void show_menu(const struct menu_item* cur_menu){
  static byte cur_size = 0;
  static byte cur_scr_pos = 0;

  if (ok_upd){
    ok_upd = false;
    path[path_pos].scr_name = cur_scr;
    path[path_pos].pos = cur_pos;
    path_pos++;
    cur_pos = 0;
    // Выполняем пункт меню
    ((void (*)()) pgm_read_ptr_near(&cur_menu[path[path_pos - 1].pos].action))();
    return;
  }

  if (scr_upd){
    for (
      cur_size = 0;
      (char) pgm_read_byte_near(&cur_menu[cur_size].str);
      cur_size++
    );
    cur_scr_pos = cur_pos > 0 ? cur_pos - 1 : cur_pos;
    lcd->clear();
  }

  if (
    !scr_upd &&
    !prev_upd &&
    !next_upd
  ){
    return;
  }

  // Если нажата кнопка NEXT
  if (next_upd){
    cur_pos++;
    if (cur_pos == cur_size){
      cur_pos = 0;
      cur_scr_pos = 0;
    }
    if (cur_pos >= cur_scr_pos + lcd->h){
      cur_scr_pos = cur_pos - lcd->h + 1;
    }
    lcd->clear();
  // Если нажата кнопка PREV
  }else if (prev_upd){
    cur_pos--;
    if (cur_pos == 255){
      cur_pos = cur_size - 1;
      cur_scr_pos = cur_size - 2;
    }
    if (cur_pos < cur_scr_pos && cur_scr_pos > 0){
      cur_scr_pos = cur_pos;
    }
    lcd->clear();
  }
  // Видимые пункты меню
  for (byte pos = 0; pos < cur_size; pos++){
    if (pos < cur_scr_pos || pos >= cur_scr_pos + lcd->h){
      continue;
    }
    lcd->print((__FlashStringHelper*) &cur_menu[pos].str, 3, pos - cur_scr_pos);
  }
  // Обновляем курсор меню
  for (byte pos = 0; pos < cur_size; pos++){
    if (pos < cur_scr_pos || pos >= cur_scr_pos + lcd->h){
      continue;
    }
    lcd->print(pos == cur_pos ? F("=>\n") : F("  \n"), 0, pos - cur_scr_pos);
  }
  scr_upd = false;
  next_upd = false;
  prev_upd = false;
}

void show_set_time(unsigned long ms){
  if (ok_upd){
    ok_upd = false;
    return;
  }
  if (
    !scr_upd &&
    !prev_upd &&
    !next_upd
  ){
    return;
  }

  if (scr_upd){
    lcd->clear();
    DateTime now = rtc.now();
    lcd->print((__FlashStringHelper*) days[now.dayOfWeek()], 0, 0);

    char mon[16];
    strcpy_P(mon, month[now.month() - 1]);
    char buffer[16];
    sprintf(buffer, "%d %s", now.day(), mon);
    lcd->print(buffer, -6, 0, 6);
    sprintf(buffer, "%d", now.year());
    lcd->print(buffer, -1, 0, 4);

    sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    lcd->print(buffer, 0, 1, 16);
  }


  scr_upd = false;
  next_upd = false;
  prev_upd = false;
}

void show_set_temp_info(unsigned long ms){
  static unsigned long ms_prev = 0;
  static byte ds_num = 0;
  // Массив для температур
  static float celsius[ds_cnt];
  static byte pass = 0;
  if (ms - ms_prev > 250){
    ms_prev = ms;
    switch (pass){
      case 0:
        ds_raw_create(addr[ds_num]);
        pass = 1;
        break;
      case 1:
        byte data[9];
        ds_raw_read(addr[ds_num], data);
        celsius[ds_num] = ds_raw_to_celsius(addr[ds_num], data);
        ds_num++;
        if (ds_num == ds_cnt){
          ds_num = 0;
        }
        pass = 0;
        break;
    }
  }
  if (!scr_upd && ((ms / 1000) % 2)){
    return;
  }
  //Serial.println(ms);
  if (scr_upd){
    // Ищем все устройства
    ds_search();
    pass = 0;
    lcd->clear();
    for (byte num = 0; num < ds_cnt; num++){
      celsius[num] = 0;
      // Выводим id устройства
      lcd->print(F("ID"), 0, num);
      lcd->print(addr_id[num], -11, num);
      lcd->print(F("\337C"), -1, num);
    }
  }

  for (byte num = 0; num < ds_cnt; num++){
    // Выводим температуру с устройства
    lcd->print(celsius[num], -3, num, 6, 2);
  }

  scr_upd = false;
}

void setup() {
  Serial.begin(57600);
  // Инициализация дисплея
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2, 10);
  lcd->backlight();

  // Обработка нажатий на пине A0
  buttons = new ButtonsTact(A0);
  // На первом месте стоит уровень по-умолчанию, когда ничего не нажато
  buttons->addLevels(NONE, UP, DOWN, LEFT, RIGHT, SELECT, END);

  // Обнуляем id устройств
  for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
      addr_id[ds_num] = 0;
  }

  // Ищем все устройства
  ds_search();

  // Инициализация календаря
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin();
  #endif
  rtc.begin();
}

void loop(){
  unsigned long ms = buttons->touch();
  switch (buttons->state(A0)){
    case UP:
      switch (cur_scr){
        case TIME:
          menu();
          break;
        default:
          prev_upd = true;
      }
      break;
    case DOWN:
      switch (cur_scr){
        case TIME:
          menu();
          break;
        default:
          next_upd = true;
      }
      break;
    case LEFT:
      switch (cur_scr){
        case TIME:
          menu();
          break;
        case MENU:
          time();
          break;
        default:
          back();
      }
      break;
    case RIGHT:
      switch (cur_scr){
        case TIME:
          menu();
          break;
        default:
          ok_upd = true;
      }
      break;
    case SELECT:
      time();
      break;
  }

  // Текущий экран
  switch (cur_scr){
    case TIME:
      show_time();
      break;
    case MENU:
      show_menu(menu_items);
      break;
    case SET_TEMP:
      show_menu(set_temp_items);
      break;
    case SET_TIME:
      show_set_time(ms);
      break;
    case SET_TEMP_SENSOR:
      show_menu(set_temp_sensor_items);
      break;
    case SET_TEMP_INFO:
      show_set_temp_info(ms);
      break;
  }
}

double readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif

  delay(75); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high << 8) | low;

  /* измерив Vcc с помощью вольтметра и нашей функции readVcc().
   * Далее заменяем константу 1125300L новой переменной:
   * scale_constant = internal1.1Ref * 1023 * 1000
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   * internal1.1Ref = 1.1 * 4960 / 5138 = 1,06189178669
   * scale_constant = 1,06189178669 * 1023 * 1000 = 1,08631529778
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
  return 1061.891 / result; // Vcc in volts
}
