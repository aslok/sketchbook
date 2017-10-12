boolean debug = false;

const char* SSID = "wifi3r";
const char* SSID_PASS = "wifi3rpassphrasehackmeplease";

#include "SoftwareSerial.h"
SoftwareSerial ESPserial(2, 3); // RX | TX
 
void setup(){
  //debug = true;

  Serial.begin(9600);
  ESPserial.begin(9600);
}

void loop(){
  char ans[128];
  if (!wget(ans)){
    return;
  }
  Serial.println(ans);
  delay(2000);
}

boolean wget(char* ans){
  const char* OK = "OK";
  const char* SEND_OK = "SEND OK";
  const __FlashStringHelper* START  = F("VVVVVVVVVVVVVVVVVVVVV");
  const __FlashStringHelper* HR     = F("---------------------");
  const __FlashStringHelper* RESULT = F("=====================");
  const __FlashStringHelper* END    = F("^^^^^^^^^^^^^^^^^^^^^");

  char buffer[128];

  if (debug){
    Serial.println(START);
  }
  println(F("AT"));
  if (!wait(OK)) { return false; }
  println(F("AT+CIFSR"));
  readln(ans);
  readln(ans);
  strncpy(buffer, ans, 128);
  if (!wait((OK))) { return false; };
  if (!strcmp(buffer, "0.0.0.0")){
    sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"", SSID, SSID_PASS);
    println(buffer);
    if (!wait((OK))) { return false; };
  }
  println(F("AT+CIPMODE?"));
  readln(ans);
  readln(ans);
  strncpy(buffer, ans, 128);
  if (!wait((OK))) { return false; };
  if (strcmp(buffer, "+CIPMODE:0")){
    println(F("AT+CIPMODE=0"));
    if (!wait((OK))) { return false; };
  }
  println(F("AT+CIPMUX?"));
  readln(ans);
  readln(ans);
  strncpy(buffer, ans, 128);
  if (!wait((OK))) { return false; };
  if (strcmp(buffer, "+CIPMUX:1")){
    println(F("AT+CIPMUX=1"));
    if (!wait((OK))) { return false; };
  }
  println(F("AT+CIPSTATUS"));
  readln(ans);
  readln(ans);
  readln(ans);
  strncpy(buffer, ans, 128);
  if (!wait((OK))) { return false; };
  if (strcmp(buffer, "+CIPSTATUS:0,\"TCP\",\"192.168.1.1\",80,0")){
    println(F("AT+CIPSTART=0,\"TCP\",\"192.168.1.1\",80"));
    if (!wait(("Linked"))) { return false; };
  }
  if (debug){
    Serial.println(HR);
  }
  println(F("AT+CIPSEND=0,24"));
  readln(ans);
  println(F("GET /data.php HTTP/1.1"));
  if (!wait((SEND_OK))) { return false; };
  println(F("AT+CIPSEND=0,19"));
  readln(ans);
  println(F("Host: 192.168.1.1"));
  if (!wait((SEND_OK))) { return false; };
  println(F("AT+CIPSEND=0,24"));
  readln(ans);
  println(F("Connection: keep-alive"));
  if (!wait((SEND_OK))) { return false; };
  println(F("AT+CIPSEND=0,2"));
  readln(ans);
  println("");
  if (!wait((SEND_OK))) { return false; };
  readln(ans);
  if (debug){
    Serial.println(HR);
  }
  if (!wait((""))) { return false; };
  readln(ans);
  readln(ans);
  strncpy(buffer, ans, 128);
  wait(OK);
  strncpy(ans, buffer, 128);
  if (debug){
    Serial.println(RESULT);
    Serial.println(ans);
    Serial.println(END);
  }
  return true;
}

boolean wait(const char* result){
  char ans[128];
  do{
    readln(ans);
    if (!strcmp(ans, "ERROR")){
      return false;
    }
  }while (strcmp(ans, result));
  return true;
}
 
void println(char* cmd){
  ESPserial.print(cmd);
  ESPserial.print("\r\n");
}
 
void println(const __FlashStringHelper* cmd){
  ESPserial.print(cmd);
  ESPserial.print("\r\n");
}

void readln(char* ans){
  int f = 0, f2, f3;
  boolean eq = false;
  char* exp;
  byte end_length = 2;
  char* end = "\r\n";
  while (!eq){
    if (!ESPserial.available()){
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
}
