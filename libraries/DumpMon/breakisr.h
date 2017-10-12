//
// C++ Interface: breakisr
//
// Description: ISR breakpoint functions.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef BREAKISR_H_
#define BREAKISR_H_

namespace dumpmon {

typedef enum {
	RUN, BREAK, STOP
} isr_state_t;

extern isr_state_t isrState;

#if defined(VE_ATmega328P)

typedef enum {
	reset, int0, int1, pcint0, pcint1, pcint2, wdt,
	timer2_compa, timer2_compb, timer2_ovf,
	timer1_capt, timer1_compa, timer1_compb, timer1_ovf,
	timer0_compa, timer0_compb, timer0_ovf,
	spi_stc, usart_rx, usart_udre, usart_tx,
	adc, ee_ready, analog_comp, twi, spm_ready
} isr_no_t;

#elif defined(VE_ATmega2560)

typedef enum {
	reset, int0, int1, int2, int3, int4, int5, int6, int7,
	pcint0, pcint1, pcint2, wdt,
	timer2_compa, timer2_compb, timer2_ovf,
	timer1_capt, timer1_compa, timer1_compb, timer1_compc, timer1_ovf,
	timer0_compa, timer0_compb, timer0_ovf,
	spi_stc, usart0_rx, usart0_udre, usart0_tx,
	analog_comp, adc, ee_ready,
	timer3_capt, timer3_compa, timer3_compb, timer3_compc, timer3_ovf,
	usart1_rx, usart1_udre, usart1_tx,
	twi, spm_ready,
	timer4_capt, timer4_compa, timer4_compb, timer4_compc, timer4_ovf,
	timer5_capt, timer5_compa, timer5_compb, timer5_compc, timer5_ovf,
	usart2_rx, usart2_udre, usart2_tx,
	usart3_rx, usart3_udre, usart3_tx
} isr_no_t;

#elif defined(VE_ATmega32U4)

typedef enum {
	reset, int0, int1, int2, int3, int6 = 7,
	pcint0 = 9, USB_GEN, USB_COM, wdt,
	timer1_capt = 16, timer1_compa, timer1_compb, timer1_compc, timer1_ovf,
	timer0_compa, timer0_compb, timer0_ovf,
	spi_stc, usart1_rx, usart1_udre, usart1_tx,
	analog_comp, adc, ee_ready,
	timer3_capt, timer3_compa, timer3_compb, timer3_compc, timer3_ovf,
	twi, spm_ready,
	timer4_compa, timer4_compb, timer4_compd, timer4_ovf, timer4_FPF
} isr_no_t;

#elif defined(VE_ATmega644PA)

typedef enum {
	reset, int0, int1, int2, pcint0, pcint1, pcint2, pcint3, wdt,
	timer2_compa, timer2_compb, timer2_ovf,
	timer1_capt, timer1_compa, timer1_compb, timer1_ovf,
	timer0_compa, timer0_compb, timer0_ovf,
	spi_stc, usart0_rx, usart0_udre, usart0_tx,
	analog_comp, adc, ee_ready, twi, spm_ready,
	usart1_rx, usart1_udre, usart1_tx
} isr_no_t;

#elif defined(VE_ATmega1284P)

typedef enum {
	reset, int0, int1, int2, pcint0, pcint1, pcint2, pcint3, wdt,
	timer2_compa, timer2_compb, timer2_ovf,
	timer1_capt, timer1_compa, timer1_compb, timer1_ovf,
	timer0_compa, timer0_compb, timer0_ovf,
	spi_stc, usart0_rx, usart0_udre, usart0_tx,
	analog_comp, adc, ee_ready, twi, spm_ready,
	usart1_rx, usart1_udre, usart1_tx,
	timer3_capt, timer3_compa, timer3_compb, timer3_ovf
} isr_no_t;

#endif

extern isr_no_t isrNo;
extern bool debugISR;

void breakISR(isr_no_t nIrq);
void dumpISR();

}

inline void dumpmon::breakISR(isr_no_t nIrq)
{
	if (debugISR && isrState == RUN) {
		isrState = BREAK;
		isrNo = nIrq;
	}
}


#endif /* BREAKISR_H_ */
