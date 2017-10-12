//
// C++ Implementation: breakisr
//
// Description: ISR breakpoint functions.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ve_avr.h"
#include "breakisr.h"
#include "printpgm.h"

namespace dumpmon {

isr_state_t isrState = RUN;
isr_no_t isrNo = reset;
bool debugISR = true;

const prog_char sInterrupt[] = { " interrupt" };
extern const prog_char sInterrupt[] PROGMEM;

void dumpISR()
{
	_serial->println();
	printPgm(&(irqVects[isrNo]));
	printlnPgm(sInterrupt);
}

} // namespace dumpmon
