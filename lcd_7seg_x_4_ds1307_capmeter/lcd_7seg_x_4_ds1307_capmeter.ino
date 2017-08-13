boolean debug = false;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

int analogPin = A7;
int charge1Pin = A0;
int charge2Pin = A1;
int charge3Pin = A2;
int chargePin = charge1Pin;
int dischargePin = A3;

// Resistor 20k
unsigned long resistor1Value = 21700;
// Resistor 50k
unsigned long resistor2Value = 46600;
// Resistor 100k
unsigned long resistor3Value = 101700;
// Current resistor value
unsigned long resistorValue;

// No cap value
float fault1Value = 12.72;
float fault2Value = 5.92;
float fault3Value = 2.49;
float faultValue = fault3Value;

unsigned long startTime;
unsigned long elapsedTime;
unsigned long startWait = 0;

float nanoFarads;

enum mode_type {
  wait,
  cap_charge,
  cap_discharge
};

mode_type mode = wait;

// For sprintf() function
char buffer[10];

byte hour;

byte brightness = 240;     // 0 - 255

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

  pinMode(charge1Pin, INPUT);
  pinMode(charge2Pin, INPUT);
  pinMode(charge3Pin, INPUT);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);

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
  if (debug){
    Serial.print(F("start loop, mode = "));
    Serial.println(mode);
    Serial.print(F("analogRead(analogPin) = "));
    Serial.println(analogRead(analogPin));
  }
  us = micros();
  if (mode == wait && us - startWait > 1000000){
    if (debug){
      Serial.print(F("mode = "));
      Serial.println(mode);
    }
    // Prevents capacitor from discharging
    pinMode(dischargePin, INPUT);
    // Begins charging the capacitor
    pinMode(chargePin, OUTPUT);
    digitalWrite(chargePin, HIGH);
    startTime = micros();
    mode = cap_charge;
  }
  if (mode == cap_charge){
    if (debug){
      Serial.print(F("mode = "));
      Serial.println(mode);
    }
    while (analogRead(analogPin) < 648){
      show_str();
      /*if (debug){
        Serial.print("analogRead(analogPin) = ");
        Serial.println(analogRead(analogPin));
      }*/
    }
    elapsedTime = micros() - startTime;

    if (chargePin == charge1Pin){
      resistorValue = resistor1Value;
      faultValue = fault1Value;
    }else if (chargePin == charge2Pin){
      resistorValue = resistor2Value;
      faultValue = fault2Value;
    }else if (chargePin == charge3Pin){
      resistorValue = resistor3Value;
      faultValue = fault3Value;
    }
    nanoFarads = analogRead(analogPin) < 100 ? 0 : ((float) elapsedTime * 1000 / resistorValue - faultValue);
    if (nanoFarads < 1){
      nanoFarads = 0;
    }

    if (debug){
      Serial.print(F("analogRead(analogPin) = "));
      Serial.println(analogRead(analogPin));
      Serial.print(F("elapsedTime = "));
      Serial.println(elapsedTime);
      Serial.print(F("resistorValue = "));
      Serial.println(resistorValue);
      Serial.print(F("faultValue = "));
      Serial.println(faultValue);
      Serial.print(F("nanoFarads = elapsedTime * 1000 / resistorValue - faultValue = "));
      Serial.println(nanoFarads);
    }

    // Stops charging capacitor
    pinMode(chargePin, INPUT);
    // Begins discharging the capacitor
    pinMode(dischargePin, OUTPUT);
    digitalWrite(dischargePin, LOW);

    // Нет емкости - показываем время
    if (!nanoFarads){
      if (debug){
        Serial.println(F("!nanoFarads"));
      }
      chargePin = charge1Pin;
      DateTime now = rtc.now();
      hour = now.hour() % 12;
      sprintf(buffer, "%d%s%02d", hour ? hour : 12, now.second() % 2 ? "." : "", now.minute());
    // Меньше 200 нанофарад
    }else if (nanoFarads < 200){
      if (debug){
        Serial.println(F("nanoFarads < 200"));
      }
      chargePin = charge3Pin;
      dtostrf(nanoFarads, 0, 1, buffer);
      byte str_len;
      for (str_len = 0; buffer[str_len]; str_len++);
      buffer[str_len] = '.';
      buffer[str_len + 1] = '\0';
    // Меньше 2 микрофарад
    }else if (nanoFarads < 2000){
      if (debug){
        Serial.println(F("nanoFarads < 2000"));
      }
      chargePin = charge3Pin;
      dtostrf(nanoFarads, 0, 0, buffer);
      byte str_len;
      for (str_len = 0; buffer[str_len]; str_len++);
      buffer[str_len] = '.';
      buffer[str_len + 1] = '\0';
    // Меньше 20 микрофарад
    }else if (nanoFarads / 1000.0 < 20){
      if (debug){
        Serial.println(F("nanoFarads / 1000 < 20"));
      }
      chargePin = charge3Pin;
      dtostrf(nanoFarads / 1000, 0, 2, buffer);
    // Меньше 200 микрофарад
    }else if (nanoFarads / 1000.0 < 200){
      if (debug){
        Serial.println(F("nanoFarads / 1000 < 200"));
      }
      chargePin = charge2Pin;
      dtostrf(nanoFarads / 1000, 0, 1, buffer);
    // Больше 200 микрофарад
    }else{
      if (debug){
        Serial.println(F("nanoFarads / 1000 > 200"));
      }
      chargePin = charge1Pin;
      dtostrf(nanoFarads / 1000, 0, 0, buffer);
    }

    if (debug){
      Serial.print(F("nanoFarads = "));
      Serial.println(nanoFarads);
      Serial.print(F("buffer = "));
      Serial.println(buffer);
    }

    show_str(buffer);
    mode = cap_discharge;
  }
  if (mode == cap_discharge && !analogRead(analogPin)){
    if (debug){
      Serial.print(F("mode = "));
      Serial.println(mode);
    }
    mode = wait;
    startWait = us;
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
    Serial.print(F("digs = "));
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
    Serial.print(F("str = "));
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
    Serial.print(F("str_len = "));
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
    // Запоминаем точку до следующего раза
    if (str[str_pos] == '.'){
      need_dot = true;
      continue;
    }
    if (debug){
      Serial.print(F("str["));
      Serial.print(str_pos);
      Serial.print(F("] = "));
      Serial.print(str[str_pos]);
      Serial.print(F(" ("));
      Serial.print(str[str_pos], DEC);
      Serial.print(F(") > "));
      Serial.println(show_pos);
    }
    // Если выводим цифру
    if (str[str_pos] >= '0' && str[str_pos] <= '9'){
      if (debug){
        Serial.println(F("Is number"));
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
  us = micros();
  if (us - us_show <= min_brightness - min_brightness / 256 * brightness){
    return;
  }
  us_show = us;
  // Обходим коды символов для вывода
  for (int8_t show_pos = 0; show_pos < digs; show_pos++){
    /*if (debug){
      Serial.print("str_code[");
      Serial.print(show_pos);
      Serial.print("] = ");
      Serial.println(str_code[show_pos], BIN);
    }*/
    // Если есть код символа для вывода (иначе пробел)
    if (!str_code[show_pos]){
      continue;
    }
    /*if (debug){
      Serial.print("digitalWrite(");
      Serial.print(dig_pinout[show_pos]);
      Serial.print(", ");
      Serial.print(dig_pinout_anode[show_pos]);
      Serial.println(");");
    }*/
    // Включаем вывод разряда (текущий разряд)
    digitalWrite(dig_pinout[show_pos], dig_pinout_anode[show_pos]);
    // Обходим сигменты разряда
    for (int8_t f = 7; f >= 0; f--){
      /*if (debug){
        Serial.print("digitalWrite(");
        Serial.print(pinout[7 - f]);
        Serial.print(", ");
        Serial.print(!(bitRead(str_code[show_pos], f) ^ pinout_anode[7 - f]));
        Serial.println(");");
      }*/
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
