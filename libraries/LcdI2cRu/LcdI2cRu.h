#ifndef LcdI2cRu_h
#define LcdI2cRu_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LcdI2cRu {
  public:
    LcdI2cRu(uint8_t address, uint8_t width, uint8_t height);
    ~LcdI2cRu();
    void init(const char* str);
    String get_str_enc(char* str);
    LiquidCrystal_I2C* lcd;
    void setCursor(int col, int row);
    void printn(int num);
    void clear();
    char** s;
    int c = 0;
    int l = 0;
};

#endif
