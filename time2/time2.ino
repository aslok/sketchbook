/*
 Time v2
 Time and date on lcd display (used rtc timer) with control by keypad 4x4

 Hardware:
 Trickle-Charge Timekeeping Chip DS1302
 http://www.maximintegrated.com/en/products/digital/real-time-clocks/DS1302.html
 http://playground.arduino.cc/Main/DS1302RTC
 LCD I2C PCF8574
 http://habrahabr.ru/post/219137/
 http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514
 Keypad 4x4

 created 18.01.2015
 modifid 24.01.2015
 by Fust Vitaliy
 with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 14 592 bytes (45%) of program storage space. Maximum is 32 256 bytes.
Global variables use 422 bytes (20%) of dynamic memory, leaving 1 626 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <CyrI2c.h>
CyrI2c* lcd;


#include <Keypad.h>
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {5, 4, 3, 2}; //Rows 0 to 3
byte colPins[numCols] = {9, 8, 7, 6}; //Columns 0 to 3
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


#include <Time.h>
#include <DS1302RTC.h>
// Set pins:  CE, IO,CLK
DS1302RTC RTC(12, 11, 10);

const uint8_t pin = 13;

void setup() {
  pinMode(pin, OUTPUT);

  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();

  tmElements_t tm;
  RTC.read(tm);
  hello(tm.Hour);
}

void loop() {
  tmElements_t tm;
  RTC.read(tm);

  lcd->init(F("Нд\rПн\rВт\rСр\rЧт\rПт\rСб"));
  lcd->printn(tm.Wday - 1, -1, 0);
  lcd->init(F("січня\rлютого\rберезня\rквітня\rтравня\rчервня\rлипня\rсерпня\rвересня\rжовтня\rлистопада\rгрудня"));
  lcd->printn(tm.Month - 1, 3, 0);

  char buffer[9];
  buffer[8] = 0;
  sprintf(buffer, "%02d", tm.Day);
  lcd->print(buffer, 0, 0);
  sprintf(buffer, "%02d:%02d:%02d", tm.Hour, tm.Minute, tm.Second);
  lcd->print(buffer, 4, 1);

  unsigned long prevtime = RTC.get();
  while(prevtime == RTC.get()){
    char keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY){
      digitalWrite(pin, HIGH);
      switch (keypressed) {
        case 'A':
          hello(tm.Hour);
          break;
        default:
          delay(200);
      }
      digitalWrite(pin, LOW);
    }
  }
}

void hello(uint8_t hour){
  lcd->clear();
  lcd->init(F("Доброї ночі!\rДоброго ранку!\rДоброго дня!\rДоброго вечора!\rЯ годинник :)"));  
  lcd->printn((hour + 1) / 6, 0, 0);
  lcd->printn(4, 3, 1);  
  delay(2000);
  lcd->clear();
}

