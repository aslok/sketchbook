// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

byte LT[8] =
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{

  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{


  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{


  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte MB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte block[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
// loop counter
int count = 0;

void setup () {
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  #endif
  rtc.begin();
  DateTime now = rtc.now();

  lcd.begin(20, 4);                      // initialize the lcd
  lcd.home();
  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,MB);
  lcd.createChar(7,block);
  lcd.clear();
}


void custom0(int x)
{ // uses segments to build the number 0

  lcd.setCursor(x,1); // set cursor to column 0, line 0 (first row)
  lcd.write((byte) 0);  // call each segment to create
  lcd.write((byte) 1);  // top half of the number
  lcd.write((byte) 2);
  lcd.setCursor(x, 2); // set cursor to colum 0, line 1 (second row)
  lcd.write((byte) 3);  // call each segment to create
  lcd.write((byte) 4);  // bottom half of the number
  lcd.write((byte) 5);
}

void custom1(int x)
{
  lcd.setCursor(x,1);
  lcd.print(" ");
  lcd.write((byte) 0);
  lcd.print(" ");
  lcd.setCursor(x,2);
  lcd.print(" ");
  lcd.write((byte) 7);
  lcd.print(" ");
}

void custom2(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 1);
  lcd.write((byte) 6);
  lcd.write((byte) 2);
  lcd.setCursor(x, 2);
  lcd.write((byte) 3);
  lcd.write((byte) 4);
  lcd.write((byte) 4);
}

void custom3(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.write((byte) 2);
  lcd.setCursor(x, 2);
  lcd.write((byte) 4);
  lcd.write((byte) 4);
  lcd.write((byte) 5);
}

void custom4(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 3);
  lcd.write((byte) 4);
  lcd.write((byte) 7);
  lcd.setCursor(x, 2);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write((byte) 7);
}

void custom5(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 3);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.setCursor(x, 2);
  lcd.write((byte) 4);
  lcd.write((byte) 4);
  lcd.write((byte) 5);
}

void custom6(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 0);
  lcd.write((byte) 6);
  lcd.write((byte) 6);
  lcd.setCursor(x, 2);
  lcd.write((byte) 3);
  lcd.write((byte) 4);
  lcd.write((byte) 5);
}

void custom7(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 1);
  lcd.write((byte) 1);
  lcd.write((byte) 2);
  lcd.setCursor(x, 2);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write((byte) 7);
}

void custom8(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 0);
  lcd.write((byte) 6);
  lcd.write((byte) 2);
  lcd.setCursor(x, 2);
  lcd.write((byte) 3);
  lcd.write((byte) 4);
  lcd.write((byte) 5);
}

void custom9(int x)
{
  lcd.setCursor(x,1);
  lcd.write((byte) 0);
  lcd.write((byte) 6);
  lcd.write((byte) 2);
  lcd.setCursor(x, 2);
  lcd.write((byte) 4);
  lcd.write((byte) 4);
  lcd.write((byte) 5);

}


void loop () {
  DateTime now = rtc.now();
  printDigits(now.hour()/10,2);
  printDigits(now.hour()%10,6);

  printDigits(now.minute()/10,11);
  printDigits(now.minute()%10,15);

  delay(1000);
}

void printDigits(int digits, int x){
  // utility function for digital clock display: prints preceding colon and leading 0

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
