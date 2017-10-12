/**
 * @file ve_avr.h
 * @brief VE_AVR Library Header
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 *
 * In order to use the VE_AVR C++ Classes Library,
 * include this header into your code
 * @code
 * #include <ve_avr.h>
 * @endcode
 */
#ifndef VE_AVR_H_
#define VE_AVR_H_

#include <inttypes.h>
#include <avr/builtins.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>

#if defined(__SAM3X8E__)
#define uint32_t	uintptr_t
#else
#define uint16_t	uintptr_t	///< Pointer As Unsigned Integer type
#endif

#if defined(__AVR_ATmega16__) || \
    defined(__AVR_ATmega32__)
#define VE_ATmega32
#endif
#if defined(__AVR_ATmega16U4__) || \
    defined(__AVR_ATmega32U4__)
#define VE_ATmega32U4
#endif
#if defined(__AVR_ATmega325__) || \
	defined(__AVR_ATmega645__)
#define VE_ATmega325
#endif
#if defined(__AVR_ATmega48PA__) || \
	defined(__AVR_ATmega88PA__) || \
	defined(__AVR_ATmega168PA__) || \
	defined(__AVR_ATmega328P__)
#define VE_ATmega328P
#endif
#if defined(__AVR_ATmega640__) || \
    defined(__AVR_ATmega1280__) || \
    defined(__AVR_ATmega1281__) || \
    defined(__AVR_ATmega2560__) || \
    defined(__AVR_ATmega2561__)
#define VE_ATmega2560
#endif
#if defined(__AVR_ATmega164A__) || \
	defined(__AVR_ATmega164PA__) || \
	defined(__AVR_ATmega324A__) || \
	defined(__AVR_ATmega324PA__) || \
	defined(__AVR_ATmega644A__) || \
	defined(__AVR_ATmega644PA__)
#define VE_ATmega644PA
#endif
#if defined(__AVR_ATmega1284__) || \
	defined(__AVR_ATmega1284P__)
#define VE_ATmega1284P
#endif

#include "ve_reg.h"
#include "ve_avrdef.h"

#if defined(VE_ATmega1284P)
#include "ve_avrdef_atmega1284p.h"
#include "ve_atmega1284p.h"
#endif
#if defined(VE_ATmega2560)
#include "ve_avrdef_atmega2560.h"
#include "ve_atmega2560.h"
#endif
#if defined(VE_ATmega32)
#include "ve_avrdef_atmega32.h"
#include "ve_atmega32.h"
#endif
#if defined(VE_ATmega325)
#include "ve_avrdef_atmega325.h"
#include "ve_atmega325.h"
#endif
#if defined(VE_ATmega328P)
#include "ve_avrdef_atmega328p.h"
#include "ve_atmega328p.h"
#endif
#if defined(VE_ATmega32U4)
#include "ve_avrdef_atmega32u4.h"
#include "ve_atmega32u4.h"
#endif
#if defined(VE_ATmega644PA)
#include "ve_avrdef_atmega1284p.h"
#include "ve_atmega644pa.h"
#endif

#include "ve_avrdevice.h"

#include "ve_stringt.h"
#include "ve_fifo.h"

#include "ve_cpu.h"
#include "ve_gpio.h"
#include "ve_usart.h"
#include "ve_timerinterruptcontrol.h"
#include "ve_timerw.h"
#include "ve_prescaler0.h"
#include "ve_prescaler2.h"
#include "ve_timer.h"
#include "ve_analogcomp.h"
#include "ve_analogmultiplexer.h"
#include "ve_adc.h"

#if defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
    defined(VE_ATmega32U4) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
#include "ve_power.h"
#include "ve_pinchangeinterruptmask.h"
#include "ve_pinchangeinterruptflags.h"
#include "ve_pinchangeinterruptcontrol.h"
#include "ve_clockprescale.h"
#endif

#include "ve_timerinterruptflags.h"
#include "ve_externalinterruptcontrol.h"
#include "ve_externalinterruptflags.h"
#include "ve_generaltimercontrol.h"
#include "ve_spi.h"
#include "ve_sleepmodecontrol.h"
#include "ve_mcucontrol.h"
#include "ve_storeprogrammemory.h"
#include "ve_eeprom.h"
#include "ve_watchdog.h"

#if defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
    defined(VE_ATmega32) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
#include "ve_asyncstatus.h"
#endif

#include "ve_twi.h"

#if defined(VE_ATmega2560)
#include "ve_externalmemory.h"
#endif

#if defined(VE_ATmega32U4)
#include "ve_pll.h"
#include "ve_timerhs.h"
#include "ve_usbgen.h"
#include "ve_usbdev.h"
#include "ve_usbep.h"
#include "ve_clockswitch.h"
#endif

#endif /* VE_AVR_H_ */
