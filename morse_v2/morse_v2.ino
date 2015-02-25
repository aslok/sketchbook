/*
 * morse_v2.ino
 * Телеграфная азбука v2.0
 * Современная телеграфная азбука (система кодировки символов короткими и
 * длинными посылками для передачи их по линиям связи, известная как
 * «код Морзе» или «морзянка»)
 *
 * В среднем 60 знаков в минуту
 * В среднем 3 символа в секунду (350ms на символ), 150 ms точка
 *
 * За единицу времени принимается длительность одной точки. Длительность
 * тире равна трём точкам. Пауза между элементами одного знака — одна точка,
 * между знаками в слове — 3 точки, между словами — 7 точек
 *
 * created 15.01.2015
 * with Arduino 1.5.8 (tested on Arduino Uno)
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

const char str[] PROGMEM = "Jah Rastafari! Джа Растафарай!";

// Флаг для отладки через порт
const boolean debug = true;

// Продолжительность 'точки'
// int ms = 150;
const byte ms = 200;
// Ожидание после каждой итерации вспышек, ms
// Если -1 то только одна итерация без повторений
const int wait = 3000;
// Служебный пин
const byte pin = 13;

typedef struct morse_chr {
  char chr;
  char ext_chr[3];
  byte m_chr;
};

const morse_chr PROGMEM abc[] = {
  { 'a', "а", B11111010 },
  { 'b', "б", B11100111 },
  { 'c', "ц", B11100101 },
  { 'd', "д", B11110011 },
  { 'e', "е", B11111101 },
  { 'e', "ё", B11111101 },
  { 'f', "ф", B11101101 },
  { 'g', "г", B11110001 },
  { 'h', "х", B11101111 },
  { 'i', "и", B11111011 },
  { 'j', "й", B11101000 },
  { 'k', "к", B11110010 },
  { 'l', "л", B11101011 },
  { 'm', "м", B11111000 },
  { 'n', "н", B11111001 },
  { 'o', "о", B11110000 },
  { 'p', "п", B11101001 },
  { 'q', "щ", B11100010 },
  { 'r', "р", B11110101 },
  { 's', "с", B11110111 },
  { 't', "т", B11111100 },
  { 'u', "у", B11110110 },
  { 'v', "ж", B11101110 },
  { 'w', "в", B11110100 },
  { 'x', "ь", B11100110 },
  { 'y', "ы", B11100100 },
  { 'z', "з", B11100011 },
  { 0,   "ö", B11100001 },
  { 0,   "ч", B11100001 },
  { 0,   "ċ", B11100000 },
  { 0,   "ш", B11100000 },
  { 0,   "ъ", B11100010 },
  { 0,   "ñ", B11100010 },
  { 0,   "é", B11011011 },
  { 0,   "э", B11011011 },
  { 0,   "ü", B11101100 },
  { 0,   "ю", B11101100 },
  { 0,   "ä", B11101010 },
  { 0,   "я", B11101010 },
  { '1', "",  B11110000 },
  { '2', "",  B11011000 },
  { '3', "",  B11011100 },
  { '4', "",  B11011110 },
  { '5', "",  B11011111 },
  { '6', "",  B11001111 },
  { '7', "",  B11000111 },
  { '8', "",  B11000011 },
  { '9', "",  B11000001 },
  { '0', "",  B11000000 },
  { '.', "",  B10111111 },
  { ',', "",  B10101010 },
  { ':', "",  B10000111 },
  { ';', "",  B10010101 },
  { '(', "",  B10010010 },
  { ')', "",  B10010010 },
  { '\'', "", B10100001 },
  { '`', "",  B10100001 },
  { '@', "",  B10100101 },
  { '"', "",  B10101101 },
  { '-', "",  B10011110 },
  { '—', "",  B10011110 },
  { '!', "",  B10001100 },
  { '?', "",  B10110011 },
  { '§', "",  B11001110 },
};

// Короткая вспышка
void dot() {
  if (debug) {
    Serial.print('.');
  }
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
}

// Длиная (х3) вспышка
void dash() {
  if (debug) {
    Serial.print('-');
  }
  digitalWrite(pin, HIGH);
  delay(ms * 3);
  digitalWrite(pin, LOW);
}

// Ждем (x2)
void space() {
  if (debug) {
    Serial.print(' ');
  }
  delay(ms * 2);
}

// Ждем (x4)
void new_word(){
  if (debug) {
    Serial.print('\n');
  }
  delay(ms * 4);
}

// Вывод строки посимвольно вспышками
void print_str(const __FlashStringHelper* str_ptr) {
  char* str = (char*) str_ptr;
  byte chr;
  static byte prefix = 0;
  for (byte pos = 0; (chr = pgm_read_byte_near(str + pos)); pos++){
    if (chr == ' '){
      new_word();
      continue;
    }
    if (debug) {
      Serial.print((char) chr);
    }
    for (byte abc_pos = 0; abc_pos < sizeof(abc) / sizeof(morse_chr); abc_pos++){
      if (!prefix && pgm_read_byte_near(&abc[abc_pos].ext_chr) == chr){
        prefix = chr;
        break;
      }else if (prefix){
        char buf[3];
        strcpy_P(buf, (char*) &abc[abc_pos].ext_chr);
        int u_chr = ((prefix & 0x1F) << 6) + (chr & 0x3F);
        int u_buf = (((byte) buf[0] & 0x1F) << 6) + ((byte) buf[1] & 0x3F);
        if (u_chr >= 0x0400 && u_chr < 0x0410){
          u_chr += 0x0050;
        }else if (u_chr >= 0x0410 && u_chr < 0x0430){
          u_chr += 0x0020;
        }
        if (u_chr == u_buf){
          print_chr(abc_pos);
          prefix = 0;
          space();
          break;
        }
      }else if (pgm_read_byte_near(&abc[abc_pos].chr) == tolower(chr)){
        print_chr(abc_pos);
        space();
        break;
      }
    }
  }
  if (debug) {
    Serial.print('\n');
  }
}

// Вывод символа вспышками
void print_chr(byte pos){
  if (debug) {
    Serial.print(" = ");
  }
  byte m_chr = pgm_read_byte_near(&abc[pos].m_chr);
  boolean ignore = true;
  byte cnt = 0;
  for(byte mask = 0x80; mask; mask >>= 1){
    if (ignore){
      if (mask & ~m_chr){
        ignore = false;
      }
      continue;
    }
    cnt++;
    if (mask & m_chr){
      dot();
    }else{
      dash();
    }
    delay(ms);
  }
  if (debug) {
    while (cnt++ < 6){
      Serial.print(' ');
    }
  }
}

void setup() {
  pinMode(pin, OUTPUT);
  if (debug) {
    Serial.begin(57600);
  }
}

void loop() {
  print_str((__FlashStringHelper*) str);
  // Если больше ничего не делаем
  if (wait == -1) {
    while (true);
  }
  // Ничего не делаем ew милисекунды
  delay(wait);
}
