/**
 * @file ve_analogcomp.h
 * @brief Analog Comparator Header
 * @author andrey
 * @date 15.05.2012
 * @copyright GNU Public License
 */
#ifndef ANALOGCOMP_H_
#define ANALOGCOMP_H_

/**
 * @brief Analog Comparator class
 * @ingroup Analog
 */
class AnalogComp: public AVR_ANACOMP
{
public:
	/**
	 * @brief Analog Comparator Positive Input Selection type
	 */
    typedef enum {
        AIN0 = 0,			///< AIN0 pin
        BandgapRef = 1		///< Bandgap Reference
    } PosInputSelect;
    /**
     * @brief Analog Comparator Interrupt Mode type
     */
    typedef enum {
        OutputToggle = 0,	///< Comparator Interrupt on Output Toggle
        FallingEdge = 2,	///< Comparator Interrupt on Falling Output Edge
        RisingEdge = 3		///< Comparator Interrupt on Rising Output Edge
    } InterruptMode;
public:
    void enable();
    void disable();
    bool isDisabled() const;
    void setDisable(bool val);

    PosInputSelect posInputSelect() const;
    void setPosInputSelect(PosInputSelect val);

    bool output() const;

    bool interruptFlag() const;
    void clearInterruptFlag();

    void interruptEnable();
    void interruptDisable();
    bool isInterruptEnabled() const;
    void setInterruptEnable(bool val);

    void inputCaptureEnable();
    void inputCaptureDisable();
    bool isInputCaptureEnabled() const;
    void setInputCaptureEnable(bool val);

    InterruptMode interruptMode() const;
    void setInterruptMode(InterruptMode val);
};

/**
 * @brief Enable Analog Comparator
 */
inline void AnalogComp::enable()
{
	setDisable(false);
}
/**
 * @brief Disable Analog Comparator
 */
inline void AnalogComp::disable()
{
	setDisable(true);
}
/**
 * @brief Return true, if Analog Comparator is disabled
 * @return True, if Analog Comparator is disabled
 */
inline bool AnalogComp::isDisabled() const
{
	return REG_(acsr).acd;
}
/**
 * @brief Set Analog Comparator Disable state
 * @param[in] val New state value
 */
inline void AnalogComp::setDisable(bool val)
{
	bool bEnable = isInterruptEnabled();
    interruptDisable();
    REG_(acsr).acd = val;
    setInterruptEnable(bEnable);
}
/**
 * @brief Return Positive Input Selection
 * @return Positive Input Selection.
 */
inline AnalogComp::PosInputSelect AnalogComp::posInputSelect() const
{
    return (PosInputSelect) REG_(acsr).acbg;
}
/**
 * @brief Set Positive Input Selection
 * @param[in] val Positive Input Selection.
 *
 * When the bandgap referance is used as input to the Analog Comparator, it will
 * take a certain time for the voltage to stabilize. If not stabilized, the first
 * conversion may give a wrong value.
 */
inline void AnalogComp::setPosInputSelect(PosInputSelect val)
{
    REG_(acsr).acbg = (unsigned char) val;
}
/**
 * @brief Return Analog Comparator Output
 * @return Analog Comparator Output.
 */
inline bool AnalogComp::output() const
{
    return REG_(acsr).aco;
}
/**
 * @brief Return Analog Comparator Interrupt Flag
 * @return Analog Comparator Interrupt Flag.
 */
inline bool AnalogComp::interruptFlag() const
{
    return REG_(acsr).aci;
}
/**
 * @brief Clear Analog Comparator Interrupt Flag
 *
 * The Analog Comparator interrupt routine is executed if the Analog Comparator Interrupt
 * is enabled and Interrupts are enabled. This Flag is cleared by hardware when executing
 * the corresponding interrupt handling vector. Alternatively, the Flag is cleared by
 * calling this function.
 */
inline void AnalogComp::clearInterruptFlag()
{
    REG_(acsr).aci = 1;
}
/**
 * @brief Enable Analog Comparator Interrupt
 */
inline void AnalogComp::interruptEnable()
{
    REG_(acsr).acie = true;
}
/**
 * @brief Disable Analog Comparator Interrupt
 */
inline void AnalogComp::interruptDisable()
{
    REG_(acsr).acie = false;
}
/**
 * @brief Return true, if Analog Comparator Interrupt is enabled
 * @return True, if Analog Comparator Interrupt is enabled.
 */
inline bool AnalogComp::isInterruptEnabled() const
{
	return REG_(acsr).acie;
}
/**
 * @brief Set Analog Comparator Interrupt Enable state
 * @param[in] val New state value
 */
inline void AnalogComp::setInterruptEnable(bool val)
{
	REG_(acsr).acie = val;
}
/**
 * @brief Enable Analog Comparator Input Capture
 *
 * This function enables the input capture function in Timer/Counter1 to be triggered by
 * the Analog Comparator. The comparator output is in this case directly connected to the
 * input capture front-end logic, making the comparator utilize the noise canceler and edge
 * select features of the Timer/Counter1 Input Capture interrupt.
 *
 * To make the comparator trigger the Timer/Counter 1 Input Capture interrupt, the
 * TimerIntCtrlW::inputCaptIntEnable() should be called.
 */
inline void AnalogComp::inputCaptureEnable()
{
    REG_(acsr).acic = true;
}
/**
 * @brief Disable Analog Comparator Input Capture
 *
 * When disabled, no connection between the Analog Comparator and the input capture function
 * exists.
 */
inline void AnalogComp::inputCaptureDisable()
{
    REG_(acsr).acic = false;
}
/**
 * @brief Return true, if Input Capture is enabled
 * @return True, if Input Capture is enabled
 */
inline bool AnalogComp::isInputCaptureEnabled() const
{
	return REG_(acsr).acic;
}
/**
 * @brief Set Input Capture Enable state
 * @param[in] val New state value
 */
inline void AnalogComp::setInputCaptureEnable(bool val)
{
	REG_(acsr).acic = val;
}
/**
 * @brief Return Analog Comparator Interrupt Mode Select
 * @return Analog Comparator Interrupt Mode Select.
 */
inline AnalogComp::InterruptMode AnalogComp::interruptMode() const
{
    return (InterruptMode) REG_(acsr).acis;
}
/**
 * @brief Set Analog Comparator Interrupt Mode
 * @param[in] val Analog Comparator Interrupt Mode Select.
 */
inline void AnalogComp::setInterruptMode(InterruptMode val)
{
	bool bEnable = isInterruptEnabled();
    interruptDisable();
    REG_(acsr).acis = (unsigned char) val;
    setInterruptEnable(bEnable);
}

#endif /* ANALOGCOMP_H_ */
