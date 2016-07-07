#include "track_v2.h"

const boolean debug = true;

const byte sonar_trigger_pin  = 6;
const byte sonar_echo_pin     = 5;
const byte sonar_max_distance = 150;
#include "NewPing.h"
NewPing sonar(sonar_trigger_pin, sonar_echo_pin, sonar_max_distance);
byte cm = 0;

#include "Wire.h"
#include "HMC5883L.h"
HMC5883L compass;

const byte v_pin = A0;

const byte motors_in_1_pwm = 3;
const byte motors_in_2_pwm = 9;
const byte motors_in_1_p = 8;
const byte motors_in_1_n = 7;
const byte motors_in_2_p = 2;
const byte motors_in_2_n = 4;


const byte k_mls = 40;      // 1000 ms / 40 = 25 ms _one_small_loop_
word prev_mls = 0;

byte look_cmps = 20;        // 20 degress for search free space
int prev_cmps = 0;

const byte look_delay = 120;// 25 ms (k_mls) * 120
const byte look_space = 60; // 60 cm for search free space


const byte speed_max = 255;
const byte speed_start = 255;
const byte speed_inc = 5;

const double v_min = 5.2;


states state = STOP;
word state_mls = 0;

void setup(){  
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, LOW);
  pinMode(motors_in_1_p, OUTPUT);
  pinMode(motors_in_1_n, OUTPUT);
  pinMode(motors_in_2_p, OUTPUT);
  pinMode(motors_in_2_n, OUTPUT);
  analogWrite(motors_in_1_pwm, speed_start);
  analogWrite(motors_in_2_pwm, speed_start);

  /*while (!compass.begin()){
    delay(100);
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(-139, -270); */

  if (debug){
    Serial.begin(56700);
    Serial.println(F("Setup done"));
  }
}

void loop(){
  word mls = get_mls();
  if (prev_mls + 1 > mls){
    loop_mls(mls);
  }
}

void loop_mls(word mls){
  prev_mls = mls;
  double vcc = readVcc();
  //int cmps = readCompass();
  int cmps = 0;
  // Напряжение на источнике питания
  // с поправкой на делитель напряжения
  double v = (analogRead(v_pin) / 1023.0) * vcc * 1.45;
  if (debug){
    Serial.println(F("loop_mls"));
    Serial.print(F("mls = "));
    Serial.println(mls);
    Serial.print(F("vcc = "));
    Serial.println(vcc);
    Serial.print(F("v = "));
    Serial.println(v);
    Serial.print(F("cmps = "));
    Serial.println(cmps);
    Serial.print(F("prev_cmps = "));
    Serial.println(prev_cmps);
  }
  /*if (v < 3){
    Serial.println(F("v < 3"));
    if (state != STOP){
      Serial.println(F("state != STOP"));
      next_state(STOP, mls, cmps);
    }
    return;
  }*/
  cm = readDistance();
  //while(1){
  if (debug){
    Serial.print(F("cm = "));
    Serial.println(cm);
    Serial.print(F("state_mls = "));
    Serial.println(state_mls);
  }
  //delay(500); }
  // Проверяем текущее состояние
  switch (state){
    // Стоим
    case STOP:
      if (debug){
        Serial.println(F("case STOP"));
      }
      if (!cm || cm >= look_space){
        next_state(LOOK_RIGHT, mls, cmps);
      }else{
        next_state(LOOK_BACK, mls, cmps);
      }
      break;
    // Смотрим вправо
    case LOOK_RIGHT:
      if (debug){
        Serial.println(F("case LOOK_RIGHT"));
      }
      if ((prev_cmps + 360 - look_cmps) % 360 > cmps){
        next_state(LOOK_LEFT, mls, cmps);
      }else if (cm && cm < look_space){
        next_state(LOOK_BACK, mls, cmps);
      /*}else if (v < v_min){
        next_state(LOOK_BACK, mls, cmps);*/
      }
      break;
    // Смотрим влево
    case LOOK_LEFT:
      if (debug){
        Serial.println(F("case LOOK_LEFT"));
      }
      if ((prev_cmps + look_cmps * 2) % 360 < cmps){
        next_state(LOOK_END, mls, cmps);
      }else if (cm && cm < look_space){
        next_state(LOOK_BACK, mls, cmps);
      /*}else if (v < v_min){
        next_state(REVERS, mls, cmps);*/
      }
      break;
    // Заканчиваем осмотр - возвращаемся на исходную позицию
    case LOOK_END:
      if (debug){
        Serial.println(F("case LOOK_END"));
      }
      if ((prev_cmps + 360 - look_cmps) % 360 > cmps){
        next_state(GO, mls, cmps);
      }
      break;
    // Продолжаем осмотр с новой позиции
    case LOOK_BACK:
      if (debug){
        Serial.println(F("case LOOK_BACK"));
      }
      if ((prev_cmps + look_cmps * 3) % 360 < cmps){
        next_state(STOP, mls, cmps);
      }else if (cm && cm >= look_space){
        next_state(LOOK_LEFT, mls, cmps);
      /*}else if (v < v_min){
        next_state(REVERS, mls, cmps);*/
      }
      break;
    // Едем
    case GO:
      if (debug){
        Serial.println(F("case GO"));
      } 
      if (cm && cm < look_space){
        next_state(STOP, mls, cmps);
      /*}else if (v < v_min){
        next_state(REVERS, mls, cmps);*/
      }
      break;
    case REVERS:
      if (debug){
        Serial.println(F("case REVERS"));
      }
      if (prev_cmps + 180 % 360 < cmps){
        next_state(STOP, mls, cmps);
      /*}else if (v < v_min){
        next_state(REVERS, mls, cmps);*/
      }
      break;
  }
}

// Переходим в новое состояние
void next_state(enum states stt, word mls, int cmps){
  if (debug){
    Serial.print(F("change state to "));
  }
  switch (stt){
    case LOOK_RIGHT:
      if (debug){
        Serial.println(F("right"));
      }
      go_right();
      break;
    case LOOK_LEFT:
      if (debug){
        Serial.println(F("left"));
      }
      go_left();
      break;
    case LOOK_BACK:
      if (debug){
        Serial.println(F("look back"));
      }
      go_left();
      break;
    case LOOK_END:
      if (debug){
        Serial.println(F("look end"));
      }
      if (state == LOOK_RIGHT){
        go_left();
      }else if (state == LOOK_LEFT){
        go_right();
      }
      break;
    case SPEED_UP:
      if (debug){
        Serial.println(F("speed up"));
      }
      break;
    case GO:
      if (debug){
        Serial.println(F("go"));
      }
      go_forward();
      break;
    case SPEED_DOWN:
      if (debug){
        Serial.println(F("speed down"));
      }
      break;
    case STOP:
      go_stop();
      if (debug){
        Serial.println(F("stop"));
      }
      break;
    case REVERS:
      go_back();
      if (debug){
        Serial.println(F("revers"));
      }
      break;
  }
  state_mls = mls;
  prev_cmps = cmps;
  state = stt;
}

word get_mls(){
  return millis() / k_mls;
}

void go_forward(){
  if (debug){
    Serial.println(F("go forward"));
  }
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_back(){
  if (debug){
    Serial.println(F("go back"));
  }
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_right(){
  if (debug){
    Serial.println(F("go right"));
  }
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_left(){
  if (debug){
    Serial.println(F("go left"));
  }
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_stop(){
  if (debug){
    Serial.println(F("go stop"));
  }
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, LOW);
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
  
  delay(35); // Wait for Vref to settle

  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  /* измерив Vcc с помощью вольтметра и нашей функции readVcc().
   * Далее заменяем константу 1125300L новой переменной:
   * scale_constant = internal1.1Ref * 1023 * 1000
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   *
   * internal1.1Ref = 1.1 * 4960 / 5138 = 1,06189178669
   * scale_constant = 1,06189178669 * 1023 = 1086,31529778
   *
   * internal1.1Ref = 1.1 * 5050 / 5260 = 1,05608365019
   * scale_constant = 1,05608365019 * 1023 = 1080,37357414   
   *
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
  return 1080.37357414 / result; // Vcc in volts
}

byte readDistance(){
  /*static byte cm_cnt[30] = { 0 };
  byte cnt_max;
  byte cnt_max_pos = 255;
  do{
    memset(cm_cnt, 0, sizeof(cm_cnt));
    for (byte cnt = 0; cnt < 10; cnt++){
      cm_cnt[sonar.ping() / US_ROUNDTRIP_CM / 5]++;
      delay(50);
    }
    cnt_max = 0;
    cnt_max_pos = 255;
    for (byte pos = 0; pos < 30; pos++){
      if (cnt_max < cm_cnt[pos]){
        cnt_max = cm_cnt[cnt_max_pos = pos];
      }
    }
  } while(cnt_max_pos == 255);
  return cnt_max_pos * 5;*/
  return sonar.ping() / US_ROUNDTRIP_CM;
}

int readCompass(){
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis) + (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  if (heading < 0){
    heading += 2 * PI;
  }

  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  return (int) (heading * 180 / M_PI);
}

