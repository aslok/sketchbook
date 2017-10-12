//
// C++ Implementation: interrupts
//
// Description: Interrupts dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpdebug.h"
#include "interrupts.h"
#include "printpgm.h"

namespace dumpmon
{

#if defined(DUMP_ARDUINO)

#define DUMP_INT_COUNT 26

const prog_char irqVect0[] = { "RESET" };
const prog_char irqVect1[] = { "INT0" };
const prog_char irqVect2[] = { "INT1" };
const prog_char irqVect3[] = { "PCINT0" };
const prog_char irqVect4[] = { "PCINT1" };
const prog_char irqVect5[] = { "PCINT2" };
const prog_char irqVect6[] = { "WDT" };
const prog_char irqVect7[] = { "TIMER2_COMPA" };
const prog_char irqVect8[] = { "TIMER2_COMPB" };
const prog_char irqVect9[] = { "TIMER2_OVF" };
const prog_char irqVect10[] = { "TIMER1_CAPT" };
const prog_char irqVect11[] = { "TIMER1_COMPA" };
const prog_char irqVect12[] = { "TIMER1_COMPB" };
const prog_char irqVect13[] = { "TIMER1_OVF" };
const prog_char irqVect14[] = { "TIMER0_COMPA" };
const prog_char irqVect15[] = { "TIMER0_COMPB" };
const prog_char irqVect16[] = { "TIMER0_OVF" };
const prog_char irqVect17[] = { "SPI STC" };
const prog_char irqVect18[] = { "USART RX" };
const prog_char irqVect19[] = { "USART UDRE" };
const prog_char irqVect20[] = { "USART TX" };
const prog_char irqVect21[] = { "ADC" };
const prog_char irqVect22[] = { "EE READY" };
const prog_char irqVect23[] = { "ANALOG COMP" };
const prog_char irqVect24[] = { "TWI" };
const prog_char irqVect25[] = { "SPM READY" };

const char* const irqVects[] = {
  irqVect0, irqVect1, irqVect2, irqVect3, irqVect4,
  irqVect5, irqVect6, irqVect7, irqVect8, irqVect9,
  irqVect10, irqVect11, irqVect12, irqVect13, irqVect14,
  irqVect15, irqVect16, irqVect17, irqVect18, irqVect19,
  irqVect20, irqVect21, irqVect22, irqVect23, irqVect24,
  irqVect25
};

extern const prog_char irqVect0[] PROGMEM;
extern const prog_char irqVect1[] PROGMEM;
extern const prog_char irqVect2[] PROGMEM;
extern const prog_char irqVect3[] PROGMEM;
extern const prog_char irqVect4[] PROGMEM;
extern const prog_char irqVect5[] PROGMEM;
extern const prog_char irqVect6[] PROGMEM;
extern const prog_char irqVect7[] PROGMEM;
extern const prog_char irqVect8[] PROGMEM;
extern const prog_char irqVect9[] PROGMEM;
extern const prog_char irqVect10[] PROGMEM;
extern const prog_char irqVect11[] PROGMEM;
extern const prog_char irqVect12[] PROGMEM;
extern const prog_char irqVect13[] PROGMEM;
extern const prog_char irqVect14[] PROGMEM;
extern const prog_char irqVect15[] PROGMEM;
extern const prog_char irqVect16[] PROGMEM;
extern const prog_char irqVect17[] PROGMEM;
extern const prog_char irqVect18[] PROGMEM;
extern const prog_char irqVect19[] PROGMEM;
extern const prog_char irqVect20[] PROGMEM;
extern const prog_char irqVect21[] PROGMEM;
extern const prog_char irqVect22[] PROGMEM;
extern const prog_char irqVect23[] PROGMEM;
extern const prog_char irqVect24[] PROGMEM;
extern const prog_char irqVect25[] PROGMEM;

#elif defined(DUMP_MEGA)

#define DUMP_INT_COUNT 57

const prog_char irqVect0[] = { "RESET" };
const prog_char irqVect1[] = { "INT0" };
const prog_char irqVect2[] = { "INT1" };
const prog_char irqVect3[] = { "INT2" };
const prog_char irqVect4[] = { "INT3" };
const prog_char irqVect5[] = { "INT4" };
const prog_char irqVect6[] = { "INT5" };
const prog_char irqVect7[] = { "INT6" };
const prog_char irqVect8[] = { "INT7" };
const prog_char irqVect9[] = { "PCINT0" };
const prog_char irqVect10[] = { "PCINT1" };
const prog_char irqVect11[] = { "PCINT2" };
const prog_char irqVect12[] = { "WDT" };
const prog_char irqVect13[] = { "TIMER2_COMPA" };
const prog_char irqVect14[] = { "TIMER2_COMPB" };
const prog_char irqVect15[] = { "TIMER2_OVF" };
const prog_char irqVect16[] = { "TIMER1_CAPT" };
const prog_char irqVect17[] = { "TIMER1_COMPA" };
const prog_char irqVect18[] = { "TIMER1_COMPB" };
const prog_char irqVect19[] = { "TIMER1_COMPC" };
const prog_char irqVect20[] = { "TIMER1_OVF" };
const prog_char irqVect21[] = { "TIMER0_COMPA" };
const prog_char irqVect22[] = { "TIMER0_COMPB" };
const prog_char irqVect23[] = { "TIMER0_OVF" };
const prog_char irqVect24[] = { "SPI STC" };
const prog_char irqVect25[] = { "USART0 RX" };
const prog_char irqVect26[] = { "USART0 UDRE" };
const prog_char irqVect27[] = { "USART0 TX" };
const prog_char irqVect28[] = { "ANALOG COMP" };
const prog_char irqVect29[] = { "ADC" };
const prog_char irqVect30[] = { "EE READY" };
const prog_char irqVect31[] = { "TIMER3_CAPT" };
const prog_char irqVect32[] = { "TIMER3_COMPA" };
const prog_char irqVect33[] = { "TIMER3_COMPB" };
const prog_char irqVect34[] = { "TIMER3_COMPC" };
const prog_char irqVect35[] = { "TIMER3_OVF" };
const prog_char irqVect36[] = { "USART1 RX" };
const prog_char irqVect37[] = { "USART1 UDRE" };
const prog_char irqVect38[] = { "USART1 TX" };
const prog_char irqVect39[] = { "TWI" };
const prog_char irqVect40[] = { "SPM READY" };
const prog_char irqVect41[] = { "TIMER4_CAPT" };
const prog_char irqVect42[] = { "TIMER4_COMPA" };
const prog_char irqVect43[] = { "TIMER4_COMPB" };
const prog_char irqVect44[] = { "TIMER4_COMPC" };
const prog_char irqVect45[] = { "TIMER4_OVF" };
const prog_char irqVect46[] = { "TIMER5_CAPT" };
const prog_char irqVect47[] = { "TIMER5_COMPA" };
const prog_char irqVect48[] = { "TIMER5_COMPB" };
const prog_char irqVect49[] = { "TIMER5_COMPC" };
const prog_char irqVect50[] = { "TIMER5_OVF" };
const prog_char irqVect51[] = { "USART2 RX" };
const prog_char irqVect52[] = { "USART2 UDRE" };
const prog_char irqVect53[] = { "USART2 TX" };
const prog_char irqVect54[] = { "USART3 RX" };
const prog_char irqVect55[] = { "USART3 UDRE" };
const prog_char irqVect56[] = { "USART3 TX" };

const char* const irqVects[] = {
  irqVect0, irqVect1, irqVect2, irqVect3, irqVect4,
  irqVect5, irqVect6, irqVect7, irqVect8, irqVect9,
  irqVect10, irqVect11, irqVect12, irqVect13, irqVect14,
  irqVect15, irqVect16, irqVect17, irqVect18, irqVect19,
  irqVect20, irqVect21, irqVect22, irqVect23, irqVect24,
  irqVect25, irqVect26, irqVect27, irqVect28, irqVect29,
  irqVect30, irqVect31, irqVect32, irqVect33, irqVect34,
  irqVect35, irqVect36, irqVect37, irqVect38, irqVect39,
  irqVect40, irqVect41, irqVect42, irqVect43, irqVect44,
  irqVect45, irqVect46, irqVect47, irqVect48, irqVect49,
  irqVect50, irqVect51, irqVect52, irqVect53, irqVect54,
  irqVect55, irqVect56
};

extern const prog_char irqVect0[] PROGMEM;
extern const prog_char irqVect1[] PROGMEM;
extern const prog_char irqVect2[] PROGMEM;
extern const prog_char irqVect3[] PROGMEM;
extern const prog_char irqVect4[] PROGMEM;
extern const prog_char irqVect5[] PROGMEM;
extern const prog_char irqVect6[] PROGMEM;
extern const prog_char irqVect7[] PROGMEM;
extern const prog_char irqVect8[] PROGMEM;
extern const prog_char irqVect9[] PROGMEM;
extern const prog_char irqVect10[] PROGMEM;
extern const prog_char irqVect11[] PROGMEM;
extern const prog_char irqVect12[] PROGMEM;
extern const prog_char irqVect13[] PROGMEM;
extern const prog_char irqVect14[] PROGMEM;
extern const prog_char irqVect15[] PROGMEM;
extern const prog_char irqVect16[] PROGMEM;
extern const prog_char irqVect17[] PROGMEM;
extern const prog_char irqVect18[] PROGMEM;
extern const prog_char irqVect19[] PROGMEM;
extern const prog_char irqVect20[] PROGMEM;
extern const prog_char irqVect21[] PROGMEM;
extern const prog_char irqVect22[] PROGMEM;
extern const prog_char irqVect23[] PROGMEM;
extern const prog_char irqVect24[] PROGMEM;
extern const prog_char irqVect25[] PROGMEM;
extern const prog_char irqVect26[] PROGMEM;
extern const prog_char irqVect27[] PROGMEM;
extern const prog_char irqVect28[] PROGMEM;
extern const prog_char irqVect29[] PROGMEM;
extern const prog_char irqVect30[] PROGMEM;
extern const prog_char irqVect31[] PROGMEM;
extern const prog_char irqVect32[] PROGMEM;
extern const prog_char irqVect33[] PROGMEM;
extern const prog_char irqVect34[] PROGMEM;
extern const prog_char irqVect35[] PROGMEM;
extern const prog_char irqVect36[] PROGMEM;
extern const prog_char irqVect37[] PROGMEM;
extern const prog_char irqVect38[] PROGMEM;
extern const prog_char irqVect39[] PROGMEM;
extern const prog_char irqVect40[] PROGMEM;
extern const prog_char irqVect41[] PROGMEM;
extern const prog_char irqVect42[] PROGMEM;
extern const prog_char irqVect43[] PROGMEM;
extern const prog_char irqVect44[] PROGMEM;
extern const prog_char irqVect45[] PROGMEM;
extern const prog_char irqVect46[] PROGMEM;
extern const prog_char irqVect47[] PROGMEM;
extern const prog_char irqVect48[] PROGMEM;
extern const prog_char irqVect49[] PROGMEM;
extern const prog_char irqVect50[] PROGMEM;
extern const prog_char irqVect51[] PROGMEM;
extern const prog_char irqVect52[] PROGMEM;
extern const prog_char irqVect53[] PROGMEM;
extern const prog_char irqVect54[] PROGMEM;
extern const prog_char irqVect55[] PROGMEM;
extern const prog_char irqVect56[] PROGMEM;

#elif defined(DUMP_LEONARDO)

#define DUMP_INT_COUNT 43

const prog_char irqVect0[] = { "RESET" };
const prog_char irqVect1[] = { "INT0" };
const prog_char irqVect2[] = { "INT1" };
const prog_char irqVect3[] = { "INT2" };
const prog_char irqVect4[] = { "INT3" };
const prog_char irqVectReserved[] = { "reserved" };
const prog_char irqVect7[] = { "INT6" };
const prog_char irqVect9[] = { "PCINT0" };
const prog_char irqVect10[] = { "USB General" };
const prog_char irqVect11[] = { "USB Endpoint" };
const prog_char irqVect12[] = { "WDT" };
const prog_char irqVect13[] = { "TIMER2 COMPA" };
const prog_char irqVect14[] = { "TIMER2 COMPB" };
const prog_char irqVect15[] = { "TIMER2 OVF" };
const prog_char irqVect16[] = { "TIMER1 CAPT" };
const prog_char irqVect17[] = { "TIMER1 COMPA" };
const prog_char irqVect18[] = { "TIMER1 COMPB" };
const prog_char irqVect19[] = { "TIMER1 COMPC" };
const prog_char irqVect20[] = { "TIMER1 OVF" };
const prog_char irqVect21[] = { "TIMER0 COMPA" };
const prog_char irqVect22[] = { "TIMER0 COMPB" };
const prog_char irqVect23[] = { "TIMER0 OVF" };
const prog_char irqVect24[] = { "SPI (STC)" };
const prog_char irqVect25[] = { "USART1 RX" };
const prog_char irqVect26[] = { "USART1 UDRE" };
const prog_char irqVect27[] = { "USART1 TX" };
const prog_char irqVect28[] = { "ANALOG COMP" };
const prog_char irqVect29[] = { "ADC" };
const prog_char irqVect30[] = { "EE READY" };
const prog_char irqVect31[] = { "TIMER3 CAPT" };
const prog_char irqVect32[] = { "TIMER3 COMPA" };
const prog_char irqVect33[] = { "TIMER3 COMPB" };
const prog_char irqVect34[] = { "TIMER3 COMPC" };
const prog_char irqVect35[] = { "TIMER3 OVF" };
const prog_char irqVect36[] = { "TWI" };
const prog_char irqVect37[] = { "SPM READY" };
const prog_char irqVect38[] = { "TIMER4 COMPA" };
const prog_char irqVect39[] = { "TIMER4 COMPB" };
const prog_char irqVect40[] = { "TIMER4 COMPD" };
const prog_char irqVect41[] = { "TIMER4 OVF" };
const prog_char irqVect42[] = { "TIMER4 FPF" };

const char* const irqVects[] = {
  irqVect0, irqVect1, irqVect2, irqVect3, irqVect4,
  irqVectReserved, irqVectReserved, irqVect7, irqVectReserved, irqVect9,
  irqVect10, irqVect11, irqVect12, irqVect13, irqVect14,
  irqVect15, irqVect16, irqVect17, irqVect18, irqVect19,
  irqVect20, irqVect21, irqVect22, irqVect23, irqVect24,
  irqVect25, irqVect26, irqVect27, irqVect28, irqVect29,
  irqVect30, irqVect31, irqVect32, irqVect33, irqVect34,
  irqVect35, irqVect36, irqVect37, irqVect38, irqVect39,
  irqVect40, irqVect41, irqVect42
};

extern const prog_char irqVect0[] PROGMEM;
extern const prog_char irqVect1[] PROGMEM;
extern const prog_char irqVect2[] PROGMEM;
extern const prog_char irqVect3[] PROGMEM;
extern const prog_char irqVect4[] PROGMEM;
extern const prog_char irqVectReserved[] PROGMEM;
extern const prog_char irqVect7[] PROGMEM;
extern const prog_char irqVect9[] PROGMEM;
extern const prog_char irqVect10[] PROGMEM;
extern const prog_char irqVect11[] PROGMEM;
extern const prog_char irqVect12[] PROGMEM;
extern const prog_char irqVect13[] PROGMEM;
extern const prog_char irqVect14[] PROGMEM;
extern const prog_char irqVect15[] PROGMEM;
extern const prog_char irqVect16[] PROGMEM;
extern const prog_char irqVect17[] PROGMEM;
extern const prog_char irqVect18[] PROGMEM;
extern const prog_char irqVect19[] PROGMEM;
extern const prog_char irqVect20[] PROGMEM;
extern const prog_char irqVect21[] PROGMEM;
extern const prog_char irqVect22[] PROGMEM;
extern const prog_char irqVect23[] PROGMEM;
extern const prog_char irqVect24[] PROGMEM;
extern const prog_char irqVect25[] PROGMEM;
extern const prog_char irqVect26[] PROGMEM;
extern const prog_char irqVect27[] PROGMEM;
extern const prog_char irqVect28[] PROGMEM;
extern const prog_char irqVect29[] PROGMEM;
extern const prog_char irqVect30[] PROGMEM;
extern const prog_char irqVect31[] PROGMEM;
extern const prog_char irqVect32[] PROGMEM;
extern const prog_char irqVect33[] PROGMEM;
extern const prog_char irqVect34[] PROGMEM;
extern const prog_char irqVect35[] PROGMEM;
extern const prog_char irqVect36[] PROGMEM;
extern const prog_char irqVect37[] PROGMEM;
extern const prog_char irqVect38[] PROGMEM;
extern const prog_char irqVect39[] PROGMEM;
extern const prog_char irqVect40[] PROGMEM;
extern const prog_char irqVect41[] PROGMEM;
extern const prog_char irqVect42[] PROGMEM;

#elif defined(DUMP_SANGUINO) || \
	   defined(DUMP_DAIDUINO)

#if defined(DUMP_SANGUINO)
#define DUMP_INT_COUNT 31
#endif
#if defined(DUMP_DAIDUINO)
#define DUMP_INT_COUNT 35
#endif

const prog_char irqVect0[] = { "RESET" };
const prog_char irqVect1[] = { "INT0" };
const prog_char irqVect2[] = { "INT1" };
const prog_char irqVect3[] = { "INT2" };
const prog_char irqVect4[] = { "PCINT0" };
const prog_char irqVect5[] = { "PCINT1" };
const prog_char irqVect6[] = { "PCINT2" };
const prog_char irqVect7[] = { "PCINT3" };
const prog_char irqVect8[] = { "WDT" };
const prog_char irqVect9[] = { "TIMER2_COMPA" };
const prog_char irqVect10[] = { "TIMER2_COMPB" };
const prog_char irqVect11[] = { "TIMER2_OVF" };
const prog_char irqVect12[] = { "TIMER1_CAPT" };
const prog_char irqVect13[] = { "TIMER1_COMPA" };
const prog_char irqVect14[] = { "TIMER1_COMPB" };
const prog_char irqVect15[] = { "TIMER1_OVF" };
const prog_char irqVect16[] = { "TIMER0_COMPA" };
const prog_char irqVect17[] = { "TIMER0_COMPB" };
const prog_char irqVect18[] = { "TIMER0_OVF" };
const prog_char irqVect19[] = { "SPI STC" };
const prog_char irqVect20[] = { "USART0 RX" };
const prog_char irqVect21[] = { "USART0 UDRE" };
const prog_char irqVect22[] = { "USART0 TX" };
const prog_char irqVect23[] = { "ANALOG COMP" };
const prog_char irqVect24[] = { "ADC" };
const prog_char irqVect25[] = { "EE READY" };
const prog_char irqVect26[] = { "TWI" };
const prog_char irqVect27[] = { "SPM READY" };
const prog_char irqVect28[] = { "USART1 RX" };
const prog_char irqVect29[] = { "USART1 UDRE" };
const prog_char irqVect30[] = { "USART1 TX" };

#if defined(DUMP_DAIDUINO)
const prog_char irqVect31[] = { "TIMER3_CAPT" };
const prog_char irqVect32[] = { "TIMER3_COMPA" };
const prog_char irqVect33[] = { "TIMER3_COMPB" };
const prog_char irqVect34[] = { "TIMER3_OVF" };
#endif

const char* const irqVects[] = {
  irqVect0, irqVect1, irqVect2, irqVect3, irqVect4,
  irqVect5, irqVect6, irqVect7, irqVect8, irqVect9,
  irqVect10, irqVect11, irqVect12, irqVect13, irqVect14,
  irqVect15, irqVect16, irqVect17, irqVect18, irqVect19,
  irqVect20, irqVect21, irqVect22, irqVect23, irqVect24,
  irqVect25, irqVect26, irqVect27, irqVect28, irqVect29,
  irqVect30
#if defined(DUMP_DAIDUINO)
  , irqVect31, irqVect32, irqVect33, irqVect34
#endif
};

extern const prog_char irqVect0[] PROGMEM;
extern const prog_char irqVect1[] PROGMEM;
extern const prog_char irqVect2[] PROGMEM;
extern const prog_char irqVect3[] PROGMEM;
extern const prog_char irqVect4[] PROGMEM;
extern const prog_char irqVect5[] PROGMEM;
extern const prog_char irqVect6[] PROGMEM;
extern const prog_char irqVect7[] PROGMEM;
extern const prog_char irqVect8[] PROGMEM;
extern const prog_char irqVect9[] PROGMEM;
extern const prog_char irqVect10[] PROGMEM;
extern const prog_char irqVect11[] PROGMEM;
extern const prog_char irqVect12[] PROGMEM;
extern const prog_char irqVect13[] PROGMEM;
extern const prog_char irqVect14[] PROGMEM;
extern const prog_char irqVect15[] PROGMEM;
extern const prog_char irqVect16[] PROGMEM;
extern const prog_char irqVect17[] PROGMEM;
extern const prog_char irqVect18[] PROGMEM;
extern const prog_char irqVect19[] PROGMEM;
extern const prog_char irqVect20[] PROGMEM;
extern const prog_char irqVect21[] PROGMEM;
extern const prog_char irqVect22[] PROGMEM;
extern const prog_char irqVect23[] PROGMEM;
extern const prog_char irqVect24[] PROGMEM;
extern const prog_char irqVect25[] PROGMEM;
extern const prog_char irqVect26[] PROGMEM;
extern const prog_char irqVect27[] PROGMEM;
extern const prog_char irqVect28[] PROGMEM;
extern const prog_char irqVect29[] PROGMEM;
extern const prog_char irqVect30[] PROGMEM;

#if defined(DUMP_DAIDUINO)
extern const prog_char irqVect31[] PROGMEM;
extern const prog_char irqVect32[] PROGMEM;
extern const prog_char irqVect33[] PROGMEM;
extern const prog_char irqVect34[] PROGMEM;
#endif

#else
#   error "TODO: Add board type support here."
#endif

const prog_char jmps0x[] = { "jmp 0x" };
const prog_char rjmps0x[] = { "rjmp 0x" };
extern const prog_char jmps0x[] PROGMEM;
extern const prog_char rjmps0x[] PROGMEM;

bool checkForBad(dump_addr_t addr);

}

bool dumpmon::checkForBad(dump_addr_t addr)
{
	using namespace dumpmon;
    unsigned int tmp = pgm_read_word(addr);
    if (tmp == 0x940C) {
        tmp = pgm_read_word(addr+2);
        if (tmp == 0)
            return true;
    }
    return false;
}

void dumpmon::dumpInterrupts()
{
	using namespace dumpmon;
    dump_addr_t addr = 0;
    dump_addr_t cmd, op;
    dump_addr_t bad = 0;
    _serial->println();
    for (unsigned char n = 0; n < DUMP_INT_COUNT; ++n) {
        dumpAddr(addr);
        printPgm(ss);
        cmd = pgm_read_word(addr);
        addr += 2;
        op = pgm_read_word(addr);
        addr += 2;
        if (cmd == 0x940C) {
            unsigned int op2 = op << 1;
            printPgm(jmps0x);
            dumpAddr(op2);
            if (op && ! bad) {
                if (checkForBad(op2))
                    bad = op;
            }
        }
        else if (hiByte(cmd) == 0xC7) {
        	unsigned int op2 = (addr - 4) + (char) loByte(cmd);
            printPgm(rjmps0x);
            dumpAddr(op2);
        }
        else {
            dumpAddr(cmd);
            _serial->print(' ');
            dumpAddr(op);
        }
        _serial->print('\t');
        _serial->print((cmd == 0x940C && (op == 0 || bad == op)) ? ' ' : '*');
        printPgm(ss);
        printPgm(&(irqVects[n]));
        _serial->println();
    }
}
