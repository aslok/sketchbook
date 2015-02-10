#include "Keypad.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"

const byte numRows = 5;
const byte numCols = 4;
char keymap[numRows][numCols] = {
  {'+', '-', '#', '*'},
  {'1', '2', '3', 'W'},
  {'4', '5', '6', 'S'},
  {'7', '8', '9', 'B'},
  {'A', '0', 'D', 'E'}
};
byte rowPins[numRows] = {4, 5, 6, 7, 8};
byte colPins[numCols] = {12, 11, 10, 9};
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
CyrI2c* lcd;

void setup() {
  Serial.begin(9600);
  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("Arduino Nano        Ардуино Нано"));
  lcd->printn(0);
}

void loop() {
  char keypressed;
  switch (keypressed = myKeypad.getKey()) {
    case '*':
      lcd->backlight();
      break;
    case 'B':
      lcd->clear();
      break;
    case 'E':
      lcd->print('\n');
      break;
    case 'S':
      lcd->print('\n');
    case 'W':
      lcd->printn(0, 0);
      break;
    case NO_KEY:
      break;
    default:
      lcd->print(keypressed);
  }
}

