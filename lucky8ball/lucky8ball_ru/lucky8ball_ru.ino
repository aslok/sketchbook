// Либа для датчика ускорения
#include "Wire.h"
#include "ADXL345.h"

// Либы для экранчика
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "Cyruit_PCD8544.h"
#include "Cyruit.h"

// Либа для режима сна
#include "LowPower.h"

const boolean DEBUG = false;

// Номер вывода для прерывания сна
const byte INTERRUPTPIN = 2;
// Номер вывода для управления подсветкой
const byte GND33PIN = 9;
// Эмулируем с помощью ШИМ ~3.3 вольта, относительно плюса который ~5 вольт
// 68pwm_negative = 255pwm_positive - 3.3v_out / (4.5v_in / 255pwm)
const byte GND33PWM = 68;
// Значение для выключения подсветки, потому что 0 = 5V, но 255 = 0V
// 255pwm_positive
const byte VCC = 255;

// Объект датчика
ADXL345 adxl;

// Объекты экранчика
// Низкоуровневый
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
// Высокоуровневый
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);

// Типа починил старый шарик
// Самая длинная строка 31 символ (кирилица х2, UTF-8)
// Включая ноль \0 в конце строки = 32
const char PROGMEM answers[][32] = {
  "уверенное\nДА",
  "конечно\nДА",
  " ВПЕРЕД!",
  "ДА",
  "это\nнеплохо",
  "это\nвозможно",
  "да,\nно позднее",
  "я думаю,\nхорошо",
  "быть может",
  "я\nне уверен",
  "кто  знает",
  "я думаю,\nне стоит",
  "слишком\nрано",
  "не сейчас",
  "не надейся\nна это",
  "ни в коем\nслучае",
  "ты шутишь?",
  "не делай\nэтого",
  "даже\nне думай",
  "забудь\nоб этом"
};


// Ф-ия выполняется при первом запуске
void setup(void) {
  // Помечаем вывод прерывания как вход
  pinMode(INTERRUPTPIN, INPUT);

  // Устанавливаем яркость подсветки
  analogWrite(GND33PIN, GND33PWM);
  // Помечаем вывод подсветки как выход
  pinMode(GND33PIN, OUTPUT);
  
  // Запускаем экранчик
  lcd.begin();
  // Устанавливаем контраст
  lcd.setContrast(61);
  // Переворачиваем
  lcd.setRotation(2);
  
  // Запускаем датчик
  adxl.powerOn();
  // В сонном режиме
  adxl.setLowPower(true);
  // Активность будет всё что больше "80"
  adxl.setActivityThreshold(80);
  // Отсутствие активности - когда меньше "18"
  adxl.setInactivityThreshold(80);
  // Если нет активности - через 1 сек засыпаем
  adxl.setTimeInactivity(1);
  // Оси по которым проверяем активность
  adxl.setActivityX(true);
  adxl.setActivityY(true);
  adxl.setActivityZ(true);
  // Оси по которым проверяем отсутствие активности
  adxl.setInactivityX(true);
  adxl.setInactivityY(true);
  adxl.setInactivityZ(true);
  // При активности датчик подаст плюс на свой первый вывод
  adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN);
  // Но сейчас нам это не нужно - ещё не спим
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT, false);
  // При остутствии активности датчик подаст плюс на свой первый вывод
  adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);
  // Как раз это сейчас актуально
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, true);
}

// На горшок и спать - запускаем когда хотим, из loop()
void sleep(){
  // Выключаем экранчик
  lcd.command(PCD8544_FUNCTIONSET | PCD8544_POWERDOWN);
  // Выключаем подсветку (без ШИМ, чтоб выключить ШИМ)
  digitalWrite(GND33PIN, VCC);
  // Отсутсвие активности не интересует
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, false);
  // При активности датчик подаст плюс на свой первый вывод
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT, true);
  // Ставим будильник - когда будет плюс на втором выводе
  // Вывод №2 генерирует прерывание №0, вывод №3 - соответственно №1
  attachInterrupt(0, wake_up, HIGH);
  // Засыпаем, выключаем что можно
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  // Продолжаем после пробуждения - выключаем будильник
  detachInterrupt(0); 
  // Активность не интересует
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT, false);
  // Отсутсвие активности сейчас актуально
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, true);
  // Включаем подсветку экранчика
  analogWrite(GND33PIN, GND33PWM);
  // Включаем экранчик
  lcd.command(PCD8544_FUNCTIONSET);
  lcd.command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

// Заглушка, но нужна ф-ии attachInterrupt
void wake_up(){
}

// Инициализируем рандомайзер
void make_seed(){
  int x,y,z;
  // Читаем показания датчика
  adxl.readAccel(&x, &y, &z);
  // Генерируем зерно
  randomSeed(millis() + x + y + z);
}

void print_answer(){
  // Очищаем дисплей
  display.clear();
  // Генерируем зерно для рандомайзера
  make_seed();
  // Кол-во строк
  byte answers_cnt = sizeof(answers) / sizeof(answers[0]) - 1;
  // Буфер для хранения ответа
  char buf[sizeof(answers[0])];
  // Копируем случайную строку в буфер
  strcpy_P(buf, answers[random(answers_cnt)]);
  // Считаем кол-во подстрок разделенных переносом
  byte count = chr_cnt(buf, '\n') + 1;
  // Текущая позиция экрана по Y, там максимум 6 строк
  byte line = ((6 - count) / 2);
  // Указатель на подстроку
  char *sub_str = strtok(buf, "\n");
  // Рубим строку на подстроки
  while (sub_str) {
    display.print(sub_str, 1, line++, 12);
    sub_str = strtok(NULL, "\n");
  }
  // Ждем 5 сек
  delay(5000);
}

// Считаем кол-во вхождений символа в строку
byte chr_cnt(char* str, char chr){
  byte cnt = 0;
  for (byte pos = 0; str[pos++]; str[pos] == chr && ++cnt);
  return cnt;
}

// Ф-ия выполняется по кругу всегда когда не спим (наше всё)
void loop(void){
  print_answer();

  if (!DEBUG){
    // Если датчик не докладывает о отсутствии активности - ждем-с
    while(!adxl.triggered(adxl.getInterruptSource(), ADXL345_INACTIVITY));
    // Засыпаем
    sleep();
  }
}

