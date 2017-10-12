/**
 * @file ve_timerinterruptcontrol.h
 * @brief Timer/Counter Interrupt Control Header
 * @author andrey
 * @date 27.01.2012
 * @copyright GNU Public License
 */
#ifndef TIMERINTERRUPTCONTROL_H_
#define TIMERINTERRUPTCONTROL_H_

/**
 * @brief TimerInterruptControlT template macro
 * @param[in] caps Capitalized function name
 * @param[in] small Small-letters function name
 * @param[in] bit Bit name
 */
#define DECLARE_TICT(caps, small, bit) \
    bool is##caps##Enabled() const { \
        return this->m_reg.bit; \
    } \
    void small##Enable() { \
        this->m_reg.bit = true; \
    } \
    void small##Disable() { \
        this->m_reg.bit = false; \
    } \
	void set##caps##Enable(bool val) { \
    	this->m_reg.bit = val; \
    }
/**
 * @brief TimerInterruptControlT template macro
 * @param[in] caps Capitalized function name
 * @param[in] small Small-letters function name
 * @param[in] letter Letter
 * @param[in] bit Bit name
 */
#define DECLARE_TICTL(caps, small, letter, bit) \
    bool is##caps##Enabled##letter() const { \
        return this->m_reg.bit; \
    } \
    void small##Enable##letter() { \
        this->m_reg.bit = true; \
    } \
    void small##Disable##letter() { \
        this->m_reg.bit = false; \
    } \
	void set##caps##letter##Enable(bool val) { \
    	this->m_reg.bit = val; \
    }

/**
 * @addtogroup Timers
 * @{
 */

/**
 * @brief Timer/Counter Interrupt Control class template
 */
template<typename _TIMSK_REG>
class TimerInterruptControlT: public _TIMSK_REG
{
public:
	/**
     * @fn bool isOverflowIntEnabled() const
     * @brief Return true, if Overflow Interrupt is enabled
     * @return True, if Overflow Interrupt is enabled
     *
     * @fn void overflowIntEnable()
     * @brief Enable Overflow Interrupt
     *
     * @fn void overflowIntDisable()
     * @brief Disable Overflow Interrupt
     *
     * @fn void setOverflowIntEnable(bool val)
     * @brief Set Overflow Interrupt Enable state
     * @param[in] val New state value
     */
	DECLARE_TICT(OverflowInt, overflowInt, toie)
	/**
	 * @fn bool isOutCompIntEnabledA() const
	 * @brief Return true, if Output Compare A Interrupt is enabled
	 * @return True, if Output Compare A Interrupt is enabled
	 *
	 * @fn void outCompIntEnableA()
	 * @brief Enable Output Compare A Interrupt
	 *
	 * @fn void outCompIntDisableA()
	 * @brief Disable Output Compare A Interrupt
	 *
	 * @fn void setOutCompIntAEnable(bool val)
	 * @brief Set Output Compare A Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_TICTL(OutCompInt, outCompInt, A, ociea)
	/**
	 * @fn bool isOutCompIntEnabledB() const
	 * @brief Return true, if Output Compare B Interrupt is enabled
	 * @return True, if Output Compare B Interrupt is enabled
	 *
	 * @fn void outCompIntEnableB()
	 * @brief Enable Output Compare B Interrupt
	 *
	 * @fn void outCompIntDisableB()
	 * @brief Disable Output Compare B Interrupt
	 *
	 * @fn void setOutCompIntBEnable(bool val)
	 * @brief Set Output Compare B Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_TICTL(OutCompInt, outCompInt, B, ocieb)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4)
	/**
	 * @fn bool isOutCompIntEnabledC() const
	 * @brief Return true, if Output Compare C Interrupt is enabled
	 * @return True, if Output Compare C Interrupt is enabled
	 *
	 * @fn void outCompIntEnableC()
	 * @brief Enable Output Compare C Interrupt
	 *
	 * @fn void outCompIntDisableC()
	 * @brief Disable Output Compare C Interrupt
	 *
	 * @fn void setOutCompIntCEnable(bool val)
	 * @brief Set Output Compare C Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_TICTL(OutCompInt, outCompInt, C, ociec)
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
	/**
	 * @fn bool isOutCompIntEnabledD() const
	 * @brief Return true, if Output Compare D Interrupt is enabled
	 * @return True, if Output Compare D Interrupt is enabled
	 *
	 * @fn void outCompIntEnableD()
	 * @brief Enable Output Compare D Interrupt
	 *
	 * @fn void outCompIntDisableD()
	 * @brief Disable Output Compare D Interrupt
	 *
	 * @fn void setOutCompIntDEnable(bool val)
	 * @brief Set Output Compare D Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_TICTL(OutCompInt, outCompInt, D, ocied)
#endif
	/**
     * @fn bool isInputCaptIntEnabled() const
     * @brief Return true, if Input Capture Interrupt is enabled
     * @return True, if Input Capture Interrupt is enabled
     *
     * @fn void inputCaptIntEnable()
     * @brief Enable Input Capture Interrupt
     *
     * @fn void inputCaptIntDisable()
     * @brief Disable Input Capture Interrupt
     *
     * @fn void setInputCaptIntEnable(bool val)
     * @brief Set Input Capture Interrupt Enable state
     * @param[in] val New state value
     */
	DECLARE_TICT(InputCaptInt, inputCaptInt, icie)
};

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
typedef TimerInterruptControlT<TIMSK_REG> TimerIntCtrl;		///< 8-bit Timer/Counter Interrupt Control class
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32)
typedef TimerInterruptControlT<TIMSK0_REG> TimerIntCtrl0;	///< ATmega32 Timer/Counter 0 Interrupt Control class
typedef TimerInterruptControlT<TIMSK2_REG> TimerIntCtrl2;	///< ATmega32 Timer/Counter 2 Interrupt Control class
#endif

typedef TimerInterruptControlT<TIMSKW_REG> TimerIntCtrlW;	///< 16-bit Timer/Counter Interrupt Control class

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
typedef TimerInterruptControlT<TIMSKHS_REG> TimerIntCtrlHS;	///< 10-bit High Speed Timer/Counter Interrupt Control class
#endif
/**
 * @}
 */
#endif /* TIMERINTERRUPTCONTROL_H_ */
