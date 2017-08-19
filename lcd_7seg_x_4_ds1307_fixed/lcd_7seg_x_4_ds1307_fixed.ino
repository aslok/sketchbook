boolean debug = false;
boolean debug_display = false;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

// For sprintf() function
char buffer[21];

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

// unixtime - таймстамп последней ручной установки , хранится по адресу #0
// adjust - количество секунд для автоматической коррекции, хранится по адресу #4
// last_adjust - таймстамп последней автоматической коррекции, хранится по адресу #8
unsigned long last_adjust = 0;
unsigned long us_status = 0;
char buffer_incom[21];
byte buffer_incom_pos = 0;
boolean buffer_incom_done = false;
// Mode: #0 - normal, #1 - set time, #2 - set adjust, #3 - set unixtime
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
  rtc.readnvram(read_arr, 4, 8);
  last_adjust = *((unsigned long*) & read_arr);
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
      byte read_arr[4];
      rtc.readnvram(read_arr, 4, 4);
      float adjust = *((float*) & read_arr);
      if (adjust){
        last_adjust = now.unixtime() + 1;
        byte* adjust_arr = (byte*) &last_adjust;
        byte write_arr[] = {
          adjust_arr[0],
          adjust_arr[1],
          adjust_arr[2],
          adjust_arr[3]
        };
        rtc.writenvram(8, write_arr, 4);

        float adjust_dec = adjust - (long) adjust;
        delay(1000 / (adjust_dec * -1));
        if (adjust < 0){
          adjust++;
        }

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
    }else if (!mode && !strcmp(buffer_incom, "adjust")){
      mode = 2;
      Serial.println(F("ADJUST: Please enter adjust"));
    }else if (!mode && !strcmp(buffer_incom, "unixtime")){
      mode = 3;
      Serial.println(F("UNIXTIME: Please enter unixtime"));
    }else if (!mode && !strcmp(buffer_incom, "read")){
      byte read_arr[8];
      rtc.readnvram(read_arr, 8, 0);
      unsigned long unixtime = *((unsigned long*) & read_arr);
      Serial.print(F("READ UNIXTIME: "));
      Serial.println(unixtime);
      float adjust = *((float*) & read_arr[4]);
      Serial.print(F("READ ADJUST: "));
      printFloat(adjust, 2);
      Serial.println();
    }else if (!mode && !strcmp(buffer_incom, "last")){
      byte write_arr[] = {0, 0, 0, 0};
      rtc.writenvram(8, write_arr, 4);
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
      byte read_arr[8];
      rtc.readnvram(read_arr, 8, 0);
      // Последний раз устанавливалось правильное время:
      unsigned long old_unixtime = *((unsigned long*) & read_arr);
      // Учитываем существующую поправку (например -12.50)
      float adjust = *((float*) & read_arr[4]);
      // Прошло столько секунд с момента последней коррекции (например 88916):
      float time_elapsed = new_unixtime - old_unixtime;
      DateTime now = rtc.now();
      // Делим прошедшие секунды на разницу в секундах
      // Например, если час назад мы переводили часы на 5 сек, тогда 3600 / 5 = 720
      // Это значит часы отстают на 1 секунду за 720 секунд, запоминаем 720
      // Такая разница в секундах с последней установки времени (например -2):
      long time_diff = new_unixtime - now.unixtime();
      // Напрмер 86400 / (89349 / -2) + (-12.50)
      float new_adjust = (time_diff ? (3600.0 * 24 / (time_elapsed / time_diff)) : 0) + adjust;
      if (debug){
        Serial.print(F("SET: New time "));
        sprintf(buffer,
                "%02d.%02d.%04d %02d:%02d:%02d",
                new_time.day(), new_time.month(), new_time.year(),
                new_time.hour(), new_time.minute(), new_time.second());
        Serial.println(buffer);
        Serial.print(F("SET: Old adjust value "));
        printFloat(adjust, 2);
        Serial.println();
        Serial.print(F("SET: Elapsed time "));
        printFloat(time_elapsed, 2);
        Serial.println();
        Serial.print(F("SET: Old timestamp "));
        Serial.print(now.unixtime());
        Serial.println();
        Serial.print(F("SET: New timestamp "));
        Serial.println(new_unixtime);
        Serial.print(F("SET: Time diff "));
        Serial.println(time_diff);
        Serial.print(F("SET: Adjust "));
        printFloat(new_adjust, 2);
        Serial.println();
      }
      byte* unixtime_arr = (byte*) &new_unixtime;
      byte* adjust_arr = (byte*) &new_adjust;
      byte write_arr[] = {
        unixtime_arr[0],
        unixtime_arr[1],
        unixtime_arr[2],
        unixtime_arr[3],
        adjust_arr[0],
        adjust_arr[1],
        adjust_arr[2],
        adjust_arr[3]
      };
      rtc.adjust(new_time);
      rtc.writenvram(0, write_arr, 8);
      Serial.println(F("SET: Done"));
    }else if (mode == 2){
      mode = 0;
      float new_adjust = atof(buffer_incom);
      byte* adjust_arr = (byte*) &new_adjust;
      byte write_arr[] = {
        adjust_arr[0],
        adjust_arr[1],
        adjust_arr[2],
        adjust_arr[3]
      };
      rtc.writenvram(4, write_arr, 4);
      Serial.print(F("ADJUST: Set "));
      printFloat(new_adjust, 2);
      Serial.println(F(" done "));
    }else if (mode == 3){
      mode = 0;
      unsigned long new_unixtime = atol(buffer_incom);
      byte* new_unixtime_arr = (byte*) &new_unixtime;
      byte write_arr[] = {
        new_unixtime_arr[0],
        new_unixtime_arr[1],
        new_unixtime_arr[2],
        new_unixtime_arr[3]
      };
      rtc.writenvram(0, write_arr, 4);
      Serial.print(F("UNIXTIME: Set "));
      Serial.print(new_unixtime);
      Serial.println(F(" done "));
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

void printFloat(float value, int places) {
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  for (i = 0; i < places; i++)
    d/= 10.0;
  tempfloat +=  d;
  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }
  if (value < 0)
    Serial.print('-');

  if (tenscount == 0)
    Serial.print(0, DEC);

  for (i=0; i< tenscount; i++) {
    digit = (int) (tempfloat/tens);
    Serial.print(digit, DEC);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }
  if (places <= 0)
    return;
  Serial.print('.');
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    Serial.print(digit,DEC);
    tempfloat = tempfloat - (float) digit;
  }
}
