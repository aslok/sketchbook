/*
 * time_ds1307_lcd_1602_cyrstal_v3.ino
 * Time v3.0
 * Time and date on lcd display (used rtc timer) with control by buttons
 *
 * Hardware:
 * Trickle-Charge Timekeeping Chip DS1307 (RTC Module V1.1 I2C)
 *   http://codehaus.blogspot.com/2012/02/i2c-rtc-ds1307-at24c32-real-time-clock.html
 * LCD1602 KeyPad Shield For Arduino
 *   https://www.dfrobot.com/wiki/index.php/LCD_KeyPad_Shield_For_Arduino_SKU:_DFR0009
 * DS18B20 Temperature Sensor Shield with DS18B20 Chip
 *   http://www.ebay.co.uk/itm/DS18B20-Temperature-Sensor-Shield-PCB-Module-Board-without-Chip-for-DIY-projects-/172041962079
 *
 *
 * created 01.11.2017
 * modifid 10.11.2017
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
Sketch uses 28,700 bytes (89.0%) of program storage space. Maximum is 32,256 bytes.
Global variables use 678 bytes (33.1%) of dynamic memory, leaving 1,370 bytes for local variables. Maximum is 2,048 bytes.
 */

const char version[] = "17111000";

// Библиотека для ввода с кнопок шилда
#include "ButtonsTact.h"
ButtonsTact* buttons;

// Уровни напряжения на A0 для разных кнопок
const int RIGHT     = 0;
const int UP        = 130;
const int DOWN      = 300;
const int LEFT      = 475;
const int SELECT    = 720;
const int NONE      = 1023;

// Библиотека для термодатчика
#include "OneWire.h"
// Шина OneWire подключена к 2-му пину
OneWire ds(2);
// Количество подключенных датчиков ds_cnt
const byte ds_cnt = 2;
// Массив из ds_cnt групп по 8 байт
byte addr[ds_cnt][8];
// Массив для id найденных устройств
unsigned int addr_id[ds_cnt];
// Массив для температур
float celsius[ds_cnt];

// Время со старта скетча
unsigned long ms = 0;
// Время последнего выполнения функции
unsigned long ms_prev = 0;
// Флаг - нужно обновить страницу
boolean scr_upd = true;
// Флаги - странице нужно обработать нажатия
boolean down_upd = false;
boolean up_upd = false;
boolean left_upd = false;
boolean right_upd = false;

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
            for (byte byte_num = 0; byte_num < 8; byte_num++){
                addr_id[ds_num] += addr[ds_num][byte_num];
            }
        }
        // Все устройства успешно найдены
        search_done = true;
    }
    return;
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

void update_temp(){
  static unsigned long ms_prev = 0;
  static byte ds_num = 0;
  static byte pass = 0;
  if (!scr_upd && ms - ms_prev < 250){
    return;
  }
  ms_prev = ms;
  if (scr_upd){
    pass = 0;
  }
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

float temp_from(unsigned int id){
  for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
    if (addr_id[ds_num] == id){
      return celsius[ds_num];
    }
  }
  return celsius[0];
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
   * Далее заменяем константу 1125.3 новой переменной:
   * scale_constant = internal1.1Ref * 1023
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   *
   * Например:
   * internal1.1Ref = 1.1 * 4960 / 5138 = 1,06189178669
   * scale_constant = 1,06189178669 * 1023 = 1086,31529778
   *
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
  return 1125.3 / result; // Vcc in volts
}

// ПЗУ для хранения id термодатчика
#include "EEPROM.h"
unsigned int ds_id = 0;

// Библиотека для вывода на экран шилда
#include "LiquidCrystal.h"
#include "Cyrstal_core.h"
#include "Cyrstal.h"
Cyrstal* lcd;

const char* EMPTY = "";

// Библиотека для часов
#include "Wire.h"
#include "RTClib.h"
#include "aRTClib.h"
ds1307* rtc;
#include "Eeprom24C32_64.h"
Eeprom24C32_64* rtc_eeprom;

const char month[][7] PROGMEM = {
  "янв", "фев", "мар", "апр", "мая", "июн", "июл", "авг", "сен", "окт", "ноя", "дек"
};
const char days[][5] PROGMEM = {
  "вс", "пн", "вт", "ср", "чт", "пт", "сб"
};

const byte speaker_pin = A3;
// Тональности нот и структура note_item для мелодий
#include "pitches.h"
// Различные мелодии
#include "melodies.h"
byte melodies_count;
int* melodies_titles;

// Сейчас играет мелодия номер melodie_num
byte melodie_num = NO_MELODIE;
// Сейчас играет нота номер note_num
unsigned int note_num = 0;
// Фоновое воспроизведение мелодий
void bg_melodie(){
  static unsigned long ms_prev = 0;
  // Сколько ждать конца ноты
  static byte wait = 0;
  // Если ничего не играем или ждем конца ноты
  if (melodie_num == NO_MELODIE || ms - ms_prev < wait * 10){
    return;
  }
  ms_prev = ms;
  // Следующая нота
  int note = (int) pgm_read_word_near(&melodies_notes[melodie_num][note_num].note);
  // Если нот больше нет - заканчиваем
  if (note == NOTE_END){
    bg_melodie_off();
    return;
  }
  // Начинаем играть ноту
  tone(speaker_pin, note, ((byte) pgm_read_byte_near(&melodies_notes[melodie_num][note_num].duration)) * 10);
  // Столько ждать конца ноты
  wait = (byte) pgm_read_byte_near(&melodies_notes[melodie_num][note_num].wait);
  // Номер следующей ноты
  note_num++;
}
// Выключаем фоновое воспроизведение мелодий
void bg_melodie_off(){
  melodie_num = NO_MELODIE;
  noTone(speaker_pin);
}
// Количество мелодий
byte bg_melodie_count(){
  byte count;
  for (count = 0; melodies_notes[count] != NULL; count++);
  return count;
}

// Названия разных страниц
enum scr {
  TIME,
  MENU,
    DATE,
    ALARM,
      ALARM_MELODIES,
    TEMP,
      TEMP_SENSOR,
      TEMP_INFO,
    AMENDMENT,
      AMENDMENT_INFO,
      AMENDMENT_EDIT,
      ADJUST,
    ABOUT,
};
// Текущая страница
scr cur_scr = TIME;

// Массивы пунктов меню для страниц menu
typedef struct menu_item {
  // Название пункта меню
  char str[33];
  // Действие которое он выполняет
  void(* action)(void);
};

// Массив страниц menu для возврата назад
typedef struct path_item {
  scr scr_name;
  byte pos;
};
path_item path[8];
byte path_pos = 0;
byte cur_pos = 0;
byte cur_suff = 0;

// Обработка действий пунктов меню
//    Переход назад по меню
void back(){
  path_pos--;
  cur_scr = path[path_pos].scr_name;
  cur_pos = path[path_pos].pos;
  scr_upd = true;
}
//    Переход на домашнюю страницу
void time(){
  cur_scr = TIME;
  scr_upd = true;
}
//    Переход на начальную страницу меню
void menu(){
  path_pos = 0;
  cur_pos = 0;
  cur_scr = MENU;
  scr_upd = true;
}
//    Переход на страницу установки даты с расчетом коррекции
void date(){
  cur_scr = DATE;
  scr_upd = true;
}
//    Переход на страницу меню Будильник
void alarm(){
  cur_scr = ALARM;
  scr_upd = true;
}
//    Переход на страницу меню Температура
void temp(){
  cur_scr = TEMP;
  scr_upd = true;
}
//    Переход на страницу меню Поправка
void amendment(){
  cur_scr = AMENDMENT;
  scr_upd = true;
}
//    Переход на страницу Об устройстве
void about(){
  cur_scr = ABOUT;
  scr_upd = true;
}
//    Переход на страницу меню Мелодии
void melodies(){
  cur_scr = ALARM_MELODIES;
  scr_upd = true;
}
//    Переход на страницу Инфо (о поправке)
void amendment_info(){
  cur_scr = AMENDMENT_INFO;
  scr_upd = true;
}
//    Переход на страницу установки поправки
void amendment_edit(){
  cur_scr = AMENDMENT_EDIT;
  scr_upd = true;
}
//    Переход на страницу установки даты без расчета коррекции
void adjust(){
  cur_scr = ADJUST;
  scr_upd = true;
}
//    Переход на страницу Инфо (о датчиках температуры)
void temp_info(){
  cur_scr = TEMP_INFO;
  scr_upd = true;
}
//    Переход на страницу меню выбора датчика температуры
void temp_sensor(){
  update_temp();
  cur_scr = TEMP_SENSOR;
  scr_upd = true;
}
//    Обработка действия пункта меню "Применить" для разных страниц
void apply(){
  switch (cur_scr){
    // На странице меню выбора датчика температуры
    case TEMP_SENSOR:
      ds_id = addr_id[cur_suff];
      EEPROM.put(0, ds_id);
      back();
      break;
    // На странице меню выбора мелодии для воспроизведения
    case ALARM_MELODIES:
      melodie_num = cur_suff;
      note_num = 0;
      break;
  }
  back();
}

// Элементы меню для страниц menu
const menu_item menu_items[] PROGMEM = {
//  "Ширина   1602"
  { "Дата", date },
  { "Будильник", alarm },
  { "Температура", temp },
  { "Поправка", amendment },
  { "Об устройстве", about },
  { "", NULL },
};
const menu_item alarm_items[] PROGMEM = {
  { "Мелодии", melodies },
  { "", NULL },
};
const menu_item melodies_items[] PROGMEM = {
  { "Мелодия", apply },
  { "", NULL },
};
const menu_item amendment_items[] PROGMEM = {
  { "Инфо", amendment_info },
  { "Поправка", amendment_edit },
  { "Дата", adjust },
  { "", NULL },
};
const menu_item temp_items[] PROGMEM = {
  { "Инфо", temp_info },
  { "Выбрать", temp_sensor },
  { "", NULL },
};
const menu_item apply_items[] PROGMEM = {
  { "Применить", apply },
  { "", NULL },
};

// Отображение домашней страницы
void show_time() {
  if (!scr_upd && ms - ms_prev < 1000){
    return;
  }
  ms_prev = ms;
  if (scr_upd){
    lcd->clear();
    lcd->print(F("\337C"), -1, 0);
  }
  rtc->update();

  lcd->print((__FlashStringHelper*) days[rtc->date.dayOfWeek()], 0, 0, 2);

  char mon[32];
  strcpy_P(mon, month[rtc->date.month() - 1]);
  char buffer[32];
  sprintf(buffer, "%d %s", rtc->date.day(), mon);
  lcd->print(buffer, -6, 0, 6);

  /*dtostrf(readVcc(), 4, 2, buffer);
  sprintf(buffer, "%sV", buffer);
  lcd->print(buffer, -1, 0);*/

  sprintf(buffer, "%02d:%02d:%02d", rtc->date.hour(), rtc->date.minute(), rtc->date.second());
  lcd->print(buffer, 0, 1, 16);

  // Выводим температуру с устройства
  lcd->print(temp_from(ds_id), -3, 0, 3, 0);

  scr_upd = false;
}

// Отображение страниц меню, возможно умножение списка на массив суффиксов suff[count]
void show_menu(const struct menu_item* cur_menu, int* suff = NULL, byte count = 0){
  static byte cur_size = 0;
  static byte cur_scr_pos = 0;

  if (right_upd){
    right_upd = false;
    path[path_pos].scr_name = cur_scr;
    path[path_pos].pos = cur_pos;
    path_pos++;
    cur_pos = 0;
    // Выполняем пункт меню
    if (!count){
      ((void (*)()) pgm_read_ptr_near(&cur_menu[path[path_pos - 1].pos].action))();
    }else{
      cur_suff = path[path_pos - 1].pos / cur_size;
      ((void (*)()) pgm_read_ptr_near(&cur_menu[(path[path_pos - 1].pos + 1) % cur_size].action))();
    }
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
    !up_upd &&
    !down_upd
  ){
    return;
  }

  // Если нажата кнопка DOWN
  if (down_upd){
    cur_pos++;
    if (cur_pos == cur_size * (count ? count : 1)){
      cur_pos = 0;
      cur_scr_pos = 0;
    }
    if (cur_pos >= cur_scr_pos + lcd->h){
      cur_scr_pos = cur_pos - lcd->h + 1;
    }
    lcd->clear();
  // Если нажата кнопка UP
  }else if (up_upd){
    cur_pos--;
    if (cur_pos == 255){
      cur_pos = cur_size * (count ? count : 1) - 1;
      cur_scr_pos = cur_size * (count ? count : 1) - 2;
    }
    if (cur_pos < cur_scr_pos && cur_scr_pos > 0){
      cur_scr_pos = cur_pos;
    }
    lcd->clear();
  }
  // Видимые пункты меню
  for (byte pos = 0, suff_pos = 0; pos < cur_size * (count ? count : 1); pos++){
    if (pos >= cur_scr_pos && pos < cur_scr_pos + lcd->h){
      lcd->print((__FlashStringHelper*) &cur_menu[pos - cur_size * suff_pos].str,
                  3,
                  pos - cur_scr_pos);
      if (suff != NULL){
        lcd->print(' ');
        lcd->print(suff[suff_pos]);
      }
    }
    if (suff != NULL && !((pos + 1) % cur_size)){
      suff_pos++;
    }
  }
  // Обновляем курсор меню
  for (byte pos = 0; pos < cur_size * (count ? count : 1); pos++){
    if (pos < cur_scr_pos || pos >= cur_scr_pos + lcd->h){
      continue;
    }
    lcd->print(pos == cur_pos ? F("=>\n") : F("  \n"), 0, pos - cur_scr_pos);
  }
  scr_upd = false;
  down_upd = false;
  up_upd = false;
}

// Отображение страницы установки времени на верное (если не adjust - также расчет коррекции)
enum date_pos_type{
  date_day, date_month, date_year, date_hour, date_minute, date_end
};
void show_date(boolean adjust = false){
  static date_pos_type date_pos = date_day;
  static DateTime now;
  if (
    ms - ms_prev < 500 &&
    !scr_upd &&
    !up_upd &&
    !down_upd &&
    !left_upd &&
    !right_upd
  ){
    return;
  }
  ms_prev = ms;

  // Если нажата кнопка right
  if (right_upd){
    date_pos = date_pos + 1;
    if (date_end == date_pos){
      right_upd = false;
      if (adjust){
        rtc->adjust(now);
      }else{
        rtc->correct(now);
      }
      back();
      return;
    }
  // Если нажата кнопка left
  }else if (left_upd){
    if (date_day == date_pos){
      left_upd = false;
      back();
      return;
    }else{
      date_pos = date_pos - 1;
    }
  // Если нажата кнопка up
  }else if (up_upd){
    switch (date_pos){
      case date_day:
        now = DateTime(DateTime(now.year(), now.month(), now.day() + 1, now.hour(), now.minute()).unixtime());
        break;
      case date_month:
        now = DateTime(DateTime(now.year(), now.month() + 1, now.day(), now.hour(), now.minute()).unixtime());
        break;
      case date_year:
        now = DateTime(DateTime(now.year() + 1, now.month(), now.day(), now.hour(), now.minute()).unixtime());
        break;
      case date_hour:
        now = DateTime(DateTime(now.year(), now.month(), now.day(), now.hour() + 1, now.minute()).unixtime());
        break;
      case date_minute:
        now = DateTime(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute() + 1).unixtime());
        break;
    }
  // Если нажата кнопка down
  }else if (down_upd){
    switch (date_pos){
      case date_day:
        now = DateTime(DateTime(now.year(), now.month(), now.day() - 1, now.hour(), now.minute()).unixtime());
        break;
      case date_month:
        now = DateTime(DateTime(now.month() == 1 ? now.year() - 1 : now.year(),
                                now.month() == 1 ? 12 : (now.month() - 1),
                                now.day(),
                                now.hour(), now.minute()).unixtime());
        break;
      case date_year:
        now = DateTime(DateTime(now.year() - 1, now.month(), now.day(), now.hour(), now.minute()).unixtime());
        break;
      case date_hour:
        now = DateTime(DateTime(now.year(),
                                now.month(),
                                !now.hour() ? (now.day() - 1) : now.day(),
                                !now.hour() ? 23 : (now.hour() - 1), now.minute()).unixtime());
        break;
      case date_minute:
        now = DateTime(DateTime(now.year(),
                                now.month(),
                                now.day(),
                                !now.minute() ? (now.hour() - 1) : now.hour(),
                                !now.minute() ? 59 : (now.minute() - 1)).unixtime());
        break;
    }
  }

  if (scr_upd){
    lcd->clear();
    date_pos = date_day;
    now = rtc->update();
    now = DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute());
  }

  lcd->print((__FlashStringHelper*) days[now.dayOfWeek()], 0, 0, 2);

  boolean hide = !up_upd && !down_upd && (ms / 500) % 2;
  char buffer[5];
  sprintf(buffer, "%2d", now.day());
  lcd->print(date_pos == date_day && hide ? EMPTY : buffer, -11, 0, 2);
  strcpy_P(buffer, month[now.month() - 1]);
  lcd->print(date_pos == date_month && hide ? EMPTY : buffer, -7, 0, 3);
  sprintf(buffer, "%04d", now.year());
  lcd->print(date_pos == date_year && hide ? EMPTY : buffer, -1, 0, 4);
  sprintf(buffer, "%02d", now.hour());
  lcd->print(date_pos == date_hour && hide ? EMPTY : buffer, 4, 1, 2);
  lcd->print(F(":"));
  sprintf(buffer, "%02d", now.minute());
  lcd->print(date_pos == date_minute && hide ? EMPTY : buffer, POS, LINE, 2);
  sprintf(buffer, ":%02d", now.second());
  lcd->print(buffer, POS, LINE, 2);

  scr_upd = false;
  down_upd = false;
  up_upd = false;
  left_upd = false;
  right_upd = false;
}
// Отображение страницы Об устройстве
void show_about(){
  if (!scr_upd && ms - ms_prev < 500){
    return;
  }
  ms_prev = ms;
  if (scr_upd){
    lcd->clear();
    lcd->print(F("Версия"));
    lcd->print(version, -1);
    lcd->print(F("Vcc"), 0, 1);
    lcd->print('V', -1);
  }

  lcd->print(readVcc(), 10, 1, 5, 3);

  scr_upd = false;
}

// Отображение страницы Инфо (о поправке)
void show_amendment_info(){
  if (!scr_upd){
    return;
  }
  lcd->clear();
  DateTime corrected = DateTime(rtc->corrected_read());
  char buffer[16];
  sprintf(buffer,
          "%02d.%02d.%04d",
          corrected.day(), corrected.month(), corrected.year());
  lcd->print(buffer, 0);
  sprintf(buffer,
          "%02d:%02d:%02d",
          corrected.hour(), corrected.minute(), corrected.second());
  lcd->print(buffer, 0, 1);
  lcd->print(rtc->amendment_read(), -1, 1);
  scr_upd = false;
}

// Отображение страницы установки поправки
enum amendment_pos_type{
  amendment_sign, amendment_integer, amendment_tenth, amendment_hundredth, amendment_thousandth, amendment_end
};
void show_amendment_edit(){
  static float amendment = 0;
  static amendment_pos_type amendment_pos = amendment_sign;
  if (
    ms - ms_prev < 500 &&
    !scr_upd &&
    !up_upd &&
    !down_upd &&
    !left_upd &&
    !right_upd
  ){
    return;
  }
  ms_prev = ms;
  // Если нажата кнопка right
  if (right_upd){
    amendment_pos = amendment_pos + 1;
    if (amendment_end == amendment_pos){
      right_upd = false;
      rtc->amendment_write(amendment);
      back();
      return;
    }
  // Если нажата кнопка left
  }else if (left_upd){
    if (amendment_sign == amendment_pos){
      left_upd = false;
      back();
      return;
    }else{
      amendment_pos = amendment_pos - 1;
    }
  // Если нажата кнопка up
  }else if (up_upd){
    switch (amendment_pos){
      case amendment_sign:
        amendment *= -1;
        break;
      case amendment_integer:
        amendment -= 1;
        break;
      case amendment_tenth:
        amendment -= 0.1;
        break;
      case amendment_hundredth:
        amendment -= 0.01;
        break;
      case amendment_thousandth:
        amendment -= 0.001;
        break;
    }
  // Если нажата кнопка down
  }else if (down_upd){
    switch (amendment_pos){
      case amendment_sign:
        amendment *= -1;
        break;
      case amendment_integer:
        amendment += 1;
        break;
      case amendment_tenth:
        amendment += 0.1;
        break;
      case amendment_hundredth:
        amendment += 0.01;
        break;
      case amendment_thousandth:
        amendment += 0.001;
        break;
    }
  }

  if (scr_upd){
    lcd->clear();
    amendment_pos = amendment_sign;
    amendment = rtc->amendment_read();
  }

  boolean hide = !up_upd && !down_upd && (ms / 500) % 2;
  char buffer[5];
  sprintf(buffer, "%c", amendment > 0 ? '+' : '-');
  lcd->print(amendment_pos == amendment_sign && hide ? EMPTY : buffer, 3, 0, 1);
  int tmp = amendment > 0 ? amendment : -amendment;
  sprintf(buffer, "%04d", tmp);
  lcd->print(amendment_pos == amendment_integer && hide ? EMPTY : buffer, POS, LINE, 4);
  lcd->print('.', POS, LINE, 1);
  tmp = (amendment - (int) amendment) * 1000;
  tmp = tmp > 0 ? tmp % 1000 : -tmp % 1000;
  sprintf(buffer, "%d", tmp / 100);
  lcd->print(amendment_pos == amendment_tenth && hide ? EMPTY : buffer, POS, LINE, 1);
  tmp = tmp % 100;
  sprintf(buffer, "%d", tmp / 10);
  lcd->print(amendment_pos == amendment_hundredth && hide ? EMPTY : buffer, POS, LINE, 1);
  tmp = tmp % 10;
  sprintf(buffer, "%d", tmp);
  lcd->print(amendment_pos == amendment_thousandth && hide ? EMPTY : buffer, POS, LINE, 1);

  scr_upd = false;
  down_upd = false;
  up_upd = false;
  left_upd = false;
  right_upd = false;
}

// Отображение страницы Инфо (о датчиках температуры)
void show_temp_info(){
  if (!scr_upd && ms - ms_prev < 500){
    return;
  }
  ms_prev = ms;
  if (scr_upd){
    lcd->clear();
    for (byte num = 0; num < ds_cnt; num++){
      if (addr_id[num] == ds_id){
        lcd->print('*', 0, num);
      }
      // Выводим id устройства
      lcd->print((int) addr_id[num], -12, num);
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
  //Serial.begin(57600);
  // Инициализация дисплея
  lcd = new Cyrstal(8, 9, 4, 5, 6, 7, 16, 2, 10);
  lcd->backlight();

  // Обработка нажатий на пине A0
  buttons = new ButtonsTact(A0);
  // На первом месте стоит уровень по-умолчанию, когда ничего не нажато
  buttons->addLevels(NONE, UP, DOWN, LEFT, RIGHT, SELECT, END);

  // Мелодии
  melodies_count = bg_melodie_count();
  melodies_titles = new int[melodies_count];
  for (byte num = 0; num < melodies_count; num++){
    melodies_titles[num] = num + 1;
  }

  // Управление динамиком
  pinMode(speaker_pin, OUTPUT);
  digitalWrite(speaker_pin, LOW);

  // Инициализация часов
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc = new ds1307();
  rtc_eeprom = new Eeprom24C32_64(0x50);

  // Питание (-) для датчиков на A1-ом пине
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

  // Обнуляем id устройств
  for (byte num = 0; num < ds_cnt; num++){
      addr_id[num] = 0;
  }
  // Ищем все устройства
  ds_search();
  // Загружаем из ПЗУ выбранный датчик
  EEPROM.get(0, ds_id);
  // Обнуляем показания датчиков
  for (byte num = 0; num < ds_cnt; num++){
    celsius[num] = 0;
  }
}

void loop(){
  // Время со старта скетча
  ms = buttons->touch();
  // Фоновое воспроизведение мелодий
  bg_melodie();
  // Обрабатываем действия от нажатия кнопок на разных экранах
  switch (buttons->state(A0)){
    case UP:
      switch (cur_scr){
        case TIME:
          bg_melodie_off();
          menu();
          break;
        default:
          up_upd = true;
      }
      //tone(speaker_pin, NOTE_C1, 100);
      break;
    case DOWN:
      switch (cur_scr){
        case TIME:
          bg_melodie_off();
          menu();
          break;
        default:
          down_upd = true;
      }
      //tone(speaker_pin, NOTE_E1, 100);
      break;
    case LEFT:
      bg_melodie_off();
      switch (cur_scr){
        case TIME:
          menu();
          break;
        case MENU:
          time();
          break;
        case DATE:
        case ADJUST:
        case AMENDMENT_EDIT:
          left_upd = true;
          break;
        default:
          back();
      }
      //tone(speaker_pin, NOTE_G1, 100);
      break;
    case RIGHT:
      bg_melodie_off();
      switch (cur_scr){
        case TIME:
          menu();
          break;
        case TEMP_INFO:
        case AMENDMENT_INFO:
        case ABOUT:
          back();
          break;
        default:
          right_upd = true;
      }
      //tone(speaker_pin, NOTE_B1, 100);
      break;
    case SELECT:
      bg_melodie_off();
      time();
      //tone(speaker_pin, NOTE_F2, 100);
      break;
  }

  // Отображаем текущий экран
  switch (cur_scr){
    case TIME:
      // Обновляем массив температур
      update_temp();
      // Отображение домашней страницы
      show_time();
      break;
    case MENU:
      // Отображение начальной страницу меню
      show_menu(menu_items);
      break;
    case DATE:
      // Отображение страницы установки времени на верное, также расчет коррекции
      show_date();
      break;
    case ALARM:
      // Отображение страницы меню Будильник
      show_menu(alarm_items);
      break;
    case TEMP:
      // Отображение страницы меню Температура
      show_menu(temp_items);
      break;
    case AMENDMENT:
      // Отображение страницы меню Поправка
      show_menu(amendment_items);
      break;
    case ABOUT:
      // Отображение страницы Об устройстве
      show_about();
      break;
    case ALARM_MELODIES:
      // Отображение страницы меню Мелодии
      show_menu(melodies_items, melodies_titles, melodies_count);
      break;
    case AMENDMENT_INFO:
      // Отображение страницы Инфо (о поправке)
      show_amendment_info();
      break;
    case AMENDMENT_EDIT:
      // Отображение страницы установки поправки
      show_amendment_edit();
      break;
    case ADJUST:
      // Отображение страницы установки времени на верное, без расчета коррекции
      show_date(true);
      break;
    case TEMP_SENSOR:
      // Отображение страницы меню c пунктами меню "Применить" для каждого датчика
      show_menu(apply_items, addr_id, ds_cnt);
      break;
    case TEMP_INFO:
      // Обновляем массив температур
      update_temp();
      // Отображение страницы Инфо (о датчиках температуры)
      show_temp_info();
      break;
  }
}
