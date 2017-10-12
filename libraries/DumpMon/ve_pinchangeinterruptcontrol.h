/**
 * @file ve_pinchangeinterruptcontrol.h
 * @brief Pin Change Interrupt Control Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef PINCHANGEINTERRUPTCONTROL_H_
#define PINCHANGEINTERRUPTCONTROL_H_

/**
 * @brief PinChangeControl class macro
 * @param[in] num Pin Change Interrupt number
 */
#define DECLARE_PCC(num) \
	inline bool isInt##num##Enabled() const { \
		return REG_(pcicr).pcie##num; \
	} \
	inline void enableInt##num() { \
		REG_(pcicr).pcie##num = true; \
	} \
	inline void disableInt##num() { \
		REG_(pcicr).pcie##num = false; \
	} \
	inline void setInt##num##Enable(bool val) { \
		REG_(pcicr).pcie##num = val; \
	}

/**
 * @brief Pin Change Interrupt Control class
 * @ingroup PCInt
 */
class PinChangeControl: public AVR_PCICTRL
{
public:
	/**
	 * @fn inline bool isInt0Enabled() const
	 * @brief Return true, if PCINT0 Interrupt is enabled
	 * @return True, if PCINT0 Interrupt is enabled
	 *
	 * @fn inline void enableInt0()
	 * @brief Enable PCINT0 Interrupt
	 *
	 * @fn inline void disableInt0()
	 * @brief Disable PCINT0 Interrupt
	 *
	 * @fn inline void setInt0Enable(bool val)
	 * @brief Set PCINT0 Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_PCC(0)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	/**
	 * @fn inline bool isInt1Enabled() const
	 * @brief Return true, if PCINT1 Interrupt is enabled
	 * @return True, if PCINT1 Interrupt is enabled
	 *
	 * @fn inline void enableInt1()
	 * @brief Enable PCINT1 Interrupt
	 *
	 * @fn inline void disableInt1()
	 * @brief Disable PCINT1 Interrupt
	 *
	 * @fn inline void setInt1Enable(bool val)
	 * @brief Set PCINT1 Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_PCC(1)
	/**
	 * @fn inline bool isInt2Enabled() const
	 * @brief Return true, if PCINT2 Interrupt is enabled
	 * @return True, if PCINT2 Interrupt is enabled
	 *
	 * @fn inline void enableInt2()
	 * @brief Enable PCINT2 Interrupt
	 *
	 * @fn inline void disableInt2()
	 * @brief Disable PCINT2 Interrupt
	 *
	 * @fn inline void setInt2Enable(bool val)
	 * @brief Set PCINT2 Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_PCC(2)
#endif

#if	defined(__DOXYGEN__) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	/**
	 * @fn inline bool isInt3Enabled() const
	 * @brief Return true, if PCINT3 Interrupt is enabled
	 * @return True, if PCINT3 Interrupt is enabled
	 *
	 * @fn inline void enableInt3()
	 * @brief Enable PCINT3 Interrupt
	 *
	 * @fn inline void disableInt3()
	 * @brief Disable PCINT3 Interrupt
	 *
	 * @fn inline void setInt3Enable(bool val)
	 * @brief Set PCINT3 Interrupt Enable state
	 * @param[in] val New state value
	 */
	DECLARE_PCC(3)
#endif
};

#endif /* PINCHANGEINTERRUPTCONTROL_H_ */
