/*
 Time
 Time and date on lcd display (used rtc timer)

 Hardware:
 Trickle-Charge Timekeeping Chip DS1302
 http://www.maximintegrated.com/en/products/digital/real-time-clocks/DS1302.html
 http://playground.arduino.cc/Main/DS1302
 LCD I2C PCF8574
 http://habrahabr.ru/post/219137/
 http://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C1602V1.zip/341635514

 created 18.01.2015
 by Fust Vitaliy
 with Arduino 1.5.8 (tested on Arduino Uno)
*/
/*
Sketch uses 5 570 bytes (17%) of program storage space. Maximum is 32 256 bytes.
Global variables use 295 bytes (14%) of dynamic memory, leaving 1 753 bytes for local variables. Maximum is 2 048 bytes.
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


#define DS1302_SCLK_PIN   11    // Arduino pin for the Serial Clock
#define DS1302_IO_PIN     12    // Arduino pin for the Data I/O
#define DS1302_CE_PIN     13    // Arduino pin for the Chip Enable
#define bcd2bin(h,l)    (((h)*10) + (l))
#define bin2bcd_h(x)   ((x)/10)
#define bin2bcd_l(x)    ((x)%10)
#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_ENABLE            0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF
#define DS1302_D0 0
#define DS1302_D1 1
#define DS1302_D2 2
#define DS1302_D3 3
#define DS1302_D4 4
#define DS1302_D5 5
#define DS1302_D6 6
#define DS1302_D7 7
#define DS1302_READBIT DS1302_D0
#define DS1302_RC DS1302_D6
#define DS1302_CH DS1302_D7
#define DS1302_AM_PM DS1302_D5
#define DS1302_12_24 DS1302_D7
#define DS1302_WP DS1302_D7
#define DS1302_ROUT0 DS1302_D0
#define DS1302_ROUT1 DS1302_D1
#define DS1302_DS0   DS1302_D2
#define DS1302_DS1   DS1302_D2
#define DS1302_TCS0  DS1302_D4
#define DS1302_TCS1  DS1302_D5
#define DS1302_TCS2  DS1302_D6
#define DS1302_TCS3  DS1302_D7
typedef struct ds1302_struct{uint8_t Seconds:4;uint8_t Seconds10:3;uint8_t CH:1;uint8_t Minutes:4;uint8_t Minutes10:3;uint8_t reserved1:1;union{struct{uint8_t Hour:4;uint8_t Hour10:2;uint8_t reserved2:1;uint8_t hour_12_24:1;}h24;struct{uint8_t Hour:4;uint8_t Hour10:1;uint8_t AM_PM:1;uint8_t reserved2:1;uint8_t hour_12_24:1;}h12;};uint8_t Date:4;uint8_t Date10:2;uint8_t reserved3:2;uint8_t Month:4;uint8_t Month10:1;uint8_t reserved4:3;uint8_t Day:3;uint8_t reserved5:5;uint8_t Year:4;uint8_t Year10:4;uint8_t reserved6:7;uint8_t WP:1;};void DS1302_clock_burst_read( uint8_t *p){int i;_DS1302_start();_DS1302_togglewrite( DS1302_CLOCK_BURST_READ, true);for( i=0; i<8; i++){*p++ = _DS1302_toggleread();}_DS1302_stop();}void DS1302_clock_burst_write( uint8_t *p){int i;_DS1302_start();_DS1302_togglewrite( DS1302_CLOCK_BURST_WRITE, false);for( i=0; i<8; i++){_DS1302_togglewrite( *p++, false);}_DS1302_stop();}uint8_t DS1302_read(int address){uint8_t data;bitSet( address, DS1302_READBIT);_DS1302_start();_DS1302_togglewrite( address, true);data = _DS1302_toggleread();_DS1302_stop();return (data);}void DS1302_write( int address, uint8_t data){bitClear( address, DS1302_READBIT);_DS1302_start();_DS1302_togglewrite( address, false);_DS1302_togglewrite( data, false);_DS1302_stop();}void _DS1302_start( void){digitalWrite( DS1302_CE_PIN, LOW);pinMode( DS1302_CE_PIN, OUTPUT);digitalWrite( DS1302_SCLK_PIN, LOW);pinMode( DS1302_SCLK_PIN, OUTPUT);pinMode( DS1302_IO_PIN, OUTPUT);digitalWrite( DS1302_CE_PIN, HIGH);delayMicroseconds( 4);}void _DS1302_stop(void){digitalWrite( DS1302_CE_PIN, LOW);delayMicroseconds( 4);}uint8_t _DS1302_toggleread( void){uint8_t i, data;data = 0;for( i = 0; i <= 7; i++){digitalWrite( DS1302_SCLK_PIN, HIGH);delayMicroseconds( 1);digitalWrite( DS1302_SCLK_PIN, LOW);delayMicroseconds( 1);bitWrite( data, i, digitalRead( DS1302_IO_PIN));}return( data);}void _DS1302_togglewrite( uint8_t data, uint8_t release){int i;for( i = 0; i <= 7; i++){digitalWrite( DS1302_IO_PIN, bitRead(data, i));delayMicroseconds( 1);digitalWrite( DS1302_SCLK_PIN, HIGH);delayMicroseconds( 1);if( release && i == 7){pinMode( DS1302_IO_PIN, INPUT);}else{digitalWrite( DS1302_SCLK_PIN, LOW);delayMicroseconds( 1);}}}void ds1302_init(){DS1302_write (DS1302_ENABLE, 0);DS1302_write (DS1302_TRICKLE, 0x00);}ds1302_struct rtc;

void setup() {
  ds1302_init();

  lcd.init();
  lcd.backlight();
  lcd.print("     Hello!     ");
  
  delay(1500);
}


void loop() {
  DS1302_clock_burst_read( (uint8_t *) &rtc);

  char buffer[15];

  sprintf( buffer, "    %02d:%02d:%02d    ", \
    bcd2bin( rtc.h24.Hour10, rtc.h24.Hour), \
    bcd2bin( rtc.Minutes10, rtc.Minutes), \
    bcd2bin( rtc.Seconds10, rtc.Seconds));
  lcd.setCursor(0, 0);
  lcd.print(buffer);

  sprintf(buffer, "   %02d.%02d.%04d   ", \
    bcd2bin( rtc.Date10, rtc.Date), \
    bcd2bin( rtc.Month10, rtc.Month), \
    2000 + bcd2bin( rtc.Year10, rtc.Year));
  lcd.setCursor(0, 1);
  lcd.print(buffer);

  delay(1000);
}

