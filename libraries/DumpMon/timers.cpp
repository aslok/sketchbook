//
// C++ Implementation: gpl
//
// Description: Timers dump.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "dumpdebug.h"
#include "timers.h"
#include "registers.h"
#include "printpgm.h"
#include "ve_avr.h"

namespace dumpmon
{

const prog_char nInvalidTimerNo[] = { "\r\nInvalid timer no.: " };
const prog_char nTimertt[]  = { "\r\nTimer\t\t" };
const prog_char powertt[] = { "Power\t\t" };
const prog_char on[]  = { "on" };
const prog_char off[]  = { "off" };
const prog_char clockSelectt[]  = { "Clock Select\t" };
const prog_char stopped[]  = { "stopped" };
const prog_char div1[]  = { "/1" };
const prog_char div8[]  = { "/8" };
const prog_char div32[]  = { "/32" };
const prog_char div64[]  = { "/64" };
const prog_char div128[]  = { "/128" };
const prog_char div256[]  = { "/256" };
const prog_char div1024[]  = { "/1024" };
const prog_char extClockFalling[]  = { "Ext.Clock Falling" };
const prog_char extClockRising[]  = { "Ext.Clock Rising" };

const char* const prescaler0[] = {
  stopped, div1, div8, div64, div256, div1024, extClockFalling, extClockRising
};
const char* const prescaler2[] = {
  stopped, div1, div8, div32, div64, div128, div256, div1024
};

#if defined(DUMP_LEONARDO)
const prog_char div2[]  = { "/2" };
const prog_char div4[]  = { "/4" };
const prog_char div16[]  = { "/16" };
const prog_char div512[]  = { "/512" };
const prog_char div2048[]  = { "/2048" };
const prog_char div4096[]  = { "/4096" };
const prog_char div8192[]  = { "/8192" };
const prog_char div16384[]  = { "/16384" };
const prog_char dtPrescalert[]  = { "DT Prescaler\t" };

const char* const prescalerHS[] = {
  stopped, div1, div2, div4, div8, div16, div32, div64,
  div128, div256, div512, div1024, div2048, div4096, div8192, div16384
};
const char* const dtPrescalerHS[] = {
  div1, div2, div4, div8
};
#endif

const prog_char waveGent[]  = { "Wave Gen.\t" };
const prog_char reserved[]  = { "---" };
const prog_char normal[]  = { "Normal" };
const prog_char phaseCorrect[]  = { "Phase Correct" };
const prog_char phaseFreqCorrect[]  = { "Phase & Freq. Correct" };
const prog_char ctc[]  = { "CTC" };
const prog_char fastPWM[]  = { "FastPWM" };
#if defined(DUMP_LEONARDO)
const prog_char singleSlopePWM6[]  = { "PWM6 Single Slope" };
const prog_char dualSlopePWM6[]  = { "PWM6 Dual Slope" };
#endif

const char* const waveGen[] = {
  normal, phaseCorrect, ctc, fastPWM, reserved, phaseCorrect, reserved, fastPWM
};
const char* const waveGenW[] = {
  normal, phaseCorrect, phaseCorrect, phaseCorrect,
  ctc, fastPWM, fastPWM, fastPWM,
  phaseFreqCorrect, phaseFreqCorrect, phaseCorrect, phaseCorrect,
  ctc, reserved, fastPWM, fastPWM
};

#if defined(DUMP_LEONARDO)
const char* const waveGenHS[] = {
  fastPWM, phaseFreqCorrect, singleSlopePWM6, dualSlopePWM6
};
#endif

const prog_char toptt[]  = { "TOP\t\t" };
const prog_char ff[]  = { "FF" };
const prog_char ocra[]  = { "OCRA" };
const prog_char ffff[]  = { "FFFF" };
const prog_char zzff[]  = { "00FF" };
const prog_char z1ff[]  = { "01FF" };
const prog_char z3ff[]  = { "03FF" };
const prog_char icr[]  = { "ICR" };

const char* const top[] = {
  ff, ff, ocra, ff, reserved, ocra, reserved, ocra
};
const char* const topW[] = {
  ffff, zzff, z1ff, z3ff, ocra, zzff, z1ff, z3ff, icr, ocra, icr, ocra, icr, reserved, icr, ocra
};

#if defined(DUMP_LEONARDO)
const char* const topHS[] = {
  ocr4c
};
#endif

const prog_char outputMode[]  = { "Output Mode " };
const prog_char disconnected[]  = { "Disconnected" };
const prog_char toggle[]  = { "Toggle" };
const prog_char clear[]  = { "Clear" };
const prog_char set[]  = { "Set" };
const prog_char onCompareMatch[]  = { " on Compare Match" };

const char* const com[] = {
	disconnected, toggle, clear, set
};

const prog_char tcnt[]  = { "TCNT" };
const prog_char ocr[]  = { "OCR" };
const prog_char tt[]  = { "\t\t" };
const prog_char noiseCancelert[]  = { "Noise Canceler\t" };
const prog_char icEdgett[]  = { "IC Edge\t\t" };
const prog_char falling[]  = { "Falling" };
const prog_char rising[]  = { "Rising" };
const prog_char synchModet[]  = { "Synch. Mode\t" };
const prog_char clockSourcet[]  = { "Clock Source\t" };
const prog_char tosc1[]  = { "TOSC1" };
const prog_char clkio[]  = { "CLKI/O" };
const prog_char extClkInputt[]  = { "Ext.Clock Input\t" };
const prog_char enabled[]  = { "Enabled" };
const prog_char disabled[]  = { "Disabled" };

#if defined(DUMP_LEONARDO)
const prog_char pwm[] = { "PWM" };
const prog_char enhancedModet[] = { "Enhanced Mode\t" };
const prog_char fpModett[] = { "FP Mode\t\t" };
const prog_char fpNoiseCancelert[] = { "FP Noise Canclr\t" };
const prog_char fpAnCompt[] = { "FP An.Comparatr\t" };
const prog_char fpEdgeSelect[] = { "FP Edge Select\t" };
const prog_char regUpdatet[] = { "Register Update\t" };
const prog_char unlocked[] = { "unlocked" };
const prog_char nOCA[] = { "nOCA " };
const prog_char OCA[]  = { "OCA " };
const prog_char nOCB[] = { "nOCB " };
const prog_char OCB[]  = { "OCB " };
const prog_char nOCD[] = { "nOCD " };
const prog_char OCD[]  = { "OCD" };
const prog_char ocOverridet[] = { "OC Override\t" };

const char* const ocOverrideHS[] = {
  nOCA, OCA, nOCB, OCB, nOCD, OCD
};
#endif

extern const prog_char nInvalidTimerNo[] PROGMEM;
extern const prog_char nTimertt[] PROGMEM;
extern const prog_char powertt[] PROGMEM;
extern const prog_char on[] PROGMEM;
extern const prog_char off[] PROGMEM;
extern const prog_char clockSelectt[] PROGMEM;
extern const prog_char stopped[] PROGMEM;
extern const prog_char div1[] PROGMEM;
extern const prog_char div8[] PROGMEM;
extern const prog_char div32[] PROGMEM;
extern const prog_char div64[] PROGMEM;
extern const prog_char div128[] PROGMEM;
extern const prog_char div256[] PROGMEM;
extern const prog_char div1024[] PROGMEM;
extern const prog_char extClockFalling[] PROGMEM;
extern const prog_char extClockRising[] PROGMEM;

extern PROGMEM const char* const prescaler0[];
extern PROGMEM const char* const prescaler2[];

#if defined(DUMP_LEONARDO)
extern const prog_char div2[] PROGMEM;
extern const prog_char div4[] PROGMEM;
extern const prog_char div16[] PROGMEM;
extern const prog_char div512[] PROGMEM;
extern const prog_char div2048[] PROGMEM;
extern const prog_char div4096[] PROGMEM;
extern const prog_char div8192[] PROGMEM;
extern const prog_char div16384[] PROGMEM;
extern const prog_char dtPrescalert[] PROGMEM;

extern PROGMEM const char* const prescalerHS[];
extern PROGMEM const char* const dtPrescalerHS[];
#endif

extern const prog_char waveGent[] PROGMEM;
extern const prog_char reserved[] PROGMEM;
extern const prog_char normal[] PROGMEM;
extern const prog_char phaseCorrect[] PROGMEM;
extern const prog_char phaseFreqCorrect[] PROGMEM;
extern const prog_char ctc[] PROGMEM;
extern const prog_char fastPWM[] PROGMEM;
#if defined(DUMP_LEONARDO)
extern const prog_char singleSlopePWM6[] PROGMEM;
extern const prog_char dualSlopePWM6[] PROGMEM;
#endif

extern PROGMEM const char* const waveGen[];
extern PROGMEM const char* const waveGenW[];

#if defined(DUMP_LEONARDO)
extern PROGMEM const char* const waveGenHS[];
#endif

extern const prog_char toptt[] PROGMEM;
extern const prog_char ff[] PROGMEM;
extern const prog_char ocra[] PROGMEM;
extern const prog_char ffff[] PROGMEM;
extern const prog_char zzff[] PROGMEM;
extern const prog_char z1ff[] PROGMEM;
extern const prog_char z3ff[] PROGMEM;
extern const prog_char icr[] PROGMEM;

extern PROGMEM const char* const top[];
extern PROGMEM const char* const topW[];

#if defined(DUMP_LEONARDO)
extern const char* const topHS[] PROGMEM;
#endif

extern const prog_char outputMode[] PROGMEM;
extern const prog_char disconnected[] PROGMEM;
extern const prog_char toggle[] PROGMEM;
extern const prog_char clear[] PROGMEM;
extern const prog_char set[] PROGMEM;
extern const prog_char onCompareMatch[] PROGMEM;

extern PROGMEM const char* const com[];

extern const prog_char tcnt[] PROGMEM;
extern const prog_char tt[] PROGMEM;
extern const prog_char ocr[] PROGMEM;
extern const prog_char tt[] PROGMEM;
extern const prog_char noiseCancelert[] PROGMEM;
extern const prog_char icEdgett[] PROGMEM;
extern const prog_char falling[] PROGMEM;
extern const prog_char rising[] PROGMEM;
extern const prog_char synchModet[] PROGMEM;
extern const prog_char clockSourcet[] PROGMEM;
extern const prog_char tosc1[] PROGMEM;
extern const prog_char clkio[] PROGMEM;
extern const prog_char extClkInputt[] PROGMEM;
extern const prog_char enabled[] PROGMEM;
extern const prog_char disabled[] PROGMEM;

#if defined(DUMP_LEONARDO)
extern const prog_char pwm[] PROGMEM;
extern const prog_char enhancedModet[] PROGMEM;
extern const prog_char fpModett[] PROGMEM;
extern const prog_char fpNoiseCancelert[] PROGMEM;
extern const prog_char fpAnCompt[] PROGMEM;
extern const prog_char fpEdgeSelect[] PROGMEM;
extern const prog_char regUpdatet[] PROGMEM;
extern const prog_char unlocked[] PROGMEM;
extern const prog_char nOCA[] PROGMEM;
extern const prog_char OCA[] PROGMEM;
extern const prog_char nOCB[] PROGMEM;
extern const prog_char OCB[] PROGMEM;
extern const prog_char nOCD[] PROGMEM;
extern const prog_char OCD[] PROGMEM;
extern const prog_char ocOverridet[] PROGMEM;

extern const char* const ocOverrideHS[] PROGMEM;
#endif

void dumpTimerPower(unsigned char tn);
void dumpTimerPrescaler(unsigned char tn);
void dumpTimerWaveGenMode(unsigned char tn);
void dumpTimerCOM(unsigned char mode, char channel);
void dumpTimerCompOutMode(unsigned char tn);
void dumpTimerCounter(unsigned char tn);
void dumpTimerOCR(unsigned char tn, char channel, unsigned int value);
void dumpTimerOCRs(unsigned char tn);
void dumpTimerICR(unsigned char tn);
void dumpTimerNoiseCanceler(unsigned char tn);
void dumpTimerInputCaptureEdge(unsigned char tn);

#if defined(DUMP_MEGA) || \
	defined(DUMP_ARDUINO) || \
	defined(DUMP_SANGUINO) || \
	defined(DUMP_DAIDUINO)
void dumpTimer2Features();
#endif

#if defined(DUMP_LEONARDO)
void dumpTimerHSPWM(char channel, bool en);
void dumpTimerHSFeatures();
#endif
}

void dumpmon::dumpTimerPower(unsigned char tn)
{
	using namespace dumpmon;
	printPgm(powertt);
	bool isOn = false;
	switch (tn)
	{
	case 0:
		isOn = DEV_POWER.isTimer0On();
		break;
	case 1:
		isOn = DEV_POWER.isTimer1On();
		break;
	case 2:
		isOn = DEV_POWER.isTimer2On();
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		isOn = DEV_POWER.isTimer3On();
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	case 4:
		isOn = DEV_POWER.isTimer4On();
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		isOn = DEV_POWER.isTimer5On();
		break;
#endif
	}
	printlnPgm(isOn ? on : off);
}

void dumpmon::dumpTimerPrescaler(unsigned char tn)
{
	const char* const *ps = 0;
	printPgm(clockSelectt);
	switch (tn)
	{
	case 0:
		ps = &(prescaler0[(unsigned char) DEV_TIMER0.clockSelect()]);
		break;
	case 1:
		ps = &(prescaler0[(unsigned char) DEV_TIMER1.clockSelect()]);
		break;
	case 2:
		ps = &(prescaler2[(unsigned char) DEV_TIMER2.clockSelect()]);
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		ps = &(prescaler0[(unsigned char) DEV_TIMER3.clockSelect()]);
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	case 4:
#if defined(DUMP_MEGA)
		ps = &(prescaler0[(unsigned char) DEV_TIMER4.clockSelect()]);
#else
		ps = &(prescalerHS[(unsigned char) DEV_TIMER4.clockSelect()]);
#endif
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		ps = &(prescaler0[(unsigned char) DEV_TIMER5.clockSelect()]);
		break;
#endif
	}
	printlnPgm(ps);
}

void dumpmon::dumpTimerWaveGenMode(unsigned char tn)
{
	unsigned char n = 0;
	const char * const *ps = 0;
	const char * const *ts = 0;
	printPgm(waveGent);
	switch(tn)
	{
	case 0:
		n = (unsigned char) DEV_TIMER0.wavGenMode();
		ps = &(waveGen[n]);
		ts = &(top[n]);
		break;
	case 1:
		n = (unsigned char) DEV_TIMER1.wavGenMode();
		ps = &(waveGenW[n]);
		ts = &(topW[n]);
		break;
	case 2:
		n = (unsigned char) DEV_TIMER2.wavGenMode();
		ps = &(waveGen[n]);
		ts = &(top[n]);
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		n = (unsigned char) DEV_TIMER3.wavGenMode();
		ps = &(waveGenW[n]);
		ts = &(topW[n]);
		break;
#endif
#if defined(DUMP_MEGA)
	case 4:
		n = (unsigned char) DEV_TIMER4.wavGenMode();
		ps = &(waveGenW[n]);
		ts = &(topW[n]);
		break;
#endif
#if defined(DUMP_LEONARDO)
	case 4:
		n = (unsigned char) DEV_TIMER4.wavGenMode();
		ps = &(waveGenHS[n]);
		ts = &(topHS[0]);
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		n = (unsigned char) DEV_TIMER5.wavGenMode();
		ps = &(waveGenW[n]);
		ts = &(topW[n]);
		break;
#endif
	}
	printlnPgm(ps);
	printPgm(toptt);
	printlnPgm(ts);
}

void dumpmon::dumpTimerCOM(unsigned char mode, char channel)
{
	if (mode < 0)
		return;
	printPgm(outputMode);
	_serial->print((char) ('A' + channel));
	_serial->print('\t');
	printPgm(&(com[mode]));
	if (mode > 0)
		printPgm(onCompareMatch);
	_serial->println();
}

void dumpmon::dumpTimerCompOutMode(unsigned char tn)
{
	char a = -1;
	char b = -1;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	char c = -1;
#endif
#if defined(DUMP_LEONARDO)
	char d = -1;
#endif
	switch(tn)
	{
	case 0:
		a = DEV_TIMER0.compOutModeA();
		b = DEV_TIMER0.compOutModeB();
		break;
	case 1:
		a = DEV_TIMER1.compOutModeA();
		b = DEV_TIMER1.compOutModeB();
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
		c = DEV_TIMER1.compOutModeC();
#endif
		break;
	case 2:
		a = DEV_TIMER2.compOutModeA();
		b = DEV_TIMER2.compOutModeB();
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		a = DEV_TIMER3.compOutModeA();
		b = DEV_TIMER3.compOutModeB();
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
		c = DEV_TIMER3.compOutModeC();
#endif
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	case 4:
		a = DEV_TIMER4.compOutModeA();
		b = DEV_TIMER4.compOutModeB();
#if defined(DUMP_MEGA)
		c = DEV_TIMER4.compOutModeC();
#endif
#if defined(DUMP_LEONARDO)
		d = DEV_TIMER4.compOutModeD();
#endif
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		a = DEV_TIMER5.compOutModeA();
		b = DEV_TIMER5.compOutModeB();
		c = DEV_TIMER5.compOutModeC();
		break;
#endif
	}
	dumpTimerCOM(a, 0);
	dumpTimerCOM(b, 1);
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	if (c != -1)
		dumpTimerCOM(c, 2);
#endif
#if defined(DUMP_LEONARDO)
	if (d != -1)
		dumpTimerCOM(d, 3);
#endif
}

void dumpmon::dumpTimerCounter(unsigned char tn)
{
	unsigned int value = 0;
	printPgm(tcnt);
	_serial->print((char) ('0' + tn));
	printPgm(tt);
	switch(tn)
	{
	case 0:
		value = DEV_TIMER0.counter();
		break;
	case 1:
		value = DEV_TIMER1.counter();
		break;
	case 2:
		value = DEV_TIMER2.counter();
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		value = DEV_TIMER3.counter();
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	case 4:
		value = DEV_TIMER4.counter();
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		value = DEV_TIMER5.counter();
		break;
#endif
	}
	dumpHexWord(value);
	_serial->println();
}

void dumpmon::dumpTimerOCR(unsigned char tn, char channel, unsigned int value)
{
	printPgm(ocr);
	_serial->print((char) ('0' + tn));
	_serial->print((char) ('A' + channel));
	printPgm(tt);
	dumpHexWord(value);
	_serial->println();
}

void dumpmon::dumpTimerOCRs(unsigned char tn)
{
	unsigned int ocra = 0;
	unsigned int ocrb = 0;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	unsigned int ocrc = 0;
#if defined(DUMP_LEONARDO)
	unsigned int ocrd = 0;
#endif
#endif
	switch(tn)
	{
	case 0:
		ocra = OCR0A;
		ocrb = OCR0B;
		break;
	case 1:
		ocra = OCR1A;
		ocrb = OCR1B;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
		ocrc = OCR1C;
#endif
		break;
#if defined(DUMP_MEGA) || \
	defined(DUMP_ARDUINO)
	case 2:
		ocra = OCR2A;
		ocrb = OCR2B;
		break;
#endif
#if defined(DUMP_LEONARDO)
	case 2:
		ocra = REG(DEV_TIMER2.ocra);
		ocrb = REG(DEV_TIMER2.ocrb);
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	case 3:
		ocra = OCR3A;
		ocrb = OCR3B;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
		ocrc = OCR3C;
#endif
		break;
#endif
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	case 4:
		ocra = OCR4A;
		ocrb = OCR4B;
		ocrc = OCR4C;
#if defined(DUMP_LEONARDO)
		ocrd = OCR4D;
#endif
		break;
#endif
#if defined(DUMP_MEGA)
	case 5:
		ocra = OCR5A;
		ocrb = OCR5B;
		ocrc = OCR5C;
		break;
#endif
	}
	dumpTimerOCR(tn, 0, ocra);
	dumpTimerOCR(tn, 1, ocrb);
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO)
	if (!(tn == 0 || tn == 2))
		dumpTimerOCR(tn, 2, ocrc);
#endif
#if defined(DUMP_LEONARDO)
	if (tn == 4)
		dumpTimerOCR(tn, 3, ocrd);
#endif
}

void dumpmon::dumpTimerICR(unsigned char tn)
{
#if defined(DUMP_LEONARDO)
	if (tn == 4)
		return;
#else
	if (tn == 0 || tn == 2)
		return;
#endif
	printPgm(icr);
	_serial->print((char) ('0' + tn));
	printPgm(tt);
	unsigned int icr = 0;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	switch(tn)
	{
	case 1:
		icr = ICR1;
		break;
	case 3:
		icr = ICR3;
		break;
#if defined(DUMP_MEGA)
	case 4:
		icr = ICR4;
		break;
	case 5:
		icr = ICR5;
		break;
#endif
	}
#else
	icr = ICR1;
#endif
	dumpHexWord(icr);
	_serial->println();
}

void dumpmon::dumpTimerNoiseCanceler(unsigned char tn)
{
#if defined(DUMP_LEONARDO)
	if (tn == 4)
		return;
#else
	if (tn == 0 || tn == 2)
		return;
#endif
	printPgm(noiseCancelert);
	bool b = false;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	switch(tn)
	{
	case 1:
		b = DEV_TIMER1.isNoiseCancelerActive();
		break;
	case 3:
		b = DEV_TIMER3.isNoiseCancelerActive();
		break;
#if defined(DUMP_MEGA)
	case 4:
		b = DEV_TIMER4.isNoiseCancelerActive();
		break;
	case 5:
		b = DEV_TIMER5.isNoiseCancelerActive();
		break;
#endif
	}
#else
	b = DEV_TIMER1.isNoiseCancelerActive();
#endif
	printlnPgm(b ? on : off);
}

void dumpmon::dumpTimerInputCaptureEdge(unsigned char tn)
{
#if defined(DUMP_LEONARDO)
	if (tn == 4)
		return;
#else
	if (tn == 0 || tn == 2)
		return;
#endif
	printPgm(icEdgett);
	TimerW::InCaptEdge ice = TimerW::Falling;
#if defined(DUMP_MEGA) || \
	defined(DUMP_LEONARDO) || \
	defined(DUMP_DAIDUINO)
	switch(tn)
	{
	case 1:
		ice = DEV_TIMER1.inputCaptureEdge();
		break;
	case 3:
		ice = DEV_TIMER3.inputCaptureEdge();
		break;
#if defined(DUMP_MEGA)
	case 4:
		ice = DEV_TIMER4.inputCaptureEdge();
		break;
	case 5:
		ice = DEV_TIMER5.inputCaptureEdge();
		break;
#endif
	}
#else
	ice = DEV_TIMER1.inputCaptureEdge();
#endif
	printlnPgm(ice==TimerW::Rising ? rising : falling);
}

#if defined(DUMP_MEGA) || \
	defined(DUMP_SANGUINO) || \
	defined(DUMP_DAIDUINO)
void dumpmon::dumpTimer2Features()
{
	printPgm(synchModet);
	printlnPgm(DEV_GTCTRL.isSynchronizationModeOn() ? on : off);
	printPgm(clockSourcet);
	printlnPgm(DEV_ASYNCST.timer2ClkSrc() == AsyncStatus::TOSC1 ? tosc1 : clkio);
	printPgm(extClkInputt);
	printlnPgm(DEV_ASYNCST.isExtClkInputEnabled() ? enabled : disabled);
}
#endif

#if defined(DUMP_LEONARDO)
void dumpmon::dumpTimerHSPWM(char channel, bool en)
{
	printPgm(pwm);
	_serial->print((char) ('A' + channel));
	printPgm(tt);
	printlnPgm(en ? enabled : disabled);
}

void dumpmon::dumpTimerHSFeatures()
{
	printPgm(enhancedModet);
	printlnPgm(DEV_TIMER4.isEnhancedModeOn() ? on : off);
	dumpTimerHSPWM(0, DEV_TIMER4.isPWMAEnabled());
	dumpTimerHSPWM(1, DEV_TIMER4.isPWMBEnabled());
	dumpTimerHSPWM(3, DEV_TIMER4.isPWMDEnabled());
	printPgm(fpModett);
	printlnPgm(DEV_TIMER4.isFaultProtModeEnabled() ? enabled : disabled);
	printPgm(dtPrescalert);
	printlnPgm(&(dtPrescalerHS[DEV_TIMER4.deadTimePrescaler()]));
	printPgm(fpNoiseCancelert);
	printlnPgm(DEV_TIMER4.isFaultProtNoiseCancelerOn() ? on : off);
	printPgm(fpAnCompt);
	printlnPgm(DEV_TIMER4.isFaultProtAnalogCompEnabled() ? enabled : disabled);
	printPgm(fpEdgeSelect);
	printlnPgm(DEV_TIMER4.faultProtEdgeSelect() ? rising : falling);
	printPgm(regUpdatet);
	printlnPgm(DEV_TIMER4.isRegisterUpdateLocked() ? &(unlocked[2]) : unlocked);
	bool b = false;
	printPgm(ocOverridet);
	for (uint8_t n = 0; n < 7; ++n)
		if (DEV_TIMER4.isOutCompOverrideEnableOn((TimerHS::OutCompOverrideEnableBit) _BV(n))) {
			printPgm(&(ocOverrideHS[n]));
			b = true;
		}
	if (b)
		_serial->println();
	else
		printlnPgm(reserved);
}
#endif

void dumpmon::dumpTimer(unsigned char tn)
{
	using namespace dumpmon;
	if(tn >= DUMP_TIMERS_COUNT) {
		printPgm(nInvalidTimerNo);
		_serial->println(tn, DEC);
		return;
	}
	printPgm(nTimertt);
	_serial->println(tn, DEC);
	dumpTimerPower(tn);
	dumpTimerPrescaler(tn);
	dumpTimerWaveGenMode(tn);
	dumpTimerCompOutMode(tn);
	dumpTimerCounter(tn);
	dumpTimerOCRs(tn);
	dumpTimerICR(tn);
	dumpTimerNoiseCanceler(tn);
	dumpTimerInputCaptureEdge(tn);
#if defined(DUMP_MEGA) || \
	defined(DUMP_SANGUINO) || \
	defined(DUMP_DAIDUINO)
	if (tn == 2)
		dumpTimer2Features();
#endif
#if defined(DUMP_LEONARDO)
	if (tn == 4)
		dumpTimerHSFeatures();
#endif
}


