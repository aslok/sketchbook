//
// C++ Interface: dumpdebug
//
// Description: Debug functions.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__DUMPDEBUG_H_INCLUDED__)
#define __DUMPDEBUG_H_INCLUDED__

#if !defined(DUMPMON_WATCHES_COUNT)
#define DUMPMON_WATCHES_COUNT 8
#endif

#if !defined(DUMPMON_WATCHNAME_LEN)
#define DUMPMON_WATCHNAME_LEN 5
#endif

//#include <WProgram.h>
#include <Arduino.h>

#if !defined(BYTE)
#define BYTE HEX
#endif

typedef enum { GO_MODE, STEP_MODE } DebugState;

namespace dumpmon
{

extern volatile DebugState debugState;
extern volatile bool nextStep;

extern Stream* _serial;

void __watch(void* pt, const char* name, unsigned char size);

void dumpBreakpoint();
void dumpWatches();
void debugLoop();

}

inline void watch(char** pt, const char* name) {
	dumpmon::__watch((void*) pt, name, 0);
}

inline void watch(const char** pt, const char* name) {
	dumpmon::__watch((void*) pt, name, 0);
}

template <typename T>
void watch(const T* pt, const char* name) {
	dumpmon::__watch((void*) pt, name, sizeof(T));
}

template <typename T>
void breakpoint(const T& id) {
	using namespace dumpmon;
    if (debugState == STEP_MODE) {
    	dumpBreakpoint();
        _serial->print(id);
        dumpWatches();
    }
    debugLoop();
}

#endif // __DUMPDEBUG_H_INCLUDED__
