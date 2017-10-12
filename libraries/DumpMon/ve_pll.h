/**
 * @file ve_pll.h
 * @brief PLL Control Header
 * @author andrey
 * @date 30.11.2012
 * @copyright GNU Public License
 */
#ifndef PLL_H_
#define PLL_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
/// @cond
typedef struct {
	unsigned char reserved[8];
} PLL_reserved;
///@endcond
#define PLL_PARENT		AVR_PLL, private PLL_reserved, public AVR_PLLFREQ	///< PLL parent type
#endif

/**
 * @brief PLL Control class
 * @ingroup Clock
 */
class PLL: public PLL_PARENT
{
public:
	/**
	 * @brief Divider type
	 */
	typedef enum {
		DIV1 = 0,			///< /1
		DIV2				///< /2
	} Divider;
	/**
	 * @brief Clock Source type
	 */
	typedef enum {
		SystemClock = 0,	///< System Clock
		Internal			///< Internal Calibrated RC Oscillator
	} ClkSrc;
	/**
	 * @brief Multiplier type
	 */
	typedef enum {
		Disconnected = 0,	///< Disconnected
		x1,					///< 1x
		x1_5,				///< 1.5x
		x2					///< 2x
	} HSTimMult;
	/**
	 * @brief Output Frequency type
	 */
	typedef enum {
		Freq_40MHz = 3,		///< 40 MHz
		Freq_48MHz,			///< 48 Mhz
		Freq_56MHz,			///< 56 MHz
		Freq_72MHz = 7,		///< 72 MHz
		Freq_80MHz,			///< 80 MHz
		Freq_88MHz,			///< 88 MHz
		Freq_96MHz			///< 96 MHz
	} OutFreq;
public:
	Divider inputPrescaler() const;
	void setInputPrescaler(Divider val);

	bool isEnabled() const;
	void enable();
	void disable();
	void setEnable(bool val);

	bool isLocked() const;

	ClkSrc clockSource() const;
	void setClockSource(ClkSrc val);

	Divider usbPostscaler() const;
	void setUsbPostscaler(Divider val);

	HSTimMult hsTimerPostcaler() const;
	void setHsTimerPostscaler(HSTimMult val);

	OutFreq lockFrequency() const;
	void setLockFrequency(OutFreq val);
};

/**
 * @brief Return Input Prescaler value
 * @return Input Prescaler value
 */
inline PLL::Divider PLL::inputPrescaler() const
{
	return (Divider) REG_(pllcsr).pindiv;
}
/**
 * @brief Set Input Prescaler value
 * @param[in] val New Input Prescaler value
 */
inline void PLL::setInputPrescaler(Divider val)
{
	REG_(pllcsr).pindiv = val;
}
/**
 * @brief Return true, if the PLL is enabled
 * @return True, if the PLL is enabled
 */
inline bool PLL::isEnabled() const
{
	return REG_(pllcsr).plle;
}
/**
 * @brief Enable the PLL
 *
 * Note that the Calibrated 8 MHz Internal RC oscillator is
 * automatically enabled when the PLLE bit is set and with
 * PINMUX (see PLLFRQ register) is set.
 *
 * The PLL must be disabled before entering Power down mode
 * in order to stop Internal RC Oscillator and avoid
 * extra-consumption.
 */
inline void PLL::enable()
{
	REG_(pllcsr).plle = true;
}
/**
 * @brief Disable the PLL
 */
inline void PLL::disable()
{
	REG_(pllcsr).plle = false;
}
/**
 * @brief Set PLL Enable state
 * @param[in] val New state value
 */
inline void PLL::setEnable(bool val)
{
	REG_(pllcsr).plle = val;
}
/**
 * @brief Return true, if the PLL is locked
 * @return True, if the PLL is locked
 *
 * After the PLL is enabled, it takes about several ms
 * for the PLL to lock. To clear PLOCK, clear PLLE.
 */
inline bool PLL::isLocked() const
{
	return REG_(pllcsr).plock;
}
/**
 * @brief Return Clock Source value
 * @return Clock Source value
 */
inline PLL::ClkSrc PLL::clockSource() const
{
	return (ClkSrc) REG_(pllfrq).pinmux;
}
/**
 * @brief Set Clock Source value
 * @param[in] val New Clock Source value
 */
inline void PLL::setClockSource(ClkSrc val)
{
	REG_(pllfrq).pinmux = val;
}
/**
 * @brief Return USB Postscaler value
 * @return USB Postscaler value
 */
inline PLL::Divider PLL::usbPostscaler() const
{
	return (Divider) REG_(pllfrq).pllusb;
}
/**
 * @brief Set USB Postscaler value
 * @param[in] val New USB Postscaler value
 */
inline void PLL::setUsbPostscaler(Divider val)
{
	REG_(pllfrq).pllusb = val;
}
/**
 * @brief Return High Speed Timer Postscaler value
 * @return High Speed Timer Postscaler value
 */
inline PLL::HSTimMult PLL::hsTimerPostcaler() const
{
	return (HSTimMult) REG_(pllfrq).plltm;
}
/**
 * @brief Set High Speed Timer Postscaler value
 * @param[in] val New High Speed Timer Postscaler value
 */
inline void PLL::setHsTimerPostscaler(HSTimMult val)
{
	REG_(pllfrq).plltm = val;
}
/**
 * @brief Return Lock Frequency value
 * @return Lock Frequency value
 */
inline PLL::OutFreq PLL::lockFrequency() const
{
	return (OutFreq) REG_(pllfrq).pdiv;
}
/**
 * @brief Set Lock Frequency value
 * @param[in] val New Lock Frequency value
 */
inline void PLL::setLockFrequency(OutFreq val)
{
	REG_(pllfrq).pdiv = val;
}

#endif /* PLL_H_ */
