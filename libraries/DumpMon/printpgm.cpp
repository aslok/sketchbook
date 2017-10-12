//
// C++ Implementation: gpl
//
// Description: Print strings from Program Memory to Hardware Serial port.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpdebug.h"
#include "printpgm.h"

void dumpmon::printPgm(const prog_char *pstr)
{
	using namespace dumpmon;
	const char *p = (const char *) pstr;
	char ch;
	do {
		ch = pgm_read_byte(p);
		if (ch)
			_serial->print(ch);
		++p;
	} while(ch);
}

void dumpmon::printPgm(const char* const *pstr)
{
	using namespace dumpmon;
	printPgm((const prog_char*) pgm_read_word(pstr));
}

void dumpmon::printlnPgm(const prog_char *pstr)
{
	using namespace dumpmon;
	printPgm(pstr);
	_serial->println();
}

void dumpmon::printlnPgm(const char* const *pstr)
{
	using namespace dumpmon;
	printlnPgm((const prog_char*) pgm_read_word(pstr));
}

char dumpmon::halfByteToHex(unsigned char hb)
{
	return (hb > 9) ? (hb -10) + 'A' : hb + '0';
}

void dumpmon::dumpHexByte(unsigned char b)
{
	using namespace dumpmon;
	_serial->print(halfByteToHex(b >> 4));
	_serial->print(halfByteToHex(b & 0x0F));
}

void dumpmon::dumpHexWord(unsigned short s)
{
	using namespace dumpmon;
    short ss = (s >> 8) & 0xFF;
    dumpHexByte(ss);
    dumpHexByte(s);
}

void dumpmon::dumpBinByte(unsigned char b)
{
	using namespace dumpmon;
	unsigned char mask = 0x80;
	for(char n=8; n!=0; --n) {
		_serial->print((b & mask) ? '1' : '0');
		mask >>= 1;
	}
}

