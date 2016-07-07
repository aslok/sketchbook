const byte ledPin = 13;

const byte DHT22_PIN = 3;
const byte DHT22_VCC = 2;
const byte DHT22_GND = 4;
#include "dht.h"
dht DHT;

char* str = "";
byte str_pos = 0;
boolean chr_done = true;
byte chr_pos;
char chr;

void print(){
  if (!chr_done){
    print_enc(0);
    return;
  }
  if (!str[str_pos]){
    str = "";
    str_pos = 0;
    return;
  }
  print_enc(str[str_pos++]);
}

void print_enc(char print_chr){
  if (chr_done){
    chr_done = false;
    chr = print_chr;
    chr_pos = 0;
  }
  if (bitRead(chr, chr_pos++)){
    Serial.print(1);
  }
  Serial.flush();
  if (chr_pos == 8){
    chr_done = true;
  }
}

void setup(){
  Serial.begin(9600);

  digitalWrite(ledPin, LOW);
  pinMode(ledPin, OUTPUT);

  digitalWrite(DHT22_GND, LOW);
  digitalWrite(DHT22_VCC, HIGH);
  pinMode(DHT22_GND, OUTPUT);
  pinMode(DHT22_VCC, OUTPUT);
}

void loop(){
  if (Serial.available() > 0){
    int inByte = Serial.read();
    //Serial.println(inByte);
    switch (inByte){
      // echo -n 0 > /dev/ttyUSB4
      case 48:
      case 250:
        print();
        break;
      // echo -n 1 > /dev/ttyUSB4
      case 49:
      case 253:
        char temp[6];
        char hum[5];
        char data[15];
        DHT.read22(DHT22_PIN);
        dtostrf(DHT.temperature, 4, 1, temp);
        dtostrf(DHT.humidity, 4, 1, hum);
        sprintf(data, "%s℃ - %s%%", temp, hum);
        str = data;
        Serial.flush();
        break;
      // echo -n 2 > /dev/ttyUSB4
      //case 250:
      //  break;
      // echo -n 3 > /dev/ttyUSB4
      //case 253:
      //  break;
      // echo -n 4 > /dev/ttyUSB4
      case 251:
        digitalWrite(ledPin, LOW);
        break;
      // echo -n 5 > /dev/ttyUSB4
      case 255:
        digitalWrite(ledPin, HIGH);
        break;
      // echo -n 6 > /dev/ttyUSB4
      //case 251:
      //  break;
      // echo -n 7 > /dev/ttyUSB4
      //case 255:
      //  break;
      // echo -n 8 > /dev/ttyUSB4
      //case 250:
      //  break;
      // echo -n 9 > /dev/ttyUSB4
      //case 253:
      //  break;
      // echo -n 10 > /dev/ttyUSB4
      case 165:
        break;
      // echo -n 11 > /dev/ttyUSB4
      case 173:
        break;
      // echo -n 12 > /dev/ttyUSB4
      //case 165:
      //  break;
      // echo -n 13 > /dev/ttyUSB4
      //case 173:
      //  break;
      // echo -n 14 > /dev/ttyUSB4
      case 181:
        break;
      // echo -n 15 > /dev/ttyUSB4
      case 189:
        break;
      // echo -n 16 > /dev/ttyUSB4
      //case 181:
      //  break;
      // echo -n 17 > /dev/ttyUSB4
      //case 189:
      //  break;
      // echo -n 18 > /dev/ttyUSB4
      //case 165:
      //  break;
      // echo -n 19 > /dev/ttyUSB4
      //case 173:
      //  break;
      // echo -n 20 > /dev/ttyUSB4
      case 74:
        str = "Привет!!";
        break;
      // echo -n 21 > /dev/ttyUSB4
      case 90:
        str = "Как дела?";
        break;
      // echo -n 22 > /dev/ttyUSB4
      //case 74:
      //  break;
      // echo -n 23 > /dev/ttyUSB4
      //case 90:
      //  break;
      // echo -n 24 > /dev/ttyUSB4
      case 106:
        str = "Проверка связи";
        break;
    }
  }
}
