boolean debug = false;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

// For sprintf() function
char buffer[10];

byte hour;

byte brightness = 220;     // 0 - 255

byte    pinout[]           = {8,     9,     4,     6,     5,     7,     3,     2};
boolean pinout_anode[]     = {true,  true,  true,  true,  true,  true,  true,  true};
byte    dig_pinout[]       = {10,    11,    12,    13,    0};
boolean dig_pinout_anode[] = {true,  true,  true,  true};

//                0          1          2          3          4
byte num[]     = {B11111100, B01100000, B11011010, B11110010, B01100110,
//                5          6          7          8          9
                  B10110110, B10111110, B11100000, B11111110, B11110110};
char en[]      = {'a',       'b',       'c',       'd',       'e',       'g',       'h',
                  'i',       'n',       'ñ',       'o',       'q',       'r',       't',       'u',       0};
byte en_code[] = {B11111010, B00111110, B00011010, B01111010, B11011110, B11110110, B00101110,
                  B00100000, B00101000, B10101010, B00111010, B11100110, B00001010, B00011110, B00111000};
char en_big[]      = {'A',       'B',       'C',       'E',       'F',       'G',       'H',       'I',
                      'J',       'L',       'O',       'P',       'S',       'U',       'Y',       'Z',       0};
byte en_big_code[] = {B11101110, B11111110, B10011100, B10011110, B10001110, B10111110, B01101110, B01100000,
                      B01111000, B00011100, B11111100, B11001110, B10110110, B01111100, B01110110, B11011010};
char ru[]      = {'г',       'д',       'е',       'и',       'й',       'о',       'п',       'с',       0};
byte ru_code[] = {B00001010, B11101110, B11011110, B00111000, B10111000, B00111010, B00101010, B00011010};
char ru_big[]      = {'А',       'Б',       'В',       'Г',       'Е',       'Н',       'О',       'П',
                      'Р',       'С',       'У',       'Ч',       'Ь',       'Э',       0};
byte ru_big_code[] = {B11101110, B10111110, B11111110, B10001100, B10011110, B01101110, B11111100, B11101100,
                      B11001110, B10011100, B01110110, B01100110, B00111110, B11110010};

// Количество разрядов дисплея
byte digs;
// Коды для повторного вывода на дисплей
byte* str_code;

unsigned long us;
unsigned long us_show = 0;
unsigned long us_prev = 0;
unsigned int min_brightness = 25000;

void setup(){
  //debug = true;

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (debug){
    Serial.begin(57600);
  }

  init_str();
}

void loop(){
  us = micros();

  if (us - us_prev > 100000){
    us_prev = us;
    DateTime now = rtc.now();
    hour = now.hour() % 12;
    sprintf(buffer, "%d%s%02d", hour ? hour : 12, now.second() % 2 ? "." : "", now.minute());
    show_str(buffer);
  }

  show_str();
}

void init_str(){
  for (byte f = 0; f < 8; f++){
    digitalWrite(pinout[f], !pinout_anode[f]);
    pinMode(pinout[f], OUTPUT);
  }
  for (digs = 0; dig_pinout[digs]; digs++);
  if (debug){
    Serial.print("digs = ");
    Serial.println(digs);
  }
  for (byte f = 0; f < digs; f++){
    digitalWrite(dig_pinout[f], !dig_pinout_anode[f]);
    pinMode(dig_pinout[f], OUTPUT);
  }
  str_code = new byte(digs);
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }
}

void show_str(char* str){
  if (debug){
    Serial.print("str = ");
    Serial.println(str);
  }

  // Стираем старые коды для вывода
  for (byte f = 0; f < digs; f++){
    str_code[f] = 0;
  }

  // Длина строки
  byte str_len;
  for (str_len = 0; str[str_len]; str_len++);
  if (debug){
    Serial.print("str_len = ");
    Serial.println(str_len);
  }

  // Пустая строка - выводить нечего
  if (!str_len){
    return;
  }

  // Флаг наличия точки
  boolean need_dot = false;
  // Обходим конец строки который помещается
  for (int8_t str_pos = str_len - 1, show_pos = 0; str_pos >= 0 && show_pos < digs; str_pos--){
    if (debug){
      Serial.print("str[");
      Serial.print(str_pos);
      Serial.print("] = ");
      Serial.print(str[str_pos]);
      Serial.print(" (");
      Serial.print(str[str_pos], DEC);
      Serial.print(") > ");
      Serial.println(show_pos);
    }
    // Запоминаем точку до следующего раза
    if (str[str_pos] == '.'){
      need_dot = true;
      continue;
    }
    // Если выводим цифру
    if (str[str_pos] >= '0' && str[str_pos] <= '9'){
      if (debug){
        Serial.println("Is number");
      }
      // Бинарный код цифры
      str_code[show_pos] = need_dot | num[str[str_pos] - '0'];
    }
    // Переходим к следующему разряду
    show_pos++;
    // Сбрасываем флаг точки
    need_dot = false;
  }
  show_str();
  //while (debug);
}

void show_str(){
  if (us - us_show <= min_brightness - min_brightness / 256 * brightness){
    return;
  }
  us_show = us;
  // Обходим коды символов для вывода
  for (int8_t show_pos = 0; show_pos < digs; show_pos++){
    if (debug){
      Serial.print("str_code[");
      Serial.print(show_pos);
      Serial.print("] = ");
      Serial.println(str_code[show_pos], BIN);
    }
    // Если есть код символа для вывода (иначе пробел)
    if (!str_code[show_pos]){
      continue;
    }
    if (debug){
      Serial.print("digitalWrite(");
      Serial.print(dig_pinout[show_pos]);
      Serial.print(", ");
      Serial.print(dig_pinout_anode[show_pos]);
      Serial.println(");");
    }
    // Включаем вывод разряда (текущий разряд)
    digitalWrite(dig_pinout[show_pos], dig_pinout_anode[show_pos]);
    // Обходим сигменты разряда
    for (int8_t f = 7; f >= 0; f--){
      if (debug){
        Serial.print("digitalWrite(");
        Serial.print(pinout[7 - f]);
        Serial.print(", ");
        Serial.print(!(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
        Serial.println(");");
      }
      // Включаем необходимый сигмент
      digitalWrite(pinout[7 - f], !(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
    }
    if (debug){
      delay(500);
    }
    // Выключаем сигменты
    for (byte f = 0; f < 8; f++){
      digitalWrite(pinout[f], !pinout_anode[f]);
      pinMode(pinout[f], OUTPUT);
    }
    // Выключаем разряд
    digitalWrite(dig_pinout[show_pos], !dig_pinout_anode[show_pos]);
    // Переходим к следующему разряду
  }
}
