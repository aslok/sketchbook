/**
 * @file ve_externalinterruptcontrol.h
 * @brief External Interrupt Control Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef EXTERNALINTERRUPTCONTROL_H_
#define EXTERNALINTERRUPTCONTROL_H_

/**
 * @brief External Interrupt Control class macro
 */
#define EIC_DECLARE(num, regletter) \
	inline SenseType senseType##num() const { \
		return (SenseType) REG_(eicr##regletter).isc##num; \
	} \
	inline void setSenseType##num(SenseType val) { \
		REG_(eicr##regletter).isc##num = val; \
	}

/**
 * @brief External Interrupt Control class
 * @ingroup ExtInt
 */
class ExtIntControl : public AVR_EXTINTCTRL
{
public:
	/**
	 * @brief Sense type
	 */
	typedef enum {
		LOW_LEVEL = 0,		///< Low Level
		ANY_CHANGE,			///< Any Change
		FALLING_EDGE,		///< Falling Edge
		RISING_EDGE			///< Rising Edge
	} SenseType;
public:
	/**
	 * @fn inline SenseType senseType0() const
	 * @brief Return Sense Type value 0
	 * @return Sense Type value 0
	 *
	 * @fn inline void setSenseType0(SenseType val)
	 * @brief Set Sense Type value 0
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(0, a)

#if defined(VE_ATmega328P)
	EIC_DECLARE(1, a)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560)
	/**
	 * @fn inline SenseType senseType1() const
	 * @brief Return Sense Type value 1
	 * @return Sense Type value 1
	 *
	 * @fn inline void setSenseType1(SenseType val)
	 * @brief Set Sense Type value 1
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(1, a)
	/**
	 * @fn inline SenseType senseType2() const
	 * @brief Return Sense Type value 2
	 * @return Sense Type value 2
	 *
	 * @fn inline void setSenseType2(SenseType val)
	 * @brief Set Sense Type value 2
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(2, a)
	/**
	 * @fn inline SenseType senseType3() const
	 * @brief Return Sense Type value 3
	 * @return Sense Type value 3
	 *
	 * @fn inline void setSenseType3(SenseType val)
	 * @brief Set Sense Type value 3
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(3, a)
	/**
	 * @fn inline SenseType senseType4() const
	 * @brief Return Sense Type value 4
	 * @return Sense Type value 4
	 *
	 * @fn inline void setSenseType4(SenseType val)
	 * @brief Set Sense Type value 4
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(4, b)
	/**
	 * @fn inline SenseType senseType5() const
	 * @brief Return Sense Type value 5
	 * @return Sense Type value 5
	 *
	 * @fn inline void setSenseType5(SenseType val)
	 * @brief Set Sense Type value 5
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(5, b)
	/**
	 * @fn inline SenseType senseType6() const
	 * @brief Return Sense Type value 6
	 * @return Sense Type value 6
	 *
	 * @fn inline void setSenseType6(SenseType val)
	 * @brief Set Sense Type value 6
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(6, b)
	/**
	 * @fn inline SenseType senseType7() const
	 * @brief Return Sense Type value 7
	 * @return Sense Type value 7
	 *
	 * @fn inline void setSenseType7(SenseType val)
	 * @brief Set Sense Type value 7
	 * @param[in] val New Sense Type value
	 */
	EIC_DECLARE(7, b)
#endif

#if defined(VE_ATmega32)
	EIC_DECLARE(1, a)
	EIC_DECLARE(2, b)
#endif

#if defined(VE_ATmega32U4)
	EIC_DECLARE(1, a)
	EIC_DECLARE(2, a)
	EIC_DECLARE(3, a)
	EIC_DECLARE(6, b)
#endif

#if defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	EIC_DECLARE(1, a)
	EIC_DECLARE(2, a)
#endif

};

#endif /* EXTERNALINTERRUPTCONTROL_H_ */
