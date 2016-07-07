// Флаг для отладки через порт
const boolean debug = true;

const byte left[5] = {
  9, 8, 7, 6, 5
};
const byte right[7] = {
  10, 11, 12, 13, A1, A2, A3
};
const byte left_top[1] = {
  5
};
const byte left_bottom[4] = {
  9, 8, 7, 6
};
const byte right_top[3] = {
  A1, A2, A3
};
const byte right_bottom[4] = {
  10, 11, 12, 13
};

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;


#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;

#define ALTITUDE 0.0

void setup() {
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  if (debug) {
    Serial.begin(57600);
  }

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc.begin();

  pressure.begin();
}

void loop() {
  DateTime now = rtc.now();

  randomSeed(now.unixtime());

  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);  
  Serial.println();

  byte hour = now.hour();
  if (hour > 12){
    hour %= 12;
  }else if (!hour){
    hour = 12;
  }
  byte min = now.minute();

  show_left(hour);
  show_right(min);

  delay(5000);

  byte month = now.month();
  byte day = now.day();

  show_left(month);
  show_right(day);

  delay(5000);

  char status;
  double T, P;
  
  status = pressure.startTemperature();
  if (status != 0){
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0){
      T -= 3.5;
      Serial.print("temperature: ");
      Serial.print(T, 2);
      Serial.println(" deg C");

      byte temp = T;
      show_left_one(temp);

      status = pressure.startPressure(3);
      if (status != 0){
        delay(status);
        status = pressure.getPressure(P, T);
        P -= 235;
        if (status != 0){

          Serial.print("absolute pressure: ");
          Serial.print(P, 2);
          Serial.println(" mb");

          byte pres = P - 700;
          show_right_one(pres);
        }
      }
    }
  }

  delay(5000);

  show_snow();

  show_wizard();
}

void show_snow(){
  for (byte f = 0, k = 0, j = -3; f < 25; f++){
    for (byte f2 = 0; f2 < 7; f2++){
      if (f2 < 5){
        digitalWrite(left[f2], LOW);
      }
      digitalWrite(right[f2], LOW);
    }
    if (k < 5){
      digitalWrite(left[k], HIGH);
    }
    digitalWrite(right[k], HIGH);
    if (k < 6){
      k++;
    }else{
      k = 0;
    }
    /*if (j >= 0){
      if (j < 5){
        digitalWrite(left[j], HIGH);
      }
      digitalWrite(right[j], HIGH);
    }
    if (j < 6 || j > 252){
      j++;
    }else{
      j = 0;
    }*/
    delay(250);
  }
}

void show_wizard(){
  const byte points = 4;
  byte on[points];
  for (byte f = 0; f < 50; f++){
    for (byte f2 = 0; f2 < 7; f2++){
      if (f2 < 5){
        digitalWrite(left[f2], LOW);
      }
      digitalWrite(right[f2], LOW);
      on[f2] = 127;
    }
    for (byte f2 = 0; f2 < points; f2++){
      byte exists;
      byte next;
      do{
        exists = false;
        next = random(0, 12);
        Serial.print("random = ");
        Serial.println(next);
        for (byte f3 = 0; f3 < points; f3++){
          if (on[f3] == 127){
            break;
          }
          if (on[f3] != next){
            continue;
          }
          exists = true;
          break;
        }
        Serial.print("exists = ");
        Serial.println(exists);
      }while (exists);
      on[f2] = next;
      Serial.print("next = ");
      Serial.println(next);
      digitalWrite(next > 4 ? right[next - 5] : left[next], HIGH);
    }
    delay(50);
  }
}

void show_left_one(byte digit){
  Serial.print("LEFT ONE - ");
  Serial.print(digit, DEC);
  Serial.println();
  for (byte f = 0; f < 5; f++){
    Serial.print(bitRead(digit, f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(left[f], bitRead(digit, f) ? HIGH : LOW);
  }
}

void show_right_one(byte digit){
  Serial.print("RIGHT ONE - ");
  Serial.print(digit, DEC);
  Serial.println();
  for (byte f = 0; f < 7; f++){
    Serial.print(bitRead(digit, f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(right[f], bitRead(digit, f) ? HIGH : LOW);
  }
}

void show_left(byte digit){
  Serial.print("LEFT - ");
  Serial.print(digit, DEC);
  Serial.println();
  int digits[2];
  int digits_count = factor_digits(digit, digits, 2);
  if (digits_count < 2){
    digits[1] = 0;
  }
  for (byte f = 0; f < 4; f++){
    Serial.print(bitRead(digits[0], f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(left_bottom[f], bitRead(digits[0], f) ? HIGH : LOW);
  }
  for (byte f = 0; f < 1; f++){
    Serial.print(bitRead(digits[1], f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(left_top[f], bitRead(digits[1], f) ? HIGH : LOW);
  }
}

void show_right(byte digit){
  Serial.print("RIGHT - ");
  Serial.print(digit, DEC);
  Serial.println();
  int digits[2];
  int digits_count = factor_digits(digit, digits, 2);
  if (digits_count < 2){
    digits[1] = 0;
  }
  for (byte f = 0; f < 4; f++){
    Serial.print(bitRead(digits[0], f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(right_bottom[f], bitRead(digits[0], f) ? HIGH : LOW);
  }
  for (byte f = 0; f < 3; f++){
    Serial.print(bitRead(digits[1], f) ? 1 : 0, DEC);
    Serial.println();
    digitalWrite(right_top[f], bitRead(digits[1], f) ? HIGH : LOW);
  }
}

int factor_digits(int num, int *digits, int limit){
  int digits_count = 0;
  if (num == 0) {
    digits[0] = 0;
    return 1;
  }
  while (num > 0 && limit) {
    digits[digits_count++] = num % 10;
    num /= 10;
    limit--;
  }
  return num ? 0 : digits_count;
}
