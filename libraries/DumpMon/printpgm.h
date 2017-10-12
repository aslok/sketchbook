//
// C++ Interface: printpgm
//
// Description: Print strings from Program Memory to Hardware Serial port.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#if !defined(__PRINTPGM_H_INCLUDED__)
#define __PRINTPGM_H_INCLUDED__

#include <avr/pgmspace.h>
#include "dumpmon.h"

#if !defined(pgm_read_byte)
#   if defined(DUMP_ARDUINO)
#       define pgm_read_byte pgm_read_byte_near
#   elif defined(DUMPMEGA)
#       define pgm_read_byte pgm_read_byte_far
#   else
#       error "TODO: Add board type support here."
#   endif
#endif

#if !defined(pgm_read_word)
#   if defined(DUMP_ARDUINO)
#       define pgm_read_word pgm_read_word_near
#   elif defined(DUMP_MEGA)
#       define pgm_read_word pgm_read_word_far
#   else
#       error "TODO: Add board type support here."
#   endif
#endif

namespace dumpmon
{
void printPgm(const char* const *pstr);
void printPgm(const prog_char *pstr);
void printlnPgm(const char* const *pstr);
void printlnPgm(const prog_char *pstr);

char halfByteToHex(unsigned char hb);
void dumpHexByte(unsigned char b);
void dumpHexWord(unsigned short b);
void dumpBinByte(unsigned char b);

inline void dumpAddr(dump_addr_t addr)
{
#if defined(DUMP_MEGA)
  dumpHexByte((addr & 0xFF0000) >> 16);
#endif
  dumpHexWord(addr);
}

}

#endif // __PRINTPGM_H_INCLUDED__
