/**
 * @file ve_eeprom.h
 * @brief EEPROM Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef EEPROM_H_
#define EEPROM_H_

bool eeprom_isBusyWrite();

/**
 * @brief %EEPROM class
 * @ingroup VE_AVR
 */
class EEPROM : public AVR_EEPROM
{
public:
	/**
	 * @brief EEPROM Pointer class
	 */
	class ptr
	{
	protected:
		/**
		 * @brief EEPROM Pointer Data type
		 */
		template <typename Type>
		union Data {
			Type m_float;					///< Stored value
			uint8_t m_data[sizeof(Type)];	///< Stored value as character vector
		};
		typedef Data<float> FloatData;		///< EEPROM Pointer Float Data type
		typedef Data<double> DoubleData;	///< EEPROM Pointer Double Data type
	public:
		char operator =(char data);
		uint8_t operator =(uint8_t data);
		uint16_t operator = (uint16_t data);
		float operator = (float data);
		double operator = (double data);
		ptr& operator >> (char &ch);
		ptr& operator >> (uint8_t &ch);
		ptr& operator >> (uint16_t &wd);
		ptr& operator << (char data);
		ptr& operator << (uint8_t data);
		ptr& operator << (uint16_t data);
		ptr& operator >> (float& data);
		ptr& operator << (float data);
		ptr& operator >> (double& data);
		ptr& operator << (double data);
	};
public:
	bool isInterruptEnabled() const;
	void enableInterrupt();
	void disableInterrupt();
	void setInterruptEnable(bool val);

	ptr& operator [] (uintptr_t address);
protected:
	void enableMasterWrite();
	bool isBusyWrite() const;
	void enableWrite();
	void enableRead();
	friend bool eeprom_isBusyWrite();

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560)
public:
	/**
	 * @brief Programming Mode type
	 */
	typedef enum {
		ERASE_WRITE = 0,	///< Erase and Write
		ERASE_ONLY,			///< Erase Only
		WRITE_ONLY			///< Write Only
	} ProgMode;
	ProgMode progMode() const;
	void setProgMode(ProgMode mode);
#endif
};

/**
 * @brief Return pointer value for the address
 * @param[in] address Address value
 * @return Reference to EEPROM pointer
 */
inline EEPROM::ptr& EEPROM::operator [] (uintptr_t address)
{
	EEPROM::ptr* p = (EEPROM::ptr*) address;
	return *p;
}
/**
 * @brief Write character to the EEPROM
 * @param[in] data Character to write
 * @return Data value
 */
inline char EEPROM::ptr::operator =(char data)
{
	while (DEV_EEPROM.isBusyWrite());
	while (DEV_SPM.isSelfProgEnabled());
	register uint8_t sreg = SREG;
	disableInterrupts();
	DEV_EEPROM.eear.m_reg = (uintptr_t) this;
	DEV_EEPROM.eedr.m_reg = data;
	DEV_EEPROM.enableMasterWrite();
	DEV_EEPROM.enableWrite();
	SREG = sreg;	// Restoring Interrupts Flag
	return data;
}
/**
 * @brief Write unsigned character to the EEPROM
 * @param[in] data Unsigned character to write
 * @return Data value
 */
inline uint8_t EEPROM::ptr::operator =(uint8_t data)
{
	return operator = ((char) data);
}
/**
 * @brief Write unsigned word to the EEPROM
 * @param[in] data Unsigned word to write
 * @return Data value
 */
inline uint16_t EEPROM::ptr::operator = (uint16_t data)
{
	EEPROM::ptr* p = this;
	p->operator = ((char) data);
	++p;
	p->operator = ((char) (data >> 8));
	return data;
}
/**
 * @brief Write float value to the EEPROM
 * @param[in] data Float value to write
 * @return Data value
 */
inline float EEPROM::ptr::operator = (float data)
{
	EEPROM::ptr* p = this;
	p->operator << (data);
	return data;
}
/**
 * @brief Write double value to the EEPROM
 * @param[in] data Double value to write
 * @return Data value
 */
inline double EEPROM::ptr::operator = (double data)
{
	EEPROM::ptr* p = this;
	p->operator << (data);
	return data;
}
/**
 * @brief Stream character from the EEPROM
 * @param[in] ch Reference to character variable
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator >> (char &ch)
{
	while (DEV_EEPROM.isBusyWrite());
	while (DEV_SPM.isSelfProgEnabled());
	register uint8_t sreg = SREG;
	disableInterrupts();
	DEV_EEPROM.eear.m_reg = (uintptr_t) this;
	DEV_EEPROM.enableRead();
	ch = DEV_EEPROM.eedr.m_reg;
	SREG = sreg;	// Restoring Interrupts Flag
	EEPROM::ptr* p = this;
	++p;
	return (*p);
}
/**
 * @brief Stream float value from the EEPROM
 * @param[in] data Reference to float variable
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator >> (float& data)
{
	EEPROM::ptr* p = this;
	EEPROM::ptr::FloatData d;
	for (uint8_t n = 0; n < sizeof(float); ++n) {
		p->operator >> ((char&) d.m_data[n]);
		++p;
	}
	data = d.m_float;
	return (*p);
}
/**
 * @brief Stream float value to the EEPROM
 * @param[in] data Float value to write
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator << (float data)
{
	EEPROM::ptr* p = this;
	EEPROM::ptr::FloatData d;
	d.m_float = data;
	for (uint8_t n = 0; n < sizeof(float); ++n) {
		(*p) = (char) d.m_data[n];
		++p;
	}
	return (*p);
}
/**
 * @brief Stream double value from the EEPROM
 * @param[in] data Reference to double variable
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator >> (double& data)
{
	EEPROM::ptr* p = this;
	EEPROM::ptr::DoubleData d;
	for (uint8_t n = 0; n < sizeof(double); ++n) {
		p->operator >> ((char&) d.m_data[n]);
		++p;
	}
	data = d.m_float;
	return (*p);
}
/**
 * @brief Stream double value to the EEPROM
 * @param[in] data Double value to write
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator << (double data)
{
	EEPROM::ptr* p = this;
	EEPROM::ptr::DoubleData d;
	d.m_float = data;
	for (uint8_t n = 0; n < sizeof(double); ++n) {
		(*p) = (char) d.m_data[n];
		++p;
	}
	return (*p);
}
/**
 * @brief Stream unsigned character from the EEPROM
 * @param[in] ch Reference to unsigned character variable
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator >> (uint8_t &ch)
{
	EEPROM::ptr* p = this;
	p->operator >> ((char&) ch);
	++p;
	return (*p);
}
/**
 * @brief Stream unsigned word from the EEPROM
 * @param[in] wd Reference to unsigned word variable
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator >> (uint16_t &wd)
{
	EEPROM::ptr* p = this;
	char* pwd = (char*) &wd;
	p->operator >> (*pwd);
	++p; ++pwd;
	p->operator >> (*pwd);
	++p;
	return (*p);
}
/**
 * @brief Stream character to the EEPROM
 * @param[in] data Character to write
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator << (char data)
{
	this->operator = (data);
	EEPROM::ptr* p = this;
	++p;
	return (*p);
}
/**
 * @brief Stream unsigned character to the EEPROM
 * @param[in] data Unsigned character to write
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator << (uint8_t data)
{
	this->operator = (data);
	EEPROM::ptr* p = this;
	++p;
	return (*p);
}
/**
 * @brief Stream unsigned word to the EEPROM
 * @param[in] data Unsigned word to write
 * @return Reference to the pointer
 */
inline EEPROM::ptr& EEPROM::ptr::operator << (uint16_t data)
{
	this->operator = (data);
	EEPROM::ptr* p = this;
	p += 2;
	return (*p);
}
/**
 * @brief Return true, if EEPROM Interrupt is enabled
 * @return True, if EEPROM Interrupt is enabled
 */
inline bool EEPROM::isInterruptEnabled() const
{
	return REG_(eecr).eerie;
}
/**
 * @brief Enable EEPROM Interrupt
 */
inline void EEPROM::enableInterrupt()
{
	REG_(eecr).eerie = true;
}
/**
 * @brief Disable EEPROM Interrupt
 */
inline void EEPROM::disableInterrupt()
{
	REG_(eecr).eerie = false;
}
/**
 * @brief Set EEPROM Interrupt Enable state
 * @param[in] val New state value
 */
inline void EEPROM::setInterruptEnable(bool val)
{
	REG_(eecr).eerie = val;
}
/**
 * @brief Enable Master Write
 */
inline void EEPROM::enableMasterWrite()
{
	REG_(eecr).eempe = true;
}
/**
 * @brief Return true, if Busy Write Flag is set
 * @return True, if Busy Write Flag is set
 */
inline bool EEPROM::isBusyWrite() const
{
	return REG_(eecr).eepe;
}
/**
 * @brief Enable to write EEPROM
 */
inline void EEPROM::enableWrite()
{
	REG_(eecr).eepe = true;
}
/**
 * @brief Enable to read EEPROM
 */
inline void EEPROM::enableRead()
{
	REG_(eecr).eere = true;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560)
/**
 * @brief Return Programming Mode value
 * @return Programming Mode value
 */
inline 	EEPROM::ProgMode EEPROM::progMode() const
{
	return (ProgMode) REG_(eecr).eepm;
}
/**
 * @brief Set Programming Mode value
 * @param[in] mode New Programming Mode value
 */
inline void EEPROM::setProgMode(ProgMode mode)
{
	REG_(eecr).eepm = mode;
}
#endif
/**
 * @brief Return true, if Busy Write Flag is set
 * @return True, if Busy Write Flag is set
 */
inline bool eeprom_isBusyWrite()
{
	return DEV_EEPROM.isBusyWrite();
}

#endif /* EEPROM_H_ */
