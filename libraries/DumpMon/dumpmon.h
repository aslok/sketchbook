//
// C++ Interface: dumpmon
//
// Description: Simple dumping monitor.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__DUMPMON_H_INCLUDED__)
#define __DUMPMON_H_INCLUDED__

#define DUMPMON_VERSION "0.34"

#include "ve_avr_dumpmon.h"
#include "ucdefs.h"
#include "dumpdebug.h"
#include "breakisr.h"

void dumpmonSetup(unsigned long serialSpd, DebugState state = STEP_MODE);
void dumpmonSetup(HardwareSerial* serial, unsigned long serialSpd, DebugState state = STEP_MODE);
void dumpmonLoop();

#if !defined(prog_char)
typedef char PROGMEM prog_char;
#endif

namespace dumpmon
{

typedef enum {
  RAM, FLASH, ROM, TIMER, ERROR, REGS, IRQS, WATCHES, RAMAVAIL, IDLE
} state_t;

typedef DUMP_ADDR_TYPE dump_addr_t;

extern Stream* _serial;

void dispatchStateWait(char cmd);
void displayUsage();
void prepareAddress(unsigned char len);
bool enterAddr(char cb);

extern const char ss[] PROGMEM;
extern const char on[] PROGMEM;
extern const char off[] PROGMEM;
extern const char* const irqVects[] PROGMEM;

#if defined(DUMP_LEONARDO)
extern const prog_char ocr4c[] PROGMEM;
#endif

}

#endif // __DUMPMON_H_INCLUDED__
