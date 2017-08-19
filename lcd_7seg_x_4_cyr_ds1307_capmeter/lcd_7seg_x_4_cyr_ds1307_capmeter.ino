/*
 * capmeter_lcd7x4_ds1307.ino
 * Capacitance meter with clock
 *
 * modified 17.09.2016
 * by Fust Vitaliy Vitaliy Fust <aslok.zp@gmail.com>
 * with Arduino 1.6.5 (tested on Arduino Pro Mini 168 5V)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
Sketch uses 13,576 bytes (94.7%) of program storage space. Maximum is 14,336 bytes.
Global variables use 522 bytes (51.0%) of dynamic memory, leaving 502 bytes for local variables. Maximum is 1,024 bytes.
 */

boolean debug = false;

#include "lcd7x4.h"
lcd7x4* lcd;

#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 rtc;

double vcc;

const byte analogPin = A7;
const byte charge1Pin = A0;
const byte charge2Pin = A1;
const byte charge3Pin = A2;
const byte dischargePin = A3;
byte chargePin = charge1Pin;

// Resistor 20k
const unsigned long resistor1Value = 22159;
// Resistor 50k
const unsigned long resistor2Value = 46600;
// Resistor 100k
const unsigned long resistor3Value = 101700;
// Current resistor value
unsigned long resistorValue;

// No cap value
const float fault1Value = 12.72;
const float fault2Value = 5.92;
const float fault3Value = 2.49;
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

enum result_type {
  na,
  cap,
  res
};

mode_type mode = wait;
result_type result_type = na;

// For sprintf() function
char buffer[7];

byte brightness = 240;     // 0 - 255

const byte    pinout[]           = {8,     9,     4,     6,     5,     7,     3,     2};
const boolean pinout_anode[]     = {true,  true,  true,  true,  true,  true,  true,  true};
const byte    dig_pinout[]       = {10,    11,    12,    13,    0};
const boolean dig_pinout_anode[] = {true,  true,  true,  true};

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

  lcd = new lcd7x4(pinout, dig_pinout, pinout_anode, dig_pinout_anode, brightness);
}

void loop(){
  if (debug){
    Serial.print(F("start loop, mode = "));
    Serial.println(mode);
    Serial.print(F("analogRead(analogPin) = "));
    Serial.println(analogRead(analogPin));
  }
  unsigned long us = micros();
  if (mode == wait && us - startWait > 1000000){
    if (debug){
      Serial.print(F("mode = "));
      Serial.println(mode);
      vcc = readVcc();
      Serial.print(F("vcc = "));
      Serial.println(vcc);
    }
    result_type = na;
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
    while (analogRead(analogPin) < 648 && micros() - startTime < 2500000){
      lcd->update();
      if (debug){
        Serial.print("analogRead(analogPin) = ");
        Serial.println(analogRead(analogPin));
      }
    }
    elapsedTime = micros() - startTime;
    int analogPinVal = analogRead(analogPin);

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
    if (analogPinVal < 640 || analogPinVal > 650){
      nanoFarads = (float) analogPinVal / (1023 - analogPinVal) * resistorValue;
      result_type = res;
    }else{
      nanoFarads = (float) elapsedTime * 1000 / resistorValue - faultValue;
      result_type = cap;
    }
    if (nanoFarads < 1){
      nanoFarads = 0;
    }

    if (debug){
      Serial.print(F("analogPinVal = "));
      Serial.println(analogPinVal);
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
    if (nanoFarads == INFINITY || nanoFarads / 1000.0 > 20000){
      // Бесконечность
      if (debug){
        Serial.println(F("nanoFarads == INFINITY"));
      }
      nanoFarads = 0;
    }
    if (!nanoFarads){
      if (debug){
        Serial.println(F("!nanoFarads"));
      }
      if (result_type == cap){
        chargePin = charge1Pin;
      }else{
        chargePin = charge1Pin;
      }
      DateTime now = rtc.now();
      byte hour;
      hour = now.hour() % 12;
      sprintf(buffer, "%d%s%02d", hour ? hour : 12, now.second() % 2 ? "." : "", now.minute());
    // Меньше 200 нанофарад
    }else if (nanoFarads < 200){
      if (debug){
        Serial.println(F("nanoFarads < 200"));
      }
      if (result_type == cap){
        chargePin = charge3Pin;
      }else{
        chargePin = charge1Pin;
      }
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
      if (result_type == cap){
        chargePin = charge3Pin;
      }else{
        chargePin = charge1Pin;
      }
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
      if (result_type == cap){
        chargePin = charge3Pin;
      }else{
        chargePin = charge1Pin;
      }
      dtostrf(nanoFarads / 1000, 0, 2, buffer);
    // Меньше 200 микрофарад
    }else if (nanoFarads / 1000.0 < 200){
      if (debug){
        Serial.println(F("nanoFarads / 1000 < 200"));
      }
      if (result_type == cap){
        chargePin = charge2Pin;
      }else{
        chargePin = charge1Pin;
      }
      dtostrf(nanoFarads / 1000, 0, 1, buffer);
    // Больше 200 микрофарад
    }else{
      if (debug){
        Serial.println(F("nanoFarads / 1000 > 200"));
      }
      if (result_type == cap){
        chargePin = charge1Pin;
      }else{
        chargePin = charge1Pin;
      }
      dtostrf(nanoFarads / 1000, 0, 0, buffer);
    }

    if (debug){
      Serial.print(F("nanoFarads = "));
      Serial.println(nanoFarads);
      Serial.print(F("buffer = "));
      Serial.println(buffer);
    }

    lcd->print(buffer);
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
  lcd->update();
}

double readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif

  delay(75);

  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  /* измерив Vcc с помощью вольтметра и нашей функции readVcc().
   * Далее заменяем константу 1125.3 новой переменной:
   * scale_constant = internal1.1Ref * 1023 * 1000
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   * internal1.1Ref = 1.1 * 5390 / 5460 = 1,085897436
   * scale_constant = internal1.1Ref * 1023 = 1110.873077
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
  return 1110.873077 / result; // Vcc in volts
}
