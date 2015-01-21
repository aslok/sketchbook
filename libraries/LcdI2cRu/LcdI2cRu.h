#ifndef LcdI2cRu_h
#define LcdI2cRu_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LcdI2cRu {
  public:
    LcdI2cRu(uint8_t address, uint8_t width, uint8_t height);
    ~LcdI2cRu();
    void init(const __FlashStringHelper* str);
    void init(const char* str);
    void createMap();
    void get_str_enc(char* str, char* result);
    void write_enc(char* str);
    void backlight();
    void backlight(boolean state);
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void printn(uint8_t num);
    boolean bl = false;
    char** s;
    uint8_t c = 0;
    uint8_t l = 0;
  private:
    LiquidCrystal_I2C* lcd;
};

#endif
