//
// C++ Implementation: dumpdebug
//
// Description: 
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpdebug.h"
#include "printpgm.h"
#include "dumpmon.h"

namespace dumpmon
{

int dump_watch_cnt = 0;
void* dump_watches[DUMPMON_WATCHES_COUNT];
char dump_watch_names[DUMPMON_WATCHES_COUNT][DUMPMON_WATCHNAME_LEN];
unsigned char dump_watch_sizes[DUMPMON_WATCHES_COUNT];

int dump_break_cnt = 0;
volatile DebugState debugState;
volatile bool nextStep = false;

}

void dumpmon::__watch(void* pt, const char* name, unsigned char size)
{
	using namespace dumpmon;
    if (dump_watch_cnt <= DUMPMON_WATCHES_COUNT) {
        unsigned char namelen = 255;
        for (unsigned char n = 0; n < DUMPMON_WATCHNAME_LEN; ++n) {
            if (namelen == 255) {
                dump_watch_names[dump_watch_cnt][n] = name[n];
                if (name[n] == 0)
                    namelen = n;
            }
            else
                dump_watch_names[dump_watch_cnt][n] = 0;
        }
        dump_watches[dump_watch_cnt] = (void*) pt;
        dump_watch_sizes[dump_watch_cnt] = size-1;
        ++dump_watch_cnt;
    }
}

void dumpmon::dumpBreakpoint()
{
	using namespace dumpmon;
    _serial->println();
    _serial->print('<');
    _serial->print(dump_break_cnt++);
    _serial->print('>');
    _serial->print(' ');
}

void dumpmon::dumpWatches()
{
	using namespace dumpmon;
    _serial->println();
    for (int n = 0; n < dump_watch_cnt; ++n) {
        dumpAddr((dump_addr_t)dump_watches[n]);
        printPgm(ss);
        for (unsigned char m = 0; m < DUMPMON_WATCHNAME_LEN; ++m) {
            char ch = dump_watch_names[n][m];
            _serial->print((ch) ? ch : ' ');
        }
        printPgm(ss);
        if (dump_watch_sizes[n] == 0xFF) {
            _serial->print('"');
            _serial->print(*((const char**)(dump_watches[n])));
            _serial->println('"');
        }
        else {
            unsigned char *p = (unsigned char*) dump_watches[n];
            for (unsigned char m = dump_watch_sizes[n]; ; --m) {
                dumpHexByte(p[m]);
                if (m == 0)
                    break;
            }
            printPgm(ss);
            _serial->print('"');
            for (unsigned char m = 0; m <= dump_watch_sizes[n]; ++m)
                _serial->print((char)((p[m]>=32 && p[m]<127) ? p[m] : '.'));
            _serial->print('"');
            printPgm(ss);
            for (unsigned char m = dump_watch_sizes[n]; ; --m) {
                dumpBinByte(p[m]);
                if (m == 0)
                    break;
                _serial->print('-');
            }
            _serial->println();
        }
    }
}

void dumpmon::debugLoop()
{
	using namespace dumpmon;
    nextStep = false;
    do
        dumpmonLoop();
    while (debugState == STEP_MODE && !nextStep);
}
