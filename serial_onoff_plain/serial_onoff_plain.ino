const byte d6Pin = 6;
const byte d7Pin = 7;
const byte d8Pin = 8;
const byte d9Pin = 9;
const byte d10Pin = 10;
const byte d11Pin = 11;
const byte d12Pin = 12;
const byte d13Pin = 13;

const byte DHT22_PIN = 3;
const byte DHT22_VCC = 2;
const byte DHT22_GND = 4;
#include "dht.h"
dht DHT;

void setup(){
  Serial.begin(9600);

  digitalWrite(d6Pin, LOW);
  digitalWrite(d7Pin, LOW);
  digitalWrite(d8Pin, LOW);
  digitalWrite(d9Pin, LOW);
  digitalWrite(d10Pin, LOW);
  digitalWrite(d11Pin, LOW);
  digitalWrite(d12Pin, LOW);
  digitalWrite(d13Pin, LOW);
  pinMode(d6Pin, OUTPUT);
  pinMode(d7Pin, OUTPUT);
  pinMode(d8Pin, OUTPUT);
  pinMode(d9Pin, OUTPUT);
  pinMode(d10Pin, OUTPUT);
  pinMode(d11Pin, OUTPUT);
  pinMode(d12Pin, OUTPUT);
  pinMode(d13Pin, OUTPUT);

  digitalWrite(DHT22_GND, LOW);
  digitalWrite(DHT22_VCC, HIGH);
  pinMode(DHT22_GND, OUTPUT);
  pinMode(DHT22_VCC, OUTPUT);
}

void loop(){
  if (!Serial.available()){
    return;
  }
  char in[4];
  byte f;
  for (f = 0; f < 3; f++){
    while (!Serial.available());
    char inByte = Serial.read();
    /*Serial.print(inByte, DEC);
    Serial.println();*/
    switch (inByte){
      case 0:
      case 13:
      case 10:
        break;
      default:
        /*Serial.print(f);
        Serial.print(" = ");
        Serial.print(inByte, DEC);
        Serial.println();*/
        in[f] = inByte;
    }
  }
  in[f] = '\0';
  byte in_num = atoi(in);
  if (!in_num){
    return;
  }
  /*Serial.print(in_num, DEC);
  Serial.println();*/
  switch (in_num){
    case 1:
      char temp[6];
      char hum[5];
      char data[15];
      DHT.read22(DHT22_PIN);
      dtostrf(DHT.temperature, 4, 1, temp);
      dtostrf(DHT.humidity, 4, 1, hum);
      sprintf(data, "%s℃ - %s%%", temp, hum);
      Serial.println(data);
      break;
    case 60:
      digitalWrite(d6Pin, LOW);
      break;
    case 61:
      digitalWrite(d6Pin, HIGH);
      break;
    case 70:
      digitalWrite(d7Pin, LOW);
      break;
    case 71:
      digitalWrite(d7Pin, HIGH);
      break;
    case 80:
      digitalWrite(d8Pin, LOW);
      break;
    case 81:
      digitalWrite(d8Pin, HIGH);
      break;
    case 90:
      digitalWrite(d9Pin, LOW);
      break;
    case 91:
      digitalWrite(d9Pin, HIGH);
      break;
    case 100:
      digitalWrite(d10Pin, LOW);
      break;
    case 101:
      digitalWrite(d10Pin, HIGH);
      break;
    case 110:
      digitalWrite(d11Pin, LOW);
      break;
    case 111:
      digitalWrite(d11Pin, HIGH);
      break;
    case 120:
      digitalWrite(d12Pin, LOW);
      break;
    case 121:
      digitalWrite(d12Pin, HIGH);
      break;
    case 130:
      digitalWrite(d13Pin, LOW);
      break;
    case 131:
      digitalWrite(d13Pin, HIGH);
      break;
  }
}
