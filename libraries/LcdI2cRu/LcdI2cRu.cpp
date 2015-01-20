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
  
  char alphabet[33][3] = { "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Ч", "Х", "Ц", "Ш", "Щ", "Ь", "Ы", "Ъ", "Э", "Ю", "Я" };
  char alphabet_replace[33][1] = { 'A',  8,  'B',  1,   2,  'E', 'E',  6,  '3', 'U', 'U', 'K', 202, 'M', 'H', 'O',  7,  'P', 'C', 'T', 191, 236, 209, 'X', 249, 'W', 'W', 'b',  3,  'b', 214,  4,   5 };
  for (int char_num = 0; char_num < 33; char_num++){
    strncpy(abc[char_num], alphabet[char_num], 3);
    strncpy(abc_replace[char_num], alphabet_replace[char_num], 1);
  }
}

LcdI2cRu::~LcdI2cRu() { }

void LcdI2cRu::init(String str){
  str += "\n";
  
  int length, pos;
  for (pos = 0, length = 0; pos < str.length(); pos++){
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
  
  s = new char*[c];
  for (pos = 0; pos < c; pos++){
    s[pos] = new char[l];
  }
  
  int cur_c = 0;
  for (pos = 0, length = 0; pos < str.length(); pos++){
    if(str[pos] != '\n'){
      s[cur_c][length] = str[pos];
      //Serial.println(length);
      //Serial.println(s[cur_c][length]);
      length++;
      continue;
    }
    //Serial.println("<br>");
    if(length){
      s[cur_c][length] = '\0';
      //Serial.println(s[cur_c]);
      cur_c++;
      length = 0;
    }
  }

  s_e = new char*[c];
  for (pos = 0; pos < c; pos++){
    s_e[pos] = new char[l];
    get_str_enc(s[pos]).toCharArray(s_e[pos], l);
  }
}

String LcdI2cRu::get_str_enc(char* str){
  String string(str);
  for (int abc_num = 0; abc_num < 33; abc_num++){
    string.replace(abc[abc_num], String(abc_replace[abc_num][0]));
  }
  return string;
}

void LcdI2cRu::setCursor(int col, int row){
  lcd->setCursor(col, row);
}

void LcdI2cRu::clear(){
  lcd->clear();
}

void LcdI2cRu::printn(int num){
  for (int cur_chr = 0; cur_chr < l; cur_chr++){
    if (!s_e[num][cur_chr]){
      break;
    }
    if (s_e[num][cur_chr] == 100){
      lcd->write(0);
    }else{
      lcd->write(s_e[num][cur_chr]);
    }
  }
}
