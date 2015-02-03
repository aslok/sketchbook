/*
created 19.01.2015
modified 03.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"

/*
Кодировка использует для хранения символа один беззнаковый байт
128  А
129  Б
130  В
131  Г
132  Д
133  Е
134  Ё
135  Ж
136  З
137  И
138  Й
139  К
140  Л
141  М
142  Н
143  О
144  П
145  Р
146  С
147  Т
148  У
149  Ф
150  Х
151  Ц
152  Ч
153  Ш
154  Щ
155  Ъ
156  Ы
157  Ь
158  Э
159  Ю
160  Я
161  Ґ
162  Є
163  І
164  Ї
*/

// Конструктор
CyrI2c::CyrI2c(byte address, byte width, byte height) {
  // Кол-во самодельных символов для замены
  const byte ru_chars_count = 25;
  // Кол-во символов, которые можно использовать
  const byte en_chars_count = 28;

  // Строка для поиска символов для замены
  abc    = (char*) F("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяҐЄІЇґєії");
  ru     = new byte*[ru_chars_count];
  ru_num = new byte[ru_chars_count];
  ru_cnt = ru_chars_count;
  en     = new byte[en_chars_count];
  en_num = new byte[en_chars_count];
  en_cnt = en_chars_count;

  ru_num[0]  = 129; // Б
  ru[0]  = new byte[8]{ 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 };
  ru_num[1]  = 131; // Г
  ru[1]  = new byte[8]{ 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru_num[2]  = 132; // Д
  ru[2]  = new byte[8]{ 0xe, 0xa, 0xa, 0xa, 0xa, 0x1f,0x11,0x0 };
  ru_num[3]  = 156; // Ы
  ru[3]  = new byte[8]{ 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 };
  ru_num[4]  = 159; // Ю
  ru[4]  = new byte[8]{ 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 };
  ru_num[5]  = 160; // Я
  ru[5]  = new byte[8]{ 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 };
  ru_num[6]  = 135; // Ж
  ru[6]  = new byte[8]{ 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 };
  ru_num[7]  = 144; // П
  ru[7]  = new byte[8]{ 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 };
  ru_num[8]  = 161; // Ґ
  ru[8]  = new byte[8]{ 0x1, 0x1f,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru_num[9]  = 152; // Ч
  ru[9]  = new byte[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0x1, 0x0 };
  ru_num[10] = 162; // Є
  ru[10] = new byte[8]{ 0xf, 0x10,0x10,0x1e,0x10,0x10,0xf, 0x0 };
  ru_num[11] = 140; // Л
  ru[11] = new byte[8]{ 0x3, 0x5, 0x9, 0x9, 0x9, 0x9, 0x19,0x0 };
  ru_num[12] = 148; // У
  ru[12] = new byte[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0xe, 0x0 };
  ru_num[13] = 149; // Ф
  ru[13] = new byte[8]{ 0xe, 0x15,0x15,0x15,0xe, 0x4, 0x4, 0x0 };
  ru_num[14] = 151; // Ц
  ru[14] = new byte[8]{ 0x12,0x12,0x12,0x12,0x12,0x12,0x1f,0x1 };
  ru_num[15] = 158; // Э
  ru[15] = new byte[8]{ 0x1e,0x1, 0x1, 0xf, 0x1, 0x1, 0x1e,0x0 };
  ru_num[16] = 155; // Ъ
  ru[16] = new byte[8]{ 0x18,0x8, 0x8, 0xe, 0x9, 0x9, 0xe, 0x0 };
  ru_num[17] = 154; // Щ
  ru[17] = new byte[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1e,0x1 };
  ru_num[18] = 164; // Ї
  ru[18] = new byte[8]{ 0xa, 0x4, 0x4, 0x4, 0x4, 0x4, 0xe, 0x0 };
  ru_num[19] = 153; // Ш
  ru[19] = new byte[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1f,0x0 };
  ru_num[20] = 138; // Й
  ru[20] = new byte[8]{ 0x15,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru_num[21] = 137; // И
  ru[21] = new byte[8]{ 0x11,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru_num[22] = 134; // Ё
  ru[22] = new byte[8]{ 0xa, 0x1f,0x10,0x1e,0x10,0x10,0x1f,0x0 };
  ru_num[23] = 136; // З
  ru[23] = new byte[8]{ 0xe, 0x11,0x1, 0xe, 0x1, 0x11,0xe, 0x0 };
  ru_num[24] = 157; // Ь
  ru[24] = new byte[8]{ 0x10,0x10,0x10,0x1c,0x12,0x12,0x1c,0x0 };

  en_num[0]  = 128; // А
  en[0]  = 'A';
  en_num[1]  = 130; // В
  en[1]  = 'B';
  en_num[2]  = 133; // Е
  en[2]  = 'E';
  en_num[3]  = 134; // Ё
  en[3]  = 'E';
  en_num[4]  = 136; // З
  en[4]  = '3';
  en_num[5]  = 137; // И
  en[5]  = 'U';
  en_num[6]  = 138; // Й
  en[6]  = 'U';
  en_num[7]  = 139; // К
  en[7]  = 'K';
  en_num[8]  = 141; // М
  en[8]  = 'M';
  en_num[9]  = 142; // Н
  en[9]  = 'H';
  en_num[10] = 143; // О
  en[10] = 'O';
  en_num[11] = 145; // Р
  en[11] = 'P';
  en_num[12] = 146; // С
  en[12] = 'C';
  en_num[13] = 147; // Т
  en[13] = 'T';
  en_num[14] = 150; // Х
  en[14] = 'X';
  en_num[15] = 153; // Ш
  en[15] = 'W';
  en_num[16] = 154; // Щ
  en[16] = 'W';
  en_num[17] = 157; // Ь
  en[17] = 'b';
  en_num[18] = 155; // Ъ
  en[18] = 'b';
  en_num[19] = 140; // Л
  en[19] = 202;
  en_num[20] = 148; // У
  en[20] = 191;
  en_num[21] = 149; // Ф
  en[21] = 236;
  en_num[22] = 152; // Ч
  en[22] = 209;
  en_num[23] = 151; // Ц
  en[23] = 249;
  en_num[24] = 158; // Э
  en[24] = 214;
  en_num[25] = 162; // Є
  en[25] = 211;
  en_num[26] = 163; // І
  en[26] = 'I';
  en_num[27] = 164; // Ї
  en[27] = 'I';

  s      = NULL;
  p_s    = NULL;
  f      = 0;
  bl     = false;
  for (byte i = 0; i < 8; i++){
    char_map[i] = 0;
  }

  lcd = new LiquidCrystal_I2C(address, width, height);
  lcd->init();
  clear();
}

// Ф-ия печати строк переданных с помощью F()
void CyrI2c::print(const __FlashStringHelper* str, int8_t position, byte go_ln, byte space){
  char* ptr = (char*) str;
  char tmp[256];
  char chr;
  byte cur_chr;
  for (cur_chr = 0; cur_chr < 255 && (chr = (char) pgm_read_byte_near(ptr + cur_chr)); cur_chr++){
    tmp[cur_chr] = chr;
  }
  tmp[cur_chr] = 0;
  print(tmp, position, go_ln, space);
}

// Ф-ия печати целых чисел
void CyrI2c::print(int chr, int8_t position, byte go_ln, byte space){
  char str[33];
  sprintf(str, "%d", chr);
  print(str, position, go_ln, space);
}

// Печать чисел с плавающей точкой
void CyrI2c::print(double chr, int8_t position, byte go_ln, byte width, byte prec){
  char str[33];
  dtostrf(chr, width, prec, str);
  print(str, position, go_ln);
}

// Печать отдельного символа
void CyrI2c::print(char chr, int8_t position, byte go_ln, byte space){
  char str[2]{chr};
  print(str, position, go_ln, space);
}

// Печать отдельного символа
// Печать массива символов по указателю
void CyrI2c::print(char* str, int8_t position, byte go_ln, byte space){
  byte cur_chr;
  for (cur_chr = 0; cur_chr < 255 && str[cur_chr]; cur_chr++);
  char* tmp = new char[cur_chr + 1];
  get_str_enc(str, tmp);
  print_enc(tmp, position, go_ln, space);
  delete[] tmp;
}

// Печать массива символов во внутренней кодировке
void CyrI2c::print_enc(char* str, int8_t position, byte go_ln, byte space){
  byte cur, old_cur, cur_chr, i, cur_pos, pos;
  if (go_ln != 255 && go_ln < 2){
    go(0, go_ln);
  }
  if (position != 127 && position < 16 && position > -17){
    if (position < 0){
      // Выясняем длину строки
      for (cur_chr = 0; str[cur_chr] && str[cur_chr] != '\n'; cur_chr++);
      go(17 - cur_chr + position, scr_pos / 16);
    }else{
      go(position, scr_pos / 16);
    }
  }
  if (space != 255){
    // Выясняем длину строки
    for (cur_chr = 0; str[cur_chr] && str[cur_chr] != '\n'; cur_chr++);
    // Сдвиг относительно текущей позиции
    i = (space - cur_chr) / 2;
    // Если сдвиг влево
    if (i < 0) {
      // Если край экрана - переносим курсор
      go(i + scr_pos >= 0 ? i + scr_pos : i % 32 + scr_pos);
    }else{
      // Если сдвиг вправо - сдвигаем курсор пробелами
      for (cur_pos = 0; cur_pos < (space - cur_chr) / 2; cur_pos++){
        print(' ');
      }
      // Печатаем строку
      print_enc(str);
      // Сдвигаем курсор пробелами
      for (cur_pos = 0; cur_pos < (space - cur_chr) / 2; cur_pos++){
        print(' ');
      }
      return;
    }
  }
  // Массив символов которые будут отображаться после вывода
  // Порядок соответствует порядку отображения
  char next_scr[33];
  //Serial.println(str);
  get_next_scr(str, next_scr);
  //Serial.println(next_scr);
  // Массив символов, на которые нужно будет заменить соответствующие
  // символы кирилицы при выводе
  char lcd_replace[32];
  // Обходим next_scr
  boolean found;
  for (cur_chr = 0; cur_chr < 32; cur_chr++){
    found = false;
    // Обходим основной набор символов для замены
    for (cur = 0; cur < en_cnt; cur++){
      if (en_num[cur] == (byte) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = en[cur];
        found = true;
        break;
      }
    }
    if (found){
      continue;
    }
    // Обходим набор использованных самодельных символов для замены
    for (i = 0; i < 8; i++){
      if (char_map[i] && char_map[i] == (byte) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = i;
        found = true;
        break;
      }
    }
    // Ничего не нашли, не заменяем символ - будет тот же
    lcd_replace[cur_chr] = next_scr[cur_chr];
  }

  // Выполнена предварительная замена, lcd_replace почти во внутренней кодировке
  // Ищем символы которые нужно и можно заменить, их коды в области 128-180
  for (cur_chr = 0; cur_chr < 32; cur_chr++){
    if ((byte) lcd_replace[cur_chr] < 128 || (byte) lcd_replace[cur_chr] > 180){
      continue;
    }
    /*Serial.println("(byte) lcd_replace[cur_chr]");
    Serial.println(cur_chr);
    Serial.println((byte) lcd_replace[cur_chr]);
    Serial.println("----------------------------");*/
    found = false;
    // Обходим набор использованных самодельных символов для замены
    for (i = 0; i < 8; i++){
      if (char_map[i] && char_map[i] == (byte) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = i;
        found = true;
        break;
      }
    }
    if (found){
      //Serial.println("Replaced");
      continue;
    }
    found = false;
    // Обходим набор самодельных символов для замены
    for (cur = 0; cur < 9; cur++){
      // Если мы можем заменить его одним из восьми первых
      if (ru_num[cur] == (byte) lcd_replace[cur_chr]){
        found = true;
        // Переменная cur хранит номер самодельного символа
        break;
      }
    }

    // Нечем заменить, наверно не нужно
    if (!found){
      continue;
    }

    // Символ найден, ищем свободную ячейку
    found = false;
    for (i = 0; i < 8; i++){
      // Ячейка занята
      if (char_map[i]){
        continue;
      }
      found = true;
      // Сохраняем в ячейку номер символа который заменяем
      char_map[i] = ru_num[cur];
      /*Serial.println("lcd->createChar(i, ru[cur]);");
      Serial.println(i);
      Serial.println(cur);
      Serial.println("----------------------------");*/
      lcd->createChar(i, ru[cur]);
      // Бага lcd->createChar - приходится обновлять курсор
      go();
      // Будем заменять его при выводе на номер ячейки
      for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
        if ((byte) lcd_replace[cur_pos] == ru_num[cur]){
          /*Serial.println("lcd_replace[cur_chr] = i");
          Serial.println(cur_chr);
          Serial.println(i);
          Serial.println("----------------------------");*/
          lcd_replace[cur_chr] = i;
        }
      }
      // Прекращаем поиск свободных ячеек
      break;
    }

    // Переходим к следующему символу
    if (found){
      continue;
    }

    // Закончились ячейки для хранения символов :(
    // Ищем что заменить
    // Обходим набор самодельных символов для замены с конца
    // Никогда не выселяем символы 0-8 потому что заменить нечем :(
    for (cur_pos = ru_cnt; cur_pos-- > 8; ){
      // Ищем ячейку занятую этим символом
      for (i = 0; i < 8; i++){
        // Если есть кандидат на выселение
        if (ru_num[cur_pos] == char_map[i]){
          found = false;
          // Обходим основной набор символов для замены
          // После выселения будет отображаться оттуда
          for (pos = 0; pos < en_cnt; pos++){
            if (en_num[pos] == char_map[i]){
              found = true;
              old_cur = pos;
              break;
            }
          }
          if (!found){
            // Если так случится - будет глюк
            // Выход один - добавить этот символ в en
            // Второй выход - переместить в начало ru
            // Этот выход невозможен:
            // 1. Количество невыселяемых символов ограничено драйвером 8 штук
            // 2. Набор одновременно отображаемых символов ограничен алфавитом
            // Одновременный вывод частей украинского и русского алфавитов
            // может привести к глюкам
            continue;
          }
          // Сохраняем в ячейку номер символа который заменяем
          char_map[i] = ru_num[cur];
          // Будем заменять его при выводе на номер ячейки
          for (pos = 0; pos < 32; pos++){
            if ((byte) lcd_replace[pos] == ru_num[cur]){
              /*Serial.println("lcd_replace[pos] = i");
              Serial.println(pos);
              Serial.println(i);
              Serial.println("----------------------------");*/
              lcd_replace[pos] = i;
            }
            // Динамическое обновление символов
            // Перетираем отображающееся предыдущее содержимое ячейки
            if ((byte) next_scr[pos] == ru_num[cur_pos]){
              lcd->setCursor(pos - pos / 16 * 16, pos / 16);
              lcd_replace[pos] = en[old_cur];
              lcd->write(en[old_cur]);
            }
          }
          // Отображающееся предыдущее содержимое перетерто, можем подменять
          lcd->createChar(i, ru[cur]);
          // Бага lcd->createChar - приходится обновлять курсор
          go();
          break;
        }
      }
      if (found){
        break;
      }
    }
  }

  // Обходим набор использованных самодельных символов char_map
  for (cur = 0; cur < 8; cur++){
    // Если ячейка используется
    // Проверяем, если уже не нужна - освобобождаем
    if (char_map[cur]) {
      found = false;
      // Обходим массив который получился для замены
      for (cur_chr = 0; cur_chr < 32; cur_chr++){
        // Если был использован один из самодельных символов
        if ((byte) lcd_replace[cur_chr] == cur){
          found = true;
          break;
        }
      }
      // Мы используем этот символ
      if (found){
        continue;
      }

      // Символ не используется - очищаем
      /*Serial.println("char_map[cur]");
      Serial.println(cur);
      Serial.println(char_map[cur]);
      Serial.println("char_map[cur] = 0");
      Serial.println("----------------------------");*/
      char_map[cur] = 0;
    }

    // Обходим дополнительные символы самодельного набора, ищем что бы ещё заменить
    for (byte ru_cur = 9; ru_cur < ru_cnt; ru_cur++){
      found = false;
      // Обходим уже использованные дополнительные символы
      for (i = 0; i < 8; i++){
        if (char_map[i] && char_map[i] == ru_num[ru_cur]){
          // Уже заменили раньше
          found = true;
          break;
        }
      }
      if (found){
        // Переходим к следующему самодельному символу
        continue;
      }
      // Обходим массив символов, которые будут отображаться после вывода
      for (cur_chr = 0; cur_chr < 32; cur_chr++){
        // Ищем текущий дополнительный самодельный символ
        if ((byte) next_scr[cur_chr] != ru_num[ru_cur]){
          continue;
        }
        // Найден текущий дополнительный самодельный символ
        // Сохраняем в ячейку номер символа
        char_map[cur] = ru_num[ru_cur];
        /*Serial.println("lcd->createChar(cur, ru[ru_cur]);");
        Serial.println(cur);
        Serial.println(ru_cur);
        Serial.println("----------------------------");*/
        lcd->createChar(cur, ru[ru_cur]);
        // Будем заменять его при выводе на номер ячейки
        // Обходим начиная с текущего, предыдущие заменили бы раньше
        for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
          if ((byte) next_scr[cur_pos] == ru_num[ru_cur]){
            /*Serial.println("lcd_replace[cur_chr] = cur");
            Serial.println(cur_chr);
            Serial.println(cur);
            Serial.println("----------------------------");*/
            lcd_replace[cur_chr] = cur;
            // Динамическое обновление символов
            lcd->setCursor(cur_chr - cur_chr / 16 * 16, cur_chr / 16);
            lcd->write(cur);
          }
        }
        // Бага lcd->createChar - приходится обновлять курсор
        go();
      }
      if (found){
        // Переходим к следующей ячейке
        break;
      }
    }
  }

  write_str_enc(str, lcd_replace);
}

// Получаем массив символов, которые будут отображаться после вывода строки
void CyrI2c::get_next_scr(char* str, char* next_scr){
  byte next_scr_pos = scr_pos;
  // Копируем текущий экран
  for (byte i = 0; i < 33; i++){
    next_scr[i] = scr[i];
  }
  // Обходим строку и эмулируем вывод
  for (byte cur_chr = 0; str[cur_chr] && cur_chr < 255; cur_chr++){
    if (str[cur_chr] == '\n'){
      if (next_scr_pos < 16){
        next_scr_pos = 16;
      }else{
        next_scr_pos = 0;
      }
    }
    if (next_scr_pos > 31){
      next_scr_pos = 0;
    }
    if (str[cur_chr] != '\n'){
      next_scr[next_scr_pos++] = str[cur_chr];
    }
    if (next_scr_pos > 31){
      next_scr_pos = 0;
    }
  }
}

// Печатаем строку сгенерированную для экрана по строке во внутренней кодировке
void CyrI2c::write_str_enc(char* str, char* lcd_chars){
  char out;
  for (byte cur_chr = 0; str[cur_chr] && cur_chr < 255; cur_chr++){
    out = str[cur_chr];
    if (out == '\n'){
      if (scr_pos < 16){
        scr_pos = 16;
      }else{
        scr_pos = 0;
      }
      go();
      continue;
    }
    if (scr_pos > 31){
      scr_pos = 0;
    }
    if (scr_pos == 0 || scr_pos == 16){
      go();
    }
    if ((byte) out >= 128 && (byte) out <= 180){
      out = lcd_chars[scr_pos];
    }
    scr[scr_pos++] = str[cur_chr];

    //Serial.println((byte) out);
    lcd->write(out);
    if (scr_pos > 31){
      scr_pos = 0;
    }
  }
  //Serial.println("--------------------------------------------------------");
}

// Конвертируем строку во внутреннюю кодировку
void CyrI2c::get_str_enc(char* str, char* result){
  boolean found = false;
  byte res_pos = 0;
  // Обходим символы строки
  for (byte str_pos = 0; str[str_pos]; str_pos++){
    // Совпадений ещё небыло
    found = false;
    // Обходим подстроки для поиска (74 символа, 33+33 русских и 4+4 украинских)
    for (byte abc_num = 0; abc_num < 148; abc_num += 2){
      // Обходим символы подстрок для поиска
      for (byte abc_chr_pos = 0, cur_pos = str_pos; abc_chr_pos < 2; abc_chr_pos++, cur_pos++){
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
        // Русский алфавит верхний регистр
        if (abc_num < 66){
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 128;
        // Русский алфавит нижний регистр
        // И символы из украинского алфавита верхний регистр
        }else if (abc_num < 140){
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 95;
        // Символы из украинского алфавита нижний регистр
        }else{
          result[res_pos++] = (abc_num / 2) + 91;
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
  result[res_pos] = 0;
}

// Подсветка экрана
void CyrI2c::backlight(boolean state){
  if (bl = state){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

// Подсветка экрана
void CyrI2c::backlight(){
  if (bl = !bl){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

// Символы
void CyrI2c::power(boolean state){
  if (pwr = state){
    lcd->display();
  }else{
    lcd->noDisplay();
  }
}

// Символы
void CyrI2c::power(){
  if (pwr = !pwr){
    lcd->display();
  }else{
    lcd->noDisplay();
  }
}

// Курсор _
void CyrI2c::cursor(boolean state){
  if (crsr = state){
    lcd->cursor();
  }else{
    lcd->noCursor();
  }
}

// Курсор _
void CyrI2c::cursor(){
  if (crsr = !crsr){
    lcd->cursor();
  }else{
    lcd->noCursor();
  }
}

// Курсор []
void CyrI2c::blink(boolean state){
  if (blnk = state){
    lcd->blink();
  }else{
    lcd->noBlink();
  }
}

// Курсор []
void CyrI2c::blink(){
  if (blnk = !blnk){
    lcd->blink();
  }else{
    lcd->noBlink();
  }
}

// Очистка экрана и установка курсора на ноль
void CyrI2c::clear(){
  byte i;
  for (i = 0; i < 32; i++){
    scr[i] = ' ';
  }
  scr[32] = 0;
  scr_pos = 0;
  lcd->clear();
}

// Установка курсора в выбранные столбец-строка
void CyrI2c::go(byte col, byte row){
  //Serial.println("go");
  //Serial.println(col);
  //Serial.println(row);
  if (col < 16 && row < 2){
    lcd->setCursor(col, row);
    scr_pos = row * 16 + col;
  }
}

// Установка курсора в выбранную позицию справа-налево сверху-вниз
void CyrI2c::go(byte col){
  if (col < 32){
    go(col - col / 16 * 16, col / 16);
  }
  if (col == 32){
    go(scr_pos);
  }
}

// Инициализация массива строк разделенных символом \r переданного через F()
void CyrI2c::init(const __FlashStringHelper* str){
  p_s = (char*) str;
  f = 1;
}

// Инициализация массива строк разделенных символом \r переданного через указатель
void CyrI2c::init(const char* str){
  s = str;
  f = 2;
}

// Печать строки из ранее переданного массива по её номеру
void CyrI2c::printn(byte num, int8_t position, byte go_ln, byte space){
  if (f == 1){
    printn_flash(num, position, go_ln, space);
    return;
  }
  if (f == 2){
    printn_str(num, position, go_ln, space);
    return;
  }
}

// Печать строки из ранее переданного массива символов по её номеру
void CyrI2c::printn_str(byte num, int8_t position, byte go_ln, byte space){
  char str[255];
  byte count = 0, str_pos;
  word pos = 0;
  while (count < num && pos < 65000 && s[pos]){
    if (s[pos++] == '\r'){
      count++;
      continue;
    }
  }
  if (count != num){
    return;
  }
  for (str_pos = 0; pos < 255 && str_pos < 255 && pos < 65000 && s[pos]; pos++){
    if (s[pos] == '\r'){
      break;
    }
    str[str_pos++] = s[pos];
  }
  str[str_pos] = 0;
  print(str, position, go_ln, space);
}

// Печать строки из ранее переданного внутри F() массива по её номеру
void CyrI2c::printn_flash(byte num, int8_t position, byte go_ln, byte space){
  char str[255];
  byte count = 0, str_pos;
  word pos = 0;
  char chr;
  while (count < num && pos < 65000 && (chr = (char) pgm_read_byte_near(p_s + pos++))){
    if (chr == '\r'){
      count++;
    }
  }
  if (count != num){
    return;
  }
  for (str_pos = 0; (chr = (char) pgm_read_byte_near(p_s + pos)) && pos < 65000; pos++){
    if (chr == '\r'){
      break;
    }
    str[str_pos++] = chr;
  }
  str[str_pos] = 0;
  print(str, position, go_ln, space);
}
