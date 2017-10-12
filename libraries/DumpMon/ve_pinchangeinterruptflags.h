/**
 * @file ve_pinchangeinterruptflags.h
 * @brief Pin Change Interrupt Flags Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef PINCHANGEINTERRUPTFLAGS_H_
#define PINCHANGEINTERRUPTFLAGS_H_

/**
 * @brief PinChangeFlags class macro
 * @param[in] num Pin Change Interrupt number
 */
#define DECLARE_PCF(num) \
	inline bool isInt##num() const { \
		return REG_(pcifr).pcif##num; \
	} \
	inline void clearInt##num()	{ \
		REG_(pcifr).pcif##num = false; \
	}

/**
 * @brief Pin Change Interrupt Flags class
 * @ingroup PCint
 */
class PinChangeFlags : public AVR_PCIFLAGS
{
public:
	/**
	 * @fn inline bool isInt0() const
	 * @brief Return true, if PCINT0 Interrupt Flag is set
	 * @return True, if PCINT0 Interrupt Flag is set
	 *
	 * @fn inline void clearInt0()
	 * @brief Clear PCINT0 Interrupt Flag
	 */
	DECLARE_PCF(0)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	/**
	 * @fn inline bool isInt1() const
	 * @brief Return true, if PCINT1 Interrupt Flag is set
	 * @return True, if PCINT1 Interrupt Flag is set
	 *
	 * @fn inline void clearInt1()
	 * @brief Clear PCINT1 Interrupt Flag
	 */
	DECLARE_PCF(1)
	/**
	 * @fn inline bool isInt2() const
	 * @brief Return true, if PCINT2 Interrupt Flag is set
	 * @return True, if PCINT2 Interrupt Flag is set
	 *
	 * @fn inline void clearInt2()
	 * @brief Clear PCINT2 Interrupt Flag
	 */
	DECLARE_PCF(2)
#endif
};

#endif /* PINCHANGEINTERRUPTFLAGS_H_ */
