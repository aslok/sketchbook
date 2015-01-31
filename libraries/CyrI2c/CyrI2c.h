#ifndef CyrI2c_h
#define CyrI2c_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class CyrI2c {
  public:
    CyrI2c(uint8_t address, uint8_t width, uint8_t height);
    void print(const __FlashStringHelper* str, int8_t position = 127, uint8_t go_ln = 255);
    void print(char chr, int8_t position = 127, uint8_t go_ln = 255);
    void print(char* str, int8_t position = 127, uint8_t go_ln = 255);
    void print_enc(char* str, int8_t position, uint8_t go_ln);
    void get_str_enc(char* str, char* result);

    void backlight();
    void backlight(boolean state);
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void setCursor(uint8_t col = 32);

    void init(const char* str);
    void init(const __FlashStringHelper* str);
    void printn(uint8_t num, int8_t position = 127, uint8_t go_ln = 255);

    boolean bl;


  private:
    void get_next_scr(char* str, char* next_scr);
    void write_str_enc(char* str, char* lcd);

    void clear_screen();

    void printn_str(uint8_t num, int8_t position, uint8_t go_ln);
		void printn_flash(uint8_t num, int8_t position, uint8_t go_ln);

    LiquidCrystal_I2C* lcd;
    char* abc;
    uint8_t** ru;
    uint8_t* ru_num;
    uint8_t ru_cnt;
    uint8_t* en;
    uint8_t* en_num;
    uint8_t en_cnt;

		const char* s;
		char* p_s;
		uint8_t f;
    char scr[33];
    uint8_t scr_pos;
    uint8_t char_map[8];
};

#endif
