#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

// Software SPI (slower updates, more flexible pin options):
// D7 - LCD 1 - reset (RST)
// D6 - LCD 2 - chip select (CS)
// D5 - LCD 3 - Data/Command select (D/C)
// D4 - LCD 4 - Serial data out (DIN)
// D3 - LCD 5 - Serial clock out (SCLK)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

const byte PROGMEM logoBmp[] =
{
  B11111111, B11111111, B10000000,
  B11111111, B11111111, B10000000,
  B11111111, B11111111, B10000000,
  B11111100, B00000011, B10000000,
  B11111000, B00000001, B10000000,
  B11111100, B00000011, B10000000,
  B11111111, B11000011, B10000000,
  B11111111, B10000111, B10000000,
  B11111111, B10001111, B10000000,
  B11111111, B00001111, B10000000,
  B11111110, B00011111, B10000000,
  B11111110, B00011111, B10000000,
  B11111100, B00111111, B10000000,
  B11111100, B01111111, B10000000,
  B11111000, B00000011, B10000000,
  B11111000, B00000001, B10000000
};


void setup()   {
  Serial.begin(9600);

  // Инициализация дисплея
  display.begin();

  // Очищаем дисплей
  display.clearDisplay();
  display.display();

  // Устанавливаем контраст
  display.setContrast(51);
  delay(1000);
}


void loop()
{
  // Рисуем заранее подготовленное лого
  // Подготовлен массив из 16 пар байтов
  // каждый байт состоит из 8 битов, соответсвенно
  // получаем матрицу 16х16 битов, 1-черный цвет, 0-белый цвет
  display.drawBitmap(LCDWIDTH/2-8, LCDHEIGHT/2-8, logoBmp, 24, 16, BLACK); // x, y, logo, w, h, color
  display.display();
  delay(1000);
  // Рисуем несколько пикселей (точек)
  display.drawPixel(0, 0, BLACK);
  display.drawPixel(1, 1, BLACK);
  display.drawPixel(2, 2, WHITE); // Посередине белый пиксель
  display.drawPixel(3, 3, BLACK);
  display.drawPixel(4, 4, BLACK);
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем диагональ
  display.drawLine(0, LCDHEIGHT-1, LCDWIDTH, 0, BLACK); // x0, y0, x1, y1, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Для рисования вертикальных и горизонтальных линий лучше использовать
  // более быстрые функции
  display.drawFastVLine(LCDWIDTH/2, 0, LCDHEIGHT, BLACK); // x, y, h, color
  display.drawFastHLine(0, LCDHEIGHT/2, LCDWIDTH, BLACK); //x, y, w, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем прямоугольник
  display.drawRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, BLACK); // x, y, w, h, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный прямоугольник
  display.fillRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, BLACK); // x, y, w, h, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Закрашиваем весь дисплей
  display.fillScreen(BLACK);
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем окружность
  display.drawCircle(LCDWIDTH/2, LCDHEIGHT/2, LCDHEIGHT/2, BLACK); // x, y, r, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенную окружность
  display.fillCircle(LCDWIDTH/2, LCDHEIGHT/2, LCDHEIGHT/2, BLACK); // x, y, r, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем треугольник
  display.drawTriangle(LCDWIDTH/4, LCDHEIGHT/4, 3*LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, 3*LCDHEIGHT/4, BLACK); // x0, y0, x1, y1, x2, y2, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный треугольник
  display.fillTriangle(LCDWIDTH/4, LCDHEIGHT/4, 3*LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, 3*LCDHEIGHT/4, BLACK); // x0, y0, x1, y1, x2, y2, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем прямоугольник с закругленными углами
  display.drawRoundRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, 10, BLACK); // x, y, w, h, r, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный прямоугольник с закругленными углами
  display.fillRoundRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, 10, BLACK); // x, y, w, h, r, colordisplay.display();
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем заранее подготовленное лого
  // Подготовлен массив из 16 пар байтов
  // каждый байт состоит из 8 битов, соответсвенно
  // получаем матрицу 16х16 битов, 1-черный цвет, 0-белый цвет
  display.drawBitmap(LCDWIDTH/2-8, LCDHEIGHT/2-8, logoBmp, 24, 16, BLACK); // x, y, logo, w, h, color
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);

  // Выведем текст
  // Устанавливаем курсор
  display.setCursor(0, 0);
  // Устанавливаем цвет текста
  display.setTextColor(BLACK);
  // Устанавливаем размер текста
  display.setTextSize(1);
  // Выводим текст
  display.write('Z');
  display.write('e');
  display.write('l');
  display.write('e');
  display.write('c');
  display.write('t');
  display.write('r');
  display.write('o');
  display.display();
  delay(1000);

  // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);
}
