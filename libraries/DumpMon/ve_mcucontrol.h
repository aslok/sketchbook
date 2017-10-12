/**
 * @file ve_mcucontrol.h
 * @brief MCU COntrol Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef MCUCONTROL_H_
#define MCUCONTROL_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
#define MCUCONTROL_PARENT AVR_MCU		///< Parent class for MCUControl class
#endif

#if defined(VE_ATmega32)
typedef struct {
	unsigned char reserved[3];
} __MCUP0;
typedef struct {
	unsigned char reserved[4];
} __MCUP1;
#define MCUCONTROL_PARENT AVR_SFIORS, private __MCUP0, public AVR_MCU, private __MCUP1, public AVR_EXTINTFLAGS
#endif

/**
 * @brief MCU Control class
 * @ingroup VE_AVR
 */
class MCUControl : public MCUCONTROL_PARENT
{
public:
	bool isIntVectorsAtProgMem() const;
	void setIntVectorsToProgMem();
	void setIntVectorsToBootLoader();

	bool isPullUpsDisabled() const;
	void enablePullUps();
	void disablePullUps();
	void setPullupsDisable(bool val);

	bool isWatchdogResetOccurs() const;
	bool isBrownOutResetOccurs() const;
	bool isExternalResetOccurs() const;
	bool isPowerOnResetOccurs() const;
	void clearWatchdogReset();
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P)
	void bodOffSleep();
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	bool isJtagDisabled() const;
	void enableJtag();
	void disableJtag();
	void setJtagDisable(bool val);
#endif
};

/**
 * @brief Return true, if Watchdog Reset Flag is set
 * @return True, if Watchdog Reset Flag is set
 */
inline bool MCUControl::isWatchdogResetOccurs() const
{
	return REG_(mcusr).wdrf;
}
/**
 * @brief Return true, if Brown-Out Reset Flag is set
 * @return True, if Brown-Out Reset Flag is set
 */
inline bool MCUControl::isBrownOutResetOccurs() const
{
	return REG_(mcusr).borf;
}
/**
 * @brief Return true, if External Reset Flag is set
 * @return True, if External Reset Flag is set
 */
inline bool MCUControl::isExternalResetOccurs() const
{
	return REG_(mcusr).extrf;
}
/**
 * @brief Return true, if Power On Reset Flag is set
 * @return True, if Power On Reset Flag is set
 */
inline bool MCUControl::isPowerOnResetOccurs() const
{
	return REG_(mcusr).porf;
}
/**
 * @brief Clear Watchdog Reset Flag
 */
inline void MCUControl::clearWatchdogReset()
{
	REG_(mcusr).wdrf = false;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325)
/**
 * @brief Return true, if Interrupt Vectors table is at beginning of Program Memory
 * @return True, if Interrupt Vectors table is at beginning of Program Memory
 */
inline bool MCUControl::isIntVectorsAtProgMem() const
{
	return (REG_(mcucr).iv & 2);
}
/**
 * @brief Use Interrupt Vectors table at beginning of Program Memory
 */
inline void MCUControl::setIntVectorsToProgMem()
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG_(mcucr).iv = 1;
	REG_(mcucr).iv = 0;
	SREG = sreg;
}
/**
 * @brief Use Interrupt Vectors table at beginning of Boot Loader Section
 */
inline void MCUControl::setIntVectorsToBootLoader()
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG_(mcucr).iv = 1;
	REG_(mcucr).iv = 2;
	SREG = sreg;
}
/**
 * @brief Return true, if Internal Pullup Resistors are disabled
 * @return True, if Internal Pullup Resistors are disabled
 */
inline bool MCUControl::isPullUpsDisabled() const
{
	return REG_(mcucr).pud;
}
/**
 * @brief Enable Internal Pullup Resistors
 */
inline void MCUControl::enablePullUps()
{
	REG_(mcucr).pud = false;
}
/**
 * @brief Disable Internal Pullup Resistors
 */
inline void MCUControl::disablePullUps()
{
	REG_(mcucr).pud = true;
}
/**
 * @brief Set Internal Pullup Resistors Disable state
 * @param[in] val New satte value
 */
inline void MCUControl::setPullupsDisable(bool val)
{
	REG_(mcucr).pud = val;
}
#endif

#if defined(VE_ATmega32)
inline bool MCUControl::isIntVectorsAtProgMem() const
{
	return !REG_(gicr).ivsel;
}
inline void MCUControl::setIntVectorsToProgMem()
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG_(gicr).ivce = 1;
	REG_(gicr).ivsel = 0;
	SREG = sreg;
}
inline void MCUControl::setIntVectorsToBootLoader()
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG_(gicr).ivce = 1;
	REG_(gicr).ivsel = 2;
	SREG = sreg;
}
inline bool MCUControl::isPullUpsDisabled() const
{
	return REG_(sfior).pud;
}
inline void MCUControl::enablePullUps()
{
	REG_(sfior).pud = false;
}
inline void MCUControl::disablePullUps()
{
	REG_(sfior).pud = true;
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P)
/**
 * @brief Turn off Brown Out Detector during sleep and goto Sleep Mode
 *
 * Writing to the BODS bit is controlled by a timed sequence and an enable bit,
 * BODSE in MCUCR.
 *
 * The BODS bit is active three clock cycles after it is set. A sleep instruction
 * must be executed while BODS is active in order to turn off the BOD for the actual
 * sleep mode. The BODS bit is automatically cleared after three clock cycles.
 *
 * ATmega48PA/88PA/168PA/328P only.
 */
inline void MCUControl::bodOffSleep()
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG_(mcucr).bods = 3;
	REG_(mcucr).bods = 2;
	SREG = sreg;
	__asm__ __volatile__ ("sleep");
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return true, if JTAG Interface is disabled
 * @return True, if JTAG Interface is disabled
 *
 * ATmega640/1280/1281/2560/2561/164A/PA/324A/PA/644A/PA/1284/P only.
 */
inline bool MCUControl::isJtagDisabled() const
{
	return REG_(mcucr).jtd;
}
/**
 * @brief Enable JTAG interface
 *
 * JTAG interface will be enabled, if the JTAGEN Fuse is programmed.
 *
 * In order to avoid unintentional disabling or enabling of the JTAG
 * interface, a timed sequence must be followed when changing this
 * bit: The application software must write this bit to the desired
 * value twice within four cycles to change its value. Note that this
 * bit must not be altered when using the On-chip Debug system.
 *
 * ATmega640/1280/1281/2560/2561/164A/PA/324A/PA/644A/PA/1284/P only.
 */
inline void MCUControl::enableJtag()
{
	REG_(mcucr).jtd = false;
	REG_(mcucr).jtd = false;
}
/**
 * @brief Disable JTAG interface
 *
 * In order to avoid unintentional disabling or enabling of the JTAG
 * interface, a timed sequence must be followed when changing this
 * bit: The application software must write this bit to the desired
 * value twice within four cycles to change its value. Note that this
 * bit must not be altered when using the On-chip Debug system.
 *
 * ATmega640/1280/1281/2560/2561/164A/PA/324A/PA/644A/PA/1284/P only.
 */
inline void MCUControl::disableJtag()
{
	REG_(mcucr).jtd = true;
	REG_(mcucr).jtd = true;
}
/**
 * @brief Disable JTAG interface

 * In order to avoid unintentional disabling or enabling of the JTAG
 * interface, a timed sequence must be followed when changing this
 * bit: The application software must write this bit to the desired
 * value twice within four cycles to change its value. Note that this
 * bit must not be altered when using the On-chip Debug system.
 *
 * ATmega640/1280/1281/2560/2561/164A/PA/324A/PA/644A/PA/1284/P only.
 */
inline void MCUControl::setJtagDisable(bool val)
{
	REG_(mcucr).jtd = val;
	REG_(mcucr).jtd = val;
}
#endif


#endif /* MCUCONTROL_H_ */
