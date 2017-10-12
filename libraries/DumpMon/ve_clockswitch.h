/**
 * @file ve_clockswitch.h
 * @brief Clock Switch Header
 * @author andrey
 * @date 07.12.2012
 * @copyright GNU Public License
 */
#ifndef CLOCKSWITCH_H_
#define CLOCKSWITCH_H_

/**
 * @brief Clock Switch class
 * @ingroup Clock
 */
class ClockSwitch : public AVR_CLKSEL
{
public:
	/**
	 * @brief Start-up Time type
	 */
	typedef enum {
		BOD_enabled     = 0,			///< Brown-Out Detector is enabled
		FastRisingPower = 1,			///< Fast Rising Power
		SlowRisingPower = 2				///< Slow Rising Power
	} StartupTime;
	/**
	 * @brief CPU Clock type
	 */
	typedef enum {
		RC  = 0,						///< Internal Calibrated RC Oscillator
		Ext = 1							///< External oscillator
	} CPUClock;
	/**
	 * @brief Clock Options type
	 */
	typedef enum {
		External     = 0,				///< External oscillator
		InternalRC   = 2,				///< Internal Calibrated RC Oscillator
		LowFreq      = 4,				///< Low Frequency oscillator
		LowPower     = 8,				///< Low Power oscillator
	} ClockOptions;
	/**
	 * @brief Frequency Range type
	 */
	typedef enum {
		LowRange  = 0,					///< Lower Frequncy Range
		HighRange = 1					///< Higher Frequency Range
	} FreqRange;
	/**
	 * @brief Wakeup Delay type
	 */
	typedef enum {
		LowPower_258 = 0,				///< Low Power Oscillator, 258 CK
		LowPower_1K  = 3,				///< Low Power Oscillator, 1K CK
		LowPower_16K = 6,				///< Low Power Oscillator, 16K CK
		LowFreq_1K   = 0,				///< Low Frequency Oscillator, 1K
		LowFreq_32K  = 4				///< Low Frequency Oscillator, 32K
	} WakeupDelay;
public:
	StartupTime rcStartupTime() const;
	void setRCStartupTime(StartupTime val);

	StartupTime extStartupTime() const;

	bool isRCEnabled() const;
	void enableRC();
	void disableRC();
	void setRCEnable(bool val);

	bool isExtEnabled() const;
	void enableExt();
	void disableExt();
	void setExtEnable(bool val);

	CPUClock cpuClock() const;
	void setCPUClock(CPUClock val);

	ClockOptions rcOptions() const;
	ClockOptions extOptions() const;
	void setExtOptions(ClockOptions ckopt, FreqRange range, StartupTime sut, WakeupDelay wkDelay);

	bool isRCOn() const;
	bool isExtOn() const;

	void switchExtToRC();
	void switchRCToExt();
protected:
	uint8_t rcSelect() const;
	void setRcSelect(uint8_t val);

	uint8_t extSelect() const;
	void setExtSelect(uint8_t val);

	bool isLowPower() const;
	bool isLowFreq() const;
};
/**
 * @brief Return RC Oscillator Startup Time type value
 * @return RC Oscillator Startup Time type value
 */
inline ClockSwitch::StartupTime ClockSwitch::rcStartupTime() const
{
	return (StartupTime) REG_(clksel0).rcsut;
}
/**
 * @brief Set RC Oscillator Startup Time type value
 * @param[in] val RC Oscillator Startup Time type value
 */
inline void ClockSwitch::setRCStartupTime(StartupTime val)
{
	REG_(clksel0).rcsut = val;
}
/**
 * @brief Return External Oscillator Startup Time type value
 * @return External Oscillator Startup Time type value
 */
inline ClockSwitch::StartupTime ClockSwitch::extStartupTime() const
{
	if (isLowPower()) {
		uint8_t cs = ((extSelect() & 1) << 2) | REG_(clksel0).exsut;
		cs += 1;
		cs = cs % 3;
		return (StartupTime) cs;
	}
	else
		return (StartupTime) REG_(clksel0).exsut;
}
/**
 * @brief Set External Oscillator Options
 * @param[in] ckopt Clock Options value
 * @param[in] range Frequency Range value
 * @param[in] sut Startup Time value
 * @param[in] wkDelay Wakeup Delay Time value
 */
inline void ClockSwitch::setExtOptions(ClockOptions ckopt, FreqRange range, StartupTime sut, WakeupDelay wkDelay)
{
	uint8_t cs = (uint8_t) sut + (uint8_t) wkDelay;
	if (isLowPower()) {
		if (cs)
			cs -= 1;
		REG_(clksel0).exsut = cs;
	}
	else
		REG_(clksel0).exsut = cs;
	if (ckopt == LowPower || ckopt == LowFreq)
		REG_(clksel1).excksel = (uint8_t) ckopt | ((uint8_t) range << 1) | ((cs & 4) >> 2);
	else
		REG_(clksel1).excksel = (uint8_t) ckopt;
}
/**
 * @brief Return true, if RC Oscillator is enabled
 * @return True, if RC Oscillator is enabled
 */
inline bool ClockSwitch::isRCEnabled() const
{
	return REG_(clksel0).rce;
}
/**
 * @brief Enable RC Oscillator
 */
inline void ClockSwitch::enableRC()
{
	REG_(clksel0).rce = true;
}
/**
 * @brief Disable RC Oscillator
 */
inline void ClockSwitch::disableRC()
{
	REG_(clksel0).rce = false;
}
/**
 * @brief Set RC Oscillator Enable state
 * @param[in] val New RC Oscillator Enable state
 */
inline void ClockSwitch::setRCEnable(bool val)
{
	REG_(clksel0).rce = val;
}
/**
 * @brief Return true, if External Oscillator is enabled
 * @return True, if External Oscillator is enabled
 */
inline bool ClockSwitch::isExtEnabled() const
{
	return REG_(clksel0).exte;
}
/**
 * @brief Enable External Oscillator
 */
inline void ClockSwitch::enableExt()
{
	REG_(clksel0).exte = true;
}
/**
 * @brief Disable External Oscillator
 */
inline void ClockSwitch::disableExt()
{
	REG_(clksel0).exte = false;
}
/**
 * @brief Set External Oscillator Enable state
 * @param[in] val New External Oscillator Enable state
 */
inline void ClockSwitch::setExtEnable(bool val)
{
	REG_(clksel0).exte = val;
}
/**
 * @brief Return CPU Clock Select
 * @return CPU Clock Select
 */
inline ClockSwitch::CPUClock ClockSwitch::cpuClock() const
{
	return (CPUClock) REG_(clksel0).clks;
}
/**
 * @brief Set CPU Clock Select value
 * @param[in] val New CPU Clock Select value
 */
inline void ClockSwitch::setCPUClock(CPUClock val)
{
	REG_(clksel0).clks = val;
}
/**
 * @brief Return RC Oscillator Options value
 * @return RC Oscillator Options value
 */
inline ClockSwitch::ClockOptions ClockSwitch::rcOptions() const
{
	return (ClockOptions) REG_(clksel1).rccksel;
}
/**
 * @brief Return External Oscillator Options value
 * @return External Oscillator Options value
 */
inline ClockSwitch::ClockOptions ClockSwitch::extOptions() const
{
	return (ClockOptions) REG_(clksel1).excksel;
}
/**
 * @brief Return true, if RC Oscillator is on
 * @return True, if RC Oscillator is on
 */
inline bool ClockSwitch::isRCOn() const
{
	return REG_(clksta).rcon;
}
/**
 * @brief Return true, if External Oscillator is on
 * @return True, if External Oscillator is on
 */
inline bool ClockSwitch::isExtOn() const
{
	return REG_(clksta).exton;
}
/**
 * @brief Return RC Oscillator Select value
 * @return RC Oscillator Select value
 */
inline uint8_t ClockSwitch::rcSelect() const
{
	return REG_(clksel1).rccksel;
}
/**
 * @brief Set RC Oscillator Select value
 * @param[in] val New RC Oscillator Select value
 */
inline void ClockSwitch::setRcSelect(uint8_t val)
{
	REG_(clksel1).rccksel = val;
}
/**
 * @brief Return External Oscillator Select value
 * @return External Oscillator Select value
 */
inline uint8_t ClockSwitch::extSelect() const
{
	return REG_(clksel1).excksel;
}
/**
 * @brief Set External Oscillator Select value
 * @param[in] val New External Oscillator Select value
 */
inline void ClockSwitch::setExtSelect(uint8_t val)
{
	REG_(clksel1).excksel = val;
}
/**
 * @brief Return true, if External Oscillator is Low Power Oscillator
 * @return True, if External Oscillator is Low Power Oscillator
 */
inline bool ClockSwitch::isLowPower() const
{
	return (bool) ((uint8_t) REG_(clksel1).excksel & 8);
}
/**
 * @brief Return true, if External Oscillator is Low Frequency Oscillator
 * @return True, if External Oscillator is Low Frequency Oscillator
 */
inline bool ClockSwitch::isLowFreq() const
{
	return !isLowPower() && ((uint8_t) REG_(clksel1).excksel & 4);
}
/**
 * @brief Switch from External Oscillator to RC Oscillator
 */
inline void ClockSwitch::switchExtToRC()
{
	if (DEV_USBDEV.suspendInt())	// if (UDINT.SUSPI == 1)
	{
		DEV_USBDEV.clearSuspendInt();	// UDINT.SUSPI = 0;
		DEV_USBGEN.disableClock(); 		// USBCON.FRZCLK = 1;
		DEV_PLL.disable();				// PLLCSR.PLLE = 0;
		enableRC(); 					// CLKSEL0.RCE = 1;
		while (!isRCOn());				// while (CLKSTA.RCON != 1);
		setCPUClock(RC); 				// CLKSEL0.CLKS = 0;
		disableExt(); 					// CLKSEL0.EXTE = 0;
	}
}
/**
 * @brief Switch from RC Oscillator to External Oscillator
 */
inline void ClockSwitch::switchRCToExt()
{
	if (DEV_USBDEV.wakeupCPUInt())	// if (UDINT.WAKEUPI == 1)
	{
		DEV_USBDEV.clearWakeupCPUInt();	// UDINT.WAKEUPI = 0;
		enableExt(); 					// CKSEL0.EXTE = 1;
		while (!isExtOn()); 			// while (CLKSTA.EXTON != 1);
		setCPUClock(Ext);				// CLKSEL0.CLKS = 1;
		DEV_PLL.enable();				// PLLCSR.PLLE = 1;
		disableRC(); 					// CLKSEL0.RCE = 0;
		while (!DEV_PLL.isLocked());	// while (PLLCSR.PLOCK != 1);
		DEV_USBGEN.enableClock();		// USBCON.FRZCLK = 0;
	}
}

#endif /* CLOCKSWITCH_H_ */
