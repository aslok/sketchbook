/**
 * @file ve_power.h
 * @brief Power Reduction Header
 * @author andrey
 * @date 12.05.2012
 * @copyright GNU Public License
 */
#ifndef POWER_H_
#define POWER_H_

/**
 * @brief Power Reduction class macro
 */
#define DECLARE_PWR(caps, small, reg, bit) \
	inline bool is##caps##On() const { \
		return !REG_(prr##reg).bit; \
	} \
	inline void small##On() { \
		REG_(prr##reg).bit = false; \
	} \
	inline void small##Off()	{ \
		REG_(prr##reg).bit = true; \
	} \
	inline void set##caps##On(bool val) { \
		REG_(prr##reg).bit = !val; \
	}

/**
 * @brief %Power Reduction class
 * @ingroup VE_AVR
 */
class Power : public AVR_POWER
{
public:
    /**
     * @fn bool isAdcOn() const
     * @brief Return true, if the ADC is on
     * @return True, if the ADC is on
     *
     * @fn void adcOn()
     * @brief Turn on the ADC
     *
     * @fn void adcOff()
     * @brief Turn off the ADC
     *
     * @fn void setAdcOn(bool val)
     * @brief Switch the ADC On state
     * @param[in] val New state value
     */
	bool isAdcOn() const;
    void adcOn();
    void adcOff();
    void setAdcOn(bool val);

    /**
     * @fn bool isSpiOn() const
     * @brief Return true, if the SPI is on
     * @return True, if the SPI is on
     *
     * @fn void spiOn()
     * @brief Turn on the SPI
     *
     * @fn void spiOff()
     * @brief Turn off the SPI
     *
     * @fn void setSpiOn(bool val)
     * @brief Switch the SPI On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Spi, spi, 0, prspi)
    /**
     * @fn bool isTimer1On() const
     * @brief Return true, if the Timer/Counter 1 is on
     * @return True, if the Timer/Counter 1 is on
     *
     * @fn void timer1On()
     * @brief Turn on the Timer/Counter 1
     *
     * @fn void timer1Off()
     * @brief Turn off the Timer/Counter 1
     *
     * @fn void setTimer1On(bool val)
     * @brief Switch the Timer/Counter 1 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer1, timer1, 0, prtim1)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
    defined(VE_ATmega2560) || \
    defined(VE_ATmega325) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
    /**
     * @fn bool isUsart0On() const
     * @brief Return true, if the USART 0 is on
     * @return True, if the USART 0 is on
     *
     * @fn void usart0On()
     * @brief Turn on the USART 0
     *
     * @fn void usart0Off()
     * @brief Turn off the USART 0
     *
     * @fn void setUsart0On(bool val)
     * @brief Switch the USART 0 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Usart0, usart0, 0, prusart0)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
    defined(VE_ATmega2560) || \
    defined(VE_ATmega32U4) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
    /**
     * @fn bool isTimer0On() const
     * @brief Return true, if the Timer/Counter 0 is on
     * @return True, if the Timer/Counter 0 is on
     *
     * @fn void timer0On()
     * @brief Turn on the Timer/Counter 0
     *
     * @fn void timer0Off()
     * @brief Turn off the Timer/Counter 0
     *
     * @fn void setTimer0On(bool val)
     * @brief Switch the Timer/Counter 0 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer0, timer0, 0, prtim0)
    /**
     * @fn bool isTwiOn() const
     * @brief Return true, if the TWI is on
     * @return True, if the TWI is on
     *
     * @fn void twiOn()
     * @brief Turn on the TWI
     *
     * @fn void twiOff()
     * @brief Turn off the TWI
     *
     * @fn void setTwiOn(bool val)
     * @brief Switch the TWI On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Twi, twi, 0, prtwi)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
    defined(VE_ATmega2560) || \
    defined(VE_ATmega32U4) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
    /**
     * @fn bool isTimer2On() const
     * @brief Return true, if the Timer/Counter 2 is on
     * @return True, if the Timer/Counter 2 is on
     *
     * @fn void timer2On()
     * @brief Turn on the Timer/Counter 2
     *
     * @fn void timer2Off()
     * @brief Turn off the Timer/Counter 2
     *
     * @fn void setTimer2On(bool val)
     * @brief Switch the Timer/Counter 2 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer2, timer2, 0, prtim2)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
    defined(VE_ATmega32U4)
    /**
     * @fn bool isUsart1On() const
     * @brief Return true, if the USART 1 is on
     * @return True, if the USART 1 is on
     *
     * @fn void usart1On()
     * @brief Turn on the USART 1
     *
     * @fn void usart1Off()
     * @brief Turn off the USART 1
     *
     * @fn void setUsart1On(bool val)
     * @brief Switch the USART 1 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Usart1, usart1, 1, prusart1)
#endif

#if defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    DECLARE_PWR(Usart1, usart1, 0, prusart1)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
    defined(VE_ATmega32U4) || \
    defined(VE_ATmega1284P)
    /**
     * @fn bool isTimer3On() const
     * @brief Return true, if the Timer/Counter 3 is on
     * @return True, if the Timer/Counter 3 is on
     *
     * @fn void timer3On()
     * @brief Turn on the Timer/Counter 3
     *
     * @fn void timer3Off()
     * @brief Turn off the Timer/Counter 3
     *
     * @fn void setTimer3On(bool val)
     * @brief Switch the Timer/Counter 3 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer3, timer3, 1, prtim3)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
    defined(VE_ATmega32U4)
    /**
     * @fn bool isTimer4On() const
     * @brief Return true, if the Timer/Counter 4 is on
     * @return True, if the Timer/Counter 4 is on
     *
     * @fn void timer4On()
     * @brief Turn on the Timer/Counter 4
     *
     * @fn void timer4Off()
     * @brief Turn off the Timer/Counter 4
     *
     * @fn void setTimer4On(bool val)
     * @brief Switch the Timer/Counter 4 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer4, timer4, 1, prtim4)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560)
    /**
     * @fn bool isTimer5On() const
     * @brief Return true, if the Timer/Counter 5 is on
     * @return True, if the Timer/Counter 5 is on
     *
     * @fn void timer5On()
     * @brief Turn on the Timer/Counter 5
     *
     * @fn void timer5Off()
     * @brief Turn off the Timer/Counter 5
     *
     * @fn void setTimer5On(bool val)
     * @brief Switch the Timer/Counter 5 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Timer5, timer5, 1, prtim5)
    /**
     * @fn bool isUsart2On() const
     * @brief Return true, if the USART 2 is on
     * @return True, if the USART 2 is on
     *
     * @fn void usart2On()
     * @brief Turn on the USART 2
     *
     * @fn void usart2Off()
     * @brief Turn off the USART 2
     *
     * @fn void setUsart2On(bool val)
     * @brief Switch the USART 2 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Usart2, usart2, 1, prusart2)
    /**
     * @fn bool isUsart3On() const
     * @brief Return true, if the USART 3 is on
     * @return True, if the USART 3 is on
     *
     * @fn void usart3On()
     * @brief Turn on the USART 3
     *
     * @fn void usart3Off()
     * @brief Turn off the USART 3
     *
     * @fn void setUsart3On(bool val)
     * @brief Switch the USART 3 On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Usart3, usart3, 1, prusart3)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
    /**
     * @fn bool isUsbOn() const
     * @brief Return true, if the USB is on
     * @return True, if the USB is on
     *
     * @fn void usbOn()
     * @brief Turn on the USB
     *
     * @fn void usbOff()
     * @brief Turn off the USB
     *
     * @fn void setUsbOn(bool val)
     * @brief Switch the USB On state
     * @param[in] val New state value
     */
    DECLARE_PWR(Usb, usb, 1, prusb)
#endif
};

inline bool Power::isAdcOn() const
{
	return !REG_(prr0).pradc;
}
inline void Power::adcOn()
{
    DEV_ADC.disable();
    REG_(prr0).pradc = false;
}
inline void Power::adcOff()
{
	DEV_ADC.disable();
    REG_(prr0).pradc = true;
}
inline void Power::setAdcOn(bool val)
{
	DEV_ADC.disable();
    REG_(prr0).pradc = !val;
}

#endif /* POWER_H_ */
