//
// C++ Interface: timers
//
// Description: Timers dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__TIMERS_H_INCLUDED__)
#define __TIMERS_H_INCLUDED__

#include "dumpmon.h"

#if defined(DUMP_ARDUINO)
#   define DUMP_TIMERS_COUNT 3
#elif defined(DUMP_MEGA)
#   define DUMP_TIMERS_COUNT 6
#elif defined(DUMP_LEONARDO)
#   define DUMP_TIMERS_COUNT 5
#elif defined(DUMP_SANGUINO)
#   define DUMP_TIMERS_COUNT 3
#elif defined(DUMP_DAIDUINO)
#   define DUMP_TIMERS_COUNT 4
#else
#   error "TODO: Add board type support here."
#endif

namespace dumpmon
{

void dumpTimer(unsigned char tn);

}

#endif // __TIMERS_H_INCLUDED__


