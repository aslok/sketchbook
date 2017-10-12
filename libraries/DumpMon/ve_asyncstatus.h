/**
 * @file ve_asyncstatus.h
 * @brief Asynchronous Status Header
 * @author andrey
 * @date 25.10.2012
 * @copyright GNU Public License
 */
#ifndef ASYNCSTATUS_H_
#define ASYNCSTATUS_H_

/**
 * @brief Asynchronous Status class
 * @ingroup Timers
 *
 *
 * If a write is performed to any of the five Timer/Counter 2 Registers
 * while its update busy flag is true, the updated value might get corrupted
 * and cause an unintentional interrupt to occur.
 *
 * The mechanisms for reading TCNT2, OCR2A, OCR2B, TCCR2A and TCCR2B are different.
 * When reading TCNT2, the actual timer value is read. When reading OCR2A, OCR2B,
 * TCCR2A and TCCR2B the value in the temporary storage register is read.
 */
class AsyncStatus : public AVR_ASYNCST
{
public:
	/**
	 * @brief Asynchronous Clock Source type
	 */
	typedef enum {
		CLKIO = 0,		///< I/O Clock
		TOSC1			///< Timer Oscillator 1 (TOSC1) pin
	} AsyncClk;
public:
	AsyncClk timer2ClkSrc() const;
	void setTimer2ClkSrc(AsyncClk clksrc);
	bool tcnt2UpdateBusy() const;
	bool ocr2AUpdateBusy() const;
	bool ocr2BUpdateBusy() const;

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	bool isExtClkInputEnabled() const;
	void enableExtClkInput();
	void disableExtClkInput();
	void setExtClkInputEnable(bool val);
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	bool tccr2AUpdateBusy() const;
	bool tccr2BUpdateBusy() const;
#endif
};

/**
 * @brief Return Asynchronous Timer/Counter 2 Clock Source
 * @return Asynchronous Timer/Counter 2 Clock Source.
 */
inline AsyncStatus::AsyncClk AsyncStatus::timer2ClkSrc() const
{
	return (AsyncClk) REG_(assr).as2;
}
/**
 * @brief Set Asynchronous Timer/Counter 2 Clock Source
 * @param[in] clksrc Asynchronous Timer/Counter 2 Clock Source.
 *
 * When this value changes, the contents of TCNT2, OCR2A, OCR2B, TCCR2A and
 * TCCR2B might be corrupted.
 */
inline void AsyncStatus::setTimer2ClkSrc(AsyncClk clksrc)
{
	REG_(assr).as2 = (bool) clksrc;
}
/**
 * @brief Return Timer/Counter 2 Update Busy Flag
 * @return Timer/Counter 2 Update Busy Flag.
 *
 * When Timer/Counter 2 operates asynchronously and TCNT2 is written, this flag
 * becomes true. When TCNT2 has been updated from the temporary storage register,
 * this flag is cleared by hardware.
 *
 * A false in this flag indicates that TCNT2 is ready to be updated with
 * a new value.
 */
inline bool AsyncStatus::tcnt2UpdateBusy() const
{
	return REG_(assr).tcn2ub;
}
/**
 * @brief Return Output Compare Register 2A Update Busy Flag
 * @return Output Compare Register 2A Update Busy Flag.
 *
 * When Timer/Counter 2 operates asynchronously and OCR2A is written, this flag
 * becomes true. When OCR2A has been updated from the temporary storage register,
 * this flag is cleared by hardware.
 *
 * A false in this flag indicates that OCR2A is ready to be updated with a new value.
 */
inline bool AsyncStatus::ocr2AUpdateBusy() const
{
	return REG_(assr).ocr2aub;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return true, if External Clock Input is enabled
 * @return True, if External Clock Input is enabled.
 */
inline bool AsyncStatus::isExtClkInputEnabled() const
{
	return REG_(assr).exclk;
}
/**
 * @brief Enable External Clock Input
 *
 * When enabled, and asynchronous clock is selected, the external clock input buffer
 * is enabled and an external clock can be input on Timer Oscillator 1 (TOSC1) pin
 * instead of a 32 kHz crystal.
 *
 * Enabling should be done before asynchronous operation is selected.
 *
 * Note that the crystal Oscillator will only run when External Clock Input is disabled.
 */
inline void AsyncStatus::enableExtClkInput()
{
	REG_(assr).exclk = true;
}
/**
 * @brief Disable External Clock Input
 */
inline void AsyncStatus::disableExtClkInput()
{
	REG_(assr).exclk = false;
}
/**
 * @brief Set External Clock Input Enable state
 * @param[in] val New state value
 */
inline void AsyncStatus::setExtClkInputEnable(bool val)
{
	REG_(assr).exclk = val;
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return Output Compare Register 2B Update Busy Flag
 * @return Output Compare Register 2B Update Busy Flag.
 *
 * When Timer/Counter 2 operates asynchronously and OCR2B is written, this flag becomes true.
 * When OCR2B has been updated from the temporary storage register, this flag is cleared by
 * hardware.
 *
 * A false in this flag indicates that OCR2B is ready to be updated with a new value.
 */
inline bool AsyncStatus::ocr2BUpdateBusy() const
{
	return REG_(assr).ocr2bub;
}
/**
 * @brief Return Timer/Counter Control Register 2A Update Busy Flag
 * @return Timer/Counter Control Register 2A Update Busy Flag.
 *
 * When Timer/Counter 2 operates asynchronously and TCCR2A is written, this flag becomes true.
 * When TCCR2A has been updated from the temporary storage register, this flag is cleared by
 * hardware.
 *
 * A false in this flag indicates that TCCR2A is ready to be updated with a new value.
 */
inline bool AsyncStatus::tccr2AUpdateBusy() const
{
	return REG_(assr).tcr2aub;
}
/**
 * @brief Return Timer/Counter Control Register 2B Update Busy Flag
 * @return Timer/Counter Control Register 2B Update Busy Flag.
 *
 * When Timer/Counter 2 operates asynchronously and TCCR2B is written, this flag becomes true.
 * When TCCR2B has been updated from the temporary storage register, this flag is cleared by
 * hardware.
 *
 * A false in this flag indicates that TCCR2A is ready to be updated with a new value.
 */
inline bool AsyncStatus::tccr2BUpdateBusy() const
{
	return REG_(assr).tcr2bub;
}
#endif

#endif /* ASYNCSTATUS_H_ */
