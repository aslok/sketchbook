//
// C++ Implementation: gpl
//
// Description: Registers dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpmon.h"
#include "dumpdebug.h"
#include "printpgm.h"
#include "registers.h"

namespace dumpmon
{

typedef DUMP_REG_ADDR_TYPE  reg_addr_t;
typedef struct {
    reg_addr_t addr;
    const char* name;
} reg_desc_t;

const prog_char regtHexBinaryASCII[] = { "\r\nReg.\tName\tHex Binary    ASCII" };
extern const prog_char regtHexBinaryASCII[] PROGMEM;

#if defined(DUMP_ARDUINO)

#define REGCOUNT 87

const prog_char pinb[] = { "PINB" };
const prog_char ddrb[] = { "DDRB" };
const prog_char portb[] = { "PORTB" };
const prog_char pinc[] = { "PINC" };
const prog_char ddrc[] = { "DDRC" };
const prog_char portc[] = { "PORTC" };
const prog_char pind[] = { "PIND" };
const prog_char ddrd[] = { "DDRD" };
const prog_char portd[] = { "PORTD" };
const prog_char tifr0[] = { "TIFR0" };
const prog_char tifr1[] = { "TIFR1" };
const prog_char tifr2[] = { "TIFR2" };
const prog_char pcifr[] = { "PCIFR" };
const prog_char eifr[] = { "EIFR" };
const prog_char eimsk[] = { "EIMSK" };
const prog_char gpior0[] = { "GPIOR0" };
const prog_char gpior1[] = { "GPIOR1" };
const prog_char gpior2[] = { "GPIOR2" };
const prog_char eecr[] = { "EECR" };
const prog_char eedr[] = { "EEDR" };
const prog_char eearl[] = { "EEARL" };
const prog_char eearh[] = { "EEARH" };
const prog_char gtccr[] = { "GTCCR" };
const prog_char tccr0a[] = { "TCCR0A" };
const prog_char tccr0b[] = { "TCCR0B" };
const prog_char tcnt0[] = { "TCNT0" };
const prog_char ocr0a[] = { "OCR0A" };
const prog_char ocr0b[] = { "OCR0B" };
const prog_char spcr[] = { "SPCR" };
const prog_char spsr[] = { "SPSR" };
const prog_char spdr[] = { "SPDR" };
const prog_char acsr[] = { "ACSR" };
const prog_char smcr[] = { "SMCR" };
const prog_char mcusr[] = { "MCUSR" };
const prog_char mcucr[] = { "MCUCR" };
const prog_char spmcsr[] = { "SPMCSR" };
const prog_char spl[] = { "SPL" };
const prog_char sph[] = { "SPH" };
const prog_char sreg[] = { "SREG" };
const prog_char wdtcsr[] = { "WDTCSR" };
const prog_char clkpr[] = { "CLKPR" };
const prog_char prr[] = { "PRR" };
const prog_char osccal[] = { "OSCCAL" };
const prog_char pcicr[] = { "PCICR" };
const prog_char eicra[] = { "EICRA" };
const prog_char pcmsk0[] = { "PCMSK0" };
const prog_char pcmsk1[] = { "PCMSK1" };
const prog_char pcmsk2[] = { "PCMSK2" };
const prog_char timsk0[] = { "TIMSK0" };
const prog_char timsk1[] = { "TIMSK1" };
const prog_char timsk2[] = { "TIMSK2" };
const prog_char adcl[] = { "ADCL" };
const prog_char adch[] = { "ADCH" };
const prog_char adcsra[] = { "ADCSRA" };
const prog_char adcsrb[] = { "ADCSRB" };
const prog_char admux[] = { "ADMUX" };
const prog_char didr0[] = { "DIDR0" };
const prog_char didr1[] = { "DIDR1" };
const prog_char tccr1a[] = { "TCCR1A" };
const prog_char tccr1b[] = { "TCCR1B" };
const prog_char tccr1c[] = { "TCCR1C" };
const prog_char tcnt1l[] = { "TCNT1L" };
const prog_char tcnt1h[] = { "TCNT1H" };
const prog_char icr1l[] = { "ICR1L" };
const prog_char icr1h[] = { "ICR1H" };
const prog_char ocr1al[] = { "OCR1AL" };
const prog_char ocr1ah[] = { "OCR1AH" };
const prog_char ocr1bl[] = { "OCR1BL" };
const prog_char ocr1bh[] = { "OCR1BH" };
const prog_char tccr2a[] = { "TCCR2A" };
const prog_char tccr2b[] = { "TCCR2B" };
const prog_char tcnt2[] = { "TCNT2" };
const prog_char ocr2a[] = { "OCR2A" };
const prog_char ocr2b[] = { "OCR2B" };
const prog_char assr[] = { "ASSR" };
const prog_char twar[] = { "TWAR" };
const prog_char twbr[] = { "TWBR" };
const prog_char twcr[] = { "TWCR" };
const prog_char twdr[] = { "TWDR" };
const prog_char twsr[] = { "TWSR" };
const prog_char twamr[] = { "TWAMR" };
const prog_char ucsr0a[] = { "UCSR0A" };
const prog_char ucsr0b[] = { "UCSR0B" };
const prog_char ucsr0c[] = { "UCSR0C" };
const prog_char ubrr0l[] = { "UBRR0L" };
const prog_char ubrr0h[] = { "UBRR0H" };
const prog_char udr0[] = { "UDR0" };

const reg_desc_t regdesc[REGCOUNT] = {
    { 0x23, pinb },
    { 0x24, ddrb },
    { 0x25, portb },
    { 0x26, pinc },
    { 0x27, ddrc },
    { 0x28, portc },
    { 0x29, pind },
    { 0x2a, ddrd },
    { 0x2b, portd },
    { 0x35, tifr0 },
    { 0x36, tifr1 },
    { 0x37, tifr2 },
    { 0x3b, pcifr },
    { 0x3c, eifr },
    { 0x3d, eimsk },
    { 0x3e, gpior0 },
    { 0x3f, eecr },
    { 0x40, eedr },
    { 0x41, eearl },
    { 0x42, eearh },
    { 0x43, gtccr },
    { 0x44, tccr0a },
    { 0x45, tccr0b },
    { 0x46, tcnt0 },
    { 0x47, ocr0a },
    { 0x48, ocr0b },
    { 0x4a, gpior1 },
    { 0x4b, gpior2 },
    { 0x4c, spcr },
    { 0x4d, spsr },
    { 0x4e, spdr },
    { 0x50, acsr },
    { 0x53, smcr },
    { 0x54, mcusr },
    { 0x55, mcucr },
    { 0x57, spmcsr },
    { 0x5d, spl },
    { 0x5e, sph },
    { 0x5f, sreg },
    { 0x60, wdtcsr },
    { 0x61, clkpr },
    { 0x64, prr },
    { 0x66, osccal },
    { 0x68, pcicr },
    { 0x69, eicra },
    { 0x6b, pcmsk0 },
    { 0x6c, pcmsk1 },
    { 0x6d, pcmsk2 },
    { 0x6e, timsk0 },
    { 0x6f, timsk1 },
    { 0x70, timsk2 },
    { 0x78, adcl },
    { 0x79, adch },
    { 0x7a, adcsra },
    { 0x7b, adcsrb },
    { 0x7c, admux },
    { 0x7e, didr0 },
    { 0x7f, didr1 },
    { 0x80, tccr1a },
    { 0x81, tccr1b },
    { 0x82, tccr1c },
    { 0x84, tcnt1l },
    { 0x85, tcnt1h },
    { 0x86, icr1l },
    { 0x87, icr1h },
    { 0x88, ocr1al },
    { 0x89, ocr1ah },
    { 0x8a, ocr1bl },
    { 0x8b, ocr1bh },
    { 0xb0, tccr2a },
    { 0xb1, tccr2b },
    { 0xb2, tcnt2 },
    { 0xb3, ocr2a },
    { 0xb4, ocr2b },
    { 0xb6, assr },
    { 0xb8, twbr },
    { 0xb9, twsr },
    { 0xba, twar },
    { 0xbb, twdr },
    { 0xbc, twcr },
    { 0xbd, twamr },
    { 0xc0, ucsr0a },
    { 0xc1, ucsr0b },
    { 0xc2, ucsr0c },
    { 0xc4, ubrr0l },
    { 0xc5, ubrr0h },
    { 0xc6, udr0 }
};

extern const prog_char pinb[] PROGMEM;
extern const prog_char ddrb[] PROGMEM;
extern const prog_char portb[] PROGMEM;
extern const prog_char pinc[] PROGMEM;
extern const prog_char ddrc[] PROGMEM;
extern const prog_char portc[] PROGMEM;
extern const prog_char pind[] PROGMEM;
extern const prog_char ddrd[] PROGMEM;
extern const prog_char portd[] PROGMEM;
extern const prog_char tifr0[] PROGMEM;
extern const prog_char tifr1[] PROGMEM;
extern const prog_char tifr2[] PROGMEM;
extern const prog_char pcifr[] PROGMEM;
extern const prog_char eifr[] PROGMEM;
extern const prog_char eimsk[] PROGMEM;
extern const prog_char gpior0[] PROGMEM;
extern const prog_char gpior1[] PROGMEM;
extern const prog_char gpior2[] PROGMEM;
extern const prog_char eecr[] PROGMEM;
extern const prog_char eedr[] PROGMEM;
extern const prog_char eearl[] PROGMEM;
extern const prog_char eearh[] PROGMEM;
extern const prog_char gtccr[] PROGMEM;
extern const prog_char tccr0a[] PROGMEM;
extern const prog_char tccr0b[] PROGMEM;
extern const prog_char tcnt0[] PROGMEM;
extern const prog_char ocr0a[] PROGMEM;
extern const prog_char ocr0b[] PROGMEM;
extern const prog_char spcr[] PROGMEM;
extern const prog_char spsr[] PROGMEM;
extern const prog_char spdr[] PROGMEM;
extern const prog_char acsr[] PROGMEM;
extern const prog_char smcr[] PROGMEM;
extern const prog_char mcusr[] PROGMEM;
extern const prog_char mcucr[] PROGMEM;
extern const prog_char spmcsr[] PROGMEM;
extern const prog_char spl[] PROGMEM;
extern const prog_char sph[] PROGMEM;
extern const prog_char sreg[] PROGMEM;
extern const prog_char wdtcsr[] PROGMEM;
extern const prog_char clkpr[] PROGMEM;
extern const prog_char prr[] PROGMEM;
extern const prog_char osccal[] PROGMEM;
extern const prog_char pcicr[] PROGMEM;
extern const prog_char eicra[] PROGMEM;
extern const prog_char pcmsk0[] PROGMEM;
extern const prog_char pcmsk1[] PROGMEM;
extern const prog_char pcmsk2[] PROGMEM;
extern const prog_char timsk0[] PROGMEM;
extern const prog_char timsk1[] PROGMEM;
extern const prog_char timsk2[] PROGMEM;
extern const prog_char adcl[] PROGMEM;
extern const prog_char adch[] PROGMEM;
extern const prog_char adcsra[] PROGMEM;
extern const prog_char adcsrb[] PROGMEM;
extern const prog_char admux[] PROGMEM;
extern const prog_char didr0[] PROGMEM;
extern const prog_char didr1[] PROGMEM;
extern const prog_char tccr1a[] PROGMEM;
extern const prog_char tccr1b[] PROGMEM;
extern const prog_char tccr1c[] PROGMEM;
extern const prog_char tcnt1l[] PROGMEM;
extern const prog_char tcnt1h[] PROGMEM;
extern const prog_char icr1l[] PROGMEM;
extern const prog_char icr1h[] PROGMEM;
extern const prog_char ocr1al[] PROGMEM;
extern const prog_char ocr1ah[] PROGMEM;
extern const prog_char ocr1bl[] PROGMEM;
extern const prog_char ocr1bh[] PROGMEM;
extern const prog_char tccr2a[] PROGMEM;
extern const prog_char tccr2b[] PROGMEM;
extern const prog_char tcnt2[] PROGMEM;
extern const prog_char ocr2a[] PROGMEM;
extern const prog_char ocr2b[] PROGMEM;
extern const prog_char assr[] PROGMEM;
extern const prog_char twar[] PROGMEM;
extern const prog_char twbr[] PROGMEM;
extern const prog_char twcr[] PROGMEM;
extern const prog_char twdr[] PROGMEM;
extern const prog_char twsr[] PROGMEM;
extern const prog_char twamr[] PROGMEM;
extern const prog_char ucsr0a[] PROGMEM;
extern const prog_char ucsr0b[] PROGMEM;
extern const prog_char ucsr0c[] PROGMEM;
extern const prog_char ubrr0l[] PROGMEM;
extern const prog_char ubrr0h[] PROGMEM;
extern const prog_char udr0[] PROGMEM;

extern PROGMEM const reg_desc_t regdesc[REGCOUNT];

#elif defined(DUMP_MEGA)

#define REGCOUNT 184

const prog_char udr3[] = { "UDR3" };
const prog_char ubrr3h[] = { "UBRR3H" };
const prog_char ubrr3l[] = { "UBRR3L" };
const prog_char ucsr3c[] = { "UCSR3C" };
const prog_char ucsr3b[] = { "UCSR3B" };
const prog_char ucsr3a[] = { "UCSR3A" };
const prog_char ocr5ch[] = { "OCR5CH" };
const prog_char ocr5cl[] = { "OCR5CL" };
const prog_char ocr5bh[] = { "OCR5BH" };
const prog_char ocr5bl[] = { "OCR5BL" };
const prog_char ocr5ah[] = { "OCR5AH" };
const prog_char ocr5al[] = { "OCR5AL" };
const prog_char icr5h[] = { "ICR5H" };
const prog_char icr5l[] = { "ICR5L" };
const prog_char tcnt5h[] = { "TCNT5H" };
const prog_char tcnt5l[] = { "TCNT5L" };
const prog_char tccr5c[] = { "TCCR5C" };
const prog_char tccr5b[] = { "TCCR5B" };
const prog_char tccr5a[] = { "TCCR5A" };
const prog_char portl[] = { "PORTL" };
const prog_char ddrl[] = { "DDRL" };
const prog_char pinl[] = { "PINL" };
const prog_char portk[] = { "PORTK" };
const prog_char ddrk[] = { "DDRK" };
const prog_char pink[] = { "PINK" };
const prog_char portj[] = { "PORTJ" };
const prog_char ddrj[] = { "DDRJ" };
const prog_char pinj[] = { "PINJ" };
const prog_char porth[] = { "PORTH" };
const prog_char ddrh[] = { "DDRH" };
const prog_char pinh[] = { "PINH" };
const prog_char udr2[] = { "UDR2" };
const prog_char ubrr2h[] = { "UBRR2H" };
const prog_char ubrr2l[] = { "UBRR2L" };
const prog_char ucsr2c[] = { "UCSR2C" };
const prog_char ucsr2b[] = { "UCSR2B" };
const prog_char ucsr2a[] = { "UCSR2A" };
const prog_char udr1[] = { "UDR1" };
const prog_char ubrr1h[] = { "UBRR1H" };
const prog_char ubrr1l[] = { "UBRR1L" };
const prog_char ucsr1c[] = { "UCSR1C" };
const prog_char ucsr1b[] = { "UCSR1B" };
const prog_char ucsr1a[] = { "UCSR1A" };
const prog_char udr0[] = { "UDR0" };
const prog_char ubrr0h[] = { "UBRR0H" };
const prog_char ubrr0l[] = { "UBRR0L" };
const prog_char ucsr0c[] = { "UCSR0C" };
const prog_char ucsr0b[] = { "UCSR0B" };
const prog_char ucsr0a[] = { "UCSR0A" };
const prog_char twamr[] = { "TWAMR" };
const prog_char twcr[] = { "TWCR" };
const prog_char twdr[] = { "TWDR" };
const prog_char twar[] = { "TWAR" };
const prog_char twsr[] = { "TWSR" };
const prog_char twbr[] = { "TWBR" };
const prog_char assr[] = { "ASSR" };
const prog_char ocr2b[] = { "OCR2B" };
const prog_char ocr2a[] = { "OCR2A" };
const prog_char tcnt2[] = { "TCNT2" };
const prog_char tccr2b[] = { "TCCR2B" };
const prog_char tccr2a[] = { "TCCR2A" };
const prog_char ocr4ch[] = { "OCR4CH" };
const prog_char ocr4cl[] = { "OCR4CL" };
const prog_char ocr4bh[] = { "OCR4BH" };
const prog_char ocr4bl[] = { "OCR4BL" };
const prog_char ocr4ah[] = { "OCR4AH" };
const prog_char ocr4al[] = { "OCR4AL" };
const prog_char icr4h[] = { "ICR4H" };
const prog_char icr4l[] = { "ICR4L" };
const prog_char tcnt4h[] = { "TCNT4H" };
const prog_char tcnt4l[] = { "TCNT4L" };
const prog_char tccr4c[] = { "TCCR4C" };
const prog_char tccr4b[] = { "TCCR4B" };
const prog_char tccr4a[] = { "TCCR4A" };
const prog_char ocr3ch[] = { "OCR3CH" };
const prog_char ocr3cl[] = { "OCR3CL" };
const prog_char ocr3bh[] = { "OCR3BH" };
const prog_char ocr3bl[] = { "OCR3BL" };
const prog_char ocr3ah[] = { "OCR3AH" };
const prog_char ocr3al[] = { "OCR3AL" };
const prog_char icr3h[] = { "ICR3H" };
const prog_char icr3l[] = { "ICR3L" };
const prog_char tcnt3h[] = { "TCNT3H" };
const prog_char tcnt3l[] = { "TCNT3L" };
const prog_char tccr3c[] = { "TCCR3C" };
const prog_char tccr3b[] = { "TCCR3B" };
const prog_char tccr3a[] = { "TCCR3A" };
const prog_char ocr1ch[] = { "OCR1CH" };
const prog_char ocr1cl[] = { "OCR1CL" };
const prog_char ocr1bh[] = { "OCR1BH" };
const prog_char ocr1bl[] = { "OCR1BL" };
const prog_char ocr1ah[] = { "OCR1AH" };
const prog_char ocr1al[] = { "OCR1AL" };
const prog_char icr1h[] = { "ICR1H" };
const prog_char icr1l[] = { "ICR1L" };
const prog_char tcnt1h[] = { "TCNT1H" };
const prog_char tcnt1l[] = { "TCNT1L" };
const prog_char tccr1c[] = { "TCCR1C" };
const prog_char tccr1b[] = { "TCCR1B" };
const prog_char tccr1a[] = { "TCCR1A" };
const prog_char didr1[] = { "DIDR1" };
const prog_char didr0[] = { "DIDR0" };
const prog_char didr2[] = { "DIDR2" };
const prog_char admux[] = { "ADMUX" };
const prog_char adcsrb[] = { "ADCSRB" };
const prog_char adcsra[] = { "ADCSRA" };
const prog_char adch[] = { "ADCH" };
const prog_char adcl[] = { "ADCL" };
const prog_char xmcrb[] = { "XMCRB" };
const prog_char xmcra[] = { "XMCRA" };
const prog_char timsk5[] = { "TIMSK5" };
const prog_char timsk4[] = { "TIMSK4" };
const prog_char timsk3[] = { "TIMSK3" };
const prog_char timsk2[] = { "TIMSK2" };
const prog_char timsk1[] = { "TIMSK1" };
const prog_char timsk0[] = { "TIMSK0" };
const prog_char pcmsk2[] = { "PCMSK2" };
const prog_char pcmsk1[] = { "PCMSK1" };
const prog_char pcmsk0[] = { "PCMSK0" };
const prog_char eicrb[] = { "EICRB" };
const prog_char eicra[] = { "EICRA" };
const prog_char pcicr[] = { "PCICR" };
const prog_char osccal[] = { "OSCCAL" };
const prog_char prr1[] = { "PRR1" };
const prog_char prr0[] = { "PRR0" };
const prog_char clkpr[] = { "CLKPR" };
const prog_char wdtcsr[] = { "WDTCSR" };
const prog_char sreg[] = { "SREG" };
const prog_char sph[] = { "SPH" };
const prog_char spl[] = { "SPL" };
const prog_char eind[] = { "EIND" };
const prog_char rampz[] = { "RAMPZ" };
const prog_char spmcsr[] = { "SPMCSR" };
const prog_char mcucr[] = { "MCUCR" };
const prog_char mcusr[] = { "MCUSR" };
const prog_char smcr[] = { "SMCR" };
const prog_char ocdr[] = { "OCDR" };
const prog_char acsr[] = { "ACSR" };
const prog_char spdr[] = { "SPDR" };
const prog_char spsr[] = { "SPSR" };
const prog_char spcr[] = { "SPCR" };
const prog_char gpior2[] = { "GPIOR2" };
const prog_char gpior1[] = { "GPIOR1" };
const prog_char ocr0b[] = { "OCR0B" };
const prog_char ocr0a[] = { "OCR0A" };
const prog_char tcnt0[] = { "TCNT0" };
const prog_char tccr0b[] = { "TCCR0B" };
const prog_char tccr0a[] = { "TCCR0A" };
const prog_char gtccr[] = { "GTCCR" };
const prog_char eearh[] = { "EEARH" };
const prog_char eearl[] = { "EEARL" };
const prog_char eedr[] = { "EEDR" };
const prog_char eecr[] = { "EECR" };
const prog_char gpior0[] = { "GPIOR0" };
const prog_char eimsk[] = { "EIMSK" };
const prog_char eifr[] = { "EIFR" };
const prog_char pcifr[] = { "PCIFR" };
const prog_char tifr5[] = { "TIFR5" };
const prog_char tifr4[] = { "TIFR4" };
const prog_char tifr3[] = { "TIFR3" };
const prog_char tifr2[] = { "TIFR2" };
const prog_char tifr1[] = { "TIFR1" };
const prog_char tifr0[] = { "TIFR0" };
const prog_char portg[] = { "PORTG" };
const prog_char ddrg[] = { "DDRG" };
const prog_char ping[] = { "PING" };
const prog_char portf[] = { "PORTF" };
const prog_char ddrf[] = { "DDRF" };
const prog_char pinf[] = { "PINF" };
const prog_char porte[] = { "PORTE" };
const prog_char ddre[] = { "DDRE" };
const prog_char pine[] = { "PINE" };
const prog_char portd[] = { "PORTD" };
const prog_char ddrd[] = { "DDRD" };
const prog_char pind[] = { "PIND" };
const prog_char portc[] = { "PORTC" };
const prog_char ddrc[] = { "DDRC" };
const prog_char pinc[] = { "PINC" };
const prog_char portb[] = { "PORTB" };
const prog_char ddrb[] = { "DDRB" };
const prog_char pinb[] = { "PINB" };
const prog_char porta[] = { "PORTA" };
const prog_char ddra[] = { "DDRA" };
const prog_char pina[] = { "PINA" };

const reg_desc_t regdesc[REGCOUNT] = {
    { 0x020, pina },
    { 0x021, ddra },
    { 0x022, porta },
    { 0x023, pinb },
    { 0x024, ddrb },
    { 0x025, portb },
    { 0x026, pinc },
    { 0x027, ddrc },
    { 0x028, portc },
    { 0x029, pind },
    { 0x02a, ddrd },
    { 0x02b, portd },
    { 0x02c, pine },
    { 0x02d, ddre },
    { 0x02e, porte },
    { 0x02f, pinf },
    { 0x030, ddrf },
    { 0x031, portf },
    { 0x032, ping },
    { 0x033, ddrg },
    { 0x034, portg },
    { 0x035, tifr0 },
    { 0x036, tifr1 },
    { 0x037, tifr2 },
    { 0x038, tifr3 },
    { 0x039, tifr4 },
    { 0x03a, tifr5 },
    { 0x03b, pcifr },
    { 0x03c, eifr },
    { 0x03d, eimsk },
    { 0x03e, gpior0 },
    { 0x03f, eecr },
    { 0x040, eedr },
    { 0x041, eearl },
    { 0x042, eearh },
    { 0x043, gtccr },
    { 0x044, tccr0a },
    { 0x045, tccr0b },
    { 0x046, tcnt0 },
    { 0x047, ocr0a },
    { 0x048, ocr0b },
    { 0x04a, gpior1 },
    { 0x04b, gpior2 },
    { 0x04c, spcr },
    { 0x04d, spsr },
    { 0x04e, spdr },
    { 0x050, acsr },
    { 0x051, ocdr },
    { 0x053, smcr },
    { 0x054, mcusr },
    { 0x055, mcucr },
    { 0x057, spmcsr },
    { 0x05b, rampz },
    { 0x05c, eind },
    { 0x05d, spl },
    { 0x05e, sph },
    { 0x05f, sreg },
    { 0x060, wdtcsr },
    { 0x061, clkpr },
    { 0x064, prr0 },
    { 0x065, prr1 },
    { 0x066, osccal },
    { 0x068, pcicr },
    { 0x069, eicra },
    { 0x06a, eicrb },
    { 0x06b, pcmsk0 },
    { 0x06c, pcmsk1 },
    { 0x06d, pcmsk2 },
    { 0x06e, timsk0 },
    { 0x06f, timsk1 },
    { 0x070, timsk2 },
    { 0x071, timsk3 },
    { 0x072, timsk4 },
    { 0x073, timsk5 },
    { 0x074, xmcra },
    { 0x075, xmcrb },
    { 0x078, adcl },
    { 0x079, adch },
    { 0x07a, adcsra },
    { 0x07b, adcsrb },
    { 0x07c, admux },
    { 0x07d, didr2 },
    { 0x07e, didr0 },
    { 0x07f, didr1 },
    { 0x080, tccr1a },
    { 0x081, tccr1b },
    { 0x082, tccr1c },
    { 0x084, tcnt1l },
    { 0x085, tcnt1h },
    { 0x086, icr1l },
    { 0x087, icr1h },
    { 0x088, ocr1al },
    { 0x089, ocr1ah },
    { 0x08a, ocr1bl },
    { 0x08b, ocr1bh },
    { 0x08c, ocr1cl },
    { 0x08d, ocr1ch },
    { 0x090, tccr3a },
    { 0x091, tccr3b },
    { 0x092, tccr3c },
    { 0x094, tcnt3l },
    { 0x095, tcnt3h },
    { 0x096, icr3l },
    { 0x097, icr3h },
    { 0x098, ocr3al },
    { 0x099, ocr3ah },
    { 0x09a, ocr3bl },
    { 0x09b, ocr3bh },
    { 0x09c, ocr3cl },
    { 0x09d, ocr3ch },
    { 0x0a0, tccr4a },
    { 0x0a1, tccr4b },
    { 0x0a2, tccr4c },
    { 0x0a4, tcnt4l },
    { 0x0a5, tcnt4h },
    { 0x0a6, icr4l },
    { 0x0a7, icr4h },
    { 0x0a8, ocr4al },
    { 0x0a9, ocr4ah },
    { 0x0aa, ocr4bl },
    { 0x0ab, ocr4bh },
    { 0x0ac, ocr4cl },
    { 0x0ad, ocr4ch },
    { 0x0b0, tccr2a },
    { 0x0b1, tccr2b },
    { 0x0b2, tcnt2 },
    { 0x0b3, ocr2a },
    { 0x0b4, ocr2b },
    { 0x0b6, assr },
    { 0x0b8, twbr },
    { 0x0b9, twsr },
    { 0x0ba, twar },
    { 0x0bb, twdr },
    { 0x0bc, twcr },
    { 0x0bd, twamr },
    { 0x0c0, ucsr0a },
    { 0x0c1, ucsr0b },
    { 0x0c2, ucsr0c },
    { 0x0c4, ubrr0l },
    { 0x0c5, ubrr0h },
    { 0x0c6, udr0 },
    { 0x0c8, ucsr1a },
    { 0x0c9, ucsr1b },
    { 0x0ca, ucsr1c },
    { 0x0cc, ubrr1l },
    { 0x0cd, ubrr1h },
    { 0x0ce, udr1 },
    { 0x0d0, ucsr2a },
    { 0x0d1, ucsr2b },
    { 0x0d2, ucsr2c },
    { 0x0d4, ubrr2l },
    { 0x0d5, ubrr2h },
    { 0x0d6, udr2 },
    { 0x100, pinh },
    { 0x101, ddrh },
    { 0x102, porth },
    { 0x103, pinj },
    { 0x104, ddrj },
    { 0x105, portj },
    { 0x106, pink },
    { 0x107, ddrk },
    { 0x108, portk },
    { 0x109, pinl },
    { 0x10a, ddrl },
    { 0x10b, portl },
    { 0x120, tccr5a },
    { 0x121, tccr5b },
    { 0x122, tccr5c },
    { 0x124, tcnt5l },
    { 0x125, tcnt5h },
    { 0x126, icr5l },
    { 0x127, icr5h },
    { 0x128, ocr5al },
    { 0x129, ocr5ah },
    { 0x12a, ocr5bl },
    { 0x12b, ocr5bh },
    { 0x12c, ocr5cl },
    { 0x12d, ocr5ch },
    { 0x130, ucsr3a },
    { 0x131, ucsr3b },
    { 0x132, ucsr3c },
    { 0x134, ubrr3l },
    { 0x135, ubrr3h },
    { 0x136, udr3 }
};

extern const prog_char udr3[] PROGMEM;
extern const prog_char ubrr3h[] PROGMEM;
extern const prog_char ubrr3l[] PROGMEM;
extern const prog_char ucsr3c[] PROGMEM;
extern const prog_char ucsr3b[] PROGMEM;
extern const prog_char ucsr3a[] PROGMEM;
extern const prog_char ocr5ch[] PROGMEM;
extern const prog_char ocr5cl[] PROGMEM;
extern const prog_char ocr5bh[] PROGMEM;
extern const prog_char ocr5bl[] PROGMEM;
extern const prog_char ocr5ah[] PROGMEM;
extern const prog_char ocr5al[] PROGMEM;
extern const prog_char icr5h[] PROGMEM;
extern const prog_char icr5l[] PROGMEM;
extern const prog_char tcnt5h[] PROGMEM;
extern const prog_char tcnt5l[] PROGMEM;
extern const prog_char tccr5c[] PROGMEM;
extern const prog_char tccr5b[] PROGMEM;
extern const prog_char tccr5a[] PROGMEM;
extern const prog_char portl[] PROGMEM;
extern const prog_char ddrl[] PROGMEM;
extern const prog_char pinl[] PROGMEM;
extern const prog_char portk[] PROGMEM;
extern const prog_char ddrk[] PROGMEM;
extern const prog_char pink[] PROGMEM;
extern const prog_char portj[] PROGMEM;
extern const prog_char ddrj[] PROGMEM;
extern const prog_char pinj[] PROGMEM;
extern const prog_char porth[] PROGMEM;
extern const prog_char ddrh[] PROGMEM;
extern const prog_char pinh[] PROGMEM;
extern const prog_char udr2[] PROGMEM;
extern const prog_char ubrr2h[] PROGMEM;
extern const prog_char ubrr2l[] PROGMEM;
extern const prog_char ucsr2c[] PROGMEM;
extern const prog_char ucsr2b[] PROGMEM;
extern const prog_char ucsr2a[] PROGMEM;
extern const prog_char udr1[] PROGMEM;
extern const prog_char ubrr1h[] PROGMEM;
extern const prog_char ubrr1l[] PROGMEM;
extern const prog_char ucsr1c[] PROGMEM;
extern const prog_char ucsr1b[] PROGMEM;
extern const prog_char ucsr1a[] PROGMEM;
extern const prog_char udr0[] PROGMEM;
extern const prog_char ubrr0h[] PROGMEM;
extern const prog_char ubrr0l[] PROGMEM;
extern const prog_char ucsr0c[] PROGMEM;
extern const prog_char ucsr0b[] PROGMEM;
extern const prog_char ucsr0a[] PROGMEM;
extern const prog_char twamr[] PROGMEM;
extern const prog_char twcr[] PROGMEM;
extern const prog_char twdr[] PROGMEM;
extern const prog_char twar[] PROGMEM;
extern const prog_char twsr[] PROGMEM;
extern const prog_char twbr[] PROGMEM;
extern const prog_char assr[] PROGMEM;
extern const prog_char ocr2b[] PROGMEM;
extern const prog_char ocr2a[] PROGMEM;
extern const prog_char tcnt2[] PROGMEM;
extern const prog_char tccr2b[] PROGMEM;
extern const prog_char tccr2a[] PROGMEM;
extern const prog_char ocr4ch[] PROGMEM;
extern const prog_char ocr4cl[] PROGMEM;
extern const prog_char ocr4bh[] PROGMEM;
extern const prog_char ocr4bl[] PROGMEM;
extern const prog_char ocr4ah[] PROGMEM;
extern const prog_char ocr4al[] PROGMEM;
extern const prog_char icr4h[] PROGMEM;
extern const prog_char icr4l[] PROGMEM;
extern const prog_char tcnt4h[] PROGMEM;
extern const prog_char tcnt4l[] PROGMEM;
extern const prog_char tccr4c[] PROGMEM;
extern const prog_char tccr4b[] PROGMEM;
extern const prog_char tccr4a[] PROGMEM;
extern const prog_char ocr3ch[] PROGMEM;
extern const prog_char ocr3cl[] PROGMEM;
extern const prog_char ocr3bh[] PROGMEM;
extern const prog_char ocr3bl[] PROGMEM;
extern const prog_char ocr3ah[] PROGMEM;
extern const prog_char ocr3al[] PROGMEM;
extern const prog_char icr3h[] PROGMEM;
extern const prog_char icr3l[] PROGMEM;
extern const prog_char tcnt3h[] PROGMEM;
extern const prog_char tcnt3l[] PROGMEM;
extern const prog_char tccr3c[] PROGMEM;
extern const prog_char tccr3b[] PROGMEM;
extern const prog_char tccr3a[] PROGMEM;
extern const prog_char ocr1ch[] PROGMEM;
extern const prog_char ocr1cl[] PROGMEM;
extern const prog_char ocr1bh[] PROGMEM;
extern const prog_char ocr1bl[] PROGMEM;
extern const prog_char ocr1ah[] PROGMEM;
extern const prog_char ocr1al[] PROGMEM;
extern const prog_char icr1h[] PROGMEM;
extern const prog_char icr1l[] PROGMEM;
extern const prog_char tcnt1h[] PROGMEM;
extern const prog_char tcnt1l[] PROGMEM;
extern const prog_char tccr1c[] PROGMEM;
extern const prog_char tccr1b[] PROGMEM;
extern const prog_char tccr1a[] PROGMEM;
extern const prog_char didr1[] PROGMEM;
extern const prog_char didr0[] PROGMEM;
extern const prog_char didr2[] PROGMEM;
extern const prog_char admux[] PROGMEM;
extern const prog_char adcsrb[] PROGMEM;
extern const prog_char adcsra[] PROGMEM;
extern const prog_char adch[] PROGMEM;
extern const prog_char adcl[] PROGMEM;
extern const prog_char xmcrb[] PROGMEM;
extern const prog_char xmcra[] PROGMEM;
extern const prog_char timsk5[] PROGMEM;
extern const prog_char timsk4[] PROGMEM;
extern const prog_char timsk3[] PROGMEM;
extern const prog_char timsk2[] PROGMEM;
extern const prog_char timsk1[] PROGMEM;
extern const prog_char timsk0[] PROGMEM;
extern const prog_char pcmsk2[] PROGMEM;
extern const prog_char pcmsk1[] PROGMEM;
extern const prog_char pcmsk0[] PROGMEM;
extern const prog_char eicrb[] PROGMEM;
extern const prog_char eicra[] PROGMEM;
extern const prog_char pcicr[] PROGMEM;
extern const prog_char osccal[] PROGMEM;
extern const prog_char prr1[] PROGMEM;
extern const prog_char prr0[] PROGMEM;
extern const prog_char clkpr[] PROGMEM;
extern const prog_char wdtcsr[] PROGMEM;
extern const prog_char sreg[] PROGMEM;
extern const prog_char sph[] PROGMEM;
extern const prog_char spl[] PROGMEM;
extern const prog_char eind[] PROGMEM;
extern const prog_char rampz[] PROGMEM;
extern const prog_char spmcsr[] PROGMEM;
extern const prog_char mcucr[] PROGMEM;
extern const prog_char mcusr[] PROGMEM;
extern const prog_char smcr[] PROGMEM;
extern const prog_char ocdr[] PROGMEM;
extern const prog_char acsr[] PROGMEM;
extern const prog_char spdr[] PROGMEM;
extern const prog_char spsr[] PROGMEM;
extern const prog_char spcr[] PROGMEM;
extern const prog_char gpior2[] PROGMEM;
extern const prog_char gpior1[] PROGMEM;
extern const prog_char ocr0b[] PROGMEM;
extern const prog_char ocr0a[] PROGMEM;
extern const prog_char tcnt0[] PROGMEM;
extern const prog_char tccr0b[] PROGMEM;
extern const prog_char tccr0a[] PROGMEM;
extern const prog_char gtccr[] PROGMEM;
extern const prog_char eearh[] PROGMEM;
extern const prog_char eearl[] PROGMEM;
extern const prog_char eedr[] PROGMEM;
extern const prog_char eecr[] PROGMEM;
extern const prog_char gpior0[] PROGMEM;
extern const prog_char eimsk[] PROGMEM;
extern const prog_char eifr[] PROGMEM;
extern const prog_char pcifr[] PROGMEM;
extern const prog_char tifr5[] PROGMEM;
extern const prog_char tifr4[] PROGMEM;
extern const prog_char tifr3[] PROGMEM;
extern const prog_char tifr2[] PROGMEM;
extern const prog_char tifr1[] PROGMEM;
extern const prog_char tifr0[] PROGMEM;
extern const prog_char portg[] PROGMEM;
extern const prog_char ddrg[] PROGMEM;
extern const prog_char ping[] PROGMEM;
extern const prog_char portf[] PROGMEM;
extern const prog_char ddrf[] PROGMEM;
extern const prog_char pinf[] PROGMEM;
extern const prog_char porte[] PROGMEM;
extern const prog_char ddre[] PROGMEM;
extern const prog_char pine[] PROGMEM;
extern const prog_char portd[] PROGMEM;
extern const prog_char ddrd[] PROGMEM;
extern const prog_char pind[] PROGMEM;
extern const prog_char portc[] PROGMEM;
extern const prog_char ddrc[] PROGMEM;
extern const prog_char pinc[] PROGMEM;
extern const prog_char portb[] PROGMEM;
extern const prog_char ddrb[] PROGMEM;
extern const prog_char pinb[] PROGMEM;
extern const prog_char porta[] PROGMEM;
extern const prog_char ddra[] PROGMEM;
extern const prog_char pina[] PROGMEM;

extern PROGMEM const reg_desc_t regdesc[REGCOUNT];

#elif defined(DUMP_LEONARDO)

#define REGCOUNT 156

const prog_char pinb[] = { "PINB" };
const prog_char ddrb[] = { "DDRB" };
const prog_char portb[] = { "PORTB" };
const prog_char pinc[] = { "PINC" };
const prog_char ddrc[] = { "DDRC" };
const prog_char portc[] = { "PORTC" };
const prog_char pind[] = { "PIND" };
const prog_char ddrd[] = { "DDRD" };
const prog_char portd[] = { "PORTD" };
const prog_char pine[] = { "PINE" };
const prog_char ddre[] = { "DDRE" };
const prog_char porte[] = { "PORTE" };
const prog_char pinf[] = { "PINF" };
const prog_char ddrf[] = { "DDRF" };
const prog_char portf[] = { "PORTF" };
const prog_char tifr0[] = { "TIFR0" };
const prog_char tifr1[] = { "TIFR1" };
const prog_char tifr2[] = { "TIFR2" };
const prog_char tifr3[] = { "TIFR3" };
const prog_char tifr4[] = { "TIFR4" };
const prog_char pcifr[] = { "PCIFR" };
const prog_char eifr[] = { "EIFR" };
const prog_char eimsk[] = { "EIMSK" };
const prog_char gpior0[] = { "GPIOR0" };
const prog_char eecr[] = { "EECR" };
const prog_char eedr[] = { "EEDR" };
const prog_char eearl[] = { "EEARL" };
const prog_char eearh[] = { "EEARH" };
const prog_char gtccr[] = { "GTCCR" };
const prog_char tccr0a[] = { "TCCR0A" };
const prog_char tccr0b[] = { "TCCR0B" };
const prog_char tcnt0[] = { "TCNT0" };
const prog_char ocr0a[] = { "OCR0A" };
const prog_char ocr0b[] = { "OCR0B" };
const prog_char tccr2a[] = { "TCCR2A" };
const prog_char tccr2b[] = { "TCCR2B" };
const prog_char tcnt2[] = { "TCNT2" };
const prog_char ocr2a[] = { "OCR2A" };
const prog_char ocr2b[] = { "OCR2B" };
const prog_char pllcsr[] = { "PLLCSR" };
const prog_char gpior1[] = { "GPIOR1" };
const prog_char gpior2[] = { "GPIOR2" };
const prog_char spcr[] = { "SPCR" };
const prog_char spsr [] = { "SPSR" };
const prog_char spdr[] = { "SPDR" };
const prog_char acsr[] = { "ACSR" };
const prog_char ocdr[] = { "OCDR" };
const prog_char pllfrq[] = { "PLLFRQ" };
const prog_char smcr[] = { "SMCR" };
const prog_char mcusr[] = { "MCUSR" };
const prog_char mcucr[] = { "MCUCR" };
const prog_char spmcsr[] = { "SPMCSR" };
const prog_char rampz[] = { "RAMPZ" };
const prog_char spl[] = { "SPL" };
const prog_char sph [] = { "SPH" };
const prog_char sreg[] = { "SREG" };
const prog_char wdtcsr[] = { "WDTCSR" };
const prog_char clkpr[] = { "CLKPR" };
const prog_char prr0[] = { "PRR0" };
const prog_char prr1[] = { "PRR1" };
const prog_char osccal[] = { "OSCCAL" };
const prog_char rcctrl[] = { "RCCTRL" };
const prog_char pcicr[] = { "PCICR" };
const prog_char eicra[] = { "EICRA" };
const prog_char eicrb[] = { "EICRB" };
const prog_char pcmsk0[] = { "PCMSK0" };
const prog_char timsk0[] = { "TIMSK0" };
const prog_char timsk1[] = { "TIMSK1" };
const prog_char timsk2[] = { "TIMSK2" };
const prog_char timsk3[] = { "TIMSK3" };
const prog_char timsk4[] = { "TIMSK4" };
const prog_char adcl[] = { "ADCL" };
const prog_char adch[] = { "ADCH" };
const prog_char adcsra[] = { "ADCSRA" };
const prog_char adcsrb[] = { "ADCSRB" };
const prog_char admux[] = { "ADMUX" };
const prog_char didr2[] = { "DIDR2" };
const prog_char didr0[] = { "DIDR0" };
const prog_char didr1[] = { "DIDR1" };
const prog_char tccr1a[] = { "TCCR1A" };
const prog_char tccr1b[] = { "TCCR1B" };
const prog_char tccr1c[] = { "TCCR1C" };
const prog_char tcnt1l[] = { "TCNT1L" };
const prog_char tcnt1h[] = { "TCNT1H" };
const prog_char icr1l[] = { "ICR1L" };
const prog_char icr1h[] = { "ICR1H" };
const prog_char ocr1al[] = { "OCR1AL" };
const prog_char ocr1ah[] = { "OCR1AH" };
const prog_char ocr1bl[] = { "OCR1BL" };
const prog_char ocr1bh[] = { "OCR1BH" };
const prog_char ocr1cl[] = { "OCR1CL" };
const prog_char ocr1ch[] = { "OCR1CH" };
const prog_char tccr3a[] = { "TCCR3A" };
const prog_char tccr3b[] = { "TCCR3B" };
const prog_char tccr3c[] = { "TCCR3C" };
const prog_char tcnt3l[] = { "TCNT3L" };
const prog_char tcnt3h[] = { "TCNT3H" };
const prog_char icr3l[] = { "ICR3L" };
const prog_char icr3h[] = { "ICR3H" };
const prog_char ocr3al[] = { "OCR3AL" };
const prog_char ocr3ah[] = { "OCR3AH" };
const prog_char ocr3bl[] = { "OCR3BL" };
const prog_char ocr3bh[] = { "OCR3BH" };
const prog_char ocr3cl[] = { "OCR3CL" };
const prog_char ocr3ch[] = { "OCR3CH" };
const prog_char twbr[] = { "TWBR" };
const prog_char twsr[] = { "TWSR" };
const prog_char twar[] = { "TWAR" };
const prog_char twdr[] = { "TWDR" };
const prog_char twcr[] = { "TWCR" };
const prog_char twamr[] = { "TWAMR" };
const prog_char tcnt4[] = { "TCNT4" };
const prog_char tc4h[] = { "TC4H" };
const prog_char tccr4a[] = { "TCCR4A" };
const prog_char tccr4b[] = { "TCCR4B" };
const prog_char tccr4c[] = { "TCCR4C" };
const prog_char tccr4d[] = { "TCCR4D" };
const prog_char tccr4e[] = { "TCCR4E" };
const prog_char clksel0[] = { "CLKSEL0" };
const prog_char clksel1[] = { "CLKSEL1" };
const prog_char clksta[] = { "CLKSTA" };
const prog_char ucsr1a[] = { "UCSR1A" };
const prog_char ucsr1b[] = { "UCSR1B" };
const prog_char ucsr1c[] = { "UCSR1C" };
const prog_char ubrr1l[] = { "UBRR1L" };
const prog_char ubrr1h[] = { "UBRR1H" };
const prog_char udr1[] = { "UDR1" };
const prog_char ocr4a[] = { "OCR4A" };
const prog_char ocr4b[] = { "OCR4B" };
const prog_char ocr4c[] = { "OCR4C" };
const prog_char ocr4d[] = { "OCR4D" };
const prog_char dt4[] = { "DT4" };
const prog_char uhwcon[] = { "UHWCON" };
const prog_char usbcon[] = { "USBCON" };
const prog_char usbsta[] = { "USBSTA" };
const prog_char usbint[] = { "USBINT" };
const prog_char udcon[] = { "UDCON" };
const prog_char udint[] = { "UDINT" };
const prog_char udien[] = { "UDIEN" };
const prog_char udaddr[] = { "UDADDR" };
const prog_char udfnuml[] = { "UDFNUML" };
const prog_char udfnumh[] = { "UDFNUMH" };
const prog_char udmfn[] = { "UDMFN" };
const prog_char ueintx[] = { "UEINTX" };
const prog_char uenum[] = { "UENUM" };
const prog_char uerst[] = { "UERST" };
const prog_char ueconx[] = { "UECONX" };
const prog_char uecfg0x[] = { "UECFG0X" };
const prog_char uecfg1x[] = { "UECFG1X" };
const prog_char uesta0x[] = { "UESTA0X" };
const prog_char uesta1x[] = { "UESTA1X" };
const prog_char ueienx[] = { "UEIENX" };
const prog_char uedatx[] = { "UEDATX" };
const prog_char uebclx[] = { "UEBCLX" };
const prog_char uebchx[] = { "UEBCHX" };
const prog_char ueint[] = { "UEINT" };

const reg_desc_t regdesc[REGCOUNT] = {
    { 0x023, pinb },
    { 0x024, ddrb },
    { 0x025, portb },
    { 0x026, pinc },
    { 0x027, ddrc },
    { 0x028, portc },
    { 0x029, pind },
    { 0x02a, ddrd },
    { 0x02b, portd },
    { 0x02c, pine },
    { 0x02d, ddre },
    { 0x02e, porte },
    { 0x02f, pinf },
    { 0x030, ddrf },
    { 0x031, portf },
    { 0x035, tifr0 },
    { 0x036, tifr1 },
    { 0x037, tifr2 },
    { 0x038, tifr3 },
    { 0x039, tifr4 },
    { 0x03b, pcifr },
    { 0x03c, eifr },
    { 0x03d, eimsk },
    { 0x03e, gpior0 },
    { 0x03f, eecr },
    { 0x040, eedr },
    { 0x041, eearl },
    { 0x042, eearh },
    { 0x043, gtccr },
    { 0x044, tccr0a },
    { 0x045, tccr0b },
    { 0x046, tcnt0 },
    { 0x047, ocr0a },
    { 0x048, ocr0b },
    { 0x049, pllcsr },
    { 0x04a, gpior1 },
    { 0x04b, gpior2 },
    { 0x04c, spcr },
    { 0x04d, spsr },
    { 0x04e, spdr },
    { 0x050, acsr },
    { 0x051, ocdr },
    { 0x052, pllfrq },
    { 0x053, smcr },
    { 0x054, mcusr },
    { 0x055, mcucr },
    { 0x057, spmcsr },
    { 0x05b, rampz },
    { 0x05d, spl },
    { 0x05e, sph },
    { 0x05f, sreg },
    { 0x060, wdtcsr },
    { 0x061, clkpr },
    { 0x064, prr0 },
    { 0x065, prr1 },
    { 0x066, osccal },
    { 0x067, rcctrl },
    { 0x068, pcicr },
    { 0x069, eicra },
    { 0x06a, eicrb },
    { 0x06b, pcmsk0 },
    { 0x06e, timsk0 },
    { 0x06f, timsk1 },
    { 0x070, timsk2 },
    { 0x071, timsk3 },
    { 0x072, timsk4 },
    { 0x078, adcl },
    { 0x079, adch },
    { 0x07a, adcsra },
    { 0x07b, adcsrb },
    { 0x07c, admux },
    { 0x07d, didr2 },
    { 0x07e, didr0 },
    { 0x07f, didr1 },
    { 0x080, tccr1a },
    { 0x081, tccr1b },
    { 0x082, tccr1c },
    { 0x084, tcnt1l },
    { 0x085, tcnt1h },
    { 0x086, icr1l },
    { 0x087, icr1h },
    { 0x088, ocr1al },
    { 0x089, ocr1ah },
    { 0x08a, ocr1bl },
    { 0x08b, ocr1bh },
    { 0x08c, ocr1cl },
    { 0x08d, ocr1ch },
    { 0x090, tccr3a },
    { 0x091, tccr3b },
    { 0x092, tccr3c },
    { 0x094, tcnt3l },
    { 0x095, tcnt3h },
    { 0x096, icr3l },
    { 0x097, icr3h },
    { 0x098, ocr3al },
    { 0x099, ocr3ah },
    { 0x09a, ocr3bl },
    { 0x09b, ocr3bh },
    { 0x09c, ocr3cl },
    { 0x09d, ocr3ch },
    { 0x0b0, tccr2a },
    { 0x0b1, tccr2b },
    { 0x0b2, tcnt2 },
    { 0x0b3, ocr2a },
    { 0x0b4, ocr2b },
    { 0x0b8, twbr },
    { 0x0b9, twsr },
    { 0x0ba, twar },
    { 0x0bb, twdr },
    { 0x0bc, twcr },
    { 0x0bd, twamr },
    { 0x0be, tcnt4 },
    { 0x0bf, tc4h },
    { 0x0c0, tccr4a },
    { 0x0c1, tccr4b },
    { 0x0c2, tccr4c },
    { 0x0c3, tccr4d },
    { 0x0c4, tccr4e },
    { 0x0c5, clksel0 },
    { 0x0c6, clksel1 },
    { 0x0c7, clksta },
    { 0x0c8, ucsr1a },
    { 0x0c9, ucsr1b },
    { 0x0ca, ucsr1c },
    { 0x0cc, ubrr1l },
    { 0x0cd, ubrr1h },
    { 0x0ce, udr1 },
    { 0x0cf, ocr4a },
    { 0x0d0, ocr4b },
    { 0x0d1, ocr4c },
    { 0x0d2, ocr4d },
    { 0x0d4, dt4 },
    { 0x0d7, uhwcon },
    { 0x0d8, usbcon },
    { 0x0d9, usbsta },
    { 0x0da, usbint },
    { 0x0e0, udcon },
    { 0x0e1, udint },
    { 0x0e2, udien },
    { 0x0e3, udaddr },
    { 0x0e4, udfnuml },
    { 0x0e5, udfnumh },
    { 0x0e6, udmfn },
    { 0x0e8, ueintx },
    { 0x0e9, uenum },
    { 0x0ea, uerst },
    { 0x0eb, ueconx },
    { 0x0ec, uecfg0x },
    { 0x0ed, uecfg1x },
    { 0x0ee, uesta0x },
    { 0x0ef, uesta1x },
    { 0x0f0, ueienx },
    { 0x0f1, uedatx },
    { 0x0f2, uebclx },
    { 0x0f3, uebchx },
    { 0x0f4, ueint }
};

extern const prog_char pinb[] PROGMEM;
extern const prog_char ddrb[] PROGMEM;
extern const prog_char portb[] PROGMEM;
extern const prog_char pinc[] PROGMEM;
extern const prog_char ddrc[] PROGMEM;
extern const prog_char portc[] PROGMEM;
extern const prog_char pind[] PROGMEM;
extern const prog_char ddrd[] PROGMEM;
extern const prog_char portd[] PROGMEM;
extern const prog_char pine[] PROGMEM;
extern const prog_char ddre[] PROGMEM;
extern const prog_char porte[] PROGMEM;
extern const prog_char pinf[] PROGMEM;
extern const prog_char ddrf[] PROGMEM;
extern const prog_char portf[] PROGMEM;
extern const prog_char tifr0[] PROGMEM;
extern const prog_char tifr1[] PROGMEM;
extern const prog_char tifr2[] PROGMEM;
extern const prog_char tifr3[] PROGMEM;
extern const prog_char tifr4[] PROGMEM;
extern const prog_char pcifr[] PROGMEM;
extern const prog_char eifr[] PROGMEM;
extern const prog_char eimsk[] PROGMEM;
extern const prog_char gpior0[] PROGMEM;
extern const prog_char eecr[] PROGMEM;
extern const prog_char eedr[] PROGMEM;
extern const prog_char eearl[] PROGMEM;
extern const prog_char eearh[] PROGMEM;
extern const prog_char gtccr[] PROGMEM;
extern const prog_char tccr0a[] PROGMEM;
extern const prog_char tccr0b[] PROGMEM;
extern const prog_char tcnt0[] PROGMEM;
extern const prog_char ocr0a[] PROGMEM;
extern const prog_char ocr0b[] PROGMEM;
extern const prog_char tccr2a[] PROGMEM;
extern const prog_char tccr2b[] PROGMEM;
extern const prog_char tcnt2[] PROGMEM;
extern const prog_char ocr2a[] PROGMEM;
extern const prog_char ocr2b[] PROGMEM;
extern const prog_char pllcsr[] PROGMEM;
extern const prog_char gpior1[] PROGMEM;
extern const prog_char gpior2[] PROGMEM;
extern const prog_char spcr[] PROGMEM;
extern const prog_char spsr [] PROGMEM;
extern const prog_char spdr[] PROGMEM;
extern const prog_char acsr[] PROGMEM;
extern const prog_char ocdr[] PROGMEM;
extern const prog_char pllfrq[] PROGMEM;
extern const prog_char smcr[] PROGMEM;
extern const prog_char mcusr[] PROGMEM;
extern const prog_char mcucr[] PROGMEM;
extern const prog_char spmcsr[] PROGMEM;
extern const prog_char rampz[] PROGMEM;
extern const prog_char spl[] PROGMEM;
extern const prog_char sph [] PROGMEM;
extern const prog_char sreg[] PROGMEM;
extern const prog_char wdtcsr[] PROGMEM;
extern const prog_char clkpr[] PROGMEM;
extern const prog_char prr0[] PROGMEM;
extern const prog_char prr1[] PROGMEM;
extern const prog_char osccal[] PROGMEM;
extern const prog_char rcctrl[] PROGMEM;
extern const prog_char pcicr[] PROGMEM;
extern const prog_char eicra[] PROGMEM;
extern const prog_char eicrb[] PROGMEM;
extern const prog_char pcmsk0[] PROGMEM;
extern const prog_char timsk0[] PROGMEM;
extern const prog_char timsk1[] PROGMEM;
extern const prog_char timsk2[] PROGMEM;
extern const prog_char timsk3[] PROGMEM;
extern const prog_char timsk4[] PROGMEM;
extern const prog_char adcl[] PROGMEM;
extern const prog_char adch[] PROGMEM;
extern const prog_char adcsra[] PROGMEM;
extern const prog_char adcsrb[] PROGMEM;
extern const prog_char admux[] PROGMEM;
extern const prog_char didr2[] PROGMEM;
extern const prog_char didr0[] PROGMEM;
extern const prog_char didr1[] PROGMEM;
extern const prog_char tccr1a[] PROGMEM;
extern const prog_char tccr1b[] PROGMEM;
extern const prog_char tccr1c[] PROGMEM;
extern const prog_char tcnt1l[] PROGMEM;
extern const prog_char tcnt1h[] PROGMEM;
extern const prog_char icr1l[] PROGMEM;
extern const prog_char icr1h[] PROGMEM;
extern const prog_char ocr1al[] PROGMEM;
extern const prog_char ocr1ah[] PROGMEM;
extern const prog_char ocr1bl[] PROGMEM;
extern const prog_char ocr1bh[] PROGMEM;
extern const prog_char ocr1cl[] PROGMEM;
extern const prog_char ocr1ch[] PROGMEM;
extern const prog_char tccr3a[] PROGMEM;
extern const prog_char tccr3b[] PROGMEM;
extern const prog_char tccr3c[] PROGMEM;
extern const prog_char tcnt3l[] PROGMEM;
extern const prog_char tcnt3h[] PROGMEM;
extern const prog_char icr3l[] PROGMEM;
extern const prog_char icr3h[] PROGMEM;
extern const prog_char ocr3al[] PROGMEM;
extern const prog_char ocr3ah[] PROGMEM;
extern const prog_char ocr3bl[] PROGMEM;
extern const prog_char ocr3bh[] PROGMEM;
extern const prog_char ocr3cl[] PROGMEM;
extern const prog_char ocr3ch[] PROGMEM;
extern const prog_char twbr[] PROGMEM;
extern const prog_char twsr[] PROGMEM;
extern const prog_char twar[] PROGMEM;
extern const prog_char twdr[] PROGMEM;
extern const prog_char twcr[] PROGMEM;
extern const prog_char twamr[] PROGMEM;
extern const prog_char tcnt4[] PROGMEM;
extern const prog_char tc4h[] PROGMEM;
extern const prog_char tccr4a[] PROGMEM;
extern const prog_char tccr4b[] PROGMEM;
extern const prog_char tccr4c[] PROGMEM;
extern const prog_char tccr4d[] PROGMEM;
extern const prog_char tccr4e[] PROGMEM;
extern const prog_char clksel0[] PROGMEM;
extern const prog_char clksel1[] PROGMEM;
extern const prog_char clksta[] PROGMEM;
extern const prog_char ucsr1a[] PROGMEM;
extern const prog_char ucsr1b[] PROGMEM;
extern const prog_char ucsr1c[] PROGMEM;
extern const prog_char ubrr1l[] PROGMEM;
extern const prog_char ubrr1h[] PROGMEM;
extern const prog_char udr1[] PROGMEM;
extern const prog_char ocr4a[] PROGMEM;
extern const prog_char ocr4b[] PROGMEM;
extern const prog_char ocr4c[] PROGMEM;
extern const prog_char ocr4d[] PROGMEM;
extern const prog_char dt4[] PROGMEM;
extern const prog_char uhwcon[] PROGMEM;
extern const prog_char usbcon[] PROGMEM;
extern const prog_char usbsta[] PROGMEM;
extern const prog_char usbint[] PROGMEM;
extern const prog_char udcon[] PROGMEM;
extern const prog_char udint[] PROGMEM;
extern const prog_char udien[] PROGMEM;
extern const prog_char udaddr[] PROGMEM;
extern const prog_char udfnuml[] PROGMEM;
extern const prog_char udfnumh[] PROGMEM;
extern const prog_char udmfn[] PROGMEM;
extern const prog_char ueintx[] PROGMEM;
extern const prog_char uenum[] PROGMEM;
extern const prog_char uerst[] PROGMEM;
extern const prog_char ueconx[] PROGMEM;
extern const prog_char uecfg0x[] PROGMEM;
extern const prog_char uecfg1x[] PROGMEM;
extern const prog_char uesta0x[] PROGMEM;
extern const prog_char uesta1x[] PROGMEM;
extern const prog_char ueienx[] PROGMEM;
extern const prog_char uedatx[] PROGMEM;
extern const prog_char uebclx[] PROGMEM;
extern const prog_char uebchx[] PROGMEM;
extern const prog_char ueint[] PROGMEM;

extern PROGMEM const reg_desc_t regdesc[REGCOUNT];

#elif defined(DUMP_SANGUINO) || \
	   defined(DUMP_DAIDUINO)

#if defined(DUMP_SANGUINO)
#define REGCOUNT 98
#endif
#if defined(DUMP_DAIDUINO)
#define REGCOUNT 111
#endif

const prog_char pina[] = { "PINA" };
const prog_char ddra[] = { "DDRA" };
const prog_char porta[] = { "PORTA" };
const prog_char pinb[] = { "PINB" };
const prog_char ddrb[] = { "DDRB" };
const prog_char portb[] = { "PORTB" };
const prog_char pinc[] = { "PINC" };
const prog_char ddrc[] = { "DDRC" };
const prog_char portc[] = { "PORTC" };
const prog_char pind[] = { "PIND" };
const prog_char ddrd[] = { "DDRD" };
const prog_char portd[] = { "PORTD" };
const prog_char tifr0[] = { "TIFR0" };
const prog_char tifr1[] = { "TIFR1" };
const prog_char tifr2[] = { "TIFR2" };

#if defined(DUMP_DAIDUINO)
const prog_char tifr3[] = { "TIFR3" };
#endif

const prog_char pcifr[] = { "PCIFR" };
const prog_char eifr[] = { "EIFR" };
const prog_char eimsk[] = { "EIMSK" };
const prog_char gpior0[] = { "GPIOR0" };
const prog_char gpior1[] = { "GPIOR1" };
const prog_char gpior2[] = { "GPIOR2" };
const prog_char eecr[] = { "EECR" };
const prog_char eedr[] = { "EEDR" };
const prog_char eearl[] = { "EEARL" };
const prog_char eearh[] = { "EEARH" };
const prog_char gtccr[] = { "GTCCR" };
const prog_char tccr0a[] = { "TCCR0A" };
const prog_char tccr0b[] = { "TCCR0B" };
const prog_char tcnt0[] = { "TCNT0" };
const prog_char ocr0a[] = { "OCR0A" };
const prog_char ocr0b[] = { "OCR0B" };
const prog_char spcr[] = { "SPCR" };
const prog_char spsr[] = { "SPSR" };
const prog_char spdr[] = { "SPDR" };
const prog_char acsr[] = { "ACSR" };
const prog_char ocdr[] = { "OCDR" };
const prog_char smcr[] = { "SMCR" };
const prog_char mcusr[] = { "MCUSR" };
const prog_char mcucr[] = { "MCUCR" };
const prog_char spmcsr[] = { "SPMCSR" };
const prog_char spl[] = { "SPL" };
const prog_char sph[] = { "SPH" };
const prog_char sreg[] = { "SREG" };
const prog_char wdtcsr[] = { "WDTCSR" };
const prog_char clkpr[] = { "CLKPR" };
const prog_char prr[] = { "PRR" };
const prog_char osccal[] = { "OSCCAL" };
const prog_char pcicr[] = { "PCICR" };
const prog_char eicra[] = { "EICRA" };
const prog_char pcmsk0[] = { "PCMSK0" };
const prog_char pcmsk1[] = { "PCMSK1" };
const prog_char pcmsk2[] = { "PCMSK2" };
const prog_char pcmsk3[] = { "PCMSK3" };
const prog_char timsk0[] = { "TIMSK0" };
const prog_char timsk1[] = { "TIMSK1" };
const prog_char timsk2[] = { "TIMSK2" };

#if defined(DUMP_DAIDUINO)
const prog_char timsk3[] = { "TIMSK3" };
#endif

const prog_char adcl[] = { "ADCL" };
const prog_char adch[] = { "ADCH" };
const prog_char adcsra[] = { "ADCSRA" };
const prog_char adcsrb[] = { "ADCSRB" };
const prog_char admux[] = { "ADMUX" };
const prog_char didr0[] = { "DIDR0" };
const prog_char didr1[] = { "DIDR1" };
const prog_char tccr1a[] = { "TCCR1A" };
const prog_char tccr1b[] = { "TCCR1B" };
const prog_char tccr1c[] = { "TCCR1C" };
const prog_char tcnt1l[] = { "TCNT1L" };
const prog_char tcnt1h[] = { "TCNT1H" };
const prog_char icr1l[] = { "ICR1L" };
const prog_char icr1h[] = { "ICR1H" };
const prog_char ocr1al[] = { "OCR1AL" };
const prog_char ocr1ah[] = { "OCR1AH" };
const prog_char ocr1bl[] = { "OCR1BL" };
const prog_char ocr1bh[] = { "OCR1BH" };

#if defined(DUMP_DAIDUINO)
const prog_char tccr3a[] = { "TCCR3A" };
const prog_char tccr3b[] = { "TCCR3B" };
const prog_char tccr3c[] = { "TCCR3C" };
const prog_char tcnt3l[] = { "TCNT3L" };
const prog_char tcnt3h[] = { "TCNT3H" };
const prog_char icr3l[] = { "ICR3L" };
const prog_char icr3h[] = { "ICR3H" };
const prog_char ocr3al[] = { "OCR3AL" };
const prog_char ocr3ah[] = { "OCR3AH" };
const prog_char ocr3bl[] = { "OCR3BL" };
const prog_char ocr3bh[] = { "OCR3BH" };
#endif

const prog_char tccr2a[] = { "TCCR2A" };
const prog_char tccr2b[] = { "TCCR2B" };
const prog_char tcnt2[] = { "TCNT2" };
const prog_char ocr2a[] = { "OCR2A" };
const prog_char ocr2b[] = { "OCR2B" };
const prog_char assr[] = { "ASSR" };
const prog_char twar[] = { "TWAR" };
const prog_char twbr[] = { "TWBR" };
const prog_char twcr[] = { "TWCR" };
const prog_char twdr[] = { "TWDR" };
const prog_char twsr[] = { "TWSR" };
const prog_char twamr[] = { "TWAMR" };
const prog_char ucsr0a[] = { "UCSR0A" };
const prog_char ucsr0b[] = { "UCSR0B" };
const prog_char ucsr0c[] = { "UCSR0C" };
const prog_char ubrr0l[] = { "UBRR0L" };
const prog_char ubrr0h[] = { "UBRR0H" };
const prog_char udr0[] = { "UDR0" };
const prog_char ucsr1a[] = { "UCSR1A" };
const prog_char ucsr1b[] = { "UCSR1B" };
const prog_char ucsr1c[] = { "UCSR1C" };
const prog_char ubrr1l[] = { "UBRR1L" };
const prog_char ubrr1h[] = { "UBRR1H" };
const prog_char udr1[] = { "UDR1" };

const reg_desc_t regdesc[REGCOUNT] = {
    { 0x20, pina },
    { 0x21, ddra },
    { 0x22, porta },
    { 0x23, pinb },
    { 0x24, ddrb },
    { 0x25, portb },
    { 0x26, pinc },
    { 0x27, ddrc },
    { 0x28, portc },
    { 0x29, pind },
    { 0x2a, ddrd },
    { 0x2b, portd },
    { 0x35, tifr0 },
    { 0x36, tifr1 },
    { 0x37, tifr2 },
#if defined(DUMP_DAIDUINO)
    { 0x38, tifr3 },
#endif
    { 0x3b, pcifr },
    { 0x3c, eifr },
    { 0x3d, eimsk },
    { 0x3e, gpior0 },
    { 0x3f, eecr },
    { 0x40, eedr },
    { 0x41, eearl },
    { 0x42, eearh },
    { 0x43, gtccr },
    { 0x44, tccr0a },
    { 0x45, tccr0b },
    { 0x46, tcnt0 },
    { 0x47, ocr0a },
    { 0x48, ocr0b },
    { 0x4a, gpior1 },
    { 0x4b, gpior2 },
    { 0x4c, spcr },
    { 0x4d, spsr },
    { 0x4e, spdr },
    { 0x50, acsr },
    { 0x51, ocdr },
    { 0x53, smcr },
    { 0x54, mcusr },
    { 0x55, mcucr },
    { 0x57, spmcsr },
    { 0x5d, spl },
    { 0x5e, sph },
    { 0x5f, sreg },
    { 0x60, wdtcsr },
    { 0x61, clkpr },
    { 0x64, prr },
    { 0x66, osccal },
    { 0x68, pcicr },
    { 0x69, eicra },
    { 0x6b, pcmsk0 },
    { 0x6c, pcmsk1 },
    { 0x6d, pcmsk2 },
    { 0x6e, timsk0 },
    { 0x6f, timsk1 },
    { 0x70, timsk2 },
#if defined(DUMP_DAIDUINO)
    { 0x71, timsk3 },
#endif
    { 0x73, pcmsk3 },
    { 0x78, adcl },
    { 0x79, adch },
    { 0x7a, adcsra },
    { 0x7b, adcsrb },
    { 0x7c, admux },
    { 0x7e, didr0 },
    { 0x7f, didr1 },
    { 0x80, tccr1a },
    { 0x81, tccr1b },
    { 0x82, tccr1c },
    { 0x84, tcnt1l },
    { 0x85, tcnt1h },
    { 0x86, icr1l },
    { 0x87, icr1h },
    { 0x88, ocr1al },
    { 0x89, ocr1ah },
    { 0x8a, ocr1bl },
    { 0x8b, ocr1bh },
#if defined(DUMP_DAIDUINO)
    { 0x90, tccr3a },
    { 0x91, tccr3b },
    { 0x92, tccr3c },
    { 0x94, tcnt3l },
    { 0x95, tcnt3h },
    { 0x96, icr3l },
    { 0x97, icr3h },
    { 0x98, ocr3al },
    { 0x99, ocr3ah },
    { 0x9a, ocr3bl },
    { 0x9b, ocr3bh },
#endif
    { 0xb0, tccr2a },
    { 0xb1, tccr2b },
    { 0xb2, tcnt2 },
    { 0xb3, ocr2a },
    { 0xb4, ocr2b },
    { 0xb6, assr },
    { 0xb8, twbr },
    { 0xb9, twsr },
    { 0xba, twar },
    { 0xbb, twdr },
    { 0xbc, twcr },
    { 0xbd, twamr },
    { 0xc0, ucsr0a },
    { 0xc1, ucsr0b },
    { 0xc2, ucsr0c },
    { 0xc4, ubrr0l },
    { 0xc5, ubrr0h },
    { 0xc6, udr0 },
    { 0xc8, ucsr1a },
    { 0xc9, ucsr1b },
    { 0xca, ucsr1c },
    { 0xcc, ubrr1l },
    { 0xcd, ubrr1h },
    { 0xce, udr1 }
};

extern const prog_char pina[] PROGMEM;
extern const prog_char ddra[] PROGMEM;
extern const prog_char porta[] PROGMEM;
extern const prog_char pinb[] PROGMEM;
extern const prog_char ddrb[] PROGMEM;
extern const prog_char portb[] PROGMEM;
extern const prog_char pinc[] PROGMEM;
extern const prog_char ddrc[] PROGMEM;
extern const prog_char portc[] PROGMEM;
extern const prog_char pind[] PROGMEM;
extern const prog_char ddrd[] PROGMEM;
extern const prog_char portd[] PROGMEM;
extern const prog_char tifr0[] PROGMEM;
extern const prog_char tifr1[] PROGMEM;
extern const prog_char tifr2[] PROGMEM;
extern const prog_char pcifr[] PROGMEM;
extern const prog_char eifr[] PROGMEM;
extern const prog_char eimsk[] PROGMEM;
extern const prog_char gpior0[] PROGMEM;
extern const prog_char gpior1[] PROGMEM;
extern const prog_char gpior2[] PROGMEM;
extern const prog_char eecr[] PROGMEM;
extern const prog_char eedr[] PROGMEM;
extern const prog_char eearl[] PROGMEM;
extern const prog_char eearh[] PROGMEM;
extern const prog_char gtccr[] PROGMEM;
extern const prog_char tccr0a[] PROGMEM;
extern const prog_char tccr0b[] PROGMEM;
extern const prog_char tcnt0[] PROGMEM;
extern const prog_char ocr0a[] PROGMEM;
extern const prog_char ocr0b[] PROGMEM;
extern const prog_char spcr[] PROGMEM;
extern const prog_char spsr[] PROGMEM;
extern const prog_char spdr[] PROGMEM;
extern const prog_char acsr[] PROGMEM;
extern const prog_char ocdr[] PROGMEM;
extern const prog_char smcr[] PROGMEM;
extern const prog_char mcusr[] PROGMEM;
extern const prog_char mcucr[] PROGMEM;
extern const prog_char spmcsr[] PROGMEM;
extern const prog_char spl[] PROGMEM;
extern const prog_char sph[] PROGMEM;
extern const prog_char sreg[] PROGMEM;
extern const prog_char wdtcsr[] PROGMEM;
extern const prog_char clkpr[] PROGMEM;
extern const prog_char prr[] PROGMEM;
extern const prog_char osccal[] PROGMEM;
extern const prog_char pcicr[] PROGMEM;
extern const prog_char eicra[] PROGMEM;
extern const prog_char pcmsk0[] PROGMEM;
extern const prog_char pcmsk1[] PROGMEM;
extern const prog_char pcmsk2[] PROGMEM;
extern const prog_char timsk0[] PROGMEM;
extern const prog_char timsk1[] PROGMEM;
extern const prog_char timsk2[] PROGMEM;
extern const prog_char pcmsk3[] PROGMEM;
extern const prog_char adcl[] PROGMEM;
extern const prog_char adch[] PROGMEM;
extern const prog_char adcsra[] PROGMEM;
extern const prog_char adcsrb[] PROGMEM;
extern const prog_char admux[] PROGMEM;
extern const prog_char didr0[] PROGMEM;
extern const prog_char didr1[] PROGMEM;
extern const prog_char tccr1a[] PROGMEM;
extern const prog_char tccr1b[] PROGMEM;
extern const prog_char tccr1c[] PROGMEM;
extern const prog_char tcnt1l[] PROGMEM;
extern const prog_char tcnt1h[] PROGMEM;
extern const prog_char icr1l[] PROGMEM;
extern const prog_char icr1h[] PROGMEM;
extern const prog_char ocr1al[] PROGMEM;
extern const prog_char ocr1ah[] PROGMEM;
extern const prog_char ocr1bl[] PROGMEM;
extern const prog_char ocr1bh[] PROGMEM;
extern const prog_char tccr2a[] PROGMEM;
extern const prog_char tccr2b[] PROGMEM;
extern const prog_char tcnt2[] PROGMEM;
extern const prog_char ocr2a[] PROGMEM;
extern const prog_char ocr2b[] PROGMEM;
extern const prog_char assr[] PROGMEM;
extern const prog_char twar[] PROGMEM;
extern const prog_char twbr[] PROGMEM;
extern const prog_char twcr[] PROGMEM;
extern const prog_char twdr[] PROGMEM;
extern const prog_char twsr[] PROGMEM;
extern const prog_char twamr[] PROGMEM;
extern const prog_char ucsr0a[] PROGMEM;
extern const prog_char ucsr0b[] PROGMEM;
extern const prog_char ucsr0c[] PROGMEM;
extern const prog_char ubrr0l[] PROGMEM;
extern const prog_char ubrr0h[] PROGMEM;
extern const prog_char udr0[] PROGMEM;
extern const prog_char ucsr1a[] PROGMEM;
extern const prog_char ucsr1b[] PROGMEM;
extern const prog_char ucsr1c[] PROGMEM;
extern const prog_char ubrr1l[] PROGMEM;
extern const prog_char ubrr1h[] PROGMEM;
extern const prog_char udr1[] PROGMEM;

#if defined(DAIDUINO)
extern const prog_char tifr3[] PROGMEM;
extern const prog_char timsk3[] PROGMEM;
extern const prog_char tccr3a[] PROGMEM;
extern const prog_char tccr3b[] PROGMEM;
extern const prog_char tccr3c[] PROGMEM;
extern const prog_char tcnt3l[] PROGMEM;
extern const prog_char tcnt3h[] PROGMEM;
extern const prog_char icr3l[] PROGMEM;
extern const prog_char icr3h[] PROGMEM;
extern const prog_char ocr3al[] PROGMEM;
extern const prog_char ocr3ah[] PROGMEM;
extern const prog_char ocr3bl[] PROGMEM;
extern const prog_char ocr3bh[] PROGMEM;
#endif

extern PROGMEM const reg_desc_t regdesc[REGCOUNT];

#else
#   error "TODO: Add board type support here."
#endif

const char ss[] PROGMEM = { "  " };

void dumpReg(reg_addr_t reg, const char** name, unsigned char value);

}

void dumpmon::dumpReg(reg_addr_t reg, const char** name, unsigned char value)
{
	using namespace dumpmon;
#if defined(DUMP_ARDUINO) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_SANGUINO) || \
	defined(DUMP_DAIDUINO)
	dumpHexByte(reg);
#elif defined(DUMP_MEGA)
	dumpHexWord(reg);
#else
#   error "TODO: Add board type support here."
#endif
	_serial->print('\t');
	printPgm(name);
	_serial->print('\t');
	dumpHexByte(value);
	printPgm(ss);
	dumpBinByte(value);
	printPgm(ss);
	if (value > ' ' && value < 127)
		_serial->println((char) value);
	else
		_serial->println();
}

void dumpmon::dumpRegisters()
{
	using namespace dumpmon;
    printlnPgm(regtHexBinaryASCII);
    for (unsigned char n = 0 ; n < REGCOUNT; ++n) {
#if defined(DUMP_ARDUINO) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_SANGUINO) || \
	defined(DUMP_DAIDUINO)
        reg_addr_t reg = pgm_read_byte_near(&(regdesc[n].addr));
#elif defined(DUMP_MEGA)
        reg_addr_t reg = pgm_read_word_near(&(regdesc[n].addr));
#else
#   error "TODO: Add board type support here."
#endif
        dumpReg(reg, (const char **)&(regdesc[n].name), _SFR_MEM8(reg));
    }
}
