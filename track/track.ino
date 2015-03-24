const byte RC1 = A2;
const byte RC2 = A3;
const byte RC3 = A0;
const byte RC4 = A1;

const byte PWM1 = 5;
const byte PWM2 = 9;

const byte IN1 = 4;
const byte IN2 = 6;
const byte IN3 = 7;
const byte IN4 = 8;

const byte start_speed = 125;
const byte max_speed = 255;
const byte speed_inc = 1;
const int8_t rev_speed = 0;
const byte dalay = 100;
word speed = 0;
word prev_millis = 0;
byte prev_speed = 0;

const word analog_low = 1023 / 2;
const word analog_high = 1023 / 2;
boolean prev_analog_1 = false;
boolean prev_analog_2 = false;
boolean prev_analog_3 = false;
boolean prev_analog_4 = false;

const byte analog_chk = 10;
byte analog_cnt_1 = 0;
byte analog_cnt_2 = 0;
byte analog_cnt_3 = 0;
byte analog_cnt_4 = 0;

void setup(){  
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  analogWrite (PWM1, start_speed);
  analogWrite (PWM2, start_speed);
  pinMode (RC1, INPUT);
  pinMode (RC2, INPUT);
  pinMode (RC3, INPUT);
  pinMode (RC4, INPUT);
  
  prev_millis = millis();
  Serial.begin(56700);
}

void loop(){
  word mls = millis();
  if (prev_millis + dalay < mls){
    return;
  }
  prev_millis = millis();

  word rc1 = analogRead(RC1);
  word rc2 = analogRead(RC2);
  word rc3 = analogRead(RC3);
  word rc4 = analogRead(RC4);
  boolean analog_1 = rc1 < analog_low && rc2 > analog_high;
  boolean analog_2 = rc2 < analog_low && rc1 > analog_high;
  boolean analog_3 = rc3 < analog_low && rc4 > analog_high;
  boolean analog_4 = rc4 < analog_low && rc3 > analog_high;
  
  Serial.print("analogRead(RC1) =");
  Serial.println(analogRead(RC1));
  Serial.print("analogRead(RC2) =");
  Serial.println(analogRead(RC2));
  /*Serial.print("analogRead(RC3) =");
  Serial.println(analogRead(RC3));
  Serial.print("analogRead(RC4) =");
  Serial.println(analogRead(RC4));*/
        
  if (analog_1 != prev_analog_1){
    analog_cnt_1++;
    if (analog_chk < analog_cnt_1){
      prev_analog_1 = analog_1;
      analog_cnt_1 = 0;
      //Serial.print("prev_analog_1 = ");
      //Serial.println(prev_analog_1);
    }
  }else{
    analog_cnt_1 = 1;
  }
        
  if (analog_2 != prev_analog_2){
    analog_cnt_2++;
    if (analog_chk < analog_cnt_2){
      prev_analog_2 = analog_2;
      analog_cnt_2 = 0;
      //Serial.print("prev_analog_2 = ");
      //Serial.println(prev_analog_2);
    }
  }else{
    analog_cnt_2 = 1;
  }
        
  if (analog_3 != prev_analog_3){
    analog_cnt_3++;
    if (analog_chk < analog_cnt_3){
      prev_analog_3 = analog_3;
      analog_cnt_3 = 0;
      //Serial.print("prev_analog_3 = ");
      //Serial.println(prev_analog_3);
    }
  }else{
    analog_cnt_3 = 1;
  }
        
  if (analog_4 != prev_analog_4){
    analog_cnt_4++;
    if (analog_chk < analog_cnt_4){
      prev_analog_4 = analog_4;
      analog_cnt_4 = 0;
      //Serial.print("prev_analog_4 = ");
      //Serial.println(prev_analog_4);
    }
  }else{
    analog_cnt_4 = 1;
  }

  if (speed && speed < max_speed){
    speed += speed_inc;
    //Serial.println(speed);
  }
  
  if (
    !analog_cnt_1 || !analog_cnt_2 ||
    (
      !speed && (!analog_cnt_3 || !analog_cnt_4)
    )
  ){
    speed = start_speed;
  }
    
  // Вперед
  if (
    (
      prev_analog_2 || 
      (!prev_analog_1 && prev_analog_3) || 
      (!prev_analog_1 && prev_analog_4)
    ) && 
    (
      speed != prev_speed || !analog_cnt_3 || !analog_cnt_4
    )
  ){
      //Serial.println("Вперед");
      //Serial.println(prev_analog_3 && !prev_analog_4 ? "влево" : (!prev_analog_3 && prev_analog_4 ? "вправо" : ""));
      digitalWrite (IN1, prev_analog_3 ? LOW : HIGH);
      digitalWrite (IN2, prev_analog_3 ? HIGH : LOW);
      digitalWrite (IN3, prev_analog_4 ? HIGH : LOW);
      digitalWrite (IN4, prev_analog_4 ? LOW : HIGH);
      analogWrite (PWM1, prev_analog_3 ? speed : (speed + rev_speed));
      analogWrite (PWM2, prev_analog_4 ? speed : (speed + rev_speed));
  // Назад
  }else if (prev_analog_1 && (speed != prev_speed || !analog_cnt_3 || !analog_cnt_4)){
    //Serial.println("Назад");
    digitalWrite (IN1, prev_analog_3 ? HIGH : LOW);
    digitalWrite (IN2, prev_analog_3 ? LOW : HIGH);
    digitalWrite (IN3, prev_analog_4 ? LOW : HIGH);
    digitalWrite (IN4, prev_analog_4 ? HIGH : LOW);
    analogWrite (PWM1, prev_analog_3 ? speed : (speed + rev_speed));
    analogWrite (PWM2, prev_analog_4 ? speed : (speed + rev_speed));
  }else if (!prev_analog_1 && !prev_analog_2 && !prev_analog_3 && !prev_analog_4 && speed){
    //Serial.println("стоп");
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, LOW);
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, LOW);
    analogWrite (PWM1, start_speed);
    analogWrite (PWM2, start_speed);
    speed = 0;
  }
  prev_speed = speed;
}

