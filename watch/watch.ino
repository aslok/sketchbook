// Флаг для отладки через порт
boolean debug = false;

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

const byte button_1_pin = A6;
const byte button_2_pin = A7;

boolean b1 = false;
boolean b2 = false;
boolean b3 = false;
boolean button1 = false;
boolean button2 = false;
boolean button3 = false;
boolean cmd_mode_1 = false;
boolean cmd_mode_2 = false;
boolean cmd_mode_3 = false;
unsigned long cmd_start_1 = 0;
unsigned long cmd_start_2 = 0;
unsigned long cmd_start_3 = 0;

unsigned long ms;
unsigned long ms_prev;

byte month;
byte day;
byte hour;

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  debug = true;

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

  pinMode(button_1_pin, INPUT_PULLUP);
  pinMode(button_2_pin, INPUT_PULLUP);

  if (debug) {
    Serial.begin(57600);
  }

#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc.begin();

  ms_prev = 0;
}

void loop() {
  ms = millis();

  read_buttons();

  if (ms - ms_prev < 1000 && !button1 && !button2 && !button3){
    return;
  }

  ms_prev = ms;

  DateTime now = rtc.now();
  if (debug) {
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
  }

  if (button1) {
    show_snow();
  }else if (button2) {
    randomSeed(now.unixtime());
    show_wizard();
  }else if (button3) {
    month = now.month();
    day = now.day();

    show_left(month);
    show_right(day);
  }else{
    hour = now.hour();
    if (hour > 12){
      hour %= 12;
    }else if (!hour){
      hour = 12;
    }
    byte min = now.minute();

    show_left(hour);
    show_right(min);
  }
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
        if (debug) {
          Serial.print("random = ");
          Serial.println(next);
        }
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
        if (debug) {
          Serial.print("exists = ");
          Serial.println(exists);
        }
      }while (exists);
      on[f2] = next;
      if (debug) {
        Serial.print("next = ");
        Serial.println(next);
        Serial.print("next > 4 ? right[next - 5] : left[next] = ");
        Serial.println(next > 4 ? right[next - 5] : left[next]);
      }
      digitalWrite(next > 4 ? right[next - 5] : left[next], HIGH);
    }
    delay(50);
  }
}

void show_left_one(byte digit){
  if (debug) {
    Serial.print("LEFT ONE - ");
    Serial.print(digit, DEC);
    Serial.println();
  }
  for (byte f = 0; f < 5; f++){
    if (debug) {
      Serial.print(bitRead(digit, f) ? 1 : 0, DEC);
      Serial.println();
    }
    digitalWrite(left[f], bitRead(digit, f) ? HIGH : LOW);
  }
}

void show_right_one(byte digit){
  if (debug) {
    Serial.print("RIGHT ONE - ");
    Serial.print(digit, DEC);
    Serial.println();
  }
  for (byte f = 0; f < 7; f++){
    if (debug) {
      Serial.print(bitRead(digit, f) ? 1 : 0, DEC);
      Serial.println();
    }
    digitalWrite(right[f], bitRead(digit, f) ? HIGH : LOW);
  }
}

void show_left(byte digit){
  if (debug) {
    Serial.print("LEFT - ");
    Serial.print(digit, DEC);
    Serial.println();
  }
  int digits[2];
  int digits_count = factor_digits(digit, digits, 2);
  if (digits_count < 2){
    digits[1] = 0;
  }
  for (byte f = 0; f < 4; f++){
    if (debug) {
      Serial.print(bitRead(digits[0], f) ? 1 : 0, DEC);
      Serial.println();
    }
    digitalWrite(left_bottom[f], bitRead(digits[0], f) ? HIGH : LOW);
  }
  for (byte f = 0; f < 1; f++){
    if (debug) {
      Serial.print(bitRead(digits[1], f) ? 1 : 0, DEC);
      Serial.println();
    }
    digitalWrite(left_top[f], bitRead(digits[1], f) ? HIGH : LOW);
  }
}

void show_right(byte digit){
  if (debug) {
    Serial.print("RIGHT - ");
    Serial.print(digit, DEC);
    Serial.println();
  }
  int digits[2];
  int digits_count = factor_digits(digit, digits, 2);
  if (digits_count < 2){
    digits[1] = 0;
  }
  for (byte f = 0; f < 4; f++){
    if (debug) {
      Serial.print(bitRead(digits[0], f) ? 1 : 0, DEC);
      Serial.println();
    }
    digitalWrite(right_bottom[f], bitRead(digits[0], f) ? HIGH : LOW);
  }
  for (byte f = 0; f < 3; f++){
    if (debug) {
      Serial.print(bitRead(digits[1], f) ? 1 : 0, DEC);
      Serial.println();
    }
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


void read_buttons(){
  b1 = !analogRead(button_1_pin);
  b2 = !analogRead(button_2_pin);
  b3 = analogRead(button_1_pin) > 100 && analogRead(button_1_pin) < 150;
  button1 = false;
  button2 = false;
  button3 = false;

  if (debug) {
    Serial.print("button #3 = ");
    Serial.println(analogRead(button_1_pin));
  }

  if (!b1){
    cmd_mode_1 = true;
  }
  if (!b2){
    cmd_mode_2 = true;
  }
  if (!b3){
    cmd_mode_3 = true;
  }

  if (cmd_mode_1 && b1){
    cmd_mode_1 = false;
    cmd_start_1 = ms;
  }
  if (cmd_mode_2 && b2){
    cmd_mode_2 = false;
    cmd_start_2 = ms;
  }
  if (cmd_mode_3 && b3){
    cmd_mode_3 = false;
    cmd_start_3 = ms;
  }

  if (cmd_mode_1 && cmd_start_1 && ms - cmd_start_1 <= 50){
    cmd_start_1 = 0;
  } 
  if (cmd_mode_2 && cmd_start_2 && ms - cmd_start_2 <= 50){
    cmd_start_2 = 0;
  }
  if (cmd_mode_3 && cmd_start_3 && ms - cmd_start_3 <= 50){
    cmd_start_3 = 0;
  }

  if (!cmd_mode_1 && cmd_start_1 && (int) (ms - cmd_start_1) > 50 && b1){
    cmd_start_1 = cmd_start_1 + 250;
    button1 = true;
  }
  if (!cmd_mode_2 && cmd_start_2 && (int) (ms - cmd_start_2) > 50 && b2){
    cmd_start_2 = cmd_start_2 + 250;
    button2 = true;
  }
  if (!cmd_mode_3 && cmd_start_3 && (int) (ms - cmd_start_3) > 50 && b3){
    cmd_start_3 = cmd_start_3 + 250;
    button3 = true;
  }
}
