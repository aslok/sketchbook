//
// C++ Implementation: gpl
//
// Description: Simple dumping monitor.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpdebug.h"
//#include <HardwaredumpmonSerial->h>
#include "printpgm.h"
#include "registers.h"
#include "dumpmon.h"
#include "memory.h"
#include "timers.h"
#include "interrupts.h"

namespace dumpmon
{

const prog_char usage[] = {
    "\r\nSimple Dumping Monitor. Version " DUMPMON_VERSION "\r\nCommands:\r\n"
    "?\tdisplay this help\r\n"
    "R\tdump registers\r\n"
    "I\tdump interrupts map\r\n"
    "W\tdump debug watches\r\n"
    "V\tshow available RAM\r\n"
    "M<addr>\tdump RAM (ie. M000"
#if (DUMP_RAM_ADDR_LEN == 4)
    "0"
#endif
    ")\r\n"
    "F<addr>\tdump Flash (ie. F0000"
#if (DUMP_FLASH_ADDR_LEN == 5)
    "0"
#endif
    ")\r\n"
    "O<addr>\tdump EEPROM (ie. O0000"
#if (DUMP_EEPROM_ADDR_LEN == 5)
    "0"
#endif
    ")\r\n"
    "T<num>\tdump timer state (ie. T1)\r\n"
    "S\tstep-execution\r\n"
    "G\tgo-execution\r\n"
    "N\tstep up to next breakpoint (step-mode)\r\n"
    "A\trepeat last command (again)\r\n"
    "C\tcontinue last dump\r\n"
    "*\tswitch ISR-debug state"
};
const prog_char nUnknownCommand[] = {
     "\r\nUnknown command: "
};
const prog_char nIllegalCharacter[] = {
      "\r\nIllegal character in address: "
};
const prog_char unknownState[] = {
      "Unknown state."
};
const prog_char isrDebug[] = {
      "\r\nISR debug "
};
extern const prog_char usage[] PROGMEM;
extern const prog_char nUnknownCommand[] PROGMEM;
extern const prog_char nIllegalCharacter[] PROGMEM;
extern const prog_char unknownState[] PROGMEM;
extern const prog_char isrDebug[] PROGMEM;

#define DUMP_PART_LEN 0x100

state_t monState = IDLE;
state_t lastFunc = IDLE;
dump_addr_t monAddr;
unsigned char nAddr;
unsigned char addrLen;
Stream* _serial = &Serial;

void dispatchStateIdle(char cmd);

}

void dumpmonSetup(unsigned long serialSpd, DebugState state)
{
	using namespace dumpmon;
	debugState = state;
	debugISR = true;
	_serial = &Serial;
	Serial.begin(serialSpd);
}

void dumpmonSetup(HardwareSerial* serial, unsigned long serialSpd, DebugState state)
{
	using namespace dumpmon;
	debugState = state;
	debugISR = true;
	_serial = serial;
	serial->begin(serialSpd);
}

void dumpmon::dispatchStateIdle(char cmd)
{
	using namespace dumpmon;
	if (cmd < ' ')
		return;

	if (cmd >= 'A' && cmd <= 'Z')
		cmd += 'a' - 'A';

	if (cmd == 'c') {
		switch (lastFunc)
		{
		case REGS:
		case IRQS:
		case WATCHES:
		case RAMAVAIL:
			cmd = 'a';
			break;
		case RAM:
		case FLASH:
		case ROM:
			monAddr += (dump_addr_t) DUMP_PART_LEN;
			cmd = 'a';
			break;
		case TIMER:
			if(++monAddr == DUMP_TIMERS_COUNT)
				monAddr = 0;
			cmd = 'a';
			break;
		default:
			break;
		}
	}
	switch(cmd)
	{
	case '?':
		displayUsage();
		break;
	case 'r':
		lastFunc = REGS;
		dumpRegisters();
		break;
	case 'i':
		lastFunc = IRQS;
		dumpInterrupts();
		break;
	case 'w':
		lastFunc = WATCHES;
	    dumpWatches();
	    break;
	case 'v':
		lastFunc = RAMAVAIL;
	    availableMemory();
	    break;
	case 'm':
		monState = RAM;
		prepareAddress(DUMP_RAM_ADDR_LEN);
		break;
	case 'f':
		monState = FLASH;
		prepareAddress(DUMP_FLASH_ADDR_LEN);
		break;
	case 'o':
		monState = ROM;
		prepareAddress(DUMP_EEPROM_ADDR_LEN);
		break;
	case 't':
		monState = TIMER;
		prepareAddress(1);
		break;
	case 'a':
		switch(lastFunc)
		{
		case REGS:
			dumpRegisters();
			break;
		case IRQS:
			dumpInterrupts();
			break;
		case WATCHES:
			dumpWatches();
			break;
		case RAMAVAIL:
			availableMemory();
			break;
		case RAM:
		case FLASH:
		case ROM:
			dumpMemory(monAddr, lastFunc);
			break;
		case TIMER:
			dumpTimer(monAddr);
			break;
		default:
			break;
		}
		break;
	case 'g':
		debugState = GO_MODE;
	    nextStep = false;
	    isrState = RUN;
	    _serial->println();
	    break;
	case 's':
	    debugState = STEP_MODE;
	    nextStep = true;
	    _serial->println();
	    break;
	case 'n':
	    debugState = STEP_MODE;
	    nextStep = true;
	    isrState = RUN;
	    _serial->println();
	    break;
	case '*':
		debugISR = ! debugISR;
		printPgm(isrDebug);
		printlnPgm(debugISR ? on : off);
		break;
	default:
		printPgm(nUnknownCommand);
		_serial->println(cmd);
		break;
	}
}

void dumpmon::displayUsage()
{
	using namespace dumpmon;
	printlnPgm(usage);
}

void dumpmon::prepareAddress(unsigned char len)
{
	using namespace dumpmon;
	monAddr = 0;
	nAddr = 0;
	addrLen = len;
}

bool dumpmon::enterAddr(char cb)
{
	using namespace dumpmon;
	if( ! ((cb >= '0' && cb <= '9') || (cb >= 'a' && cb <='f') || (cb >= 'A' && cb <='F'))) {
		printPgm(nIllegalCharacter);
		_serial->print(cb);
		monState = ERROR;
		return false;
	}
	monAddr <<= 4;
	if(cb >= '0' && cb <= '9')
		monAddr += cb - '0';
	else if(cb >= 'a' && cb <='f')
		monAddr += cb - 'a' + 10;
	else if(cb >= 'A' && cb <='F')
		monAddr += cb - 'A' + 10;
	++nAddr;
	return (nAddr == addrLen);
}

void dumpmonLoop()
{
	using namespace dumpmon;
    char cmd;
    if (isrState == BREAK) {
    	dumpISR();
    	isrState = STOP;
    	debugState = STEP_MODE;
	    nextStep = true;
	    _serial->print('>');
    }
    uint8_t nChars = _serial->available();
    for ( ; nChars != 0; --nChars) {
        cmd = _serial->read();
        _serial->print(cmd);
        switch(monState) {
            case IDLE:
                dispatchStateIdle(cmd);
                break;

            case RAM:
            case FLASH:
            case ROM:
                if(enterAddr(cmd)) {
                    dumpMemory(monAddr, monState);
                    lastFunc = monState;
                    monState = IDLE;
                }
                break;

            case TIMER:
                if(enterAddr(cmd)) {
                    dumpTimer(monAddr);
                    lastFunc = monState;
                    monState = IDLE;
                }
                break;

            default:
                printlnPgm(unknownState);
                monState = IDLE;
        }
        if (monState == ERROR)
            monState = IDLE;
        if (monState == IDLE)
            _serial->print('>');
    }
}  

