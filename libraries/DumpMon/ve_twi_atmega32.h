/**
 * @file ve_twi_atmega32.h
 * @brief ATmega32 Two-Wire Interface (TWI) Control Header
 * @author andrey
 * @date 05.11.2012
 * @copyright GNU Public License
 */
#ifndef TWI_ATMEGA32_H_
#define TWI_ATMEGA32_H_

/**
 * @brief ATmega32 Two-Wire Interface (TWI) Control class template
 * @ingroup TWI
 */
template <typename _TWCR_REG>
class TWIControlT: public _TWCR_REG
{
public:
	/**
	 * @brief Return true, if TWI Interrupt Flag is set
	 * @return True, if TWI Interrupt Flag is set
	 */
	inline bool isInt() const
	{
		return this->m_reg.twint;
	}
	/**
	 * @brief Clear TWI Interrupt Flag
	 */
	inline void clearInt()
	{
		this->m_reg.twint = true;
	}
	/**
	 * @brief Return true, if Acknowledge is enabled
	 * @return True, if Acknowledge is enabled
	 */
	inline bool isAckEnabled() const
	{
		return this->m_reg.twea;
	}
	/**
	 * @brief Enable Acknowledge
	 *
	 * The TWEA bit controls the generation of the acknowledge pulse.
	 * If the TWEA bit is written to one, the ACK pulse is generated
	 * on the TWI bus if the following conditions are met:
	 * 1. The device’s own slave address has been received.
	 * 2. A general call has been received, while the TWGCE bit in
	 * the TWAR is set.
	 * 3. A data byte has been received in Master Receiver or Slave
	 * Receiver mode.
	 */
	inline void enableAck()
	{
		this->m_reg.twea = true;
	}
	/**
	 * @brief Disable Acknowledge
	 *
	 * By writing the TWEA bit to zero, the device can be virtually
	 * disconnected from the 2-wire Serial Bus temporarily. Address
	 * recognition can then be resumed by writing the TWEA bit to one
	 * again.
	 */
	inline void disableAck()
	{
		this->m_reg.twea = false;
	}
	/**
	 * @brief Set Acknowledge Enable state
	 * @param[in] val New state value
	 */
	inline void setAckEnable(bool val)
	{
		this->m_reg.twea = val;
	}
	/**
	 * @brief Start transmition
	 *
	 * The application writes the TWSTA bit to one when it desires to
	 * become a Master on the 2-wire Serial Bus. The TWI hardware checks
	 * if the bus is available, and generates a START condition on the bus
	 * if it is free. However, if the bus is not free, the TWI waits until
	 * a STOP condition is detected, and then generates a new START condition
	 * to claim the bus Master status.
	 *
	 * TWSTA must be cleared by software when the START condition has been
	 * transmitted.
	 */
	inline void start()
	{
		this->m_reg.twsta = true;
	}
	/**
	 * @brief Clear Start Transmition Bit
	 */
	inline void endStart()
	{
		this->m_reg.twsta = false;
	}
	/**
	 * @brief Stop transmition
	 *
	 * Writing the TWSTO bit to one in Master mode will generate a STOP
	 * condition on the 2-wire Serial Bus. When the STOP condition is
	 * executed on the bus, the TWSTO bit is cleared automatically.
	 *
	 * In Slave mode, setting the TWSTO bit can be used to recover from an
	 * error condition. This will not generate a STOP condition, but the TWI
	 * returns to a well-defined unaddressed Slave mode and releases the SCL
	 * and SDA lines to a high impedance state.
	 */
	inline void stop()
	{
		this->m_reg.twsto = true;
	}
	/**
	 * @brief Return true, if Write Collision Flag is set
	 * @return True, if Write Collision Flag is set
	 */
	inline bool isWriteCollision() const
	{
		return this->m_reg.twwc;
	}
	/**
	 * @brief Return true, if the TWI is enabled
	 * @return True, if the TWI is enabled
	 */
	inline bool isEnabled() const
	{
		return this->m_reg.twen;
	}
	/**
	 * @brief Enable the TWI
	 */
	inline void enable()
	{
		this->m_reg.twen = true;
	}
	/**
	 * @brief Disable the TWI
	 */
	inline void disable()
	{
		this->m_reg.twen = false;
	}
	/**
	 * @brief Set TWI Enable state
	 * @param[in] val New state value
	 */
	inline void setEnable(bool val)
	{
		this->m_reg.twen = val;
	}
	/**
	 * @brief Return true, if TWI Interrupt is enabled
	 * @return True, if TWI Interrupt is enabled
	 */
	inline bool isIntEnabled() const
	{
		return this->m_reg.twie;
	}
	/**
	 * @brief Enable TWI Interrupt
	 */
	inline void enableInt()
	{
		this->m_reg.twie = true;
	}
	/**
	 * @brief Disable TWI Interrupt
	 */
	inline void disableInt()
	{
		this->m_reg.twie = false;
	}
	/**
	 * @brief Set TWI Interrupt Enable state
	 * @param[in] val New state value
	 */
	inline void setIntEnable(bool val)
	{
		this->m_reg.twie = val;
	}
};

typedef TWIControlT<TWCR_REG> TWIControl;	///< ATmega32 Two-Wire Interface (TWI) Control class

#endif /* TWI_ATMEGA32_H_ */
