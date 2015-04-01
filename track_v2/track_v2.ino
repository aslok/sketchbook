#include "track_v2.h"

#include "NewPing.h"
const byte sonar_vcc_pin      = A4;
const byte sonar_trigger_pin  = 6;
const byte sonar_echo_pin     = 5;
const byte sonar_max_distance = 150;
NewPing sonar(sonar_trigger_pin, sonar_echo_pin, sonar_max_distance);
byte cm = 0;


const byte motors_in_1_pwm = 3;
const byte motors_in_2_pwm = 9;
const byte motors_in_1_p = 8;
const byte motors_in_1_n = 7;
const byte motors_in_2_p = 2;
const byte motors_in_2_n = 4;


const byte k_mls = 20;      // 1000 ms / 20 = 50 ms _one_small_loop_
word prev_k_mls = 0;
const word inc_mls = 50;    // 50 * 50 ms (one loop) = 2500 ms _one_big_loop_
word prev_mls = 0;


const byte look_delay = 6;  // 50 ms (k_mls) * 20
const byte look_space = 50; // 50 cm for search free space


const byte speed_max = 255;
const byte speed_start = 255;
const byte speed_inc = 5;

const double vraw_min = 4.5;


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
  
  Serial.begin(56700);
  Serial.println("Setup done");
}

void loop_k_mls(){
  Serial.println("loop_k_mls");
  cm = get_distance();
  Serial.print("cm = ");
  Serial.println(cm);
  word mls = get_mls();
  Serial.print("mls = ");
  Serial.println(mls);
  Serial.print("state_mls = ");
  Serial.println(state_mls);
  double vcc = readVcc();
  double vraw = (analogRead(A0) / 1023.0) * vcc * 1.66;
  //while(1){
  Serial.print("vcc = ");
  Serial.println(vraw);
  //delay(500); }
  // Проверяем текущее состояние
  switch (state){
    // Стоим
    case STOP:
      Serial.println("case STOP");
      if (cm >= look_space){
        next_state(LOOK_RIGHT, mls);
      }else{
        next_state(LOOK_BACK, mls);
      }
      break;
    // Смотрим вправо
    case LOOK_RIGHT:
      Serial.println("case LOOK_RIGHT");
      if (state_mls + look_delay < mls){
        next_state(LOOK_LEFT, mls);
      }else if(cm < look_space){
        next_state(LOOK_BACK, mls - look_delay - (mls - state_mls));
      }else if(vraw < vraw_min){
        next_state(LOOK_BACK, mls + look_delay);
      }
      break;
    // Смотрим влево
    case LOOK_LEFT:
      Serial.println("case LOOK_LEFT");
      if (state_mls + look_delay < mls){
        next_state(LOOK_END, mls);
      }else if(cm < look_space){
        next_state(LOOK_BACK, mls + look_delay + (mls - state_mls));
      }else if(vraw < vraw_min){
        next_state(REVERS, mls);
      }
      break;
    // Заканчиваем осмотр - возвращаемся на исходную позицию
    case LOOK_END:
      Serial.println("case LOOK_BACK");
      if (state_mls + look_delay < mls){
        next_state(GO, mls);
      }
      break;
    // Продолжаем осмотр с новой позиции
    case LOOK_BACK:
      Serial.println("case LOOK_BACK");
      if (state_mls + look_delay * 2 < mls){
        next_state(STOP, mls);
      }else if(vraw < vraw_min){
        next_state(REVERS, mls);
      }
      break;
    // Едем
    case GO:
      if(cm < look_space){
        next_state(STOP, mls);
      }else if(vraw < vraw_min){
        next_state(REVERS, mls);
      }
      break;
    case REVERS:
      if (state_mls + look_delay * 2 < mls){
        next_state(STOP, mls);
      }
      break;
  }
}

byte get_distance(){
  byte cm_cnt[15] = { 0 };
  for (byte cnt = 0; cnt < 10; cnt++){
    byte cm_tmp = sonar.ping() / US_ROUNDTRIP_CM / 10;
    cm_cnt[cm_tmp]++;
  }
  byte cnt_max = 0;
  byte cnt_max_pos = 255;
  for (byte pos = 0; pos < 15; pos++){
    if (cnt_max < cm_cnt[pos]){
      cnt_max = cm_cnt[cnt_max_pos = pos];
    }
  }
  return cnt_max_pos != 255 ? (cnt_max_pos * 10) : get_distance();
}

// Переходим в новое состояние
void next_state(enum states stt, word mls){
  Serial.print("change state to ");
  switch (stt){
    case LOOK_RIGHT:
      Serial.println("right");
      go_right();
      break;
    case LOOK_LEFT:
      Serial.println("left");
      go_left();
      break;
    case LOOK_BACK:
      Serial.println("look back");
      go_left();
      break;
    case LOOK_END:
      Serial.println("look end");
      if (state == LOOK_RIGHT){
        go_left();
      }else if (state == LOOK_LEFT){
        go_right();
      }
      break;
    case SPEED_UP:
      Serial.println("speed up");
      break;
    case GO:
      Serial.println("go");
      go_forward();
      break;
    case SPEED_DOWN:
      Serial.println("speed down");
      break;
    case STOP:
      go_stop();
      Serial.println("stop");
      break;
    case REVERS:
      go_back();
      Serial.println("stop");
      break;
  }
  state_mls = mls;
  state = stt;
}

void next_state(enum states stt){
  next_state(stt, get_mls());
}

void loop_inc_mls(){
  Serial.println("loop_inc_mls");
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
  Serial.println("go forward");
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_back(){
  Serial.println("go back");
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_right(){
  Serial.println("go right");
  digitalWrite(motors_in_1_p, LOW);
  digitalWrite(motors_in_1_n, HIGH);
  digitalWrite(motors_in_2_p, HIGH);
  digitalWrite(motors_in_2_n, LOW);
}

void go_left(){
  Serial.println("go left");
  digitalWrite(motors_in_1_p, HIGH);
  digitalWrite(motors_in_1_n, LOW);
  digitalWrite(motors_in_2_p, LOW);
  digitalWrite(motors_in_2_n, HIGH);
}

void go_stop(){
  Serial.println("go stop");
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

  delay(75); // Wait for Vref to settle
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

