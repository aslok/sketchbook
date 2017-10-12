const byte sonar_trigger_pin  = 3;
const byte sonar_echo_pin     = 2;
const byte sonar_max_distance = 150;
#include "NewPing.h"
NewPing sonar(sonar_trigger_pin, sonar_echo_pin, sonar_max_distance);

#include "Wire.h"
#include "HMC5883L.h"
HMC5883L compass;
Vector compass_norm;

boolean debug = false;

const byte BATTERY_V_IN = A3;

const byte PWM1 = 11;
const byte PWM2 = 10;

const byte IN1 = 9;
const byte IN2 = 8;
const byte IN3 = 7;
const byte IN4 = 6;

const byte SIGNAL_OUT = 13;

enum direction_enum{
  stop,
  forward,
  back,
  left,
  right
};
direction_enum direction = stop;

const byte speed_start = 100;
int speed = 0;
byte speed_prev = 0;
const byte speed_max = 255;
const byte speed_rotate_max = 200;
const byte speed_amp = 3;

float battery_v = 0;
float battery_max = 0;
float vcc = 0;

const byte distance_try = 5;
byte distance = 0;
const byte distance_max = 70;

boolean signal = false;
boolean dot = false;
boolean signal_out_state = false;

unsigned long ms = 0;
unsigned long debug_ms = 0;
unsigned long signal_ms = 0;
unsigned long dot_ms = 0;
unsigned long distance_ms = 0;
unsigned long speed_up_ms = 0;
unsigned long orientation_ms = 0;
unsigned long motion_ms = 0;
unsigned long rotate_ms = 0;
unsigned long back_ms = 0;
unsigned long stop_ms = 0;
unsigned long break_ms = 0;


enum compass_enum{
  north,
  north_east,
  east,
  south_east,
  south,
  south_west,
  west,
  north_west,
  na
};
compass_enum orientation = na;
compass_enum orientation_start = orientation;
compass_enum orientation_target = orientation;

boolean rotate = false;
boolean rotating = false;

void setup(){  
  //debug = true;

  while (!compass.begin())
  {
    if (debug){
      Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    }
    delay(500);
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_15HZ);
  compass.setSamples(HMC5883L_SAMPLES_1);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  analogWrite (PWM1, speed_start);
  analogWrite (PWM2, speed_start);
  pinMode (PWM1, OUTPUT);
  pinMode (PWM2, OUTPUT);
  
  pinMode (BATTERY_V_IN, INPUT);

  digitalWrite(SIGNAL_OUT, LOW);
  pinMode (SIGNAL_OUT, OUTPUT);

  if (debug){
    Serial.begin(57600);
  }

  go_stop();
}

void loop(){
  ms = millis();
  calc_distance();
  battery_v = analogRead(BATTERY_V_IN) * (5 / 1023.0) * 3 * 1.07;
  calc_orientation();

  if (debug) {
    vcc = readVcc();
  }

  check_battery();
  check_rotate();
  check_distance();
  continue_motion();
  show_stop();
  show_signal();
  show_dot();

  show_debug();
}

void check_distance(){
  if (signal == true){
    return;
  }
  switch (direction) {
    case forward:
      if (distance < distance_max){
        go_break();
      }else if (ms - motion_ms > 1500){
        go_stop();
      }
      break;
    case stop:
      if (ms - stop_ms < 1000 || speed){
        break;
      }
      if (orientation_start != orientation && distance > distance_max){
        go_forward();
      }
      orientation_start = orientation;
      orientation_target = (compass_enum) ((int)orientation + 1);
      if (orientation_target > 7){
        orientation_target = (compass_enum) 0;
      }
      if (direction != stop){
        break;
      }
      if (random(0, 3) < 1.0){
        go_left();
      }else{
        go_right();
      }
      break;
    case right:
    case left:
      if (speed >= speed_rotate_max){
        go_stop();
      }
      break;
    case back:
      if (break_ms){
        if (ms - break_ms > 50){
          break_ms = 0;
          go_wait();
        }
        break;
      }
      if (/*(ms - back_ms > 100 && battery_v < battery_max - 3) || */ms - back_ms > 500){
        if (random(0, 3) < 1.0){
          go_left();
        }else{
          go_right();
        }
      }
      break;
  }
}

void continue_motion(){
  /*if (battery_v < 6 && direction != stop){
    go_stop();
    signal = true;
  }*/
  if (rotating){// || battery_v < battery_max - 3){
    go_back();
  }

  int speed_k = ceil((ms - speed_up_ms) / speed_amp);
  if (speed_k < 1){
    speed_k = 1;
  }

  if (direction != stop){
    if (direction == right || direction == left){
      if (speed < speed_rotate_max){
        speed += speed_k;
      }
    }else if (speed < speed_max){
      speed += speed_k;
    }
  }else if (speed >= speed_start){
    speed -= speed_k;
  }
  speed_up_ms = ms;
  if (direction == right || direction == left){
    if (speed > speed_rotate_max){
      speed = speed_rotate_max;
    }
  }else if (speed > speed_max){
    speed = speed_max;
  }
  if (speed && speed < speed_start){
    speed = 0;
  }
  if (speed != speed_prev){
    speed_prev = speed;
    analogWrite(PWM1, speed);
    analogWrite(PWM2, speed);
  }
}

void calc_distance(){
  if (ms - distance_ms < 100){
    return;
  }
  distance_ms = ms;
  /*if (direction == stop){
    byte getted_count = 0;
    byte getted_distance = 0;
    byte correct_distance = 0;
    for (byte f = 0; f < distance_try; f++){
      getted_distance = sonar.ping() / US_ROUNDTRIP_CM;
      if (getted_distance){
        correct_distance = getted_distance;
        getted_count++;
      }
      delay(100);
    }
    distance = getted_count > (distance_try / 5 * 3) ? correct_distance : 0;
  }else{*/
    distance = sonar.ping() / US_ROUNDTRIP_CM;
  //}
  return;
}

void calc_orientation(){
  if (ms - orientation_ms < 5 || speed){
    return;
  }
  orientation_ms = ms;
  
  compass_norm = compass.readNormalize();
  float heading = atan2(compass_norm.YAxis, compass_norm.XAxis);
  float declinationAngle = (6.0 + (1.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  if (heading < 0){
    heading += 2 * PI;
  }
  if (heading > 2 * PI){
    heading -= 2 * PI;
  }
  float headingDegrees = heading * 180/M_PI; 
  orientation = (compass_enum) (headingDegrees / 45);
}

void check_rotate(){
  if (rotate){
    if (!rotate_ms){
      rotate_ms = ms;
    }
    if (ms - rotate_ms > 10000){
      rotating = true;
      rotate_ms = 0;
    }
  }else{
    rotating = false;
    rotate_ms = 0;
  }
}

void check_battery(){
  if (battery_v > battery_max){
    battery_max = battery_v;
  }
}

void show_signal(){
  if (signal){
    if (ms - signal_ms < 1000){
      return;
    }
    signal_ms = ms;
    if (signal_out_state){
      signal_out_state = false;
      digitalWrite(SIGNAL_OUT, LOW);
    }else{
      signal_out_state = true;
      digitalWrite(SIGNAL_OUT, HIGH);
    }
  }else if (!dot && signal_out_state){
    signal_out_state = false;
    digitalWrite(SIGNAL_OUT, LOW);
  }
}

void show_stop(){
  if (stop_ms){
    dot = true;
  }
  if (dot && !stop_ms){
    dot = false;
  }
}

void show_dot(){
  if (!signal && dot){
    if (ms - dot_ms < 500){
      return;
    }
    dot_ms = ms;
    if (signal_out_state){
      signal_out_state = false;
      digitalWrite(SIGNAL_OUT, LOW);
    }else{
      signal_out_state = true;
      digitalWrite(SIGNAL_OUT, HIGH);
    }
  }else if (!signal && signal_out_state){
    signal_out_state = false;
    digitalWrite(SIGNAL_OUT, LOW);
  }
}

void show_debug(){
  if (debug && ms - debug_ms < 500){
    //return;
  }
  debug_ms = ms;

  Serial.print("ms = ");
  Serial.println(ms);

  Serial.print("distance = ");
  Serial.println(distance);

  Serial.print("battery_v = ");
  Serial.println(battery_v);

  Serial.print("vcc = ");
  Serial.println(vcc);

  Serial.print("orientation = ");
  Serial.println(orientation);

  Serial.print("orientation_target = ");
  Serial.println(orientation_target);

  Serial.print("direction = ");
  Serial.println(direction);

  Serial.print("speed = ");
  Serial.println(speed);

  Serial.println("-------------------------------------");
}

void go_forward(){
  direction = forward;
  speed = speed_start;
  rotate = false;
  motion_ms = ms;
  digitalWrite(IN1, LOW);  // BACK RIGHT
  digitalWrite(IN2, HIGH); // FORWARD RIGHT
  digitalWrite(IN3, HIGH); // FORWARD LEFT
  digitalWrite(IN4, LOW);  // BACK LEFT
}
void go_back(){
  direction = back;
  speed = speed_start;
  rotate = false;
  back_ms = ms;
  digitalWrite(IN1, HIGH); // BACK RIGHT
  digitalWrite(IN2, LOW);  // FORWARD RIGHT
  digitalWrite(IN3, LOW);  // FORWARD LEFT
  digitalWrite(IN4, HIGH); // BACK LEFT
}
void go_left(){
  direction = left;
  speed = speed_start;
  rotate = true;
  digitalWrite(IN1, HIGH); // BACK RIGHT
  digitalWrite(IN2, LOW);  // FORWARD RIGHT
  digitalWrite(IN3, HIGH); // FORWARD LEFT
  digitalWrite(IN4, LOW);  // BACK LEFT
}
void go_right(){
  direction = right;
  speed = speed_start;
  rotate = true;
  digitalWrite(IN1, LOW);  // BACK RIGHT
  digitalWrite(IN2, HIGH); // FORWARD RIGHT
  digitalWrite(IN3, LOW);  // FORWARD LEFT
  digitalWrite(IN4, HIGH); // BACK LEFT
}
void go_stop(){
  direction = stop;
  stop_ms = ms;
}
void go_break(){
  byte speed_tmp = speed;
  go_back();
  speed = speed_tmp + 30;
  break_ms = ms;
}
void go_wait(){
  go_stop();
  speed = 0;
  digitalWrite(IN1, LOW);  // BACK RIGHT
  digitalWrite(IN2, LOW);  // FORWARD RIGHT
  digitalWrite(IN3, LOW);  // FORWARD LEFT
  digitalWrite(IN4, LOW);  // BACK LEFT
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

  delay(75); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  /* измерив Vcc с помощью вольтметра и нашей функции readVcc().
   * Далее заменяем константу 1125.3 новой переменной:
   * scale_constant = internal1.1Ref * 1023
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   * internal1.1Ref = 1.1 * 4930 / 5138 = 1.05546905410666
   * scale_constant = 1.05546905410666 * 1023 = 1079.74484235111318
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
   
  // return 1125.3 / result; // Vcc in volts
  return 1079.744842 / result;
}
