#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "LcdI2cRu.h"

LcdI2cRu::LcdI2cRu(uint8_t address, uint8_t width, uint8_t height) {
  uint8_t ru[8][8] =
  {
    { 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 }, // Б
    { 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 }, // Г
    { 0xe, 0xa, 0xa, 0xa, 0x1f,0x11,0x11,0x0 }, // Д
    { 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 }, // Ы
    { 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 }, // Ю
    { 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 }, // Я
    { 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 }, // Ж
    { 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 }, // П
  };

  lcd = new LiquidCrystal_I2C(address, width, height);
  lcd->init();
  lcd->backlight();

  for (int char_num = 0; char_num < 8; char_num++){
    lcd->createChar(char_num, ru[char_num]);
  }
  lcd->home();
  lcd->clear();
}

LcdI2cRu::~LcdI2cRu() { }

void LcdI2cRu::init(const __FlashStringHelper* str){
  char* ptr = (char*) str;
  int length, pos;
  for (pos = 0, length = 0; (char)pgm_read_byte_near(ptr + pos) != '\0'; pos++){
    if((char)pgm_read_byte_near(ptr + pos) != '\n'){
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
  int cur_c = 0;
  for (pos = 0, length = 0; (char)pgm_read_byte_near(ptr + pos) != '\0'; pos++){
    if((char)pgm_read_byte_near(ptr + pos) != '\n'){
      tmp[length] = (char)pgm_read_byte_near(ptr + pos);
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
}

void LcdI2cRu::get_str_enc(char* str, char* result){
  char abc[][3] = { "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Ч", "Х", "Ц", "Ш", "Щ", "Ь", "Ы", "Ъ", "Э", "Ю", "Я" };
  char abc_replace[][1] = { 'A',  8,  'B',  1,   2,  'E', 'E',  6,  '3', 'U', 'U', 'K', 202, 'M', 'H', 'O',  7,  'P', 'C', 'T', 191, 236, 209, 'X', 249, 'W', 'W', 'b',  3,  'b', 214,  4,   5 };
  boolean found = false;
  int res_pos = 0;
  // Обходим символы строки
  for (int str_pos = 0; str[str_pos] != '\0'; str_pos++){
    // Совпадений ещё небыло
    found = false;
    // Обходим подстроки для поиска
    for (int abc_num = 0; abc_num < 33; abc_num++){
      // Обходим символы подстрок для поиска
      for (int abc_chr_pos = 0, cur_pos = str_pos; abc_chr_pos < 2; abc_chr_pos++, cur_pos++){
        // Если текущий символ подстроки это конец подстроки
        if (abc[abc_num][abc_chr_pos] == '\0'){
          // Прерываем обход символов подстроки
          // Переходим к следующей подстроке
          break;
        }
        // Если текущий символ подстроки не равен текущему символу строки
        if (str[cur_pos] != abc[abc_num][abc_chr_pos]){
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
        // Копируем в результат строку для замены найденной строки
        memcpy(&result[res_pos++], &abc_replace[abc_num], 1);
        // Сдвигаем текущую позицию строки на один символ (потому что всего надо на два)
        str_pos++;
        // Заканчиваем цикл обхода подстрок - подстрока найдена
        break;
      }
    }
    if (!found){
      // Подстрока не была найдена - копируем текущий символ как он есть
      memcpy(&result[res_pos++], &str[str_pos], 1);
    }
  }
  result[res_pos] = '\0';
}

void LcdI2cRu::setCursor(int col, int row){
  lcd->setCursor(col, row);
}

void LcdI2cRu::clear(){
  lcd->clear();
}

void LcdI2cRu::printn(int num){
  for (int cur_chr = 0; cur_chr < l; cur_chr++){
    if (!s[num][cur_chr]){
      break;
    }
    if (s[num][cur_chr] == 100){
      lcd->write(0);
    }else{
      lcd->write(s[num][cur_chr]);
    }
  }
}
