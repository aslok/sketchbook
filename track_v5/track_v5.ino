boolean debug = false;
boolean loop_debug = false;
boolean read_debug = false;
boolean print_debug = false;

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

//#include "MemoryFree.h"

const int read_buff_len = 1024;
const byte tmp_buff_len = 64;
const unsigned long read_timeout_ms = 10000;

const char* AT                      = "AT";
const char* OK                      = "OK";
const char* SEND_OK                 = "SEND OK";
const char* NO_CHANGE               = "no change";
const char* EMPTY_STR               = "";
const char* END                     = "\r\n";

int integ2 = 12;

void setup(){  
  debug = true;
  loop_debug = true;
  //read_debug = true;
  //print_debug = true;

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

  nginx(ans);

  /*int buffer;
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
  }*/
}

boolean nginx(char* ans){
  const __FlashStringHelper* HTML     = F("<script>var g=0,h=0;if(void 0!==window.DeviceMotionEvent){var i=0,j=0;window.ondeviceorientation=function(b){g=Math.round(b.beta);h=Math.round(b.gamma)};var k=function(){var b=60-(0>h?-1*h:h);-40>b?b=-40:40<b?b=40:20>b&&-20<b&&(b=0);var b=parseInt(b/(40/255)),c=parseInt(100*(g/30))/100;1<c?c=1:-1>c&&(c=-1);-0.3<c&&0.3>c&&(c=0);var e=b,f=b;c&&(0<c?0==b?(e=parseInt(255*c),f=parseInt(-255*c)):(e=b,f=(0<b?b:-1*b)-parseInt(255*c)):0==b?(e=parseInt(255*c),f=parseInt(-255*c)):(e=(0<b?b:-1*b)-parseInt(-255*c),f=b));if(i!=e||j!=f)i=e,j=f,b=new XMLHttpRequest,b.open('POST','data.php',!0),b.setRequestHeader('Content-Type','application/x-www-form-urlencoded'),b.send('speed_left='+encodeURIComponent(e)+'&speed_right='+encodeURIComponent(f));window.setTimeout(k,500,null,null)};k()};</script>");
  const __FlashStringHelper* HEADERS1 = F("HTTP/1.1 200 OK");
  const __FlashStringHelper* HEADERS2 = F("Content-Type: text/html");
  const __FlashStringHelper* HEADERS3 = F("Connection: keep-alive");
  const __FlashStringHelper* HEADERS4 = F("Accept-Ranges: bytes");

  const __FlashStringHelper* START    = F("VVVVVVVVVVVVVVVVVVVVV");
  const __FlashStringHelper* HR       = F("---------------------");
  const __FlashStringHelper* RESULT   = F("=====================");
  const __FlashStringHelper* END      = F("^^^^^^^^^^^^^^^^^^^^^");

  char buffer[tmp_buff_len];

  if (debug){
    Serial.println(START);
  }

  println(AT);
  if (!wait(AT, ans))   { return false; }
  if (!wait(OK, ans))   { return false; }
  println(F("AT+CIPMODE?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, tmp_buff_len);
  if (!wait(OK, ans))   { return false; }
  if (strcmp(buffer, "+CIPMODE:0")){
    println(F("AT+CIPMODE=0"));
    if (!wait(OK, ans))   { return false; }
  }
  println(F("AT+CIPMUX?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, tmp_buff_len);
  if (!wait(OK, ans))   { return false; }
  if (strcmp(buffer, "+CIPMUX:1")){
    println(F("AT+CIPMUX=1"));
    if (!wait(OK, ans))   { return false; }
  }
  println(F("AT+CWMODE?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, tmp_buff_len);
  if (!wait(OK, ans))   { return false; }
  if (strcmp(buffer, "+CWMODE:2")){
    println(F("AT+CWMODE=2"));
    if (!wait(OK, ans))   { return false; }
  }
  println(F("AT+CWSAP=\"Drive\",\"\",10,0"));
  if (!wait(OK, ans))   { return false; }
  println(F("AT+CIPSERVER=0"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  println(F("AT+CIPSERVER=1,80"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }

  while(true){
    if (!wait("Link", ans)){
      continue;
    }
    boolean end = false;
    while (!end){
      if (!readln(ans)){
        end = true;
      }else if (strstr(ans, "GET / HTTP/1.1")){
        end = true;
        if (!wait(OK, ans)) { return false; }

        sprintf(ans, "AT+CIPSEND=0,%d", F_strlen(HEADERS1) + 2);
        println(ans);
        if (!readln(ans))   { return false; }
        println(HEADERS1);
        if (!wait(SEND_OK, ans)) { return false; }
        sprintf(ans, "AT+CIPSEND=0,%d", F_strlen(HEADERS2) + 2);
        println(ans);
        if (!readln(ans))   { return false; }
        println(HEADERS2);
        if (!wait(SEND_OK, ans)) { return false; }
        sprintf(ans, "AT+CIPSEND=0,%d", F_strlen(HEADERS3) + 2);
        println(ans);
        if (!readln(ans))   { return false; }
        println(HEADERS3);
        if (!wait(SEND_OK, ans)) { return false; }
        sprintf(ans, "AT+CIPSEND=0,%d", F_strlen(HEADERS4) + 2);
        println(ans);
        if (!readln(ans))   { return false; }
        println(HEADERS4);
        if (!wait(SEND_OK, ans)) { return false; }
        sprintf(ans, "Content-Length: %d", F_strlen(HTML));
        sprintf(buffer, "AT+CIPSEND=0,%d", strlen(ans) + 2);
        println(buffer);
        if (!readln(buffer)){ return false; }
        println(ans);
        if (!wait(SEND_OK, ans)) { return false; }
        println(F("AT+CIPSEND=0,2"));
        if (!readln(ans))   { return false; }
        println(EMPTY_STR);
        if (!wait(SEND_OK, ans)) { return false; }
        sprintf(ans, "AT+CIPSEND=0,%d", F_strlen(HTML) + 2);
        println(ans);
        if (!readln(ans))   { return false; }
        println(HTML);
        if (!wait(SEND_OK, ans)) { return false; }
      }else if (strstr(ans, "POST /data.php HTTP/1.1")){
        end = true;
        if (!wait(OK, ans)) { return false; }
        if (!readln(ans))     { return false; }
        if (!readln(ans))     { return false; }
        strtok(ans, "=&");
        strncpy(buffer, strtok(NULL, "=&"), tmp_buff_len);
        Serial.println(buffer);
        strtok(NULL, "=&");
        strncpy(buffer, strtok(NULL, "=&"), tmp_buff_len);
        Serial.println(buffer);
      }
    }
    println(F("AT+CIPCLOSE=0"));
    if (!wait(OK, ans))   { return false; }
  }

  return true;
}

boolean wait(const char* result, char* ans){
  if (debug){
    Serial.print(F("wait("));
    Serial.print(result);
    Serial.println(F(")"));
  }
  do{
    if (!readln(ans) || !strcmp(ans, "ERROR")){
      if (debug){
        Serial.println(F("WAIT ERRROR"));
      }
      return false;
    }
  }while (strcmp(ans, result));
  return true;
}

/*boolean wait(const char* result){
}*/

boolean readln(char* ans){
  if (read_debug){
    Serial.println(F("readln()"));
  }
  unsigned int f = 0;
  unsigned long ms = millis();
  do{
    while (!ESPserial.available()){
      if (millis() - ms < read_timeout_ms){
        continue;
      }
      ans[f] = '\0';
      if (read_debug){
        Serial.println(F("READ ERROR"));
        Serial.print("f = ");
        Serial.println(f);
        Serial.print("ans = ");
        Serial.println(ans);
      }
      return false;
    }
    ans[f++] = ESPserial.read();
    //delay(1);
    if (read_debug){
      Serial.print(F("READ: "));
      Serial.println(ans[f - 1], DEC);
      Serial.println(ans[f - 1]);
      Serial.print("f = ");
      Serial.println(f);
      Serial.println(EMPTY_STR);
    }
    if (f < 2 || END[0] != ans[f - 2] || END[1] != ans[f - 1]){
      continue;
    }
    while (f > 0 && (ans[f - 1] == '\r' || ans[f - 1] == '\n')){
      if (read_debug){
        Serial.print(F("f = "));
        Serial.println(f);
        Serial.print(F("ans[f - 1] = "));
        Serial.println(ans[f - 1]);
      }
      f--;
    }
    if (read_debug){
      Serial.print(F("f = "));
      Serial.println(f);
    }
    ans[f] = '\0';
    break;
  }while (true);
  if (debug || read_debug){
    Serial.println(ans);
  }
  return true;
}

void println(const char* cmd){
  if (print_debug){
    Serial.print(F("println("));
    Serial.print(cmd);
    Serial.println(F(")"));
  }
  ESPserial.print(cmd);
  print_rn();
}
 
void println(char* cmd){
  if (print_debug){
    Serial.print(F("println("));
    Serial.print(cmd);
    Serial.println(F(")"));
  }
  ESPserial.print(cmd);
  print_rn();
}
 
void println(const __FlashStringHelper* cmd){
  if (print_debug){
    Serial.print(F("println("));
    Serial.print(cmd);
    Serial.println(F(")"));
  }
  ESPserial.print(cmd);
  print_rn();
}

void print_rn(){
  ESPserial.print(F("\r\n"));
  delay(1);
}

/*boolean wget(char* ans){
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
  if (!wait(OK, ans))        { return false; }
  println(F("AT+CIFSR"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK, ans))        { return false; }
  if (!strcmp(buffer, "0.0.0.0")){
    sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"", SSID, SSID_PASS);
    println(buffer);
    if (!wait(OK, ans))      { return false; }
  }
  println(F("AT+CIPMODE?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK, ans))        { return false; }
  if (strcmp(buffer, "+CIPMODE:0")){
    println(F("AT+CIPMODE=0"));
    if (!wait(OK, ans))      { return false; }
  }
  println(F("AT+CIPMUX?"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK, ans))        { return false; }
  if (strcmp(buffer, "+CIPMUX:1")){
    println(F("AT+CIPMUX=1"));
    if (!wait(OK, ans))      { return false; }
  }
  println(F("AT+CIPSTATUS"));
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  strncpy(buffer, ans, read_buff_len);
  if (!wait(OK, ans))        { return false; }
  sprintf(tmp, "+CIPSTATUS:0,\"TCP\",\"%s\",%s,0", HOST, PORT);
  if (strcmp(buffer, tmp)){
    sprintf(buffer, "AT+CIPSTART=0,\"TCP\",\"%s\",%s", HOST, PORT);
    println(buffer);
    if (!wait(LINKED, ans))  { return false; }
  }
  if (debug){
    Serial.println(HR);
  }
  sprintf(buffer, "AT+CIPSEND=0,%d", strlen(PATH) + 15);
  println(buffer);
  if (!readln(ans))     { return false; }
  sprintf(buffer, "GET %s HTTP/1.1", PATH);
  println(buffer);
  if (!wait(SEND_OK, ans))   { return false; }
  println(F("AT+CIPSEND=0,19"));
  if (!readln(ans))     { return false; }
  println(F("Host: 192.168.1.1"));
  if (!wait(SEND_OK, ans))   { return false; }
  println(F("AT+CIPSEND=0,24"));
  if (!readln(ans))     { return false; }
  println(F("Connection: keep-alive"));
  if (!wait(SEND_OK, ans))   { return false; }
  println(F("AT+CIPSEND=0,2"));
  if (!readln(ans))     { return false; }
  println(EMPTY_STR);
  if (!wait(SEND_OK, ans))   { return false; }
  if (!readln(ans))     { return false; }
  if (debug){
    Serial.println(HR);
  }
  if (!wait(EMPTY_STR, ans)) { return false; }
  if (!readln(ans))     { return false; }
  if (!readln(ans))     { return false; }
  if (!wait(OK, ans))        { return false; }
  if (debug){
    Serial.println(RESULT);
    Serial.println(ans);
    Serial.println(END);
  }
  return true;
}

boolean wait(const char* result){
  char ans[read_buff_len];
  return wait(result, ans);
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
}*/

unsigned int F_strlen(const __FlashStringHelper* str){
  char* ptr = (char*) str;
  unsigned int cur_chr;
  for (
    cur_chr = 0;
    (char) pgm_read_byte_near(ptr + cur_chr++);
  );
  return --cur_chr;
}
