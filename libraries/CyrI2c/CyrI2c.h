#ifndef CyrI2c_h
#define CyrI2c_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class CyrI2c {
  public:
    CyrI2c(byte address, byte width, byte height);
    void print(const __FlashStringHelper* str, int8_t position = 127, byte go_ln = 255, byte space = 0);
    void print(int chr, int8_t position = 127, byte go_ln = 255, byte space = 0);
    void print(double chr, int8_t position = 127, byte go_ln = 255, byte width = 5, byte prec = 2);
    void print(char chr, int8_t position = 127, byte go_ln = 255, byte space = 0);
    void print(char* str, int8_t position = 127, byte go_ln = 255, byte space = 0);
    void print_enc(char* str, int8_t position, byte go_ln, byte space = 0);

    void backlight();
    void backlight(boolean state);
    void power();
    void power(boolean state);
    void cursor();
    void cursor(boolean state);
    void blink();
    void blink(boolean state);
    void clear();
    void go(byte col, byte row);
    void go(byte col = 32);

    void init(const char* str);
    void init(const __FlashStringHelper* str);
    void printn(byte num, int8_t position = 127, byte go_ln = 255, byte space = 0);

    boolean bl = false;
    boolean pwr = true;
    boolean crsr = false;
    boolean blnk = false;


  private:
    void get_next_scr(char* str, char* next_scr);
    void write_str_enc(char* str, char* lcd);
    void get_str_enc(char* str, char* result);

    void printn_str(byte num, int8_t position, byte go_ln, byte space = 0);
		void printn_flash(byte num, int8_t position, byte go_ln, byte space = 0);

    LiquidCrystal_I2C* lcd;
    char* abc;
    byte** ru;
    byte* ru_num;
    byte ru_cnt;
    byte* en;
    byte* en_num;
    byte en_cnt;

		const char* s;
		char* p_s;
		byte f;
    char scr[33];
    byte scr_pos;
    byte char_map[8];
};

#endif
