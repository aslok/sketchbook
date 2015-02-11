/*
created 10.02.2015
modified 10.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#include "Cyruit.h"

/*
Кодировка CP1251 использует для хранения символа один байт
Для использования необходимо скопировать glcdfont_cp1251.c в
в каталог Adafruit-GFX-Library-master
и заменить в начале файла Adafruit_GFX.cpp название файла
строку
#include "glcdfont.c"
на строку
#include "glcdfont_cp1251.c"
*/

const Letter PROGMEM g_letters[61] = {
  {0x82, 0x201A}, // SINGLE LOW-9 QUOTATION MARK
  {0x83, 0x0453}, // CYRILLIC SMALL LETTER GJE
  {0x84, 0x201E}, // DOUBLE LOW-9 QUOTATION MARK
  {0x85, 0x2026}, // HORIZONTAL ELLIPSIS
  {0x86, 0x2020}, // DAGGER
  {0x87, 0x2021}, // DOUBLE DAGGER
  {0x88, 0x20AC}, // EURO SIGN
  {0x89, 0x2030}, // PER MILLE SIGN
  {0x8A, 0x0409}, // CYRILLIC CAPITAL LETTER LJE
  {0x8B, 0x2039}, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
  {0x8C, 0x040A}, // CYRILLIC CAPITAL LETTER NJE
  {0x8D, 0x040C}, // CYRILLIC CAPITAL LETTER KJE
  {0x8E, 0x040B}, // CYRILLIC CAPITAL LETTER TSHE
  {0x8F, 0x040F}, // CYRILLIC CAPITAL LETTER DZHE
  {0x90, 0x0452}, // CYRILLIC SMALL LETTER DJE
  {0x91, 0x2018}, // LEFT SINGLE QUOTATION MARK
  {0x92, 0x2019}, // RIGHT SINGLE QUOTATION MARK
  {0x93, 0x201C}, // LEFT DOUBLE QUOTATION MARK
  {0x94, 0x201D}, // RIGHT DOUBLE QUOTATION MARK
  {0x95, 0x2022}, // BULLET
  {0x96, 0x2013}, // EN DASH
  {0x97, 0x2014}, // EM DASH
  {0x99, 0x2122}, // TRADE MARK SIGN
  {0x9A, 0x0459}, // CYRILLIC SMALL LETTER LJE
  {0x9B, 0x203A}, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
  {0x9C, 0x045A}, // CYRILLIC SMALL LETTER NJE
  {0x9D, 0x045C}, // CYRILLIC SMALL LETTER KJE
  {0x9E, 0x045B}, // CYRILLIC SMALL LETTER TSHE
  {0x9F, 0x045F}, // CYRILLIC SMALL LETTER DZHE
  {0xA0, 0x00A0}, // NO-BREAK SPACE
  {0xA1, 0x040E}, // CYRILLIC CAPITAL LETTER SHORT U
  {0xA2, 0x045E}, // CYRILLIC SMALL LETTER SHORT U
  {0xA3, 0x0408}, // CYRILLIC CAPITAL LETTER JE
  {0xA4, 0x00A4}, // CURRENCY SIGN
  {0xA5, 0x0490}, // CYRILLIC CAPITAL LETTER GHE WITH UPTURN
  {0xA6, 0x00A6}, // BROKEN BAR
  {0xA7, 0x00A7}, // SECTION SIGN
  {0xA8, 0x0401}, // CYRILLIC CAPITAL LETTER IO
  {0xA9, 0x00A9}, // COPYRIGHT SIGN
  {0xAA, 0x0404}, // CYRILLIC CAPITAL LETTER UKRAINIAN IE
  {0xAB, 0x00AB}, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
  {0xAC, 0x00AC}, // NOT SIGN
  {0xAD, 0x00AD}, // SOFT HYPHEN
  {0xAE, 0x00AE}, // REGISTERED SIGN
  {0xAF, 0x0407}, // CYRILLIC CAPITAL LETTER YI
  {0xB0, 0x00B0}, // DEGREE SIGN
  {0xB1, 0x00B1}, // PLUS-MINUS SIGN
  {0xB2, 0x0406}, // CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I
  {0xB3, 0x0456}, // CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
  {0xB4, 0x0491}, // CYRILLIC SMALL LETTER GHE WITH UPTURN
  {0xB5, 0x00B5}, // MICRO SIGN
  {0xB6, 0x00B6}, // PILCROW SIGN
  {0xB7, 0x00B7}, // MIDDLE DOT
  {0xB8, 0x0451}, // CYRILLIC SMALL LETTER IO
  {0xB9, 0x2116}, // NUMERO SIGN
  {0xBA, 0x0454}, // CYRILLIC SMALL LETTER UKRAINIAN IE
  {0xBB, 0x00BB}, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
  {0xBC, 0x0458}, // CYRILLIC SMALL LETTER JE
  {0xBD, 0x0405}, // CYRILLIC CAPITAL LETTER DZE
  {0xBE, 0x0455}, // CYRILLIC SMALL LETTER DZE
  {0xBF, 0x0457}  // CYRILLIC SMALL LETTER YI
};

// Конструктор
Cyruit::Cyruit(int8_t sclk, int8_t din, int8_t dc, int8_t cs, int8_t rst, byte contrast){
  lcd = new Adafruit_PCD8544(sclk, din, dc, cs, rst);
  lcd->begin();
  lcd->setContrast(contrast);
  clear();
}

// Ф-ия печати строк переданных с помощью F()
void Cyruit::print(const __FlashStringHelper* str, int8_t position, byte go_ln, byte space){
  char tmp[99];
  strcpy_P(tmp, (char*) str);
  print(tmp, position, go_ln, space);
}

// Ф-ия печати целых чисел
void Cyruit::print(int chr, int8_t position, byte go_ln, byte space){
  char str[98];
  sprintf(str, "%d", chr);
  print(str, position, go_ln, space);
}

// Печать чисел с плавающей точкой
void Cyruit::print(double chr, int8_t position, byte go_ln, byte width, byte prec){
  char str[98];
  dtostrf(chr, width, prec, str);
  print(str, position, go_ln);
}

// Печать отдельного символа
void Cyruit::print(char chr, int8_t position, byte go_ln, byte space){
  char str[2]{chr};
  print(str, position, go_ln, space);
}

// Печать отдельного символа несколько раз
void Cyruit::print(char chr, int count){
  char str[2]{chr};
  while (count--){
    print(str);
  }
}

// Печать массива символов по указателю
void Cyruit::print(char* str, int8_t position, byte go_ln, byte space){
  byte cur, old_cur, i, cur_pos, pos;
  if (go_ln != 255 && go_ln < 7){
    go(0, go_ln);
  }
  // Создаем копию во внутренней кодировке
  char out[98];
  utf8_to_cp1251(str, out);
  byte out_size = strlen(out);
  if (position != 127 && position < 14 && position > -15){
    if (position < 0){
      if (space != 255){
        go(15 - space + position, scr_pos / 14);
        print(' ', space - out_size);
      }else{
        go(15 - out_size + position, scr_pos / 14);
      }
    }else{
      go(position, scr_pos / 14);
    }
  }
  if (space != 255){
    // Сдвиг относительно текущей позиции
    i = (space - out_size) / 2;
    // Если сдвиг влево
    if (i < 0) {
      // Если край экрана - переносим курсор
      go(i + scr_pos >= 0 ? i + scr_pos : i % 98 + scr_pos);
    }else{
      // Если сдвиг вправо - сдвигаем курсор пробелами
      print(' ', (space - out_size) / 2);
      // Печатаем строку
      print(str);
      // Сдвигаем курсор пробелами
      print(' ', space - out_size - ((space - out_size) / 2));
      return;
    }
  }
  // Печатаем строку во внутренней кодировке
  write_str_enc(out);
}

// Печатаем строку во внутренней кодировке
void Cyruit::write_str_enc(char* str){
  for (byte cur_chr = 0; str[cur_chr]; cur_chr++){
    if (scr_pos >= 98){
      go(0);
    }
    write_bg();
    lcd->print(str[cur_chr]);
    scr_pos++;
  }
  lcd->display();
}

void Cyruit::write_bg(){
  lcd->fillRect(
    (scr_pos - scr_pos / 14 * 14) * 6, scr_pos / 14 * 8,
    6, 8,
    WHITE
  );
}

int Cyruit::utf8_to_cp1251(const char* utf8, char* windows1251, word n){
  int j = 0;
  for(int i = 0; i < n && utf8[i] != 0; ++i) {
    char prefix = utf8[i];
    char suffix = utf8[i+1];
    if ((prefix & 0x80) == 0) {
      windows1251[j] = (char)prefix;
      ++j;
    } else if ((~prefix) & 0x20) {
      int first5bit = prefix & 0x1F;
      first5bit <<= 6;
      int sec6bit = suffix & 0x3F;
      int unicode_char = first5bit + sec6bit;
      if ( unicode_char >= 0x410 && unicode_char <= 0x44F ) {
        windows1251[j] = (char)(unicode_char - 0x350);
      } else if (unicode_char >= 0x80 && unicode_char <= 0xFF) {
        windows1251[j] = (char)(unicode_char);
      } else if (unicode_char >= 0x402 && unicode_char <= 0x403) {
        windows1251[j] = (char)(unicode_char - 0x382);
      } else {
        for (int k = 0; k < 61; k++) {
          if (unicode_char == letter_utf8(g_letters + k)) {
            windows1251[j] = letter_cp1251(g_letters + k);
            goto NEXT_LETTER;
          }
        }
        // can't convert this char
        return 0;
      }
NEXT_LETTER:
      ++i;
      ++j;
    } else {
      // can't convert this chars
      return 0;
    }
  }
  windows1251[j] = 0;
  return 1;
}

char Cyruit::letter_cp1251(const Letter* ptr){
  return (char) pgm_read_byte_near(ptr);
}

int Cyruit::letter_utf8(const Letter* ptr){
  return (int) pgm_read_word_near((char*) ptr + 1);
}

// Очистка экрана и установка курсора на ноль
void Cyruit::clear(){
  lcd->clearDisplay();
  go(0);
}

// Установка курсора в выбранные столбец-строка
void Cyruit::go(byte col, byte row){
  //Serial.println("go");
  //Serial.println(col);
  //Serial.println(row);
  if (col < 14 && row < 7){
    lcd->setCursor(col * 6, row * 8);
    scr_pos = row * 14 + col;
  }
}

// Установка курсора в выбранную позицию справа-налево сверху-вниз
void Cyruit::go(byte col){
  //Serial.println("go");
  //Serial.println(col);
  if (col < 98){
    go(col - col / 14 * 14, col / 14);
  }else if (col == 98){
    go(scr_pos);
  }
}

void Cyruit::drawBitmap(int x, int y, const byte *bitmap, int w, int h, word color){
  lcd->drawBitmap(x, y, bitmap, w, h, color);
  lcd->display();
}

void Cyruit::drawBitmap(int x, int y, const byte *bitmap, int w, int h, word color, word bg){
  lcd->drawBitmap(x, y, bitmap, w, h, color, bg);
  lcd->display();
}
