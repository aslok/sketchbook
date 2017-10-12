//
// C++ Interface: ram
//
// Description: Registers dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__REGISTERS_H_INCLUDED__)
#define __REGISTERS_H_INCLUDED__

#include <avr/pgmspace.h>

namespace dumpmon
{
void dumpReg(const prog_char* name, unsigned char value);
void dumpRegisters();
};

#endif // __REGISTERS_H_INCLUDED__ 
