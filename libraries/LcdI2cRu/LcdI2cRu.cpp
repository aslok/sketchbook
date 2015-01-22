/*
created 19.01.2015
modified 21.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "LcdI2cRu.h"

/*
Кодировка использует для хранения символа один байт
192	А
193	Б
194	В
195	Г
196	Д
197	Е
198	Ё
199	Ж
200	З
201	И
202	Й
203	К
204	Л
205	М
206	Н
207	О
208	П
209	Р
210	С
211	Т
212	У
213	Ф
214	Ч
215	Х
216	Ц
217	Ш
218	Щ
219	Ь
220	Ы
221	Ъ
222	Э
223	Ю
224	Я
*/

LcdI2cRu::LcdI2cRu(uint8_t address, uint8_t width, uint8_t height) {
  const uint8_t ru_chars_count = 13;
  
  abc = (char*) F("АБВГДЕЁЖЗИЙКЛМНОПРСТУФЧХЦШЩЬЫЪЭЮЯабвгдеёжзийклмнопрстуфчхцшщьыъэюя");
  ru = new uint8_t*[ru_chars_count];
  ru_names = new uint8_t[ru_chars_count];
  
  ru_names[0]  = 193; // Б
  ru[0]  = new uint8_t[8]{ 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 };
  ru_names[1]  = 195; // Г
  ru[1]  = new uint8_t[8]{ 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru_names[2]  = 196; // Д
  ru[2]  = new uint8_t[8]{ 0xe, 0xa, 0xa, 0xa, 0x1f,0x11,0x11,0x0 };
  ru_names[3]  = 220; // Ы
  ru[3]  = new uint8_t[8]{ 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 };
  ru_names[4]  = 223; // Ю
  ru[4]  = new uint8_t[8]{ 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 };
  ru_names[5]  = 224; // Я
  ru[5]  = new uint8_t[8]{ 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 };
  ru_names[6]  = 199; // Ж
  ru[6]  = new uint8_t[8]{ 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 };
  ru_names[7]  = 208; // П
  ru[7]  = new uint8_t[8]{ 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 };
  ru_names[8]  = 214; // Ч
  ru[8]  = new uint8_t[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0x1, 0x0 };
  ru_names[9]  = 216; // Ц
  ru[9]  = new uint8_t[8]{ 0x12,0x12,0x12,0x12,0x12,0x1f,0x1, 0x0 };
  ru_names[10] = 222; // Э
  ru[10] = new uint8_t[8]{ 0xe, 0x11,0x1, 0xf, 0x1, 0x11,0xe, 0x0 };
  ru_names[11] = 213; // Ф
  ru[11] = new uint8_t[8]{ 0xe, 0x15,0x15,0x15,0xe, 0x4, 0x4, 0x0 };
  ru_names[12] = 204; // Л
  ru[12] = new uint8_t[8]{ 0x3, 0x5, 0x9, 0x9, 0x9, 0x9, 0x19,0x0 };

  lcd = new LiquidCrystal_I2C(address, width, height);
  lcd->init();
  clear_screen();
}

LcdI2cRu::~LcdI2cRu() { }

void LcdI2cRu::init(const char* str){
  word length, pos;
  for (pos = 0, length = 0; str[pos] != '\0'; pos++){
    if(str[pos] != '\r'){
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
  word cur_c = 0;
  for (pos = 0, length = 0; str[pos] != '\0'; pos++){
    if(str[pos] != '\r'){
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
  word length, pos;
  char chr;
  for (pos = 0, length = 0; (chr = (char) pgm_read_byte_near(ptr + pos)) != '\0'; pos++){
    if(chr != '\r'){
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
  word cur_c = 0;
  for (pos = 0, length = 0; (chr = (char) pgm_read_byte_near(ptr + pos)) != '\0'; pos++){
    if(chr != '\r'){
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
  for (uint8_t char_num = 0; char_num < 8; char_num++){
    lcd->createChar(char_num, ru[char_num]);
  }
  lcd->clear();
}

void LcdI2cRu::get_str_enc(char* str, char* result){
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
  static char lcd_replace[]{ 'A', 0, 'B', 1, 2, 'E', 'E', 6, '3', 'U', 'U', 'K', 202, 'M', 'H', 'O', 7, 'P', 'C', 'T', 191, 236, 209, 'X', 249, 'W', 'W', 'b', 3, 'b', 214, 4, 5 };
  
  char out;
  char out_h[3]{0, 0, 0};
  if ((unsigned char) *str >= 192 && (unsigned char) *str <= 255){
    out = lcd_replace[(unsigned char) *str - 192];
    for (uint8_t pos = 0; pos < 2; pos++){
      out_h[pos] = (char) pgm_read_byte_near(abc + (((unsigned char) *str - 192) * 2) + pos);
    }
  }else{
    out = *str;
    out_h[0] = *str;
    out_h[1] = 0;
  }
  if (out == '\n'){
    if (scr_pos < 16){
      scr_pos = 16;
    }else{
      scr_pos = 0;
    }
  }
  if (scr_pos > 31){
    scr_pos = 0;
  }
  if (scr_pos == 0){
    lcd->setCursor(0, 0);
  }
  if (scr_pos == 16){
    lcd->setCursor(0, 1);
  }
  if (out == '\n'){
    return;
  }
  scr_h[scr_pos * 2] = out_h[0];
  if (!out_h[1]){
    scr_h[scr_pos * 2 + 1] = 127;
  }else{
    scr_h[scr_pos * 2 + 1] = out_h[1];
  }
  scr[scr_pos++] = *str;

  lcd->write(out);
}

void LcdI2cRu::clear_screen(){
  for (uint8_t i = 0; i < 32; i++){
    scr[i] = 26;
  }
  scr[32] = 0;
  for (uint8_t i = 0; i < 64; i++){
    scr_h[i] = 127;
  }
  scr_h[64] = 0;
  scr_pos = 0;
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
  clear_screen();
}

void LcdI2cRu::home(){
  lcd->home();
  scr_pos = 0;
}

void LcdI2cRu::setCursor(uint8_t col, uint8_t row){
  lcd->setCursor(col, row);
  scr_pos = row * 16 + col;
}

void LcdI2cRu::printn(uint8_t num){
  for (uint8_t cur_chr = 0; cur_chr < l; cur_chr++){
    if (!s[num][cur_chr] || num >= c){
      break;
    }
    write_enc(&s[num][cur_chr]);
  }
}
