#ifndef CyrI2c_h
#define CyrI2c_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class CyrI2c {
  public:
    CyrI2c(uint8_t address, uint8_t width, uint8_t height);
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
    void print(char chr);
    void print(char* str);
    void printn(uint8_t num, int8_t position);
    void print(char chr, int8_t position);
    void print(char* str, int8_t position);
    void printn(uint8_t num, int8_t position, uint8_t go_ln);
    void print(char chr, int8_t position, uint8_t go_ln);
    void print(char* str, int8_t position, uint8_t go_ln);
    void ln(uint8_t row);
    boolean bl = false;
    char** s;
    uint8_t c = 0;
    uint8_t l = 0;
    char scr[33];
    char scr_h[65];
    uint8_t scr_pos;
    uint8_t char_map[8];
  private:
    void get_next_scr(char* str, char& next_scr);
    void write_str_enc(char* str, char* lcd);
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
