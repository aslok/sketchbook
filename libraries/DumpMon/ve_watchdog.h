/**
 * @file ve_watchdog.h
 * @brief %Watchdog Timer Class Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef WATCHDOG_H_
#define WATCHDOG_H_

/**
 * @brief %Watchdog Timer class
 * @ingroup Watchdog
 *
 *
 * %Watchdog Timer Configuration
 * WDTON Fuse Bit | Watchdog::isResetEnabled() | Watchdog::isIntEnabled() | Mode                            | Action on Time-out
 * :-------------:|:--------------------------:|:------------------------:|:--------------------------------|:------------------
 *   0            |  false                     |   false                  | Stopped                         | None
 *   0            |  false                     |   true                   | Interrupt Mode                  | Interrupt
 *   0            |  true                      |   false                  | System Reset Mode               | Reset
 *   0            |  true                      |   true                   | Interrupt and System Reset Mode | Interrupt, then go to System Reset Mode
 *   1            |  x                         |   x                      | System Reset Mode               | Reset
 */
class Watchdog: public AVR_WATCHDOG
{
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
public:
	/**
	 * @brief Watchdog Timer Prescale Select type
	 *
	 * Number of WDT Oscillator cycles.
	 */
	typedef enum {
		OSC_2K = 0,		///< 2048 cycles
		OSC_4K,			///< 4096 cycles
		OSC_8K,			///< 8192 cycles
		OSC_16K,		///< 16384 cycles
		OSC_32K,		///< 32768 cycles
		OSC_64K,		///< 65536 cycles
		OSC_128K,		///< 131072 cycles
		OSC_256K,		///< 262144 cycles
		OSC_512K,		///< 524288 cycles
		OSC_1024K		///< 1048576 cycles
	} Prescaler;
#endif

#if defined(VE_ATmega325) || \
	defined(VE_ATmega32)
public:
	typedef enum {
		OSC_16K = 0,
		OSC_32K,
		OSC_64K,
		OSC_128K,
		OSC_256K,
		OSC_512K,
		OSC_1024K,
		OSC_2048K
	} Prescaler;
#endif
public:
	Prescaler prescaler() const;
	void setPrescaler(Prescaler val);
	bool isChangeEnabled() const;
	void enableChange();
	void reset();

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	bool isInt() const;
	void clearInt();
	bool isIntEnabled() const;
	void enableInt();
	void disableInt();
	bool isResetEnabled() const;
	void enableReset();
	void disableReset();
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32)
	bool isEnabled() const;
	void enable();
	void disable();
#endif
};

/**
 * @brief Reset %Watchdog Timer
 */
inline void Watchdog::reset()
{
	__asm__ __volatile__ ("wdr");
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return Watchdog Timer Prescaler value
 * @return Watchdog Timer Prescaler value
 */
inline Watchdog::Prescaler Watchdog::prescaler() const
{
	return (Prescaler) ((REG_(wdtcsr).wdp3 << 3) | REG_(wdtcsr).wdp);
}
/**
 * @brief Set Watchdog Timer Prescaler value
 * @param[in] val New Prescaler value
 */
inline void Watchdog::setPrescaler(Prescaler val)
{
	register unsigned char wdp3 = (val & 8) ? 1 : 0;
	register unsigned char wdp = val & 7;
	register unsigned char sreg = SREG;
	register unsigned char _wdtcsr = REG(wdtcsr);
	_wdtcsr &= ~(_BV(WDP3) | 7);
	_wdtcsr |= (wdp3 << WDP3) | wdp;
	disableInterrupts();
	enableChange();
	REG(wdtcsr) = _wdtcsr;
	SREG = sreg;
}
/**
 * @brief Return true, if Watchdog Interrupt Flag is set
 *
 * This bit is set when a time-out occurs in the Watchdog Timer and the
 * Watchdog Timer is configured for interrupt.
 *
 * WDIF is cleared by hardware when executing the corresponding interrupt
 * handling vector. Alternatively, WDIF is cleared by writing a logic one
 * to the flag.
 *
 * When the isInterruptsEnabled() and Watchdog::isIntEnabled(), the Watchdog
 * Time-out Interrupt is executed.
 * @see Watchdog::clearInt()
 * @return True, if Watchdog Interrupt Flag is set
 */
inline bool Watchdog::isInt() const
{
	return REG_(wdtcsr).wdif;
}
/**
 * @brief Clear Watchdog Interrupt Flag
 */
inline void Watchdog::clearInt()
{
	REG_(wdtcsr).wdif = true;
}
/**
 * @brief Return true, if Watchdog Interrupt Enable bit is set
 *
 * When this bit is written to one and isInterruptsEnabled(), the Watchdog
 * Interrupt is enabled.
 *
 * If not Watchdog::isResetEnabled() in combination with this setting, the
 * Watchdog Timer is in Interrupt Mode, and the corresponding interrupt is
 * executed if time-out in the Watchdog Timer occurs.
 *
 * If Watchdog::isResetEnabled(), the Watchdog Timer is in Interrupt and
 * System Reset Mode.
 *
 * The first time-out in the Watchdog Timer will set WDIF (Watchdog::isInt()).
 *
 * Executing the corresponding interrupt vector will clear WDIE and WDIF
 * automatically by hardware (the Watchdog goes to System Reset Mode). This is
 * useful for keeping the Watchdog Timer security while using the interrupt.
 *
 * To stay in Interrupt and System Reset Mode, WDIE must be set after each
 * interrupt. This should however not be done within the interrupt service
 * routine itself, as this might compromise the safety-function of the Watchdog
 * System Reset mode.
 *
 * If the interrupt is not executed before the next time-out, a System Reset
 * will be applied.
 * @see Watchdog::enableInt(), Watchdog::disableInt()
 * @return True, if Watchdog Interrupt Enable bit is set
 */
inline bool Watchdog::isIntEnabled() const
{
	return REG_(wdtcsr).wdie;
}
/**
 * @brief Enable Watchdog Interrupt
 */
inline void Watchdog::enableInt()
{
	REG_(wdtcsr).wdie = true;
}
/**
 * @brief Disable Watchdog Interrupt
 */
inline void Watchdog::disableInt()
{
	REG_(wdtcsr).wdie = false;
}
/**
 * @brief Return true, if Watchdog Change Enable bit is set
 *
 * This bit is used in timed sequences for changing WDE and prescaler bits. To
 * clear the WDE bit, and/or change the prescaler bits, WDCE must be set.
 *
 * Once written to one, hardware will clear WDCE after four clock cycles.
 * @see Watchdog::enableChange()
 * @return True, if Watchdog Change Enable bit is set
 */
inline bool Watchdog::isChangeEnabled() const
{
	return REG_(wdtcsr).wce;
}
/**
 * @brief Enable Watchdog Change
 *
 * Once enabled, hardware will clear WDCE after four clock cycles.
 *
 */
inline void Watchdog::enableChange()
{
	reset();
	REG(wdtcsr) |= _BV(WDCE) | _BV(WDE);
}
/**
 * @brief Return true, if Watchdog System Reset Enable bit is set
 *
 * This bit (WDE) is overridden by MCUControl::isWatchdogResetOccurs() in MCUSR.
 * This means that WDE is always set when MCUControl::isWatchdogResetOccurs() is
 * true.
 *
 * To clear WDE, MCUControl::clearWatchdogReset() must be called first. This
 * feature ensures multiple resets during conditions causing failure, and a safe
 * start-up after the failure.
 * @see Watchdog::enableReset(), Watchdog::disableReset()
 * @return True, if Watchdog System Reset Enable bit is set
 */
inline bool Watchdog::isResetEnabled() const
{
	return REG_(wdtcsr).wde;
}
/**
 * @brief Enable Watchdog System Reset
 */
inline void Watchdog::enableReset()
{
	REG_(wdtcsr).wde = true;
}
/**
 * @brief Disable Watchdog System Reset
 */
inline void Watchdog::disableReset()
{
	register unsigned char sreg = SREG;
	disableInterrupts();
	DEV_MCU.clearWatchdogReset();
	enableChange();
	REG_(wdtcsr).wde = false;
	SREG = sreg;
}
#endif

#if defined(VE_ATmega325) || \
	defined(VE_ATmega32)
inline Watchdog::Prescaler Watchdog::prescaler() const
{
	return (Prescaler) REG_(wdtcsr).wdp;
}
inline void Watchdog::setPrescaler(Prescaler val)
{
	register unsigned char sreg = SREG;
	disableInterrupts();
	enableChange();
	REG_(wdtcsr).wdp = val;
	SREG = sreg;
}
inline bool Watchdog::isChangeEnabled() const
{
	return REG_(wdtcsr).wdce;
}
inline void Watchdog::enableChange()
{
	reset();
	REG(wdtcsr) |= _BV(WDCE) | _BV(WDE);
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32)
/**
 * @addtogroup ATmega32
 * @{
 */
/**
 * @brief Return true, if Watchdog Enable bit is set
 *
 * When the WDE is written to logic one, the Watchdog Timer is enabled, and if the WDE
 * is written to logic zero, the Watchdog Timer function is disabled. WDE can only be
 * cleared if the WDCE bit has logic level one. To disable an enabled Watchdog Timer,
 * the following procedure must be followed:
 * 1. In the same operation, write a logic one to WDCE and WDE. A logic one must be
 * written to WDE even though it is set to one before the disable operation starts.
 * 2. Within the next four clock cycles, write a logic 0 to WDE. This disables the
 * Watchdog.
 *
 * In safety level 2, it is not possible to disable the Watchdog Timer, even with the
 * algorithm described above.
 * @see Watchdog::enable(), Watchdog::disable()
 * @return True, if Watchdog Enable bit is set
 */
inline bool Watchdog::isEnabled() const
{
	return REG_(wdtcsr).wde;
}
/**
 * @brief Enable Watchdog
 */
inline void Watchdog::enable()
{
	REG_(wdtcsr).wde = true;
}
/**
 * @brief Disable Watchdog
 */
inline void Watchdog::disable()
{
	register unsigned char sreg = SREG;
	disableInterrupts();
	enableChange();
	REG(wdtcsr) |= _BV(WDCE) | _BV(WDE);
	REG(wdtcsr) = 0;
	SREG = sreg;
}
/**
 * @}
 */
#endif

#endif /* WATCHDOG_H_ */
