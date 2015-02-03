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
  // Строка для поиска символов для замены
  abc    = (char*) F("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяҐЄІЇґєії");
  en     = (char*) F("ABEE3UUKMHOPCTXWWbb\312\277\354\321\371\326\323II");
  en_num = (byte*) F("\200\202\205\206\210\211\212\213\215\216\217\221\222\223\226\231\232\235\233\214\224\225\230\227\236\242\243\244");
  ru_num = (byte*) F("\201\203\204\234\237\240\207\220\241\230\242\214\224\225\227\236\233\232\244\231\212\211\206\210\235");
  byte ru_cnt;
  // Выясняем длину строки
  for (ru_cnt = 0; (char) pgm_read_byte_near(ru_num + ru_cnt); ru_cnt++);
  ru     = new byte*[ru_cnt];
  ru[0]  = new byte[8]{ 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 };
  ru[1]  = new byte[8]{ 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru[2]  = new byte[8]{ 0xe, 0xa, 0xa, 0xa, 0xa, 0x1f,0x11,0x0 };
  ru[3]  = new byte[8]{ 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 };
  ru[4]  = new byte[8]{ 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 };
  ru[5]  = new byte[8]{ 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 };
  ru[6]  = new byte[8]{ 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 };
  ru[7]  = new byte[8]{ 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 };
  ru[8]  = new byte[8]{ 0x1, 0x1f,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru[9]  = new byte[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0x1, 0x0 };
  ru[10] = new byte[8]{ 0xf, 0x10,0x10,0x1e,0x10,0x10,0xf, 0x0 };
  ru[11] = new byte[8]{ 0x3, 0x5, 0x9, 0x9, 0x9, 0x9, 0x19,0x0 };
  ru[12] = new byte[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0xe, 0x0 };
  ru[13] = new byte[8]{ 0xe, 0x15,0x15,0x15,0xe, 0x4, 0x4, 0x0 };
  ru[14] = new byte[8]{ 0x12,0x12,0x12,0x12,0x12,0x12,0x1f,0x1 };
  ru[15] = new byte[8]{ 0x1e,0x1, 0x1, 0xf, 0x1, 0x1, 0x1e,0x0 };
  ru[16] = new byte[8]{ 0x18,0x8, 0x8, 0xe, 0x9, 0x9, 0xe, 0x0 };
  ru[17] = new byte[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1e,0x1 };
  ru[18] = new byte[8]{ 0xa, 0x4, 0x4, 0x4, 0x4, 0x4, 0xe, 0x0 };
  ru[19] = new byte[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1f,0x0 };
  ru[20] = new byte[8]{ 0x15,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru[21] = new byte[8]{ 0x11,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru[22] = new byte[8]{ 0xa, 0x1f,0x10,0x1e,0x10,0x10,0x1f,0x0 };
  ru[23] = new byte[8]{ 0xe, 0x11,0x1, 0xe, 0x1, 0x11,0xe, 0x0 };
  ru[24] = new byte[8]{ 0x10,0x10,0x10,0x1c,0x12,0x12,0x1c,0x0 };

  s      = NULL;
  f      = 0;
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
  byte tmp;
  for (cur_chr = 0; cur_chr < 32; cur_chr++){
    found = false;
    // Обходим основной набор символов для замены
    for (cur = 0; (char) (tmp = (byte) pgm_read_byte_near(en_num + cur)); cur++){
      if (tmp == (byte) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = (char) pgm_read_byte_near(en + cur);
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
      if ((byte) pgm_read_byte_near(ru_num + cur) == (byte) lcd_replace[cur_chr]){
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
      char_map[i] = (byte) pgm_read_byte_near(ru_num + cur);
      /*Serial.println("lcd->createChar(i, ru[cur]);");
      Serial.println(i);
      Serial.println(cur);
      Serial.println("----------------------------");*/
      lcd->createChar(i, ru[cur]);
      // Бага lcd->createChar - приходится обновлять курсор
      go();
      // Будем заменять его при выводе на номер ячейки
      for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
        if ((byte) lcd_replace[cur_pos] == (byte) pgm_read_byte_near(ru_num + cur)){
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
    for (i = 0; (char) pgm_read_byte_near(ru_num + i); i++);
    for (cur_pos = i; cur_pos-- > 8; ){
      // Ищем ячейку занятую этим символом
      for (i = 0; i < 8; i++){
        // Если есть кандидат на выселение
        if ((byte) pgm_read_byte_near(ru_num + cur_pos) == char_map[i]){
          found = false;
          // Обходим основной набор символов для замены
          // После выселения будет отображаться оттуда
          for (pos = 0; (char) (tmp = (byte) pgm_read_byte_near(en_num + pos)); pos++){
            if (tmp == char_map[i]){
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
          char_map[i] = (byte) pgm_read_byte_near(ru_num + cur);
          // Будем заменять его при выводе на номер ячейки
          for (pos = 0; pos < 32; pos++){
            if ((byte) lcd_replace[pos] == (byte) pgm_read_byte_near(ru_num + cur)){
              /*Serial.println("lcd_replace[pos] = i");
              Serial.println(pos);
              Serial.println(i);
              Serial.println("----------------------------");*/
              lcd_replace[pos] = i;
            }
            // Динамическое обновление символов
            // Перетираем отображающееся предыдущее содержимое ячейки
            if ((byte) next_scr[pos] == (byte) pgm_read_byte_near(ru_num + cur_pos)){
              lcd->setCursor(pos - pos / 16 * 16, pos / 16);
              lcd_replace[pos] = (char) pgm_read_byte_near(en + old_cur);
              lcd->write((char) pgm_read_byte_near(en + old_cur));
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
    for (byte ru_cur = 9; (char) (tmp = (byte) pgm_read_byte_near(ru_num + ru_cur)); ru_cur++){
      found = false;
      // Обходим уже использованные дополнительные символы
      for (i = 0; i < 8; i++){
        if (char_map[i] && char_map[i] == tmp){
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
        if ((byte) next_scr[cur_chr] != tmp){
          continue;
        }
        // Найден текущий дополнительный самодельный символ
        // Сохраняем в ячейку номер символа
        char_map[cur] = tmp;
        /*Serial.println("lcd->createChar(cur, ru[ru_cur]);");
        Serial.println(cur);
        Serial.println(ru_cur);
        Serial.println("----------------------------");*/
        lcd->createChar(cur, ru[ru_cur]);
        // Будем заменять его при выводе на номер ячейки
        // Обходим начиная с текущего, предыдущие заменили бы раньше
        for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
          if ((byte) next_scr[cur_pos] == tmp){
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
  s = (char*) str;
  f = 1;
}

// Инициализация массива строк разделенных символом \r переданного через указатель
void CyrI2c::init(const char* str){
  s = (char*) str;
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
  while (count < num && pos < 65000 && ((char*) s)[pos]){
    if (((char*) s)[pos++] == '\r'){
      count++;
      continue;
    }
  }
  if (count != num){
    return;
  }
  for (str_pos = 0; pos < 255 && str_pos < 255 && pos < 65000 && ((char*) s)[pos]; pos++){
    if (((char*) s)[pos] == '\r'){
      break;
    }
    str[str_pos++] = ((char*) s)[pos];
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
  while (count < num && pos < 65000 && (chr = (char) pgm_read_byte_near(s + pos++))){
    if (chr == '\r'){
      count++;
    }
  }
  if (count != num){
    return;
  }
  for (str_pos = 0; (chr = (char) pgm_read_byte_near(s + pos)) && pos < 65000; pos++){
    if (chr == '\r'){
      break;
    }
    str[str_pos++] = chr;
  }
  str[str_pos] = 0;
  print(str, position, go_ln, space);
}
