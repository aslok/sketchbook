//
// C++ Implementation: memory
//
// Description: Dump memory.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <avr/eeprom.h>
#include "dumpdebug.h"
#include "memory.h"
#include "printpgm.h"

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

namespace dumpmon
{

const prog_char nMemoryDump[] = { "\r\nMemory dump: " };
const prog_char ram[] = { "RAM" };
const prog_char flash[] = { "FLASH" };
const prog_char eeprom[] = { "EEPROM" };

const char* const memType[] = { ram, flash, eeprom };

const prog_char nAvailable[] = { "\r\nAvailable: " };
const prog_char bytes[] = { " Bytes" };

extern const prog_char nMemoryDump[] PROGMEM;
extern const prog_char ram[] PROGMEM;
extern const prog_char flash[] PROGMEM;
extern const prog_char eeprom[] PROGMEM;
extern const prog_char ss[] PROGMEM;

extern PROGMEM const char* const memType[];

extern const prog_char nAvailable[] PROGMEM;
extern const prog_char bytes[] PROGMEM;

unsigned char getByte(dump_addr_t addr, state_t type);
dump_addr_t getMemoryEnd(state_t type);

}

unsigned char dumpmon::getByte(dump_addr_t addr, state_t type)
{
	using namespace dumpmon;
    switch (type)
    {
    case RAM:
        return *((unsigned char*) addr);
    case FLASH:
#if defined(DUMP_ARDUINO) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_SANGUINO)
        return pgm_read_byte_near(addr);
#elif defined(DUMP_MEGA) || \
		defined(DUMP_DAIDUINO)
        if (addr < 0x10000)
            return pgm_read_byte_near(addr);
        else
            return pgm_read_byte_far(addr);
#else
#   error "TODO: Add board support here."
#endif
    case ROM:
        return eeprom_read_byte((unsigned char*) addr);
    default:
    	return 0;
    }
}

dumpmon::dump_addr_t dumpmon::getMemoryEnd(state_t type)
{
	using namespace dumpmon;
    switch (type)
    {
    case RAM:
        return RAMEND;
    case FLASH:
        return FLASHEND;
    case ROM:
        return E2END;
    default:
        return 0;
    }
}

void dumpmon::dumpMemory(dump_addr_t addr, state_t type)
{
	using namespace dumpmon;
    dump_addr_t p = addr;
    dump_addr_t pp;
    char ch;
    unsigned char nEnd = 16;
    dump_addr_t memEnd = getMemoryEnd(type);
    if(p > memEnd+1) {
        p = memEnd+1-256;
        nEnd = 16;
    }
    else
        while (p + (nEnd << 4) > memEnd+1)
            --nEnd;
    printPgm(nMemoryDump);
    printlnPgm(&(memType[type]));
    for (unsigned char n = 0; n < nEnd; ++n)
    {
        dumpAddr((dump_addr_t) p);
        printPgm(ss);
        pp = p;
        for (unsigned char m = 0; m < 16; ++m)
        {
            dumpHexByte(getByte(p, type));
            _serial->print(' ');
            ++p;
        }
        _serial->print(' ');
        for (unsigned char m = 0; m < 16; ++m)
        {
            ch = (char) getByte(pp, type);
            _serial->print((ch >= ' ' && ch < 127) ? ch : '.');
            ++pp;
        }
        _serial->println();
    }
}

void dumpmon::availableMemory()
{
	using namespace dumpmon;
    int free_memory;
    printPgm(nAvailable);

    if ((int) __brkval == 0)
        free_memory = ((int) &free_memory) - ((int) &__bss_end);
    else
        free_memory = ((int) &free_memory) - ((int) __brkval);

    _serial->print(free_memory);
    printlnPgm(bytes);
}
