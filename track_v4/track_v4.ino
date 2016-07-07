boolean debug = false;
boolean loop_debug = false;

const byte VCC_IN = A5;

const byte PWM1 = 11;
const byte PWM2 = 10;

const byte IN1 = 9;
const byte IN2 = 8;
const byte IN3 = 7;
const byte IN4 = 6;

// Arduino RX -> ESP TX 
const byte RX = 2;
// Arduino TX -> ESP RX
const byte TX = 3;

const char* SSID = "wifi3r";
const char* SSID_PASS = "wifi3rpassphrasehackmeplease";
const char* HOST = "192.168.1.1";
const char* PORT = "80";
const char* PATH = "/drive/data.php";

#include "SoftwareSerial.h"
SoftwareSerial ESPserial(RX, TX);

const byte read_buff_len = 64;
const unsigned long read_timeout_ms = 10000;
 
void setup(){  
  //debug = true;
  //loop_debug = true;

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  analogWrite (PWM1, 0);
  analogWrite (PWM2, 0);
  pinMode (PWM1, OUTPUT);
  pinMode (PWM2, OUTPUT);

  if (debug || loop_debug){
    Serial.begin(9600);
  }
  ESPserial.begin(9600);
}

void loop(){
  char ans[read_buff_len];
  int buffer;
  if (!wget(ans)){
    analogWrite (PWM1, 0);
    analogWrite (PWM2, 0);
    return;
  }
  if (loop_debug){
    Serial.println(ans);
  }

  buffer = atoi(strtok(ans, "|"));
  if (loop_debug){
    Serial.println(buffer);
  }
  if (buffer > 0){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite (PWM2, buffer);
  }else{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite (PWM2, buffer * -1);
  }

  buffer = atoi(strtok(NULL, "|"));
  if (loop_debug){
    Serial.println(buffer);
  }
  if (buffer > 0){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite (PWM1, buffer);
  }else{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite (PWM1, buffer * -1);
  }
}

boolean wget(char* ans){
  const char* OK = "OK";
  const char* SEND_OK = "SEND OK";
  const char* LINKED = "Linked";
  const char* EMPTY_STR = "";

  const __FlashStringHelper* START  = F("VVVVVVVVVVVVVVVVVVVVV");
  const __FlashStringHelper* HR     = F("---------------------");
  const __FlashStringHelper* RESULT = F("=====================");
  const __FlashStringHelper* END    = F("^^^^^^^^^^^^^^^^^^^^^");

  char buffer[read_buff_len];
  char tmp[read_buff_len];

  if (debug){
    Serial.println(START);
  }
  println(F("AT"));
  if (!wait(OK))        { return false; }
  println(F("AT+CIFSR"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK))        { return false; }
  if (!strcmp(buffer, "0.0.0.0")){
    sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"", SSID, SSID_PASS);
    println(buffer);
    if (!wait(OK))      { return false; }
  }
  println(F("AT+CIPMODE?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK))        { return false; }
  if (strcmp(buffer, "+CIPMODE:0")){
    println(F("AT+CIPMODE=0"));
    if (!wait(OK))      { return false; }
  }
  println(F("AT+CIPMUX?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK))        { return false; }
  if (strcmp(buffer, "+CIPMUX:1")){
    println(F("AT+CIPMUX=1"));
    if (!wait(OK))      { return false; }
  }
  println(F("AT+CIPSTATUS"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK))        { return false; }
  sprintf(tmp, "+CIPSTATUS:0,\"TCP\",\"%s\",%s,0", HOST, PORT);
  if (strcmp(buffer, tmp)){
    sprintf(buffer, "AT+CIPSTART=0,\"TCP\",\"%s\",%s", HOST, PORT);
    println(buffer);
    if (!wait(LINKED))  { return false; }
  }
  if (debug){
    Serial.println(HR);
  }
  sprintf(buffer, "AT+CIPSEND=0,%d", strlen(PATH) + 15);
  println(buffer);
  if (!readln(ans))     { return false; }
  sprintf(buffer, "GET %s HTTP/1.1", PATH);
  println(buffer);
  if (!wait(SEND_OK))   { return false; }
  println(F("AT+CIPSEND=0,19"));
  if (!readln(ans))     { return false; }
  println(F("Host: 192.168.1.1"));
  if (!wait(SEND_OK))   { return false; }
  println(F("AT+CIPSEND=0,24"));
  if (!readln(ans))     { return false; }
  println(F("Connection: keep-alive"));
  if (!wait(SEND_OK))   { return false; }
  println(F("AT+CIPSEND=0,2"));
  if (!readln(ans))     { return false; }
  println(EMPTY_STR);
  if (!wait(SEND_OK))   { return false; }
  if (!readln(ans))     { return false; }
  if (debug){
    Serial.println(HR);
  }
  if (!wait(EMPTY_STR)) { return false; }
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  if (!wait(OK))        { return false; }
  if (debug){
    Serial.println(RESULT);
    Serial.println(ans);
    Serial.println(END);
  }
  return true;
}

boolean wait(const char* result){
  char ans[read_buff_len];
  do{
    if (!readln(ans) || !strcmp(ans, "ERROR")){
      return false;
    }
  }while (strcmp(ans, result));
  return true;
}
 
void println(const char* cmd){
  ESPserial.print(cmd);
  print_rn();
}
 
void println(char* cmd){
  ESPserial.print(cmd);
  print_rn();
}
 
void println(const __FlashStringHelper* cmd){
  ESPserial.print(cmd);
  print_rn();
}

void print_rn(){
  ESPserial.print("\r\n");
  delay(1);
}

boolean readln(char* ans){
  int f = 0, f2, f3;
  boolean eq = false;
  char* exp;
  byte end_length = 2;
  char* end = "\r\n";
  unsigned long ms = millis();
  while (!eq){
    if (!ESPserial.available()){
      if (millis() - ms > read_timeout_ms){
        ans[f] = '\0';
        return false;
      }
      continue;
    }
    ans[f] = ESPserial.read();
    delay(1);
    ans[++f] = '\0';
    f2 = end_length;
    f3 = f;
    eq = true;
    while (f2 && eq){
      if (!f3 || end[--f2] != ans[--f3]){
        eq = false;
      }
    }
  }
  f = 0, f2 = 0;
  while (ans[f2]){
    if (ans[f2] != 10 && ans[f2] != 13){
      ans[f++] = ans[f2];
    }
    f2++;
  }
  ans[f] = '\0';
  if (debug){
    Serial.println(ans);
  }
  return true;
}
