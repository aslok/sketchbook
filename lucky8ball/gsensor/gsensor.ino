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

// Номер вывода для прерывания сна
#define INTERRUPTPIN 2
// Номер вывода для управления подсветкой
#define GND33PIN 9
// Яркость подсветки
// Эмулируем с помощью ШИМ ~3.3 вольта, относительно плюса который ~5 вольт
// 68pwm_negative = 255pwm_positive - 3.3v_out / (4.5v_in / 255pwm)
#define GND33PWM 68
// Значение для выключения подсветки, потому что 0 = 5V, но 255 = 0V
// 255pwm_positive
#define VCC 255

// Объект датчика
ADXL345 adxl;

// Объекты экранчика
Cyruit_PCD8544 lcd = Cyruit_PCD8544(3, 4, 5, 6, 7);
Cyruit display = Cyruit(&lcd, 84, 48, 6, 8);

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
  
  // Запускаем датчик
  adxl.powerOn();
  // В сонном режиме
  adxl.setLowPower(true);
  // Активность будет всё что больше "80"
  adxl.setActivityThreshold(80);
  // Отсутствие активности - когда меньше "18"
  adxl.setInactivityThreshold(18);
  // Если нет активности - через 15 сек засыпаем
  adxl.setTimeInactivity(15);
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

// Ф-ия выполняется по кругу всегда когда не спим (наше всё)
void loop(void){
  // Читаем показания датчика
  int x,y,z;  
  adxl.readAccel(&x, &y, &z);
  // Выводим показания на экран
  display.print('x', 2, 0);
  display.print('y', 2, 1);
  display.print('z', 2, 2);
  display.print(x, -5, 0, 4);
  display.print(y, -5, 1, 4);
  display.print(z, -5, 2, 4);

  // Если датчик докладывает о отсутствии активности
  if(adxl.triggered(adxl.getInterruptSource(), ADXL345_INACTIVITY)){
    // Засыпаем
    sleep();
  }
}

