/*
 * dimmer.ino
 * Диммер на ардуино
 * Регулятор мощности — электронное устройство, предназначенное для
 * изменения электрической мощности
 * 220V, 300W
 *
 * created 20.08.2016
 * modifid 07.06.2017
 * with Arduino 1.6.5 (tested on Arduino Pro Mini ATmega168)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

boolean debug = false;
boolean debug_blink = false;

#include "EEPROM.h"
#include "TimerOne.h"

volatile unsigned long us;
unsigned long eeprom_us = 0;

const byte button_1_pin = A1;
const byte button_2_pin = A0;
const byte buttons_low_pin = 10;

const byte cros_zero_low_pin = 8;
const byte cros_zero_high_pin = 7;
const byte cros_zero_pin = 2;
volatile unsigned long cros_zero_us = 0;
volatile boolean interrupt_signal_skip;
int period = 0;

boolean b1 = false;
boolean b2 = false;
boolean button1 = false;
boolean button2 = false;
boolean cmd_mode_1 = false;
boolean cmd_mode_2 = false;
unsigned long cmd_start_1 = 0;
unsigned long cmd_start_2 = 0;

const byte signal_pin = 9;

const byte m = 11;
const byte r = 3;
const byte g = 5;
const byte b = 6;
const byte m_val = 15;

const byte steps[][3] = {
  // выкл       пурпурный
  {0, 0, 0}, {255, 0, 255},
  // фиолет         синий
  {244, 0, 192}, {0, 0, 255},
  // голубой        зеленый
  {0, 191, 255}, {0, 255, 0},
  // желтый         оранжевый
  {255, 200, 0}, {255, 83, 0},
  // красный
  {255, 0, 0}
};

byte step = 0;
byte step_prev = 7;
byte step_part = 0;
byte step_part_prev = 2;

boolean blink = false;
unsigned long blink_us = 0;
boolean blink_prev = false;

byte signal = 0;
int signal_prev = -1;

void setup(){
  //debug = true;
  //debug_blink = true;
  if (debug){
    Serial.begin(57600);
  }

  Timer1.initialize();
  interrupt_signal_skip = true;
  Timer1.attachInterrupt(interrupt_signal_stop);
  Timer1.stop();

  pinMode(button_1_pin, INPUT_PULLUP);
  pinMode(button_2_pin, INPUT_PULLUP);
  digitalWrite(buttons_low_pin, LOW);
  pinMode(buttons_low_pin, OUTPUT);

  digitalWrite(cros_zero_low_pin, LOW);
  pinMode(cros_zero_low_pin, OUTPUT);
  digitalWrite(cros_zero_high_pin, HIGH);
  pinMode(cros_zero_high_pin, OUTPUT);
  pinMode(cros_zero_pin, INPUT);
  attachInterrupt(0, interrupt_cros_zero, RISING);

  digitalWrite(signal_pin, LOW);
  pinMode(signal_pin, OUTPUT);
  // set timer 0 (Pins 5 and 6, millis, micros, delay) divisor to 1 for PWM frequency of 62500.00 Hz
  //TCCR0B = (TCCR0B & B11111000) | B00000001;
  // set timer 1 (Pins 9 and 10) divisor to 1 for PWM frequency of 31372.55 Hz
  //TCCR1B = (TCCR1B & B11111000) | B00000001;
  // set timer 2 (Pins 11 and 3) divisor to 1 for PWM frequency of 31372.55 Hz
  TCCR2B = (TCCR2B & B11111000) | B00000001;

  analogWrite(m, 255 - m_val);
  digitalWrite(r, LOW);
  pinMode(r, OUTPUT);
  digitalWrite(g, LOW);
  pinMode(g, OUTPUT);
  digitalWrite(b, LOW);
  pinMode(b, OUTPUT);

  step = EEPROM.read(0);
  step_prev = step - 1;
  step_part = EEPROM.read(1);
  step_part_prev = step_part - 1;
}

void loop(){
  us = micros();

  if (us < blink_us || us < cros_zero_us){
    blink_us = 0;
    cros_zero_us = 0;
  }

  read_buttons();

  if (button1 && (step < 8 || step_part < 2)){
    if (step_part > 1 || step == 0){
      step_part = 0;
      step++;
    }else{
      step_part++;
    }
    blink = true;
    blink_us = us;
  }else if (button2 && step > 0){
    if (step_part == 0){
      step--;
      if (step > 0){
        step_part = 2;
      }
    }else{
      step_part--;
    }
    blink = true;
    blink_us = us;
  }

  switch (step_part){
    case 0:
      if (step > 0 && blink != true){
        blink = true;
        blink_us = us;
      }
      break;
    case 1:
      if (us - blink_us > 500000){
        blink = !blink;
        blink_us = us;
      }
      break;
    case 2:
      if (us - blink_us > 250000){
        blink = !blink;
        blink_us = us;
      }
      break;
  }

  if (eeprom_us && us - eeprom_us > 5000000){
    if (debug){
      Serial.print("EEPROM.write = ");
      Serial.println(us, DEC);
    }
    eeprom_us = 0;
    EEPROM.write(0, step);
    EEPROM.write(1, step_part);
  }

  if (step == step_prev && step_part == step_part_prev && blink == blink_prev){
    return;
  }
  if (step_prev != step || step_part != step_part_prev){
    step_prev = step;
    step_part_prev = step_part;
    eeprom_us = us;
    if (debug){
      Serial.print("eeprom_us = ");
      Serial.println(eeprom_us, DEC);
    }
  }
  if (debug && debug_blink){
    Serial.print("step = ");
    Serial.println(step, DEC);
    Serial.print("step_part = ");
    Serial.println(step_part, DEC);
  }
  blink_prev = blink;
  if (blink){
    analogWrite(r, steps[step][0]);
    analogWrite(g, steps[step][1]);
    analogWrite(b, steps[step][2]);
    if (debug && debug_blink){
      Serial.print("us = ");
      Serial.println(us);
      Serial.print("r = ");
      Serial.println(steps[step][0]);
      Serial.print("g = ");
      Serial.println(steps[step][1]);
      Serial.print("b = ");
      Serial.println(steps[step][2]);
    }
  }else{
    analogWrite(r, 0);
    analogWrite(g, 0);
    analogWrite(b, 0);
  }
  uint16_t signal_val = step > 0 || step_part > 0 ? ceil(pow((6.248 / 24.0) * ((step - 1) * 3 + step_part + 1), 3)) : 0;
  if (signal_val && step >= 1){
    if (step == 1 && step_part){
      signal_val += step_part;
    }
    if (step > 1){
      signal_val += 2;
    }
    signal_val += 10;
  }
  signal = signal_val > 255 ? 255 : signal_val;
  if (signal_prev != signal){
    signal_prev = signal;
    period = 9000 - 9000 / 255.0 * signal;
    if (debug){
      Serial.print("signal_val = ");
      Serial.println(signal_val, DEC);
      Serial.print("signal = ");
      Serial.println(signal, DEC);
      Serial.print("period = ");
      Serial.println(period, DEC);
    }
  }
}

void interrupt_cros_zero(){
  us = micros();
  if (us - cros_zero_us < 2500){
    return;
  }
  cros_zero_us = us;
  if (signal < 255){
    digitalWrite(signal_pin, LOW);
  }
  if (signal){
    Timer1.setPeriod(period + 1000);
    interrupt_signal_skip = true;
    Timer1.start();
  }
}

void interrupt_signal_stop(){
  if (interrupt_signal_skip){
    interrupt_signal_skip = false;
    return;
  }
  digitalWrite(signal_pin, HIGH);
  Timer1.stop();
}

void read_buttons(){
  b1 = digitalRead(button_1_pin) != 1;
  b2 = digitalRead(button_2_pin) != 1;
  button1 = false;
  button2 = false;

  if (!b1){
    cmd_mode_1 = true;
  }
  if (!b2){
    cmd_mode_2 = true;
  }

  if (cmd_mode_1 && b1){
    cmd_mode_1 = false;
    cmd_start_1 = us;
  }
  if (cmd_mode_2 && b2){
    cmd_mode_2 = false;
    cmd_start_2 = us;
  }

  if (cmd_mode_1 && cmd_start_1 && us - cmd_start_1 <= 50000){
    cmd_start_1 = 0;
  }
  if (cmd_mode_2 && cmd_start_2 && us - cmd_start_2 <= 50000){
    cmd_start_2 = 0;
  }

  if (!cmd_mode_1 && cmd_start_1 && us - cmd_start_1 > 50000 && b1){
    cmd_start_1 = cmd_start_1 + 250;
    button1 = true;
  }
  if (!cmd_mode_2 && cmd_start_2 && us - cmd_start_2 > 50000 && b2){
    cmd_start_2 = cmd_start_2 + 250;
    button2 = true;
  }
}

