/*
created 19.01.2015
modified 21.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "LcdI2cRu.h"

LcdI2cRu::LcdI2cRu(uint8_t address, uint8_t width, uint8_t height) {
  lcd = new LiquidCrystal_I2C(address, width, height);
  lcd->init();
}

LcdI2cRu::~LcdI2cRu() { }

void LcdI2cRu::init(const char* str){
  uint8_t length, pos;
  for (pos = 0, length = 0; str[pos] != '\0'; pos++){
    if(str[pos] != '\n'){
      length++;
      continue;
    }
    if(length){
      length++;
      c++;
      if (l < length){
        l = length;
      }
      length = 0;
    }
  }
  // Если в конце забыли энтер
  if(length){
    length++;
    c++;
    if (l < length){
      l = length;
    }
    length = 0;
  }
  
  s = new char*[c];
  
  char tmp[l];
  uint8_t cur_c = 0;
  for (pos = 0, length = 0; str[pos] != '\0'; pos++){
    if(str[pos] != '\n'){
      tmp[length] = str[pos];
      length++;
      continue;
    }
    if(length){
      tmp[length] = '\0';
      s[cur_c] = new char[l];
      get_str_enc(tmp, s[cur_c]);
      cur_c++;
      length = 0;
    }
  }
  if(length){
    tmp[length] = '\0';
    s[cur_c] = new char[l];
    get_str_enc(tmp, s[cur_c]);
    cur_c++;
    length = 0;
  }
  createMap();
}

void LcdI2cRu::init(const __FlashStringHelper* str){
  char* ptr = (char*) str;
  uint8_t length, pos;
  char chr;
  for (pos = 0, length = 0; (chr = (char) pgm_read_byte_near(ptr + pos)) != '\0'; pos++){
    if(chr != '\n'){
      length++;
      continue;
    }
    if(length){
      length++;
      c++;
      if (l < length){
        l = length;
      }
      length = 0;
    }
  }
  // Если в конце забыли энтер
  if(length){
    length++;
    c++;
    if (l < length){
      l = length;
    }
    length = 0;
  }
  
  s = new char*[c];
  
  char tmp[l];
  uint8_t cur_c = 0;
  for (pos = 0, length = 0; (chr = (char) pgm_read_byte_near(ptr + pos)) != '\0'; pos++){
    if(chr != '\n'){
      tmp[length] = chr;
      length++;
      continue;
    }
    if(length){
      tmp[length] = '\0';
      s[cur_c] = new char[l];
      get_str_enc(tmp, s[cur_c]);
      cur_c++;
      length = 0;
    }
  }
  if(length){
    tmp[length] = '\0';
    s[cur_c] = new char[l];
    get_str_enc(tmp, s[cur_c]);
    cur_c++;
    length = 0;
  }
  createMap();
}

void LcdI2cRu::createMap(){
  static uint8_t ru[8][8] =
  {
    { 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 }, // 0 Б
    { 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 }, // 1 Г
    { 0xe, 0xa, 0xa, 0xa, 0x1f,0x11,0x11,0x0 }, // 2 Д
    { 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 }, // 3 Ы
    { 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 }, // 4 Ю
    { 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 }, // 5 Я
    { 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 }, // 6 Ж
    { 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 }, // 7 П
  };
  for (uint8_t char_num = 0; char_num < 8; char_num++){
    lcd->createChar(char_num, ru[char_num]);
  }
}

void LcdI2cRu::get_str_enc(char* str, char* result){
  char* abc = (char*) F("АБВГДЕЁЖЗИЙКЛМНОПРСТУФЧХЦШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфчхцшщьыъэюя");
  boolean found = false;
  uint8_t res_pos = 0;
  // Обходим символы строки
  for (uint8_t str_pos = 0; str[str_pos] != '\0'; str_pos++){
    // Совпадений ещё небыло
    found = false;
    // Обходим подстроки для поиска
    for (uint8_t abc_num = 0; abc_num < 132; abc_num += 2){
      // Обходим символы подстрок для поиска
      for (uint8_t abc_chr_pos = 0, cur_pos = str_pos; abc_chr_pos < 2; abc_chr_pos++, cur_pos++){
        // Если текущий символ подстроки не равен текущему символу строки
        if (str[cur_pos] != (char) pgm_read_byte_near(abc + abc_num + abc_chr_pos)){
          // Прерываем обход символов подстроки
          found = false;
          // Переходим к следующей подстроке
          break;
        }
        // Эти символы строк совпадают
        found = true;
      }
      // Проверяем результаты сравнения строк
      if (found){
        if (abc_num < 66){
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 192;
        }else{
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 159;
        }
        // Сдвигаем текущую позицию строки на один символ (потому что всего надо на два)
        str_pos++;
        // Заканчиваем цикл обхода подстрок - подстрока найдена
        break;
      }
    }
    if (!found){
      // Подстрока не была найдена - копируем текущий символ как он есть
      result[res_pos++] = str[str_pos];
    }
  }
  result[res_pos] = '\0';
}

void LcdI2cRu::write_enc(char* str){
  static char abc_replace[][1] = { 'A',  0,  'B',  1,   2,  'E', 'E',  6,  '3', 'U', 'U', 'K', 202, 'M', 'H', 'O',  7,  'P', 'C', 'T', 191, 236, 209, 'X', 249, 'W', 'W', 'b',  3,  'b', 214,  4,   5 };

  if ((unsigned char) *str >= 192 && (unsigned char) *str <= 255){
    lcd->write(abc_replace[(unsigned char) *str - 192][0]);
  }else{
    lcd->write(*str);
  }
}

void LcdI2cRu::backlight(boolean state){
  if (state){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

void LcdI2cRu::backlight(){
  if (bl = !bl){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

void LcdI2cRu::clear(){
  lcd->clear();
}

void LcdI2cRu::home(){
  lcd->home();
}

void LcdI2cRu::setCursor(uint8_t col, uint8_t row){
  lcd->setCursor(col, row);
}

void LcdI2cRu::printn(uint8_t num){
  for (uint8_t cur_chr = 0; cur_chr < l; cur_chr++){
    if (!s[num][cur_chr]){
      break;
    }
    write_enc(&s[num][cur_chr]);
  }
}
