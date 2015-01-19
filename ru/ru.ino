/*
Ru
Test russification of lcd display connected by i2c

Hardware:
LCD I2C PCF8574
http://habrahabr.ru/post/219137/
http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

created 19.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 3 508 bytes (10%) of program storage space. Maximum is 32 256 bytes.
Global variables use 309 bytes (15%) of dynamic memory, leaving 1 739 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t ru[8][8] =
{
  { 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 }, // Б
  { 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 }, // Г
  { 0xe, 0xa, 0xa, 0xa, 0x1f,0x11,0x11,0x0 }, // Д
  { 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 }, // Ы
  { 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 }, // Ю
  { 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 }, // Я
  { 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 }, // Ж
  { 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 }, // П
};

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // initialize the lcd 
  lcd.init();
  lcd.backlight();

  // Creating missing chars  
  for (int char_num = 0; char_num < 8; char_num++){
    lcd.createChar(char_num, ru[char_num]);
  }
  lcd.home();
  lcd.clear();

  lcd.printByte('A');
  lcd.printByte(0);
  lcd.printByte('B');
  lcd.printByte(1);
  lcd.printByte(2);
  lcd.printByte('E');
  lcd.printByte(6);
  lcd.printByte('3');
  lcd.printByte('U');
  lcd.printByte('K');
  lcd.printByte(202);
  lcd.printByte('M');
  lcd.printByte('H');
  lcd.printByte('O');
  lcd.printByte(7);
  lcd.printByte('P');
  
  lcd.setCursor(0, 1);
  
  lcd.printByte('C');
  lcd.printByte('T');
  lcd.printByte(191);
  lcd.printByte(236);
  lcd.printByte('X');
  lcd.printByte(209);
  lcd.printByte(249);
  lcd.printByte('W');
  lcd.printByte('b');
  lcd.printByte(3);
  lcd.printByte(214);
  lcd.printByte(4);
  lcd.printByte(5);
}

void loop()
{

}

