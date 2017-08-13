boolean debug = false;
boolean debug_display = false;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

// For sprintf() function
char buffer[10];

byte brightness = 245;     // 0 - 255

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

unsigned long last_adjust = 0;
unsigned long us_status = 0;
char buffer_incom[21];
byte buffer_incom_pos = 0;
boolean buffer_incom_done = false;
// Mode: #0 - normal, #1 - set time
byte mode = 0;

void setup(){
  //debug = true;
  //debug_display = true;

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  //if (debug || debug_display){
    Serial.begin(57600);
  //}

  byte read_arr[4];
  rtc.readnvram(read_arr, 4, 6);
  last_adjust =
    ((unsigned long) read_arr[0] << 24) |
    ((unsigned long) read_arr[1] << 16) |
    ((unsigned long) read_arr[2] << 8) |
    (unsigned long) read_arr[3];
  if (debug){
    Serial.print(F("Adjusted last time: "));
    Serial.println(last_adjust);
  }

  DateTime now = rtc.now();
  sprintf(buffer,
          "%02d.%02d.%04d %02d:%02d:%02d",
          now.day(), now.month(), now.year(),
          now.hour(), now.minute(), now.second());
  Serial.println(buffer);

  init_str();
}

void loop(){
  us = micros();

  if (us - us_prev > 1000000){
    us_prev = us;
    DateTime now = rtc.now();
    byte hour = now.hour() % 12;
    sprintf(buffer, "%d%s%02d", hour ? hour : 12, now.second() % 2 ? "." : "", now.minute());
    show_str(buffer);

    if (now.hour() == 12 && now.minute() == 30 && now.second() == 30 && now.unixtime() > last_adjust){
      byte read_arr[2];
      rtc.readnvram(read_arr, 2, 4);
      int adjust =
        ((int) read_arr[0] << 8) |
        (int) read_arr[1];
      if (adjust){
        last_adjust = now.unixtime() + 1;
        byte write_arr[] = {
          (last_adjust & 0xff000000UL) >> 24,
          (last_adjust & 0x00ff0000UL) >> 16,
          (last_adjust & 0x0000ff00UL) >>  8,
          (last_adjust & 0x000000ffUL)
        };
        rtc.writenvram(6, write_arr, 4);
        DateTime new_time = DateTime(now.unixtime() + adjust);
        rtc.adjust(new_time);
      }
      if (debug){
        Serial.print(F("Adjusted time: "));
        Serial.println(adjust);
      }
    }
  }

  if (debug && !mode && us - us_status > 1000000){
    us_status = us;
    DateTime now = rtc.now();
    sprintf(buffer,
            "%02d.%02d.%04d %02d:%02d:%02d",
            now.day(), now.month(), now.year(),
            now.hour(), now.minute(), now.second());
    Serial.println(buffer);
  }

  while (Serial.available() > 0){
    switch (char incom_byte = Serial.read()){
      case 10:
        break;
      case 13:
        buffer_incom[buffer_incom_pos] = '\0';
        buffer_incom_pos = 0;
        buffer_incom_done = true;
        if (debug){
          Serial.print(F("Received: "));
          Serial.println(buffer_incom);
        }
        break;
      default:
        buffer_incom[buffer_incom_pos++] = incom_byte;
    }
  }

  if (buffer_incom_done){
    if (!mode && !strcmp(buffer_incom, "set")){
      mode = 1;
      Serial.println(F("SET: Please enter date and time"));
    }else if (!mode && !strcmp(buffer_incom, "read")){
      byte read_arr[6];
      rtc.readnvram(read_arr, 6, 0);
      unsigned long unixtime =
        ((unsigned long) read_arr[0] << 24) |
        ((unsigned long) read_arr[1] << 16) |
        ((unsigned long) read_arr[2] << 8) |
        (unsigned long) read_arr[3];
      Serial.print(F("READ UNIXTIME: "));
      Serial.println(unixtime);
      int adjust =
        ((int) read_arr[4] << 8) |
        (int) read_arr[5];
      Serial.print(F("READ ADJUST: "));
      Serial.println(adjust);
    }else if (!mode && !strcmp(buffer_incom, "adjust")){
      byte write_arr[] = {0, 0};
      rtc.writenvram(4, write_arr, 2);
      Serial.println(F("ADJUST: Set null done "));
    }else if (!mode && !strcmp(buffer_incom, "last")){
      byte write_arr[] = {0, 0, 0, 0};
      rtc.writenvram(6, write_arr, 4);
      Serial.println(F("LAST ADJUST: Set null done "));
    }else if (mode == 1){
      mode = 0;
      char delim[] = " :.";
      byte day = atoi(strtok(buffer_incom, delim));
      byte month = atoi(strtok(NULL, delim));
      int year = atoi(strtok(NULL, delim));
      byte hour = atoi(strtok(NULL, delim));
      byte minute = atoi(strtok(NULL, delim));
      byte second = atoi(strtok(NULL, delim));
      // Правильное время:
      DateTime new_time = DateTime(year, month, day, hour, minute, second);
      unsigned long new_unixtime = new_time.unixtime();
      byte read_arr[6];
      rtc.readnvram(read_arr, 6, 0);
      // Последний раз устанавливалось правильное время:
      unsigned long old_unixtime =
        ((unsigned long) read_arr[0] << 24) |
        ((unsigned long) read_arr[1] << 16) |
        ((unsigned long) read_arr[2] << 8) |
        (unsigned long) read_arr[3];
      int adjust =
        ((int) read_arr[4] << 8) |
        (int) read_arr[5];
      // Прошло столько секунд с момента последней коррекции:
      long time_elapsed = new_unixtime - old_unixtime;
      if (debug){
        Serial.print(F("SET: Elapsed time "));
        Serial.println(time_elapsed);
      }
      DateTime now = rtc.now();
      // Делим прошедшие секунды на разницу в секундах
      // Например, если час назад мы переводили часы на 5 сек, тогда 3600 / 5 = 720
      // Это значит часы отстают на 1 секунду за 720 секунд, запоминаем 720
      // Такая разница в секундах с последней установки времени:
      long time_diff = new_unixtime - now.unixtime();
      if (debug){
        Serial.print(F("SET: Time diff "));
        Serial.println(time_diff);
      }
      int new_adjust = (time_diff ? (3600L * 24 / (time_elapsed / time_diff)) : 0) + adjust;
      if (debug){
        Serial.print(F("SET: Adjust "));
        Serial.println(new_adjust);
      }
      byte write_arr[] = {
        (new_unixtime & 0xff000000UL) >> 24,
        (new_unixtime & 0x00ff0000UL) >> 16,
        (new_unixtime & 0x0000ff00UL) >>  8,
        (new_unixtime & 0x000000ffUL),
        (new_adjust & 0x0000ff00UL) >>  8,
        (new_adjust & 0x000000ffUL)
      };
      rtc.adjust(new_time);
      rtc.writenvram(0, write_arr, 6);
      Serial.println(F("SET: Done"));
    }
    buffer_incom_done = false;
  }

  show_str();
}

void init_str(){
  for (byte f = 0; f < 8; f++){
    digitalWrite(pinout[f], !pinout_anode[f]);
    pinMode(pinout[f], OUTPUT);
  }
  for (digs = 0; dig_pinout[digs]; digs++);
  if (debug_display){
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
  if (debug_display){
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
  if (debug_display){
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
    if (debug_display){
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
      if (debug_display){
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
  //while (debug_display);
}

void show_str(){
  if (us - us_show <= min_brightness - min_brightness / 256 * brightness){
    return;
  }
  us_show = us;
  // Обходим коды символов для вывода
  for (int8_t show_pos = 0; show_pos < digs; show_pos++){
    if (debug_display){
      Serial.print("str_code[");
      Serial.print(show_pos);
      Serial.print("] = ");
      Serial.println(str_code[show_pos], BIN);
    }
    // Если есть код символа для вывода (иначе пробел)
    if (!str_code[show_pos]){
      continue;
    }
    if (debug_display){
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
      if (debug_display){
        Serial.print("digitalWrite(");
        Serial.print(pinout[7 - f]);
        Serial.print(", ");
        Serial.print(!(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
        Serial.println(");");
      }
      // Включаем необходимый сигмент
      digitalWrite(pinout[7 - f], !(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
    }
    if (debug_display){
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
