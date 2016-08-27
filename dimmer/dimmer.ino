boolean debug = false;

#include "EEPROM.h"

const byte button_1_pin = A1;
const byte button_2_pin = A0;
const byte buttons_low_pin = 10;

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

unsigned long ms;

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
unsigned long blink_ms = 0;
boolean blink_prev = false;

char signal;
int signal_prev = -1;

void setup(){
  //debug = true;
  if (debug){
    Serial.begin(9600);
  }
  pinMode(button_1_pin, INPUT_PULLUP);
  pinMode(button_2_pin, INPUT_PULLUP);
  digitalWrite(buttons_low_pin, LOW);
  pinMode(buttons_low_pin, OUTPUT);

  digitalWrite(signal_pin, LOW);
  pinMode(signal_pin, OUTPUT);
  //TCCR1B = TCCR1B & B11111000 | B00000001;
  //TCCR2B = TCCR2B & B11111000 | B00000001;

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
  ms = millis();

  read_buttons();

  if (button1 && (step < 8 || step_part < 2)){
    if (step_part > 1 || step == 0){
      step_part = 0;
      step++;
    }else{
      step_part++;
    }
    blink = true;
    blink_ms = ms;
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
    blink_ms = ms;
  }

  switch (step_part){
    case 0:
      if (step > 0 && blink != true){
        blink = true;
        blink_ms = ms;
      }
      break;
    case 1:
      if (ms - blink_ms > 500){
        blink = !blink;
        blink_ms = ms;
      }
      break;
    case 2:
      if (ms - blink_ms > 250){
        blink = !blink;
        blink_ms = ms;
      }
      break;
  }

  if (step_prev != step || step_part != step_part_prev || blink_prev != blink){
    if (step_prev != step || step_part != step_part_prev){
      step_prev = step;
      step_part_prev = step_part;
      EEPROM.write(0, step);
      EEPROM.write(1, step_part);
    }
    blink_prev = blink;
    if (blink){
      analogWrite(r, steps[step][0]);
      analogWrite(g, steps[step][1]);
      analogWrite(b, steps[step][2]);
    }else{
      analogWrite(r, 0);
      analogWrite(g, 0);
      analogWrite(b, 0);
    }
    signal = step > 0 || step_part > 0 ? (2 + ((step - 1) * 3 + step_part) * 11) : 0;
    if (debug){
      Serial.println(signal);
    }
    if (signal_prev != signal){
      signal_prev = signal;
      analogWrite(signal_pin, signal);
    }
  }
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
    cmd_start_1 = ms;
  }
  if (cmd_mode_2 && b2){
    cmd_mode_2 = false;
    cmd_start_2 = ms;
  }

  if (cmd_mode_1 && cmd_start_1 && ms - cmd_start_1 <= 50){
    cmd_start_1 = 0;
  } 
  if (cmd_mode_2 && cmd_start_2 && ms - cmd_start_2 <= 50){
    cmd_start_2 = 0;
  }

  if (!cmd_mode_1 && cmd_start_1 && (int) (ms - cmd_start_1) > 50 && b1){
    cmd_start_1 = cmd_start_1 + 250;
    button1 = true;
  }
  if (!cmd_mode_2 && cmd_start_2 && (int) (ms - cmd_start_2) > 50 && b2){
    cmd_start_2 = cmd_start_2 + 250;
    button2 = true;
  }
}

