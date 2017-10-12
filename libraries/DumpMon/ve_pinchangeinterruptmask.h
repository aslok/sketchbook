/**
 * @file ve_pinchangeinterruptmask.h
 * @brief Pin Change Interrupt Mask Header
 * @author andrey
 * @date 01.11.2012
 * @copyright GNU Public License
 */
#ifndef PINCHANGEINTERRUPTMASK_H_
#define PINCHANGEINTERRUPTMASK_H_

/**
 * @brief PinChangeMaskT template macro
 * @param[in] num Pin Change Interrupt numberInterrupt
 */
#define PCMT_DECLARE(num) \
	inline bool isInt##num##Enabled() const { \
		return this->m_reg.pcint##num; \
	} \
	inline void enableInt##num() { \
		this->m_reg.pcint##num = true; \
	} \
	inline void disableInt##num() { \
		this->m_reg.pcint##num = true; \
	} \
	inline void setInt##num##Enable(bool val) { \
		this->m_reg.pcint##num = val; \
	}

/**
 * @brief Pin Change Interrupt Mask class template
 * @ingroup PCInt
 */
template <typename _PCMASK_REG>
class PinChangeMaskT: public _PCMASK_REG
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
	PCMT_DECLARE(0)
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
	PCMT_DECLARE(1)
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
	PCMT_DECLARE(2)
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
	PCMT_DECLARE(3)
	/**
	 * @fn inline bool isInt4Enabled() const
	 * @brief Return true, if PCINT4 Interrupt is enabled
	 * @return True, if PCINT4 Interrupt is enabled
	 *
	 * @fn inline void enableInt4()
	 * @brief Enable PCINT4 Interrupt
	 *
	 * @fn inline void disableInt4()
	 * @brief Disable PCINT4 Interrupt
	 *
	 * @fn inline void setInt4Enable(bool val)
	 * @brief Set PCINT4 Interrupt Enable state
	 * @param[in] val New state value
	 */
	PCMT_DECLARE(4)
	/**
	 * @fn inline bool isInt5Enabled() const
	 * @brief Return true, if PCINT5 Interrupt is enabled
	 * @return True, if PCINT5 Interrupt is enabled
	 *
	 * @fn inline void enableInt5()
	 * @brief Enable PCINT5 Interrupt
	 *
	 * @fn inline void disableInt5()
	 * @brief Disable PCINT5 Interrupt
	 *
	 * @fn inline void setInt5Enable(bool val)
	 * @brief Set PCINT5 Interrupt Enable state
	 * @param[in] val New state value
	 */
	PCMT_DECLARE(5)
	/**
	 * @fn inline bool isInt6Enabled() const
	 * @brief Return true, if PCINT6 Interrupt is enabled
	 * @return True, if PCINT6 Interrupt is enabled
	 *
	 * @fn inline void enableInt6()
	 * @brief Enable PCINT6 Interrupt
	 *
	 * @fn inline void disableInt6()
	 * @brief Disable PCINT6 Interrupt
	 *
	 * @fn inline void setInt6Enable(bool val)
	 * @brief Set PCINT6 Interrupt Enable state
	 * @param[in] val New state value
	 */
	PCMT_DECLARE(6)
	/**
	 * @fn inline bool isInt7Enabled() const
	 * @brief Return true, if PCINT7 Interrupt is enabled
	 * @return True, if PCINT7 Interrupt is enabled
	 *
	 * @fn inline void enableInt7()
	 * @brief Enable PCINT7 Interrupt
	 *
	 * @fn inline void disableInt7()
	 * @brief Disable PCINT7 Interrupt
	 *
	 * @fn inline void setInt7Enable(bool val)
	 * @brief Set PCINT7 Interrupt Enable state
	 * @param[in] val New state value
	 */
	PCMT_DECLARE(7)
};

/**
 * @brief Pin Change Interrupt Mask class
 * @ingroup PCInt
 */
typedef PinChangeMaskT<PCMSK_REG> PinChangeMask;

/**
 * @addtogroup PCIfunc
 * @{
 */

/**
 * @brief Pin Change Interrupt Mask functions macro
 * @param[in] pin Pin Change Interrupt number
 * @param[in] mask Device number
 * @param[in] bit Bit number
 */
#define PCM_DECLARE(pin, mask, bit) \
inline bool isPinChangeInt##pin##Enabled() { \
	return DEV_PCIMASK##mask.isInt##bit##Enabled(); \
} \
inline void enablePinChangeInt##pin() { \
	DEV_PCIMASK##mask.enableInt##bit(); \
} \
inline void disablePinChangeInt##pin() { \
	DEV_PCIMASK##mask.disableInt##bit(); \
} \
inline void setPinChangeInt##pin##Enable(bool val) { \
	DEV_PCIMASK##mask.setInt##bit##Enable(val); \
}

/**
 * @fn inline bool isPinChangeInt0Enabled()
 * @brief Return true, if PCINT0 Interrupt is enabled
 * @return True, if PCINT0 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt0()
 * @brief Enable PCINT0 Interrupt
 *
 * @fn inline void disablePinChangeInt0()
 * @brief Disable PCINT0 Interrupt
 *
 * @fn inline void setPinChangeInt0Enable(bool val)
 * @brief Set PCINT0 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(0, 0, 0)
/**
 * @fn inline bool isPinChangeInt1Enabled()
 * @brief Return true, if PCINT1 Interrupt is enabled
 * @return True, if PCINT1 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt1()
 * @brief Enable PCINT1 Interrupt
 *
 * @fn inline void disablePinChangeInt1()
 * @brief Disable PCINT1 Interrupt
 *
 * @fn inline void setPinChangeInt1Enable(bool val)
 * @brief Set PCINT1 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(1, 0, 1)
/**
 * @fn inline bool isPinChangeInt2Enabled()
 * @brief Return true, if PCINT2 Interrupt is enabled
 * @return True, if PCINT2 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt2()
 * @brief Enable PCINT2 Interrupt
 *
 * @fn inline void disablePinChangeInt2()
 * @brief Disable PCINT2 Interrupt
 *
 * @fn inline void setPinChangeInt2Enable(bool val)
 * @brief Set PCINT2 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(2, 0, 2)
/**
 * @fn inline bool isPinChangeInt3Enabled()
 * @brief Return true, if PCINT3 Interrupt is enabled
 * @return True, if PCINT3 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt3()
 * @brief Enable PCINT3 Interrupt
 *
 * @fn inline void disablePinChangeInt3()
 * @brief Disable PCINT3 Interrupt
 *
 * @fn inline void setPinChangeInt3Enable(bool val)
 * @brief Set PCINT3 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(3, 0, 3)
/**
 * @fn inline bool isPinChangeInt4Enabled()
 * @brief Return true, if PCINT4 Interrupt is enabled
 * @return True, if PCINT4 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt4()
 * @brief Enable PCINT4 Interrupt
 *
 * @fn inline void disablePinChangeInt4()
 * @brief Disable PCINT4 Interrupt
 *
 * @fn inline void setPinChangeInt4Enable(bool val)
 * @brief Set PCINT4 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(4, 0, 4)
/**
 * @fn inline bool isPinChangeInt5Enabled()
 * @brief Return true, if PCINT5 Interrupt is enabled
 * @return True, if PCINT5 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt5()
 * @brief Enable PCINT5 Interrupt
 *
 * @fn inline void disablePinChangeInt5()
 * @brief Disable PCINT5 Interrupt
 *
 * @fn inline void setPinChangeInt5Enable(bool val)
 * @brief Set PCINT5 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(5, 0, 5)
/**
 * @fn inline bool isPinChangeInt6Enabled()
 * @brief Return true, if PCINT6 Interrupt is enabled
 * @return True, if PCINT6 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt6()
 * @brief Enable PCINT6 Interrupt
 *
 * @fn inline void disablePinChangeInt6()
 * @brief Disable PCINT6 Interrupt
 *
 * @fn inline void setPinChangeInt6Enable(bool val)
 * @brief Set PCINT6 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(6, 0, 6)
/**
 * @fn inline bool isPinChangeInt7Enabled()
 * @brief Return true, if PCINT7 Interrupt is enabled
 * @return True, if PCINT7 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt7()
 * @brief Enable PCINT7 Interrupt
 *
 * @fn inline void disablePinChangeInt7()
 * @brief Disable PCINT7 Interrupt
 *
 * @fn inline void setPinChangeInt7Enable(bool val)
 * @brief Set PCINT7 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(7, 0, 7)

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @fn inline bool isPinChangeInt8Enabled()
 * @brief Return true, if PCINT8 Interrupt is enabled
 * @return True, if PCINT8 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt8()
 * @brief Enable PCINT8 Interrupt
 *
 * @fn inline void disablePinChangeInt8()
 * @brief Disable PCINT8 Interrupt
 *
 * @fn inline void setPinChangeInt8Enable(bool val)
 * @brief Set PCINT8 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(8, 1, 0)
/**
 * @fn inline bool isPinChangeInt9Enabled()
 * @brief Return true, if PCINT9 Interrupt is enabled
 * @return True, if PCINT9 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt9()
 * @brief Enable PCINT9 Interrupt
 *
 * @fn inline void disablePinChangeInt9()
 * @brief Disable PCINT9 Interrupt
 *
 * @fn inline void setPinChangeInt9Enable(bool val)
 * @brief Set PCINT9 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(9, 1, 1)
/**
 * @fn inline bool isPinChangeInt10Enabled()
 * @brief Return true, if PCINT10 Interrupt is enabled
 * @return True, if PCINT10 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt10()
 * @brief Enable PCINT10 Interrupt
 *
 * @fn inline void disablePinChangeInt10()
 * @brief Disable PCINT10 Interrupt
 *
 * @fn inline void setPinChangeInt10Enable(bool val)
 * @brief Set PCINT10 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(10, 1, 2)
/**
 * @fn inline bool isPinChangeInt11Enabled()
 * @brief Return true, if PCINT11 Interrupt is enabled
 * @return True, if PCINT11 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt11()
 * @brief Enable PCINT11 Interrupt
 *
 * @fn inline void disablePinChangeInt11()
 * @brief Disable PCINT11 Interrupt
 *
 * @fn inline void setPinChangeInt11Enable(bool val)
 * @brief Set PCINT11 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(11, 1, 3)
/**
 * @fn inline bool isPinChangeInt12Enabled()
 * @brief Return true, if PCINT12 Interrupt is enabled
 * @return True, if PCINT12 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt12()
 * @brief Enable PCINT12 Interrupt
 *
 * @fn inline void disablePinChangeInt12()
 * @brief Disable PCINT12 Interrupt
 *
 * @fn inline void setPinChangeInt12Enable(bool val)
 * @brief Set PCINT12 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(12, 1, 4)
/**
 * @fn inline bool isPinChangeInt13Enabled()
 * @brief Return true, if PCINT13 Interrupt is enabled
 * @return True, if PCINT13 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt13()
 * @brief Enable PCINT13 Interrupt
 *
 * @fn inline void disablePinChangeInt13()
 * @brief Disable PCINT13 Interrupt
 *
 * @fn inline void setPinChangeInt13Enable(bool val)
 * @brief Set PCINT13 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(13, 1, 5)
/**
 * @fn inline bool isPinChangeInt14Enabled()
 * @brief Return true, if PCINT14 Interrupt is enabled
 * @return True, if PCINT14 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt14()
 * @brief Enable PCINT14 Interrupt
 *
 * @fn inline void disablePinChangeInt14()
 * @brief Disable PCINT14 Interrupt
 *
 * @fn inline void setPinChangeInt14Enable(bool val)
 * @brief Set PCINT14 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(14, 1, 6)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @fn inline bool isPinChangeInt15Enabled()
 * @brief Return true, if PCINT15 Interrupt is enabled
 * @return True, if PCINT15 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt15()
 * @brief Enable PCINT15 Interrupt
 *
 * @fn inline void disablePinChangeInt15()
 * @brief Disable PCINT15 Interrupt
 *
 * @fn inline void setPinChangeInt15Enable(bool val)
 * @brief Set PCINT15 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(15, 1, 7)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P) || \
	defined(VE_ATmega328P)
/**
 * @fn inline bool isPinChangeInt16Enabled()
 * @brief Return true, if PCINT16 Interrupt is enabled
 * @return True, if PCINT16 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt16()
 * @brief Enable PCINT16 Interrupt
 *
 * @fn inline void disablePinChangeInt16()
 * @brief Disable PCINT16 Interrupt
 *
 * @fn inline void setPinChangeInt16Enable(bool val)
 * @brief Set PCINT16 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(16, 2, 0)
/**
 * @fn inline bool isPinChangeInt17Enabled()
 * @brief Return true, if PCINT17 Interrupt is enabled
 * @return True, if PCINT17 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt17()
 * @brief Enable PCINT17 Interrupt
 *
 * @fn inline void disablePinChangeInt17()
 * @brief Disable PCINT17 Interrupt
 *
 * @fn inline void setPinChangeInt17Enable(bool val)
 * @brief Set PCINT17 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(17, 2, 1)
/**
 * @fn inline bool isPinChangeInt18Enabled()
 * @brief Return true, if PCINT18 Interrupt is enabled
 * @return True, if PCINT18 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt18()
 * @brief Enable PCINT18 Interrupt
 *
 * @fn inline void disablePinChangeInt18()
 * @brief Disable PCINT18 Interrupt
 *
 * @fn inline void setPinChangeInt18Enable(bool val)
 * @brief Set PCINT18 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(18, 2, 2)
/**
 * @fn inline bool isPinChangeInt19Enabled()
 * @brief Return true, if PCINT19 Interrupt is enabled
 * @return True, if PCINT19 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt19()
 * @brief Enable PCINT19 Interrupt
 *
 * @fn inline void disablePinChangeInt19()
 * @brief Disable PCINT19 Interrupt
 *
 * @fn inline void setPinChangeInt19Enable(bool val)
 * @brief Set PCINT19 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(19, 2, 3)
/**
 * @fn inline bool isPinChangeInt20Enabled()
 * @brief Return true, if PCINT20 Interrupt is enabled
 * @return True, if PCINT20 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt20()
 * @brief Enable PCINT20 Interrupt
 *
 * @fn inline void disablePinChangeInt20()
 * @brief Disable PCINT20 Interrupt
 *
 * @fn inline void setPinChangeInt20Enable(bool val)
 * @brief Set PCINT20 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(20, 2, 4)
/**
 * @fn inline bool isPinChangeInt21Enabled()
 * @brief Return true, if PCINT21 Interrupt is enabled
 * @return True, if PCINT21 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt21()
 * @brief Enable PCINT21 Interrupt
 *
 * @fn inline void disablePinChangeInt21()
 * @brief Disable PCINT21 Interrupt
 *
 * @fn inline void setPinChangeInt21Enable(bool val)
 * @brief Set PCINT21 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(21, 2, 5)
/**
 * @fn inline bool isPinChangeInt22Enabled()
 * @brief Return true, if PCINT22 Interrupt is enabled
 * @return True, if PCINT22 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt22()
 * @brief Enable PCINT22 Interrupt
 *
 * @fn inline void disablePinChangeInt22()
 * @brief Disable PCINT22 Interrupt
 *
 * @fn inline void setPinChangeInt22Enable(bool val)
 * @brief Set PCINT22 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(22, 2, 6)
/**
 * @fn inline bool isPinChangeInt23Enabled()
 * @brief Return true, if PCINT23 Interrupt is enabled
 * @return True, if PCINT23 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt23()
 * @brief Enable PCINT23 Interrupt
 *
 * @fn inline void disablePinChangeInt23()
 * @brief Disable PCINT23 Interrupt
 *
 * @fn inline void setPinChangeInt23Enable(bool val)
 * @brief Set PCINT23 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(23, 2, 7)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @fn inline bool isPinChangeInt24Enabled()
 * @brief Return true, if PCINT24 Interrupt is enabled
 * @return True, if PCINT24 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt24()
 * @brief Enable PCINT24 Interrupt
 *
 * @fn inline void disablePinChangeInt24()
 * @brief Disable PCINT24 Interrupt
 *
 * @fn inline void setPinChangeInt24Enable(bool val)
 * @brief Set PCINT24 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(24, 3, 0)
/**
 * @fn inline bool isPinChangeInt25Enabled()
 * @brief Return true, if PCINT25 Interrupt is enabled
 * @return True, if PCINT25 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt25()
 * @brief Enable PCINT25 Interrupt
 *
 * @fn inline void disablePinChangeInt25()
 * @brief Disable PCINT25 Interrupt
 *
 * @fn inline void setPinChangeInt25Enable(bool val)
 * @brief Set PCINT25 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(25, 3, 1)
/**
 * @fn inline bool isPinChangeInt26Enabled()
 * @brief Return true, if PCINT26 Interrupt is enabled
 * @return True, if PCINT26 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt26()
 * @brief Enable PCINT26 Interrupt
 *
 * @fn inline void disablePinChangeInt26()
 * @brief Disable PCINT26 Interrupt
 *
 * @fn inline void setPinChangeInt26Enable(bool val)
 * @brief Set PCINT26 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(26, 3, 2)
/**
 * @fn inline bool isPinChangeInt27Enabled()
 * @brief Return true, if PCINT27 Interrupt is enabled
 * @return True, if PCINT27 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt27()
 * @brief Enable PCINT27 Interrupt
 *
 * @fn inline void disablePinChangeInt27()
 * @brief Disable PCINT27 Interrupt
 *
 * @fn inline void setPinChangeInt27Enable(bool val)
 * @brief Set PCINT0 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(27, 3, 3)
/**
 * @fn inline bool isPinChangeInt28Enabled()
 * @brief Return true, if PCINT28 Interrupt is enabled
 * @return True, if PCINT28 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt28()
 * @brief Enable PCINT28 Interrupt
 *
 * @fn inline void disablePinChangeInt28()
 * @brief Disable PCINT28 Inter27upt
 *
 * @fn inline void setPinChangeInt28Enable(bool val)
 * @brief Set PCINT28 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(28, 3, 4)
/**
 * @fn inline bool isPinChangeInt29Enabled()
 * @brief Return true, if PCINT29 Interrupt is enabled
 * @return True, if PCINT29 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt29()
 * @brief Enable PCINT29 Interrupt
 *
 * @fn inline void disablePinChangeInt29()
 * @brief Disable PCINT29 Interrupt
 *
 * @fn inline void setPinChangeInt29Enable(bool val)
 * @brief Set PCINT29 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(29, 3, 5)
/**
 * @fn inline bool isPinChangeInt30Enabled()
 * @brief Return true, if PCINT30 Interrupt is enabled
 * @return True, if PCINT30 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt30()
 * @brief Enable PCINT30 Interrupt
 *
 * @fn inline void disablePinChangeInt30()
 * @brief Disable PCINT30 Interrupt
 *
 * @fn inline void setPinChangeInt30Enable(bool val)
 * @brief Set PCINT30 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(30, 3, 6)
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @fn inline bool isPinChangeInt31Enabled()
 * @brief Return true, if PCINT31 Interrupt is enabled
 * @return True, if PCINT31 Interrupt is enabled
 *
 * @fn inline void enablePinChangeInt31()
 * @brief Enable PCINT31 Interrupt
 *
 * @fn inline void disablePinChangeInt31()
 * @brief Disable PCINT31 Interrupt
 *
 * @fn inline void setPinChangeInt31Enable(bool val)
 * @brief Set PCINT31 Interrupt Enable state
 * @param[in] val New state value
 */
PCM_DECLARE(31, 3, 7)
#endif
/**
 * @}
 */
#endif /* PINCHANGEINTERRUPTMASK_H_ */
