/**
 * @file ve_timerinterruptflags.h
 * @brief Timer/Counter Interrupt Flags Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef TIMERINTERRUPTFLAGS_H_
#define TIMERINTERRUPTFLAGS_H_

/**
 * @brief TimerIntFlagsT template macro
 * @param[in] func Function name
 * @param[in] bit Bit name
 */
#define DECLARE_TIFT(func, bit) \
	bool is##func() const { \
		return this->m_reg.bit; \
	} \
	void clear##func() { \
		this->m_reg.bit = true; \
	}

/**
 * @addtogroup Timers
 * @{
 */

/**
 * @brief Timer/Counter Interrupt Flags class
 */
template <typename _TIFR_REG>
class TimerIntFlagsT: public _TIFR_REG
{
public:
	/**
	 * @fn bool isOverflow() const
	 * @brief Return true, if Overflow Interrupt Flag is set
	 * @return True, if Overflow Interrupt Flag is set
	 *
	 * @fn void clearOverflow()
	 * @brief Clear Overflow Interrupt Flag
	 */
	DECLARE_TIFT(Overflow, tov)
	/**
	 * @fn bool isInputCapture() const
	 * @brief Return true, if Input Capture Interrupt Flag is set
	 * @return True, if Input Capture Interrupt Flag is set
	 *
	 * @fn void clearInputCapture()
	 * @brief Clear Input Capture Interrupt Flag
	 */
	DECLARE_TIFT(InputCapture, icf)
	/**
	 * @fn bool isOutputCompareMatchA() const
	 * @brief Return true, if Output Compare Match A Interrupt Flag is set
	 * @return True, if Output Compare Match A Interrupt Flag is set
	 *
	 * @fn void clearOutputCompareMatchA()
	 * @brief Clear Output Compare Match A Interrupt Flag
	 */
	DECLARE_TIFT(OutputCompareMatchA, ocfa)
	/**
	 * @fn bool isOutputCompareMatchB() const
	 * @brief Return true, if Output Compare Match B Interrupt Flag is set
	 * @return True, if Output Compare Match B Interrupt Flag is set
	 *
	 * @fn void clearOutputCompareMatchB()
	 * @brief Clear Output Compare Match B Interrupt Flag
	 */
	DECLARE_TIFT(OutputCompareMatchB, ocfb)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4)
	/**
	 * @fn bool isOutputCompareMatchC() const
	 * @brief Return true, if Output Compare Match C Interrupt Flag is set
	 * @return True, if Output Compare Match C Interrupt Flag is set
	 *
	 * @fn void clearOutputCompareMatchC()
	 * @brief Clear Output Compare Match C Interrupt Flag
	 */
	DECLARE_TIFT(OutputCompareMatchC, ocfc)
#endif
};

typedef TimerIntFlagsT<TIFR_REG> TimerIntFlags;		///< 8-bit Timer/Counter Interrupt Flags class
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) ||\
	defined(VE_ATmega32U4)
typedef TimerIntFlagsT<TIFRW_REG> TimerIntFlagsW;	///< 16-bit Timer/Counter Interrupt Flags class
#endif
/**
 * @}
 */
#endif /* TIMERINTERRUPTFLAGS_H_ */
