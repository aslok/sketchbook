boolean debug = false;

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"
CyrI2c* lcd;

int analogPin = 0;
int chargePin = 12;
int dischargePin = 11;

// Resistor 100k
unsigned long resistorValue = 101700;

float faultValue = 1.2;

unsigned long startTime;
unsigned long elapsedTime;

float nanoFarads;

// For dtostrf() round function
char buffer[9];

void setup()
{
  //debug = true;

  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  

  lcd = new CyrI2c(0x27, 16, 2);
  lcd->backlight();
  lcd->init(F("мк\rп\rк\r? фарад\rЕмкость кондера\r           "));
  lcd->clear();
  lcd->printn(4, 0, 0);
  lcd->printn(3, -1, 1);     

  if (debug){
    Serial.begin(57600);
  }
}

void loop()
{
  digitalWrite(chargePin, HIGH); // Begins charging the capacitor
  startTime = micros();
  
  while(analogRead(analogPin) < 648); // 63.2% of total voltage

  elapsedTime = micros() - startTime;
  nanoFarads = (float) elapsedTime * 1000 / resistorValue - faultValue;
  if (nanoFarads < 1){
    nanoFarads = 0;
  }

  if (debug){
    Serial.print("elapsedTime = ");
    Serial.println(elapsedTime);
    Serial.print("resistorValue = ");
    Serial.println(resistorValue);
    Serial.print("faultValue = ");
    Serial.println(faultValue);
    Serial.print("nanoFarads = elapsedTime * 1000 / resistorValue - faultValue = ");
    Serial.println(nanoFarads);
  }

  lcd->printn(5, 0, 1);
  if (nanoFarads > 1000){
    lcd->print((int) (nanoFarads / 1000), -9, 1);
    lcd->printn(0, -6, 1);       
  }else{
    dtostrf(nanoFarads, 0, 1, buffer);
    lcd->print(buffer, -9, 1);
    lcd->printn(2, -8, 1);
    lcd->printn(1, -6, 1);   
  }

  delay(500); 

  digitalWrite(chargePin, LOW); // Stops charging capacitor
  pinMode(dischargePin, OUTPUT); 
  digitalWrite(dischargePin, LOW);    
  while(analogRead(analogPin) > 0);

  pinMode(dischargePin, INPUT); // Prevents capacitor from discharging  
}
