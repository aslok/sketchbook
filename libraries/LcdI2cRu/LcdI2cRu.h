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
    void get_str_enc(char* str, char* result);
    void backlight();
    void backlight(boolean state);
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void setCursor(uint8_t col = 32);
    void printn(uint8_t num);
    boolean bl = false;
    char** s;
    uint8_t c = 0;
    uint8_t l = 0;
    char scr[33];
    char scr_h[65];
    uint8_t scr_pos;
    uint8_t char_map[8];
  private:
    void get_next_scr(uint8_t num, char& next_scr);
    void clear_screen();
    LiquidCrystal_I2C* lcd;
    char* abc;
    uint8_t** ru;
    uint8_t* ru_num;
    uint8_t ru_cnt;
    uint8_t* en;
    uint8_t* en_num;
    uint8_t en_cnt;
    char null_char = 0;
};

#endif
