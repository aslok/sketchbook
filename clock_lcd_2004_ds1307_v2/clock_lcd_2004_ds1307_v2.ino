// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

// include the library code:
#include "LiquidCrystal.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

byte MM[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte TL[8] = {
  B00001,
  B00011,
  B00011,
  B00111,
  B00111,
  B01111,
  B01111,
  B11111
};
byte TR[8] = {
  B10000,
  B11000,
  B11000,
  B11100,
  B11100,
  B11110,
  B11110,
  B11111
};
byte BL[8] = {
  B11111,
  B01111,
  B01111,
  B00111,
  B00111,
  B00011,
  B00011,
  B00001
};
byte BR[8] = {
  B11111,
  B11110,
  B11110,
  B11100,
  B11100,
  B11000,
  B11000,
  B10000
};
byte TM[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte BM[8] = {
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte HM[8] = {
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
};

void setup () {
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin();
  #endif
  rtc.begin();

  lcd.begin(20, 4);
  lcd.home();
  lcd.createChar(0, MM);
  lcd.createChar(1, TL);
  lcd.createChar(2, TR);
  lcd.createChar(3, BL);
  lcd.createChar(4, BR);
  lcd.createChar(5, TM);
  lcd.createChar(6, BM);
  lcd.createChar(7, HM);
  lcd.clear();
}


void custom0(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write((byte) 0);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);

  lcd.setCursor(x, 2);
  lcd.write((byte) 0);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);

  lcd.setCursor(x, 3);
  lcd.write((byte) 3);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom1(int x){
  lcd.setCursor(x, 0);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 1);
  lcd.write(' ');

  lcd.setCursor(x, 1);
  lcd.write(' ');
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write(' ');

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);
  lcd.write(' ');

  lcd.setCursor(x, 3);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);
  lcd.write(' ');
}


void custom2(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 1);
  lcd.write((byte) 4);

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write((byte) 1);
  lcd.write((byte) 4);
  lcd.write(' ');

  lcd.setCursor(x, 3);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
}


void custom3(int x){
  lcd.setCursor(x, 0);
  lcd.write(' ');
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write(' ');
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write((byte) 0);

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 0);

  lcd.setCursor(x, 3);
  lcd.write(' ');
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom4(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 0);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);

  lcd.setCursor(x, 1);
  lcd.write((byte) 0);
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write((byte) 0);

  lcd.setCursor(x, 2);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 0);

  lcd.setCursor(x, 3);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);
}


void custom5(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);

  lcd.setCursor(x, 1);
  lcd.write((byte) 3);
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write(' ');

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 2);

  lcd.setCursor(x, 3);
  lcd.write((byte) 3);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom6(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write((byte) 0);
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write(' ');

  lcd.setCursor(x, 2);
  lcd.write((byte) 0);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 2);

  lcd.setCursor(x, 3);
  lcd.write((byte) 3);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom7(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);

  lcd.setCursor(x, 3);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write(' ');
  lcd.write((byte) 0);
}


void custom8(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write((byte) 3);
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write((byte) 4);

  lcd.setCursor(x, 2);
  lcd.write((byte) 1);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 2);

  lcd.setCursor(x, 3);
  lcd.write((byte) 3);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom9(int x){
  lcd.setCursor(x, 0);
  lcd.write((byte) 1);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 2);

  lcd.setCursor(x, 1);
  lcd.write((byte) 0);
  lcd.write((byte) 5);
  lcd.write((byte) 5);
  lcd.write((byte) 0);

  lcd.setCursor(x, 2);
  lcd.write(' ');
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 0);

  lcd.setCursor(x, 3);
  lcd.write((byte) 3);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 4);
}


void custom_column(int x, boolean del = false){
  char num = del ? (byte) 7 : ' ';

  lcd.setCursor(x + 1, 1);
  lcd.write(num);

  lcd.setCursor(x + 1, 3);
  lcd.write(num);
}


void loop () {
  DateTime now = rtc.now();
  printDigits(now.hour()/10,0);
  printDigits(now.hour()%10,4);

  printDigits(now.minute()/10,12);
  printDigits(now.minute()%10,16);

  custom_column(8, now.second() & 1);

  delay(1000);
}

void printDigits(int digits, int x){
  switch (digits) {
  case 0:
    custom0(x);
    break;
  case 1:
    custom1(x);
    break;
  case 2:
    custom2(x);
    break;
  case 3:
    custom3(x);
    break;
  case 4:
    custom4(x);
    break;
  case 5:
    custom5(x);
    break;
  case 6:
    custom6(x);
    break;
  case 7:
    custom7(x);
    break;
  case 8:
    custom8(x);
    break;
  case 9:
    custom9(x);
    break;

  }
}
