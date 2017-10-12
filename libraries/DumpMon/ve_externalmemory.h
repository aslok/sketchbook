/**
 * @file ve_externalmemory.h
 * @brief External Memory Control Header
 * @author andrey
 * @date 01.11.2012
 * @copyright GNU Public License
 */
#ifndef EXTERNALMEMORY_H_
#define EXTERNALMEMORY_H_

/**
 * @brief External Memory Control class
 * @ingroup VE_AVR
 */
class ExtMemory: public AVR_EXTMEM
{
public:
	/**
	 * @brief Split type
	 */
	typedef enum {
		NO_SPLIT = 0,	///< No Split
		x4000,			///< Split at 0x4000
		x6000,			///< Split at 0x6000
		x8000,			///< Split at 0x8000
		xA000,			///< Split at 0xA000
		xC000,			///< Split at 0xC000
		xE000			///< Split at 0xE000
	} Split;
	/**
	 * @brief Wait State type
	 */
	typedef enum {
		NO_WAIT = 0,	///< No wait-states
		WS_1_0,			///< Wait one cycle during read/write strobe
		WS_2_0,			///< Wait two cycles during read/write strobe
		WS_2_1			///< Wait two cycles during read/write and wait one cycle before driving out new address
	} WaitState;
	/**
	 * @brief High Mask type
	 */
	typedef enum {
		xFF = 0,		///< 8 bits (Full 56KB space)
		x7F,			///< 7 bits
		x3F,			///< 6 bits
		x1F,			///< 5 bits
		x0F,			///< 4 bits
		x07,			///< 3 bits
		x03,			///< 2 bits
		x01,			///< 1 bit
		x00				///< No Address high bits
	} HighMask;
public:
	bool enabled() const;
	void enable();
	void disable();
	void setEnable(bool val);

	Split split() const;
	void setSplit(Split val);

	WaitState waitState0() const;
	void setWaitState0(WaitState val);

	WaitState waitState1() const;
	void setWaitState1(WaitState val);

	bool busKeeperEnabled() const;
	void enableBusKeeper();
	void disableBusKeeper();
	void setBusKeeperEnable(bool val);

	HighMask highMask() const;
	void setHighMask(HighMask val);
};

/**
 * @brief Return true, if External Memory Interface is enabled
 * @return True, if External Memory Interface is enabled
 */
inline bool ExtMemory::enabled() const
{
	return REG_(xmcra).sre;
}
/**
 * @brief Enable External Memory Interface
 */
inline void ExtMemory::enable()
{
	REG_(xmcra).sre = true;
}
/**
 * @brief Disable External Memory Interface
 */
inline void ExtMemory::disable()
{
	REG_(xmcra).sre = false;
}
/**
 * @brief Set External Memory Interface Enable state
 * @param[in] val New state value
 */
inline void ExtMemory::setEnable(bool val)
{
	REG_(xmcra).sre = val;
}
/**
 * @brief Return Split Type value
 * @return Split Type value
 */
inline ExtMemory::Split ExtMemory::split() const
{
	return (Split) REG_(xmcra).srl;
}
/**
 * @brief Set Split Type value
 * @param[in] val New Split Type value
 */
inline void ExtMemory::setSplit(Split val)
{
	REG_(xmcra).srl = val;
}
/**
 * @brief Return Wait-State 0 value
 * @return Wait-State 0 value
 */
inline ExtMemory::WaitState ExtMemory::waitState0() const
{
	return (WaitState) REG_(xmcra).srw0;
}
/**
 * @brief Set Wait-State 0 value
 * @param[in] val New Wait-State 0 value
 */
inline void ExtMemory::setWaitState0(WaitState val)
{
	REG_(xmcra).srw0 = val;
}
/**
 * @brief Return Wait-State 1 value
 * @return Wait-State 1 value
 */
inline ExtMemory::WaitState ExtMemory::waitState1() const
{
	return (WaitState) REG_(xmcra).srw1;
}
/**
 * @brief Set Wait-State 1 value
 * @param[in] val New Wait-State 1 value
 */
inline void ExtMemory::setWaitState1(WaitState val)
{
	REG_(xmcra).srw1 = val;
}
/**
 * @brief Return true, if Bus Keeper is enabled
 * @return True, if Bus Keeper is enabled
 */
inline bool ExtMemory::busKeeperEnabled() const
{
	return REG_(xmcrb).xmbk;
}
/**
 * @brief Enable Bus Keeper
 */
inline void ExtMemory::enableBusKeeper()
{
	REG_(xmcrb).xmbk = true;
}
/**
 * @brief Disable Bus Keeper
 */
inline void ExtMemory::disableBusKeeper()
{
	REG_(xmcrb).xmbk = false;
}
/**
 * @brief Set Bus Keeper Enable state
 * @param[in] val New state value
 */
inline void ExtMemory::setBusKeeperEnable(bool val)
{
	REG_(xmcrb).xmbk = val;
}
/**
 * @brief Return High Mask value
 * @return High Mask value
 */
inline ExtMemory::HighMask ExtMemory::highMask() const
{
	return (HighMask) REG_(xmcrb).xmm;
}
/**
 * @brief Set High Mask value
 * @param[in] val New High Mask value
 */
inline void ExtMemory::setHighMask(HighMask val)
{
	REG_(xmcrb).xmm = val;
}


#endif /* EXTERNALMEMORY_H_ */
