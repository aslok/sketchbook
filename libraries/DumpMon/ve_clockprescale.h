/**
 * @file ve_clockprescale.h
 * @brief System Clock Prescaler Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef CLOCKPRESCALE_H_
#define CLOCKPRESCALE_H_

/**
 * @brief System Clock Prescaler class
 * @ingroup Clock
 */
class ClockPrescale : public AVR_CLKPR
{
public:
	/**
	 * @brief Factor type
	 */
	typedef enum {
		DIV_1 = 0,		///< /1
		DIV_2,			///< /2
		DIV_4,			///< /4
		DIV_8,			///< /8
		DIV_16,			///< /16
		DIV_32,			///< /32
		DIV_64,			///< /64
		DIV_128,		///< /128
		DIV_256			///< /256
	} Factor;
public:
	Factor factor() const;
	void setFactor(Factor val);
protected:
	void enableChange();
};

/**
 * @brief Return Factor value
 * @return Factor value
 */
inline ClockPrescale::Factor ClockPrescale::factor() const
{
	return (Factor) REG_(clkpr);
}
/**
 * @brief Set Factor value
 * @param[in] val New Factor value
 */
inline void ClockPrescale::setFactor(Factor val)
{
	register unsigned char sreg = SREG;
	disableInterrupts();
	enableChange();
	REG_(clkpr) = val;
	SREG = sreg;
}
/**
 * @brief Enable change the value
 */
inline void ClockPrescale::enableChange()
{
	REG_(clkpr) = _BV(CLKPCE);
}

#endif /* CLOCKPRESCALE_H_ */
