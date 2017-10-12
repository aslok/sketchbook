/**
 * @file ve_adc.h
 * @brief ADC Header
 * @author andrey
 * @date 11.05.2012
 * @copyright GNU Public License
 */
#ifndef ADC_H_
#define ADC_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
#define ADCONV_PARENT	AVR_AMUX	///< A/D Converter parent class type
#endif

#if defined(VE_ATmega32)
typedef struct {
	unsigned char reserved[40];
} __ADConvP;
#define ADCONV_PARENT	AVR_AMUX, private __ADConvP, public AVR_SFIORS
#endif

/**
 *  @brief ADC class
 *  @ingroup Analog
 */
class ADConv: public ADCONV_PARENT
{
public:
	/**
	 * @brief ADC Prescaler value type
	 */
    typedef enum {
        Default_2 = 0,			///< Clock /2
        Prescaler_2 = 1,		///< Clock /2
        Prescaler_4 = 2,		///< Clock /4
        Prescaler_8 = 3,		///< Clock /8
        Prescaler_16 = 4,		///< Clock /16
        Prescaler_32 = 5,		///< Clock /32
        Prescaler_64 = 6,		///< Clock /64
        Prescaler_128 = 7		///< Clock /128
    } Prescaler;

#if defined(__DOXYGEN__) || \
    defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    /**
     * @brief ADC Auto Trigger Source value type
     *
     * For ATmega328P, ATmega2560, ATmega325, ATmega32, ATmega644PA, ATmega1284P.
     */
    typedef enum {
        FreeRunningMode     = 0,	///< Free-Running Mode
        AnalogComparator    = 1,	///< Analog Comparator
        ExtIntRequest       = 2,	///< External Interrupt Request 0
        Timer0CompareMatchA = 3,	///< Timer/Counter 0 Compare Match A
        Timer0Overflow      = 4,	///< Timer/Counter 0 Overflow
        Timer1CompareMatchB = 5,	///< Timer/Counter 1 Compare Match B
        Timer1Overflow      = 6,	///< Timer/Counter 1 Overflow
        Timer1Capture       = 7		///< Timer/Counter 1 Capture Event
    } ATmega328P_TriggerSrc;
    /**
     * @brief ADC Auto Trigger Source value type
     *
     * For ATmega328P, ATmega2560, ATmega325, ATmega32, ATmega644PA, ATmega1284P.
     */
    typedef ATmega328P_TriggerSrc TriggerSrc;
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
    /**
     * @brief ATmega32U4 ADC Auto Trigger Source type
     */
    typedef enum {
        FreeRunningMode     = 0,	///< Free-Running Mode
        AnalogComparator    = 1,	///< Analog Comparator
        ExtIntRequest       = 2,	///< External Interrupt Request 0
        Timer0CompareMatch  = 3,	///< Timer/Counter 0 Compare Match A
        Timer0Overflow      = 4,	///< Timer/Counter 0 Overflow
        Timer1CompareMatchB = 5,	///< Timer/Counter 1 Compare Match B
        Timer1Overflow      = 6,	///< Timer/Counter 1 Overflow
        Timer1Capture       = 7,	///< Timer/Counter 1 Capture Event
        Timer4Overflow		= 8,	///< Timer/Counter 4 Overflow
        Timer4CompareMatchA = 9,	///< Timer/Counter 1 Compare Match A
        Timer4CompareMatchB = 10,	///< Timer/Counter 1 Compare Match B
        Timer4CompareMatchD = 11	///< Timer/Counter 1 Compare Match D
    } ATmega32U4_TriggerSrc;
    /**
     * @brief ATmega32U4 ADC Auto Trigger Source type
     */
    typedef ATmega32U4_TriggerSrc TriggerSrc;
#endif

public:
    void enable();
    void disable();
    bool isEnabled() const;
    void setEnable(bool val);

    void startConversion();
    bool isConversionStarted()const;

    void autoTriggerEnable();
    void autoTriggerDisable();
    bool isAutoTriggerEnabled() const;
    void setAutoTriggerEnable(bool val);

    bool isConversionComplete();

    void resetIntFlag();

    void enableInt();
    void disableInt();
    bool isIntEnabled() const;
    void setIntEnable(bool val);

    Prescaler prescaler() const;
    void setPrescaler(Prescaler val);

    AnalogMux::VoltageRef voltageReference() const;
    void setVoltageReference(AnalogMux::VoltageRef ref);

    bool isLeftAjustResult() const;
    void setLeftAdjustResult(bool adj);

    AnalogMux::Channel channel() const;
    void setChannel(AnalogMux::Channel chnl);

    uint16_t result() const;

    TriggerSrc triggerSource() const;
    void setTriggerSource(TriggerSrc val);

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    bool isDigitalInputDisabled(AnalogMux::DigitalInput pin) const;
    void disableDigitalInput(AnalogMux::DigitalInput pin);
    void enableDigitalInput(AnalogMux::DigitalInput pin);
    void setDigitalInputDisable(AnalogMux::DigitalInput pin, bool val);
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
    bool isHighSpeedModeEnabled() const;
    void enableHighSpeedMode();
    void disableHighSpeedMode();
    void setHighSpeedModeEnable(bool val);
#endif
};

/**
 * @brief Enable the ADC
 */
inline void ADConv::enable()
{
    REG_(adcsra).aden = true;
}
/**
 * @brief Disable the ADC
 *
 * Turning the ADC off while a conversion is in progress,
 * will terminate this conversion.
 */
inline void ADConv::disable()
{
    REG_(adcsra).aden = false;
}
/**
 * @brief Return true, if the ADC is enabled
 * @return True, if the ADC is eanbled.
 */
inline bool ADConv::isEnabled() const
{
    return REG_(adcsra).aden;
}
/**
 * @brief Set ADC Enable state
 * @param[in] val New state value
 */
inline void ADConv::setEnable(bool val)
{
	REG_(adcsra).aden = val;
}
/**
 * @brief Return true, if the ADC is enabled
 * @return True, if the ADC is eanbled.
 */
inline bool isADCEnabled()
{
	return DEV_ADC.isEnabled();
}
/**
 * @brief Start A/D conversion
 *
 * In Single Conversion mode, call this function to start each conversion.
 * In Free Running mode, call this function to start the first conversion.
 * The first conversion after ADSC has been written after the ADC has been enabled,
 * or if ADSC is written at the same time as the ADC is enabled, will take 25 ADC
 * clock cycles instead of the normal 13. This first conversion performs
 * initialization of the ADC.
 *
 * ADSC bit will read as one as long as a conversion is in progress.
 * When the conversion is complete, it returns to zero.
 * Writing zero to this bit has no effect.
 */
inline void ADConv::startConversion()
{
    REG_(adcsra).adsc = true;
}
/**
 * @brief Return true, if A/D conversion is started
 * @return True, if A/D conversion is started.
 *
 * When the conversion is complete, it returns false.
 */
inline bool ADConv::isConversionStarted() const
{
    return REG_(adcsra).adsc;
}
/**
 * @brief Enable ADC Auto Triggering
 *
 * The ADC will start a conversion on a positive edge of the selected
 * trigger signal.
 *
 * The trigger source is selected by calling ADConv::setTriggerSource().
 */
inline void ADConv::autoTriggerEnable()
{
    REG_(adcsra).adate = true;
}
/**
 * @brief Disable ADC Auto Triggering
 */
inline void ADConv::autoTriggerDisable()
{
    REG_(adcsra).adate = false;
}
/**
 * @brief Return true, if ADC Auto Triggering is enabled
 * @return True, if ADC Auto Triggering is enabled.
 */
inline bool ADConv::isAutoTriggerEnabled() const
{
    return REG_(adcsra).adate;
}
/**
 * @brief Set Auto Trigger Enable state
 * @param[in] val New state value
 */
inline void ADConv::setAutoTriggerEnable(bool val)
{
	REG_(adcsra).adate = val;
}
/**
 * @brief Return true, if A/D conversion is complete
 */
inline bool ADConv::isConversionComplete()
{
    return REG_(adcsra).adif;
}
/**
 * @brief Reset ADC Interrupt Flag
 */
inline void ADConv::resetIntFlag()
{
    REG_(adcsra).adif = false;
}
/**
 * @brief Enable ADC Interrupt
 */
inline void ADConv::enableInt()
{
    REG_(adcsra).adie = true;
}
/**
 * @brief Disable ADC Interrupt
 */
inline void ADConv::disableInt()
{
    REG_(adcsra).adie = false;
}
/**
 * @brief Return true, if ADC Interrupt is enabled
 * @return True, if ADC Interrupt is enabled.
 */
inline bool ADConv::isIntEnabled() const
{
    return REG_(adcsra).adie;
}
/**
 * @brief Set ADC Interrupt Enable state
 * @param[in] val New state value
 */
inline void ADConv::setIntEnable(bool val)
{
	REG_(adcsra).adie = val;
}
/**
 * @brief Return ADC Prescaler value
 * @return ADC Prescaler value.
 */
inline ADConv::Prescaler ADConv::prescaler() const
{
    return (ADConv::Prescaler) REG_(adcsra).adps;
}
/**
 * @brief Set ADC Prescaler
 * @param[in] val Prescaler value.
 *
 * ADC Prescaler determines the division factor between the system clock
 * frequency and the input clock to the ADC.
 */
inline void ADConv::setPrescaler(Prescaler val)
{
    REG_(adcsra).adps = (unsigned char) val;
}
/**
 * @brief Return voltage reference for the ADC
 * @return Voltage reference for the ADC.
 */
inline AnalogMux::VoltageRef ADConv::voltageReference() const
{
    return DEV_ANAMUX.voltageReference();
}
/**
 * @brief Set voltage reference for the ADC
 * @param[in] ref Voltage reference selection.
 *
 * If this value is changed during a conversion, the change will not go in
 * effect until this conversion is complete (ADIF in ADCSRA is set).
 *
 * The internal voltage reference options may not be used if an external
 * reference voltage is being applied to the AREF pin.
 */
inline void ADConv::setVoltageReference(AnalogMux::VoltageRef ref)
{
	DEV_ANAMUX.setVoltageReference(ref);
}
/**
 * @brief Return true, if result of conversion is left adjusted
 * @return True, if result of conversion is left adjusted.
 */
inline bool ADConv::isLeftAjustResult() const
{
    return DEV_ANAMUX.isLeftAjustResult();
}
/**
 * @brief Set adjustment of the result of conversion in ADC Data Register
 * @param[in] adj True for left adjusted result.
 *
 * Write true to left adjust the result. Otherwise, the result is right adjusted.
 * Changing this value will affect the ADC Data Register immediately, regardless
 * of any ongoing conversions.
 */
inline void ADConv::setLeftAdjustResult(bool adj)
{
	DEV_ANAMUX.setLeftAdjustResult(adj);
}
/**
 * @brief Return current ADC input channel
 * @return Current ADC input channel.
 */
inline AnalogMux::Channel ADConv::channel() const
{
    return DEV_ANAMUX.channel();
}
/**
 * @brief Connect input channel to the ADC
 * @param[in] chnl Input channel.
 *
 * If this value is changed during a conversion, the change will not go in effect
 * until this conversion is complete (ADIF in ADCSRA is set).
 */
inline void ADConv::setChannel(AnalogMux::Channel chnl)
{
	DEV_ANAMUX.setChannel(chnl);
}
/**
 * @brief Return ADC Conversion Result
 * @return ADC Conversion Result.
 */
inline uint16_t ADConv::result() const
{
    return REGW(adc);
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return true, if given digital input is disabled
 * @param[in] pin Digital input.
 * @return True, if given digital input is disabled.
 *
 * Not available for ATmega32.
 */
inline bool ADConv::isDigitalInputDisabled(AnalogMux::DigitalInput pin) const
{
    return DEV_ANAMUX.digitalInputDisabled(pin);
}
/**
 * @brief Disable digital input
 * @param[in] pin Digital input.
 *
 * Not available for ATmega32.
 */
inline void ADConv::disableDigitalInput(AnalogMux::DigitalInput pin)
{
    DEV_ANAMUX.disableDigitalInput(pin);
}
/**
 * @brief Enable digital input
 * @param[in] pin Digital input.
 *
 * Not available for ATmega32.
 */
inline void ADConv::enableDigitalInput(AnalogMux::DigitalInput pin)
{
    DEV_ANAMUX.enableDigitalInput(pin);
}
/**
 * @brief Set Digital Input Disable state
 * @param[in] pin Digital input
 * @param[in] val New state value
 */
inline void ADConv::setDigitalInputDisable(AnalogMux::DigitalInput pin, bool val)
{
	DEV_ANAMUX.setDigitalInputDisable(pin, val);
}
/**
 * @brief Return the ADC Auto Triggering source
 * @return ADC Auto Triggering source.
 */
inline ADConv::TriggerSrc ADConv::triggerSource() const
{
    return (ADConv::TriggerSrc) REG_(adcsrb).adts;
}
/**
 * @brief Set the ADC Auto Triggering source
 * @param[in] val ADC Auto Triggering source.
 */
inline void ADConv::setTriggerSource(TriggerSrc val)
{
    REG_(adcsrb).adts = (unsigned char) val;
}
#endif

#if defined(VE_ATmega32)
inline ADConv::TriggerSrc ADConv::triggerSource() const
{
    return (ADConv::TriggerSrc) REG_(sfior).adts;
}
inline void ADConv::setTriggerSource(TriggerSrc val)
{
    REG_(sfior).adts = (unsigned char) val;
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
/**
 * @brief Return true, if High-Speed mode is enabled
 * @return True, if High-Speed mode is enabled.
 *
 * Only for ATmega32U4.
 */
inline bool ADConv::isHighSpeedModeEnabled() const
{
	return REG_(adcsrb).adhsm;
}
/**
 * @brief Enable High-Speed mode
 *
 * Only for ATmega32U4.
 */
inline void ADConv::enableHighSpeedMode()
{
	REG_(adcsrb).adhsm = true;
}
/**
 * @brief Enable High-Speed mode
 *
 * Only for ATmega32U4.
 */
inline void ADConv::disableHighSpeedMode()
{
	REG_(adcsrb).adhsm = false;
}
/**
 * @brief Set High Speed Mode Enable state
 * @param[in] val New state value
 */
inline void ADConv::setHighSpeedModeEnable(bool val)
{
	REG_(adcsrb).adhsm = val;
}
#endif

#endif /* ADC_H_ */
