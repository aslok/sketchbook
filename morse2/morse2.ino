/*
  Телеграфная азбука
 Современная телеграфная азбука (система кодировки символов короткими и
 длинными посылками для передачи их по линиям связи, известная как
 «код Морзе» или «морзянка»)

 В среднем 60 знаков в минуту
 В среднем 3 символа в секунду (350ms на символ), 150 ms точка

 За единицу времени принимается длительность одной точки. Длительность
 тире равна трём точкам. Пауза между элементами одного знака — одна точка,
 между знаками в слове — 3 точки, между словами — 7 точек

 created 15.01.2015
 by Fust Vitaliy
 */

// Sketch uses 6 784 bytes (21%) of program storage space. Maximum is 32 256 bytes.
// Global variables use 1 094 bytes (53%) of dynamic memory, leaving 954 bytes for local variables. Maximum is 2 048 bytes.

// Строка для вывода
const char str[] = "1 SOS? SOS! 2 SOS? SOS!";

// Флаг для отладки через порт
const boolean debug = true;
// Дополнительные опции отладки
const boolean debug_t = false;

// Продолжительность 'точки'
// int ms = 150;
const int ms = 200;
// Служебный пин
const int pin = 13;

// Строка для вывода
char out[sizeof(str) / sizeof(char)];


void dump(String& msg) {
  if (debug) {
    Serial.println(msg.c_str());
  }
}

void dump(unsigned int chr) {
  if (debug) {
    if (debug_t)
      Serial.print('<');
    Serial.print(chr);
    if (debug_t)
      Serial.print('>');
    Serial.println();
  }
}

void dump(int& chr) {
  if (debug) {
    if (debug_t)
      Serial.print('<');
    Serial.print(chr);
    if (debug_t)
      Serial.print('>');
    Serial.println();
  }
}

void dump(char chr) {
  if (debug) {
    if (debug_t)
      Serial.print('<');
    Serial.print(chr);
    if (debug_t)
      Serial.print('>');
    Serial.println();
  }
}

void dump(const char* chr) {
  if (debug) {
    if (debug_t)
      Serial.print('<');
    Serial.print(chr);
    if (debug_t)
      Serial.print('>');
    Serial.println();
  }
}

void dump(char chr[]) {
  if (debug) {
    if (debug_t)
      Serial.print('<');
    Serial.print(chr);
    if (debug_t)
      Serial.print('>');
    Serial.println();
  }
}

void dot() {
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
}

void dash() {
  digitalWrite(pin, HIGH);
  delay(ms * 3);
  digitalWrite(pin, LOW);
}

/*
  {
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'z', 'x', 'c', 'v', 'b', 'n', 'm'
  }
  ,
  {
    '--.-', '.--', '.', '.-.', '-', '-.--', '..-', '..', '---', '.--.',
    '.-', '...', '-..', '..-.', '--.', '....', '.---', '-.-', '.-..',
    '--..', '-..-', '-.-.', '...-', '-...', '-.', '--'
  }
  {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '.', ',', ':', ';', '(', ')', '\'', '`', '@',
    '"', '-', '—', '!', '?', '§', ' '
  }
  ,
  {
    '.----', '..---', '...--', '....-', '.....', '-....', '--...', '---..', '----.', '-----',
    '......', '.-.-.-', '---...', '-.-.-.', '-.--.-', '-.--.-', '.----.', '.----.', '.--.-.',
    '.-..-.', '-....-', '-....-', '--..--', '..--..', '-...-', '|'
  }
*/

void setup() {
  pinMode(pin, OUTPUT);
  if (debug) {
    Serial.begin(9600);
  }
}

void loop() {
}

