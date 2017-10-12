/**
 * @file ve_gpio.h
 * @brief General Purpose I/O Header
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef GPIO_H_
#define GPIO_H_

/**
 * @brief General Purpose I/O class
 * @ingroup VE_AVR
 */
class GPIO: public AVR_GPIO
{
public:
	/**
	 * @brief Pin I/O Mode type
	 */
	typedef enum {
		MODE_INPUT = 0,		///< Input Mode
		MODE_OUTPUT			///< Output Mode
	} PinMode;
	/**
	 * @brief Mode structure
	 */
	typedef struct _ModeBits
	{
	public:
		PinMode pin0 : 1;		///< Pin 0 Mode
		PinMode pin1 : 1;		///< Pin 1 Mode
		PinMode pin2 : 1;		///< Pin 2 Mode
		PinMode pin3 : 1;		///< Pin 3 Mode
		PinMode pin4 : 1;		///< Pin 4 Mode
		PinMode pin5 : 1;		///< Pin 5 Mode
		PinMode pin6 : 1;		///< Pin 6 Mode
		PinMode pin7 : 1;		///< Pin 7 Mode
		_ModeBits(uint8_t ch);
		operator uint8_t () const;
	} ModeBits;
	/**
	 * @brief Pullup State type
	 */
	typedef enum {
		Pullup_OFF = 0,		///< Pullup is off
		Pullup_ON			///< Pullup is on
	} PullupState;
	/**
	 * @brief Pullup State structure
	 */
	typedef struct _PullupBits {
	public:
		PullupState pin0 : 1;	///< Pin 0 Pullup State
		PullupState pin1 : 1;	///< Pin 1 Pullup State
		PullupState pin2 : 1;	///< Pin 2 Pullup State
		PullupState pin3 : 1;	///< Pin 3 Pullup State
		PullupState pin4 : 1;	///< Pin 4 Pullup State
		PullupState pin5 : 1;	///< Pin 5 Pullup State
		PullupState pin6 : 1;	///< Pin 6 Pullup State
		PullupState pin7 : 1;	///< Pin 7 Pullup State
		_PullupBits(uint8_t ch);
		operator uint8_t () const;
	} PullupBits;
    void setModeInput(uint8_t _pin);
    void setModeInput();
    void setModeOutput(uint8_t _pin);
    void setModeOutput();
    PinMode mode(uint8_t _pin) const;
    void setMode(uint8_t _pin, PinMode mode);
    ModeBits mode() const;
    void setMode(const ModeBits& mode);

    void pullupOn(uint8_t _pin);
    void pullupOn();
    void pullupOff(uint8_t _pin);
    void pullupOff();
    PullupState pullup(uint8_t _pin);
    void setPullup(uint8_t _pin, PullupState val);
    PullupBits pullup();
    void setPullup(PullupBits val);

    void setHigh(uint8_t _pin);
    void setLow(uint8_t _pin);
    bool isLow(uint8_t _pin) const;
    bool isHigh(uint8_t _pin) const;
    void setState(uint8_t _pin, bool val);

    GPIO& operator <<(uint8_t _data);
    GPIO& operator =(uint8_t _data);

    unsigned char read() const;
};

/**
 * @brief Copy constructor
 * @param[in] ch Unsigned character value
 */
inline GPIO::_ModeBits::_ModeBits(uint8_t ch)
{
	*((uint8_t*) this) = ch;
}
/**
 * @brief Return Mode Bits structure as unsigned character value
 * @return Unsigned character value
 */
inline GPIO::_ModeBits::operator uint8_t () const
{
	return *((const uint8_t*) this);
}
/**
 * @brief Copy constructor
 * @param[in] ch Unsigned character value
 */
inline GPIO::_PullupBits::_PullupBits(uint8_t ch)
{
	*((uint8_t*) this) = ch;
}
/**
 * @brief Return Pullup Bits structure as unsigned character value
 * @return Unsigned character value
 */
inline GPIO::_PullupBits::operator uint8_t () const
{
	return *((const uint8_t*) this);
}
/**
 * @brief Set Input Mode for pin
 * @param[in] _pin Pin number
 */
inline void GPIO::setModeInput(uint8_t _pin)
{
    REG(ddr).reset(_pin);
}
/**
 * @brief Set Input Mode for all port pins
 */
inline void GPIO::setModeInput()
{
    REG(ddr) = 0;
}
/**
 * @brief Set Output Mode for pin
 * @param[in] _pin Pin number
 */
inline void GPIO::setModeOutput(uint8_t _pin)
{
    REG(ddr).set(_pin);
}
/**
 * @brief Set Output Mode for all port pins
 */
inline void GPIO::setModeOutput()
{
    REG(ddr) = 0xFF;
}
/**
 * @brief Return Mode value for pin
 * @param[in] _pin Pin number
 * @return Mode value for pin
 */
inline GPIO::PinMode GPIO::mode(uint8_t _pin) const
{
	return (PinMode) REG(ddr).isSet(_pin);
}
/**
 * @brief Set Mode value for pin
 * @param[in] _pin Pin number
 * @param[in] mode New Mode value
 */
inline void GPIO::setMode(uint8_t _pin, PinMode mode)
{
	REG(ddr).setState(_pin, (bool) mode);
}
/**
 * @brief Return Mode bit structure for the port
 * @return Mode bit structure for the port
 */
inline GPIO::ModeBits GPIO::mode() const
{
	return (ModeBits) REG(ddr);
}
/**
 * @brief Set Mode bits for the port
 * @param[in] mode New Mode bit values
 */
inline void GPIO::setMode(const ModeBits& mode)
{
	REG(ddr) = (uint8_t) mode;
}
/**
 * @brief Switch on Internal Pullup Resistor for input pin
 * @param[in] _pin Pin number
 */
inline void GPIO::pullupOn(uint8_t _pin)
{
    setHigh(_pin);
}
/**
 * @brief Switch on Internal Pullup Resistors for input port
 */
inline void GPIO::pullupOn()
{
    REG(port) = 0xFF;
}
/**
 * @brief Switch off Internal Pullup Resistor for input pin
 * @param[in] _pin Pin number
 */
inline void GPIO::pullupOff(uint8_t _pin)
{
    setLow(_pin);
}
/**
 * @brief Switch off Internal Pullup Resistors for input port
 */
inline void GPIO::pullupOff()
{
    REG(port) = 0;
}
/**
 * @brief Return Pullup State for input pin
 * @param[in] _pin Pin number
 * @return Pullup State for the pin
 */
inline GPIO::PullupState GPIO::pullup(uint8_t _pin)
{
	return (PullupState) REG(port).isSet(_pin);
}
/**
 * @brief Set Pullup State for input pin
 * @param[in] _pin Pin number
 * @param[in] val New state value
 */
inline void GPIO::setPullup(uint8_t _pin, PullupState val)
{
	REG(port).setState(_pin, (bool) val);
}
/**
 * @brief Return Pullup bits for the input port
 * @return Pullup bits for the port
 */
inline GPIO::PullupBits GPIO::pullup()
{
	return (PullupBits) REG(port);
}
/**
 * @brief Set Pullup bits for the input port
 * @param[in] val New state value
 */
inline void GPIO::setPullup(PullupBits val)
{
	REG(port) = (uint8_t) val;
}
/**
 * @brief Set High Level on output pin
 * @param[in] _pin Pin number
 */
inline void GPIO::setHigh(uint8_t _pin)
{
    REG(port).set(_pin);
}
/**
 * @brief Set Low Level on output pin
 * @param[in] _pin Pin number
 */
inline void GPIO::setLow(uint8_t _pin)
{
    REG(port).reset(_pin);
}
/**
 * @brief Return true, if Low Level is set on input pin
 * @return True, if Low Level is set on input pin
 */
inline bool GPIO::isLow(uint8_t _pin) const
{
    return !isHigh(_pin);
}
/**
 * @brief Return true, if High Level is set on input pin
 * @return True, if High Level is set on input pin
 */
inline bool GPIO::isHigh(uint8_t _pin) const
{
    return REG(pin).isSet(_pin);
}
/**
 * @brief Set level on output pin
 * @param[in] _pin Pin number
 * @param[in] val New level value
 */
inline void GPIO::setState(uint8_t _pin, bool val)
{
    REG(port).setState(_pin, val);
}
/**
 * @brief Write value to the output port
 * @param _data Value to write
 * @return Reference to the GPIO
 */
inline GPIO& GPIO::operator <<(uint8_t _data)
{
    REG(port) = _data;
    return (*this);
}
/**
 * @brief Write value to the output port
 * @param _data Value to write
 * @return Reference to the GPIO
 */
inline GPIO& GPIO::operator =(uint8_t _data)
{
    REG(port) = _data;
    return (*this);
}
/**
 * @brief Read state from the input port
 * @return State from the input port
 */
inline unsigned char GPIO::read() const
{
    return REG(pin);
}

/**
 * @addtogroup GPIOfunc
 * @{
 */

/**
 * @brief General Purpose I/O set method macro
 */
#define DECLARE_GPIO_MTHD_VOID(_funcName) \
	inline void _funcName(GPIO& gpio, uint8_t pin) \
	{ \
		gpio._funcName(pin); \
	}
/**
 * @brief General Purpose I/O get method macro
 */
#define DECLARE_GPIO_MTHD(_result, _funcName) \
	inline _result _funcName(GPIO& gpio, uint8_t pin) \
	{ \
		return gpio._funcName(pin); \
	} \

/**
 * @fn inline void setModeOutput(GPIO& gpio, uint8_t pin)
 * @brief Set Output Mode for pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(setModeOutput)
/**
 * @fn inline void setModeInput(GPIO& gpio, uint8_t pin)
 * @brief Set Input Mode for pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(setModeInput)
/**
 * @fn inline void setHigh(GPIO& gpio, uint8_t pin)
 * @brief Set High Level on output pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(setHigh)
/**
 * @fn inline void setLow(GPIO& gpio, uint8_t pin)
 * @brief Set Low Level on output pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(setLow)
/**
 * @fn inline void pullupOn(GPIO& gpio, uint8_t pin)
 * @brief Switch on Internal Pullup Resistor for input pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(pullupOn)
/**
 * @fn inline void pullupOff(GPIO& gpio, uint8_t pin)
 * @brief Switch off Internal Pullup Resistor for input pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 */
DECLARE_GPIO_MTHD_VOID(pullupOff)
/**
 * @fn inline bool isLow(GPIO& gpio, uint8_t pin)
 * @brief Return true, if Low Level is set on input pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 * @return True, if Low Level is set on input pin
 */
DECLARE_GPIO_MTHD(bool, isLow)
/**
 * @fn inline bool isHigh(GPIO& gpio, uint8_t pin)
 * @brief Return true, if High Level is set on input pin
 * @param[in] gpio Reference to GPIO
 * @param[in] pin Pin number
 * @return True, if High Level is set on input pin
 */
DECLARE_GPIO_MTHD(bool, isHigh)
/**
 * @}
 */
#endif /* GPIO_H_ */
