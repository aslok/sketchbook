/**
 * @file ve_externalinterruptflags.h
 * @brief External Interrupt Flags Header
 * @author andrey
 * @date 30.10.2012
 * @copyright GNU Public License
 */
#ifndef EXTERNALINTERRUPTFLAGS_H_
#define EXTERNALINTERRUPTFLAGS_H_

/**
 * @brief External Interrupt Flags class macro
 */
#define EIF_DECLARE(num) \
	inline bool isInterrupt##num () const { \
		return REG_(eifr).intf##num; \
	} \
	inline void clearInterrupt##num () { \
		REG_(eifr).intf##num = false; \
	} \
	inline bool isInterrupt##num##Enabled() const { \
		return REG_(eimsk).int##num; \
	} \
	inline void enableInterrupt##num() { \
		REG_(eimsk).int##num = true; \
	} \
	inline void disableInterrupt##num() { \
		REG_(eimsk).int##num = false; \
	} \
	inline void setInterrupt##num##Enable(bool val) { \
		REG_(eimsk).int##num = val; \
	}

/**
 * @brief External Interrupt Flags class
 * @ingroup ExtInt
 */
class ExtIntFlags : public AVR_EXTINTFLAGS
{
public:
	/**
	 * @fn inline bool isInterrupt0() const
	 * @brief Return true, if INTF0 Flag is set
	 * @return True, if INTF0 Flag is set
	 *
	 * @fn inline void clearInterrupt0()
	 * @brief Clear INTF0 Flag
	 *
	 * @fn inline bool isInterrupt0Enabled() const
	 * @brief Return true, if INT0 Interrupt is enabled
	 * @return True, if INT0 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt0()
	 * @brief Enable INT0 Interrupt
	 *
	 * @fn inline void disableInterrupt0()
	 * @brief Disable INT0 Interrupt
	 *
	 * @fn inline void setInterrupt0Enable(bool val)
	 * @brief Set INT0 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(0)
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega328P)
	/**
	 * @fn inline bool isInterrupt1() const
	 * @brief Return true, if INTF1 Flag is set
	 * @return True, if INTF1 Flag is set
	 *
	 * @fn inline void clearInterrupt1()
	 * @brief Clear INTF1 Flag
	 *
	 * @fn inline bool isInterrupt1Enabled() const
	 * @brief Return true, if INT1 Interrupt is enabled
	 * @return True, if INT1 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt1()
	 * @brief Enable INT1 Interrupt
	 *
	 * @fn inline void disableInterrupt1()
	 * @brief Disable INT1 Interrupt
	 *
	 * @fn inline void setInterrupt1Enable(bool val)
	 * @brief Set INT1 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(1)
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P) || \
	defined(VE_ATmega32U4)
	/**
	 * @fn inline bool isInterrupt2() const
	 * @brief Return true, if INTF2 Flag is set
	 * @return True, if INTF2 Flag is set
	 *
	 * @fn inline void clearInterrupt2()
	 * @brief Clear INTF2 Flag
	 *
	 * @fn inline bool isInterrupt2Enabled() const
	 * @brief Return true, if INT2 Interrupt is enabled
	 * @return True, if INT2 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt2()
	 * @brief Enable INT2 Interrupt
	 *
	 * @fn inline void disableInterrupt2()
	 * @brief Disable INT2 Interrupt
	 *
	 * @fn inline void setInterrupt2Enable(bool val)
	 * @brief Set INT2 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(2)
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4)
	/**
	 * @fn inline bool isInterrupt3() const
	 * @brief Return true, if INTF3 Flag is set
	 * @return True, if INTF3 Flag is set
	 *
	 * @fn inline void clearInterrupt3()
	 * @brief Clear INTF3 Flag
	 *
	 * @fn inline bool isInterrupt3Enabled() const
	 * @brief Return true, if INT3 Interrupt is enabled
	 * @return True, if INT3 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt3()
	 * @brief Enable INT3 Interrupt
	 *
	 * @fn inline void disableInterrupt3()
	 * @brief Disable INT3 Interrupt
	 *
	 * @fn inline void setInterrupt3Enable(bool val)
	 * @brief Set INT3 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(3)
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560)
	/**
	 * @fn inline bool isInterrupt4() const
	 * @brief Return true, if INTF4 Flag is set
	 * @return True, if INTF4 Flag is set
	 *
	 * @fn inline void clearInterrupt4()
	 * @brief Clear INTF4 Flag
	 *
	 * @fn inline bool isInterrupt4Enabled() const
	 * @brief Return true, if INT4 Interrupt is enabled
	 * @return True, if INT4 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt4()
	 * @brief Enable INT4 Interrupt
	 *
	 * @fn inline void disableInterrupt4()
	 * @brief Disable INT4 Interrupt
	 *
	 * @fn inline void setInterrupt4Enable(bool val)
	 * @brief Set INT4 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(4)
	/**
	 * @fn inline bool isInterrupt5() const
	 * @brief Return true, if INTF5 Flag is set
	 * @return True, if INTF5 Flag is set
	 *
	 * @fn inline void clearInterrupt5()
	 * @brief Clear INTF5 Flag
	 *
	 * @fn inline bool isInterrupt5Enabled() const
	 * @brief Return true, if INT5 Interrupt is enabled
	 * @return True, if INT5 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt5()
	 * @brief Enable INT5 Interrupt
	 *
	 * @fn inline void disableInterrupt5()
	 * @brief Disable INT5 Interrupt
	 *
	 * @fn inline void setInterrupt5Enable(bool val)
	 * @brief Set INT5 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(5)
	/**
	 * @fn inline bool isInterrupt6() const
	 * @brief Return true, if INTF6 Flag is set
	 * @return True, if INTF6 Flag is set
	 *
	 * @fn inline void clearInterrupt6()
	 * @brief Clear INTF6 Flag
	 *
	 * @fn inline bool isInterrupt6Enabled() const
	 * @brief Return true, if INT6 Interrupt is enabled
	 * @return True, if INT6 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt6()
	 * @brief Enable INT6 Interrupt
	 *
	 * @fn inline void disableInterrupt6()
	 * @brief Disable INT6 Interrupt
	 *
	 * @fn inline void setInterrupt6Enable(bool val)
	 * @brief Set INT6 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(6)
	/**
	 * @fn inline bool isInterrupt7() const
	 * @brief Return true, if INTF7 Flag is set
	 * @return True, if INTF7 Flag is set
	 *
	 * @fn inline void clearInterrupt7()
	 * @brief Clear INTF7 Flag
	 *
	 * @fn inline bool isInterrupt7Enabled() const
	 * @brief Return true, if INT7 Interrupt is enabled
	 * @return True, if INT7 Interrupt is enabled
	 *
	 * @fn inline void enableInterrupt7()
	 * @brief Enable INT7 Interrupt
	 *
	 * @fn inline void disableInterrupt7()
	 * @brief Disable INT7 Interrupt
	 *
	 * @fn inline void setInterrupt7Enable(bool val)
	 * @brief Set INT7 Interrupt Enable state
	 * @param[in] val New state value
	 */
	EIF_DECLARE(7)
#endif
};

#endif /* EXTERNALINTERRUPTFLAGS_H_ */
