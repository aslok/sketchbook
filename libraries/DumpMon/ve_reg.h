/**
 * @file ve_reg.h
 * @brief AVR8 Register Header
 * @author andrey
 * @date 23.01.2012
 * @copyright GNU Public License
 */
#ifndef REG_H_
#define REG_H_

/**
 * @addtogroup Register
 * @{
 */

/**
 * @brief Reference to an 8-bit Register object
 * @param[in] _avr_reg Register name in the Register structure
 *
 * Example:
 * @code
 * inline void GPIO::setModeInput(uint8_t _pin)
 * {
 *     REG(ddr).reset(_pin);
 * }
 * inline void GPIO::setModeInput()
 * {
 *     REG(ddr) = 0;
 * }
 * @endcode
 * These are equivalent to the following code:
 * @code
 * inline void GPIO::setModeInput(uint8_t _pin)
 * {
 *     ((AVR_GPIO*) this)->ddr.reset(_pin);      // REG(ddr).reset(_pin);
 * }
 * inline void GPIO::setModeInput()
 * {
 *     ((AVR_GPIO*) this)->ddr.operator = (0);   // REG(ddr) = 0;
 * }
 * @endcode
 * @sa REGW(), REG_()
 */
#define REG(_avr_reg)   (*((Reg*) &(_avr_reg)))
/**
 * @brief Reference to an 16-bit Register object
 * @param[in] _avr_reg Register name in the Register structure
 *
 * Example:
 * @code
 * // Return ADC Conversion Result
 * inline uint16_t ADConv::result() const
 * {
 *     return REGW(adc);
 * }
 * @endcode
 * This is equivalent to the following code:
 * @code
 * inline uint16_t ADConv::result() const
 * {
 *     return ((AVR_AMUX*) this)->adc.operator uint16_t ();   // return REGW(adc);
 * }
 * @endcode
 * @sa REG()
 */
#define REGW(_avr_reg)  (*((RegW*) &(_avr_reg)))
/**
 * @brief Reference to the Register Bits structure
 * @param[in] _avr_reg Register name in the Register structure
 *
 * Example:
 * @code
 * // Enable the ADC
 * inline void ADConv::enable()
 * {
 *     REG_(adcsra).aden = true;
 * }
 * @endcode
 * This is equivalent to the following code:
 * @code
 * inline void ADConv::enable()
 * {
 *     ((AVR_AMUX*) this)->adcsra.aden = true;    // REG_(adcsra).aden = true;
 * }
 * @endcode
 * Please note that this macro is not containing @b this pointer. For version with
 * @b this pointer see TREG_().
 * @sa REG(), REGW(), TREG_()
 */
#define REG_(_avr_reg)  (_avr_reg.m_reg)			///<
/**
 * @brief Reference to object's Register Bits structure
 * @param[in] _avr_reg Register name in the Register structure
 *
 * Sometimes @b this pointer must be specified. This macro is the version of REG_()
 * macro with @b this pointer.
 * @sa REG_()
 */
#define TREG_(_avr_reg)  (this->_avr_reg.m_reg)

/**
 * @brief Register declaration macro
 * @param[in] reg Register name
 *
 * Example:
 * @code
 * DECLARE_REGT(TIFR);
 * @endcode
 * This declaration generates following code:
 * @code
 * typedef _AVR_REG_T<AVR_TIFR>   TIFR_REG;    // Register structure type
 * typedef TIFR_REG*              PTIFR_REG;   // Pointer to Register structure type
 * typedef RegT<AVR_TIFR>         RegTIFR;     // Register class
 * @endcode
 */
#define DECLARE_REGT(reg) \
    typedef _AVR_REG_T<AVR_##reg> reg##_REG; \
    typedef reg##_REG* P##reg##_REG; \
    typedef RegT<AVR_##reg> Reg##reg

/**
 * @brief Register structure template
 */
template<typename _T>
struct _AVR_REG_T
{
    volatile _T m_reg;			///< Register
};

/**
 * @brief Register class template
 */
template<typename _T>
class RegT: public _AVR_REG_T<_T>
{
public:
	/**
	 * @brief Write value to the register
	 * @param[in] val Value
	 * @return Reference to the register
	 */
    RegT& operator =(_T val)
    {
        this->m_reg = val;
        return (*this);
    }
    /**
     * @brief Read value from the register
     * @return Register value
     */
    operator _T()
    {
        return this->m_reg;
    }
    /**
     * @brief Set register bit
     * @param[in] bit Bit number
	 * @return Reference to the register
     */
    RegT& set(uint8_t bit)
    {
        this->m_reg |= _BV(bit);
        return (*this);
    }
    /**
     * @brief Clear register bit
     * @param[in] bit Bit number
	 * @return Reference to the register
     */
    RegT& reset(uint8_t bit)
    {
        this->m_reg &= ~_BV(bit);
        return (*this);
    }
    /**
     * @brief Return true, if the bit is set
     * @param[in] bit bit number
     * @return True, if the bit is set
     */
    bool isSet(_T bit)
    {
        return (this->m_reg & _BV(bit));
    }
    /**
     * @brief Set bit state
     * @param[in] bit Bit number
     * @param[in] val New bit state
	 * @return Reference to the register
     */
    RegT& setState(uint8_t bit, bool val)
    {
    	this->m_reg = (this->m_reg & ~_BV(bit)) | (val ? _BV(bit) : 0);
    	return (*this);
    }
    /**
     * @brief Set masked register bits
     * @param[in] val Bit mask
	 * @return Reference to the register
     */
    RegT& operator |=(_T val)
    {
        this->m_reg |= val;
        return (*this);
    }
    /**
     * @brief Reset unmasked register bits
     * @param[in] val Bit mask
	 * @return Reference to the register
     */
    RegT& operator &=(_T val)
    {
        this->m_reg &= val;
        return (*this);
    }
};

typedef _AVR_REG_T<uint8_t> AVR_REG;		///< 8-bit Register structure type
typedef AVR_REG* AVRP_REG;					///< Pointer to 8-bit Register structure type
typedef RegT<uint8_t> Reg;					///< 8-bit Register class

typedef _AVR_REG_T<uint16_t> AVR_REGW;		///< 16-bit Register structure type
typedef AVR_REG* AVRP_REGW;					///< Pointer to 16-bit Register structure type
typedef RegT<uint16_t> RegW;				///< 16-bit Register class
/**
 * @}
 */
#endif /* REG_H_ */
