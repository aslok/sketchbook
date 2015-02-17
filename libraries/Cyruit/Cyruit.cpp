/*
 * Cyruit.h
 * Основной файл библиотеки Cyruit
 * Класс содержит методы вывода текста на экраны
 *
 * created 10.02.2015
 * modified 17.02.2015
 * with Arduino 1.5.8 (tested on Arduino Nano)
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

#include "Cyruit.h"

// Конструктор
Cyruit::Cyruit(
  void* ptr, display_type type, byte width, byte height, byte f_width, byte f_height
){
  s = NULL;
  s_type = NoString;
  s_length = 0;
  lcd = ptr;
  lcd_type = type;
  font_width = f_width,
  font_height = f_height,
  scr_width = width / font_width,
  scr_height = height / font_height,
  scr_length = scr_width * scr_height;
  scr_upd = true;
  clear();
}

Cyruit::Cyruit(
  Cyruit_PCD8544* ptr,
  byte width, byte height, byte f_width, byte f_height
):Cyruit(ptr, Cyruit_PCD8544_lib, width, height, f_width, f_height){
}

// Ф-ия печати строк переданных с помощью F()
void Cyruit::print(const __FlashStringHelper* str, int8_t position, byte go_ln, byte space){
  word str_len = strlen_P((char*) str) + 1;
  char* tmp = new char[str_len];
  strcpy_P(tmp, (char*) str);
  print(tmp, position, go_ln, space);
  delete[] tmp;
}

// Ф-ия печати целых чисел
void Cyruit::print(int chr, int8_t position, byte go_ln, byte space){
  char str[max_num_length];
  sprintf(str, "%d", chr);
  print(str, position, go_ln, space);
}

// Печать чисел с плавающей точкой
void Cyruit::print(double chr, int8_t position, byte go_ln, byte width, byte prec){
  char str[max_num_length];
  dtostrf(chr, width, prec, str);
  print(str, position, go_ln);
}

// Печать отдельного символа
void Cyruit::print(char chr, int8_t position, byte go_ln, byte space){
  char str[2]{chr};
  print(str, position, go_ln, space);
}

// Печать отдельного utf символа по номеру
void Cyruit::print(word utf8_num, int8_t position, byte go_ln, byte space){
  word utf8_chr = (utf8_num & 0x07C0) << 2 | utf8_num & 0x003F | 0xC080;
  char utf8_str[3]{(utf8_chr & 0xff00) >> 8, utf8_chr & 0xff};
  print(utf8_str, position, go_ln, space);
}

// Печать отдельного символа несколько раз
void Cyruit::print(char chr, int count, boolean upd){
  char str[2]{chr};
  while (count-- > 0){
    print_lcd(str, false);
  }
  if (upd){
    update();
  }
}

void Cyruit::print(char chr, word count, boolean upd){
  print(chr, (int) count, upd);
}

// Печать массива символов по указателю
void Cyruit::print(char* str, int8_t position, byte go_ln, byte space){
  if (go_ln != def_go_ln && go_ln < scr_height){
    go(0, go_ln);
  }
  word str_size = utf8_strlen(str);
  // Сдвиг относительно текущей позиции
  word free_size = ((space - str_size) / 2) % scr_length;
  word free_size_pp = free_size + (space - str_size) % 2;
  /*Serial.println(str);
  Serial.println(str_size);
  Serial.println(scr_pos);
  Serial.println(scr_pos / scr_width);*/
  byte scr_width_pp = scr_width + 1;
  // Если указана новая позиция
  if (position != def_position && position < scr_width && position > -1 * scr_width_pp){
    // Если позиция от правого края
    if (position < 0){
      // Если нужна центровка
      if (space != def_space){
        go(scr_width_pp - space + position, scr_pos / scr_width);
        // Сдвигаем курсор пробелами
        print(' ', free_size_pp, false);
        print_lcd(str, false);
        print(' ', free_size);
        return;
      // Если равнение на право
      }else{
        // Если край экрана - переносим курсор
        word new_pos = scr_width_pp - str_size + position + scr_pos;
        go(new_pos >= 0 ? new_pos : (new_pos % scr_length) + scr_length);
      }
    // Если позиция от левого края
    }else{
      go(position, scr_pos / scr_width);
      // Если нужна центровка
      if (space != def_space){
        // Если сдвиг влево
        if (free_size < 0) {
          // Если край экрана - переносим курсор
          word new_pos = free_size + scr_pos;
          go(new_pos >= 0 ? new_pos : (new_pos % scr_length) + scr_length);
        }else{
          // Сдвигаем курсор пробелами
          print(' ', free_size, false);
          print_lcd(str, false);
          print(' ', free_size_pp);
          return;
        }
      }
    }
  }
  // Печатаем строку во внутренней кодировке
  print_lcd(str);
  //Serial.println("--------------");
}

// Ф-ия печати строк без параметров
void Cyruit::print_lcd(char* str, boolean upd){
  switch (lcd_type){
    case Cyruit_PCD8544_lib:
      for (word i = 0; str[i] && str[i] != '\r' && i < 65535; i++){
        if (str[i] == '\n'){
          byte new_pos = scr_pos + scr_width;
          new_pos = new_pos < scr_length ? new_pos - new_pos % scr_width : 0;
          go(new_pos);
          continue;
        }
        if ((~str[i]) & 0x80 || (byte) str[i] >> 5 == 6){
          ((Cyruit_PCD8544*) lcd)->fillRect(
            scr_pos % scr_width * font_width,
            scr_pos / scr_width * font_height,
            font_width, font_height,
            WHITE
          );
        }
        ((Cyruit_PCD8544*) lcd)->write(str[i]);
        if ((~str[i]) & 0x80 || (byte) str[i] >> 5 != 6){
          scr_pos++;
          if (scr_pos >= scr_length){
            go(0);
          }
        }
      }
      if (upd) {
        update();
      }
      break;
  }
}

// Очистка экрана и установка курсора на ноль
void Cyruit::clear(){
  switch (lcd_type){
    case Cyruit_PCD8544_lib:
      ((Cyruit_PCD8544*) lcd)->clearDisplay();
      break;
  }
  update();
  go(0);
}

// Обновление экрана после изменения буфера
void Cyruit::update_set(boolean toggle){
  scr_upd = toggle;
}

void Cyruit::update(boolean){
  switch (lcd_type){
    case Cyruit_PCD8544_lib:
      ((Cyruit_PCD8544*) lcd)->display();
      break;
  }
}

void Cyruit::update(){
  if (!scr_upd) {
    return;
  }
  update(true);
}

// Установка курсора в выбранные столбец-строка
void Cyruit::go(byte col, byte row){
  /*Serial.print(col);
  Serial.print(", ");
  Serial.print(row);
  Serial.print('\n');*/
  if (col < scr_width && row < scr_height){
    switch (lcd_type){
      case Cyruit_PCD8544_lib:
        ((Cyruit_PCD8544*) lcd)->setCursor(col * font_width, row * font_height);
        break;
    }
    scr_pos = row * scr_width + col;
  }
}

// Установка курсора в выбранную позицию справа-налево сверху-вниз
void Cyruit::go(byte col){
  if (col < scr_length){
    go(col % scr_width, col / scr_width);
  }else if (col == 255){
    go(scr_pos);
  }
}

// Возвращает длину строки закодированной в utf-8
word Cyruit::utf8_strlen(char* str){
  word str_len = 0;
  byte chr_len = 1;
  for (word i = 0; str[i] && i < 65535; i += chr_len){
    chr_len = 0;
    for(
      byte mask = 0x80;
      mask && mask & str[i];
      chr_len++, mask >>= 1
    );
    if (!chr_len || chr_len > 6){
      chr_len = 1;
    }
    str_len++;
  }
  return str_len;
}

// Инициализация массива строк разделенных символом \r переданного через F()
void Cyruit::init(const __FlashStringHelper* str){
  s = (char*) str;
  s_type = FlashStringHelper;
  s_length = n_count();
}

// Инициализация массива строк разделенных символом \r переданного через указатель
void Cyruit::init(const char* str){
  s = (char*) str;
  s_type = ASCIZString;
  s_length = n_count();
}

// Печать строки из ранее переданного массива по её номеру
void Cyruit::printn(byte num, int8_t position, byte go_ln, byte space){
  if (s_type == FlashStringHelper){
    printn_flash(num, position, go_ln, space);
  }else if (s_type == ASCIZString){
    printn_str(num, position, go_ln, space);
  }
}

// Печать строки из ранее переданного массива символов по её номеру
// Максимальная длина строки - 255 символов
// Максимальный размер массива - 255 строк
void Cyruit::printn_str(byte num, int8_t position, byte go_ln, byte space){
  char str[255];
  byte count = 0, str_pos;
  word pos = 0;
  while (count < 255 && pos < 65535 && count < num && s[pos]){
    if (s[pos++] == '\r'){
      count++;
    }
  }
  if (count != num){
    return;
  }
  for (
    str_pos = 0;
    str_pos < 255 && pos < 65535 && s[pos] && s[pos] != '\r';
    str[str_pos++] = s[pos++]
  );
  str[str_pos] = 0;
  print(str, position, go_ln, space);
}

// Печать строки из ранее переданного внутри F() массива по её номеру
// Максимальная длина строки - 255 символов
// Максимальный размер массива - 255 строк
void Cyruit::printn_flash(byte num, int8_t position, byte go_ln, byte space){
  char str[255];
  byte count = 0, str_pos;
  word pos = 0;
  char chr;
  while (
    count < 255 && pos < 65535 && count < num &&
      (chr = (char) pgm_read_byte_near(s + pos++))
  ){
    if (chr == '\r'){
      count++;
    }
  }
  if (count != num){
    return;
  }
  for (
    str_pos = 0;
    str_pos < 255 && pos < 65535 &&
      (chr = (char) pgm_read_byte_near(s + pos++)) && chr != '\r';
    str[str_pos++] = chr
  );
  str[str_pos] = 0;
  print(str, position, go_ln, space);
}

// Возвращает кол-во строк в ранее переданном массиве
inline byte Cyruit::n_count(){
  byte count = 0, pos = 0;
  char chr;
  while (
    count < 255 && pos < 65535 &&
    (chr = (char) pgm_read_byte_near(s + pos++))
  ){
    if (chr == '\r'){
      count++;
    }
  }
  return ++count;
}
