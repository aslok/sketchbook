#include "track_v2.h"

const boolean debug = false;

#include "NewPing.h"
const byte sonar_vcc_pin      = A4;
const byte sonar_trigger_pin  = 6;
const byte sonar_echo_pin     = 5;
const byte sonar_max_distance = 150;
NewPing sonar(sonar_trigger_pin, sonar_echo_pin, sonar_max_distance);
byte cm = 0;

const byte v_pin = A0;

const byte motors_in_1_pwm = 3;
const byte motors_in_2_pwm = 9;
const byte motors_in_1_p = 8;
const byte motors_in_1_n = 7;
const byte motors_in_2_p = 2;
const byte motors_in_2_n = 4;


const byte k_mls = 40;      // 1000 ms / 40 = 25 ms _one_small_loop_
word prev_k_mls = 0;
const word inc_mls = 30;    // 30 * 50 ms (one loop) = 1500 ms _one_big_loop_
word prev_mls = 0;


const byte look_delay = 3;  // 25 ms (k_mls) * 5
const byte look_space = 60; // 50 cm for search free space


const byte speed_max = 255;
const byte speed_start = 255;
const byte speed_inc = 5;

const double v_min = 5.2;


states state = STOP;
word state_mls = 0;

void setup(){  
  digitalWrite(sonar_vcc_pin, HIGH);
  pinMode(sonar_vcc_pin, OUTPUT);
  
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
  
  delay(100);

  if (debug){
    Serial.begin(56700);
    Serial.println("Setup done");
  }
}

void loop_k_mls(){
  word mls = get_mls();
  double vcc = readVcc();
  // Напряжение на источнике питания
  // с поправкой на делитель напряжения
  double v = (analogRead(v_pin) / 1023.0) * vcc * 1.66;
  if (debug){
    Serial.println("loop_k_mls");
    Serial.print("mls = ");
    Serial.println(mls);
    Serial.print("vcc = ");
    Serial.println(vcc);
    Serial.print("v = ");
    Serial.println(v);
  }
  if (v < 4){
    Serial.println("v < 5");
    if (state != STOP){
      Serial.println("state != STOP");
      next_state(STOP, mls);
    }
    return;
  }
  cm = get_distance(mls);
  //while(1){
  if (debug){
    Serial.print("cm = ");
    Serial.println(cm);
    Serial.print("state_mls = ");
    Serial.println(state_mls);
  }
  //delay(500); }
  // Проверяем текущее состояние
  switch (state){
    // Стоим
    case STOP:
      if (debug){
        Serial.println("case STOP");
      }
      if (cm >= look_space){
        next_state(LOOK_RIGHT, mls);
      }else{
        next_state(LOOK_BACK, mls);
      }
      break;
    // Смотрим вправо
    case LOOK_RIGHT:
      if (debug){
        Serial.println("case LOOK_RIGHT");
      }
      if (state_mls + look_delay < mls){
        next_state(LOOK_LEFT, mls);
      }else if(cm < look_space){
        next_state(LOOK_BACK, mls - look_delay - (mls - state_mls));
      }else if(v < v_min){
        next_state(LOOK_BACK, mls + look_delay);
      }
      break;
    // Смотрим влево
    case LOOK_LEFT:
      if (debug){
        Serial.println("case LOOK_LEFT");
      }
      if (state_mls + look_delay < mls){
        next_state(LOOK_END, mls);
      }else if(cm < look_space){
        next_state(LOOK_BACK, mls + look_delay + (mls - state_mls));
      }else if(v < v_min){
        next_state(REVERS, mls);
      }
      break;
    // Заканчиваем осмотр - возвращаемся на исходную позицию
    case LOOK_END:
      if (debug){
        Serial.println("case LOOK_END");
      }
      if (state_mls + look_delay < mls){
        next_state(GO, mls);
      }
      break;
    // Продолжаем осмотр с новой позиции
    case LOOK_BACK:
      if (debug){
        Serial.println("case LOOK_BACK");
      } 
      if (state_mls + look_delay * 4 < mls){
        next_state(STOP, mls);
      }else if(cm >= look_space){
        next_state(LOOK_LEFT, mls + look_delay);
      }else if(v < v_min){
        next_state(REVERS, mls);
      }
      break;
    // Едем
    case GO:
      if (debug){
        Serial.println("case GO");
      } 
      if(cm < look_space){
        next_state(STOP, mls);
      }else if(v < v_min){
        next_state(REVERS, mls);
      }
      break;
    case REVERS:
      if (debug){
        Serial.println("case REVERS");
      } 
      if (state_mls + look_delay * 2 < mls){
        next_state(STOP, mls);
      }else if(v < v_min){
        next_state(REVERS, mls);
      }
      break;
  }
}

byte get_distance(word& mls){
  static byte cm_cnt[30] = { 0 };
  byte cnt_max;
  byte cnt_max_pos = 255;
  do{
    if (
      state == STOP || 
      (state == LOOK_RIGHT && state_mls + look_delay < mls) ||
      (state == LOOK_LEFT && state_mls + look_delay < mls)
    ){
      go_stop();
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
      mls = get_mls();
    }else{
      if (!(cnt_max_pos = sonar.ping() / US_ROUNDTRIP_CM / 5)){
        cnt_max_pos = 30;
      }
    }
  } while(cnt_max_pos == 255);
  return cnt_max_pos * 5;
}

// Переходим в новое состояние
void next_state(enum states stt, word mls){
  if (debug){
    Serial.print("change state to ");
  }
  switch (stt){
    case LOOK_RIGHT:
      if (debug){
        Serial.println("right");
      }
      go_right();
      break;
    case LOOK_LEFT:
      if (debug){
        Serial.println("left");
      }
      go_left();
      break;
    case LOOK_BACK:
      if (debug){
        Serial.println("look back");
      }
      go_left();
      break;
    case LOOK_END:
      if (debug){
        Serial.println("look end");
      }
      if (state == LOOK_RIGHT){
        go_left();
      }else if (state == LOOK_LEFT){
        go_right();
      }
      break;
    case SPEED_UP:
      if (debug){
        Serial.println("speed up");
      }
      break;
    case GO:
      if (debug){
        Serial.println("go");
      }
      go_forward();
      break;
    case SPEED_DOWN:
      if (debug){
        Serial.println("speed down");
      }
      break;
    case STOP:
      go_stop();
      if (debug){
        Serial.println("stop");
      }
      break;
    case REVERS:
      go_back();
      if (debug){
        Serial.println("revers");
      }
      break;
  }
  state_mls = mls;
  state = stt;
}

void next_state(enum states stt){
  next_state(stt, get_mls());
}

void loop_inc_mls(){
  if (debug){
    Serial.println("loop_inc_mls");
  }
}

void loop(){
  word mls = get_mls();
  if (prev_k_mls + 1 > mls){
    return;
  }
  prev_k_mls = mls;
  loop_k_mls();

  if ((prev_mls + inc_mls) > mls){
    return;
  }
  prev_mls = mls;
  loop_inc_mls();
}

word get_mls(){
  return millis() / k_mls;
}

void go_forward(){
  if (debug){
    Serial.println("go forward");
  }
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_back(){
  if (debug){
    Serial.println("go back");
  }
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_right(){
  if (debug){
    Serial.println("go right");
  }
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_left(){
  if (debug){
    Serial.println("go left");
  }
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_stop(){
  if (debug){
    Serial.println("go stop");
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

