//
// C++ Interface: memory
//
// Description: Dump memory.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__MEMORY_H_INCLUDED__)
#define __MEMORY_H_INCLUDED__

#include "dumpmon.h"

namespace dumpmon
{
void dumpMemory(dump_addr_t addr, state_t type);
void availableMemory();
}

#endif // __MEMORY_H_INCLUDED__
