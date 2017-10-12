/**
 * @file ve_sleepmodecontrol.h
 * @brief Sleep Mode Control Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef SLEEPMODECONTROL_H_
#define SLEEPMODECONTROL_H_

/**
 * @brief Sleep Mode Control class
 * @ingroup VE_AVR
 */
class SleepControl: public AVR_SLEEP
{
public:
	/**
	 * @brief Mode type
	 */
	typedef enum {
		IDLE = 0,			///< Idle
		ADC_NR = 1,			///< ADC Noise Reduction
		PWR_DOWN = 2,		///< Power Down
		PWR_SAVE = 3,		///< Power Save
		STANDBY = 6,		///< Standby
		EXT_STANDBY = 7		///< Extended Standby
	} Mode;
public:
	Mode mode() const;
	void setMode(Mode val);

	bool isSleepEnabled() const;
	void enableSleep();
	void disableSleep();
	void setSleepEnable(bool val);
};

/**
 * @brief Return Sleep Mode type
 * @return Sleep Mode type
 */
inline SleepControl::Mode SleepControl::mode() const
{
	return (Mode) REG_(smcr).sm;
}
/**
 * @brief Set Sleep Mode type
 * @param[in] val new Sleep Mode type
 *
 * Standby modes are only recommended for use with external crystals
 * or resonators.
 */
inline void SleepControl::setMode(Mode val)
{
	REG_(smcr).sm = val;
}
/**
 * @brief Return true, if Sleep Mode is enabled
 * @return True, if Sleep Mode is enabled
 */
inline bool SleepControl::isSleepEnabled() const
{
	return REG_(smcr).se;
}
/**
 * @brief Enable Sleep Mode
 */
inline void SleepControl::enableSleep()
{
	REG_(smcr).se = true;
}
/**
 * @brief Disable Sleep Mode
 */
inline void SleepControl::disableSleep()
{
	REG_(smcr).se = false;
}
/**
 * @brief Set Sleep Mode Enable state
 * @param[in] val New state value
 */
inline void SleepControl::setSleepEnable(bool val)
{
	REG_(smcr).se = val;
}
/**
 * @brief Sleep now
 */
inline void sleep()
{
	__asm__ __volatile__("sleep");
}

#endif /* SLEEPMODECONTROL_H_ */
