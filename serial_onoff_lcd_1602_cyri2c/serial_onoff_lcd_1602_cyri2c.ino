const int ledPin = 13;

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

void setup(){
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
}

void loop(){
  if (Serial.available() > 0){
    int inByte = Serial.read();

    Serial.println(inByte);
    lcd->print(inByte);
    lcd->print(' ');

    switch (inByte){
      // echo -n 0 > /dev/ttyUSB4
      case 250:
        digitalWrite(ledPin, LOW);
        Serial.println("OFF");
        break;
      // echo -n 1 > /dev/ttyUSB4
      case 253:
        digitalWrite(ledPin, HIGH);
        Serial.println("ON!");
        break;
      // echo -n 2 > /dev/ttyUSB4
      //case 250:
      //  break;
      // echo -n 3 > /dev/ttyUSB4
      //case 253:
      //  break;
      // echo -n 4 > /dev/ttyUSB4
      case 251:
        break;
      // echo -n 5 > /dev/ttyUSB4
      case 255:
        break;
      // echo -n 6 > /dev/ttyUSB4
      //case 251:
      //  break;
      // echo -n 7 > /dev/ttyUSB4
      //case 255:
      //  break;
      // echo -n 8 > /dev/ttyUSB4
      //case 250:
      //  break;
      // echo -n 9 > /dev/ttyUSB4
      //case 253:
      //  break;
      // echo -n 10 > /dev/ttyUSB4
      case 165:
        break;
      // echo -n 11 > /dev/ttyUSB4
      case 173:
        break;
      // echo -n 12 > /dev/ttyUSB4
      //case 165:
      //  break;
      // echo -n 13 > /dev/ttyUSB4
      //case 173:
      //  break;
      // echo -n 14 > /dev/ttyUSB4
      case 181:
        break;
      // echo -n 15 > /dev/ttyUSB4
      case 189:
        break;
      // echo -n 16 > /dev/ttyUSB4
      //case 181:
      //  break;
      // echo -n 17 > /dev/ttyUSB4
      //case 189:
      //  break;
      // echo -n 18 > /dev/ttyUSB4
      //case 165:
      //  break;
      // echo -n 19 > /dev/ttyUSB4
      //case 173:
      //  break;
      // echo -n 20 > /dev/ttyUSB4
      case 74:
        break;
      // echo -n 21 > /dev/ttyUSB4
      case 90:
        break;
      // echo -n 22 > /dev/ttyUSB4
      //case 74:
      //  break;
      // echo -n 23 > /dev/ttyUSB4
      //case 90:
      //  break;
      // echo -n 24 > /dev/ttyUSB4
      case 106:
        break;
    }
  }
}
