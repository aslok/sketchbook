//
// C++ Interface: interrupts
//
// Description: Interrupts dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__INTERRUPTS_H_INCLUDED__)
#define __INTERRUPTS_H_INCLUDED__

namespace dumpmon
{
void dumpInterrupts();

typedef union {
	unsigned int _uint;
	struct {
		unsigned char _lo;
		unsigned char _hi;
	} _bytes;
} uint16_bytes_t;

inline unsigned char hiByte(unsigned int val)
{
	uint16_bytes_t tmp = { _uint: val };
	return tmp._bytes._hi;
}

inline unsigned char loByte(unsigned int val)
{
	return val;
}

}

#endif // __INTERRUPTS_H_INCLUDED__
