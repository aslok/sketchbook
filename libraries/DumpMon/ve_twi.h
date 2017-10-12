/**
 * @file ve_twi.h
 * @brief Two-Wire Serial Interface (TWI) Header
 * @author andrey
 * @date 25.10.2012
 * @copyright GNU Public License
 */
#ifndef TWI_H_
#define TWI_H_

/**
 * @brief Two-Wire Serial Interface (TWI) class
 * @ingroup TWI
 */
class TWI: public AVR_TWI
{
public:
	/**
	 * @brief Status type
	 */
	typedef enum {
		BUS_ERROR = 0,						///< Bus Error
		START = 1,							///< Start Condition
		REP_START = 2,						///< Repeated Start Condition
		MT_SLA_ACK = 3,						///< Master Transmitter, Slave ACK received
		MT_SLA_NACK = 4,					///< Master Transmitter, Slave NACK received
		MT_DATA_ACK = 5,					///< Master Transmitter, Data byte transmitted, ACK received
		MT_DATA_NACK = 6,					///< Master Transmitter, Data byte transmitted, NACK received
		M_ARB_LOST = 7,						///< Master, Arbitration lost
		MR_SLA_ACK = 8,						///< Master Receiver, Slave ACK received
		MR_SLA_NACK = 9,					///< Master Receiver, Slave NACK received
		MR_DATA_ACK = 10,					///< Master Receiver, Data byte transmitted, ACK received
		MR_DATA_NACK = 11,					///< Master Receiver, Data byte transmitted, NACK received
		SR_SLA_ACK = 12,					///< Slave Receiver, Own SLA+W received, ACK returned
		SR_ARB_LOST_SLA_ACK = 13,			///< Slave Receiver, Arbitration lost in SLA+R/W as Master, Own SLA+W received, ACK returned
		SR_GCALL_SLA_ACK = 14,				///< Slave Receiver, General Call received, ACK returned
		SR_ARB_LOST_GCALL_SLA_ACK = 15,		///< Slave Receiver, Arbitration lost in SLA+R/W as Master, General Call received, ACK returned
		SR_DATA_ACK = 16,					///< Slave Receiver, Own SLA+W addressed, Data byte received, ACK returned
		SR_DATA_NACK = 17,					///< Slave Receiver, Own SLA+W addressed, Data byte received, NACK returned
		SR_GCALL_DATA_ACK = 18,				///< Slave Receiver, General Call addressed, Data byte received, ACK returned
		SR_GCALL_DATA_NACK = 19,			///< Slave Receiver, General Call addressed, Data byte received, NACK returned
		SR_STOP = 20,						///< Slave Receiver, Stop Condition or Repeated Start condition received
		ST_SLA_ACK = 21,					///< Slave Transmitter, Own SLA+R received, ACK returned
		ST_ARB_LOST_SLA_ACK = 22,			///< Slave Transmitter, Arbitration lost in SLA+R/W as Master, Own SLA+R received, ACK returned
		ST_DATA_ACK = 23,					///< Slave Transmitter, Data byte transmitted, ACK received
		ST_DATA_NACK = 24,					///< Slave Transmitter, Data byte transmitted, NACK received
		ST_LAST_DATA = 25,					///< Slave Transmitter, Last data byte transmitted, ACK received
		NO_INFO = 31						///< No info
	} Status;
	/**
	 * @brief Prescaler type
	 */
	typedef enum {
		DIV_1 = 0,							///< /1
		DIV_4,								///< /4
		DIV_16,								///< /16
		DIV_64								///< /64
	} Prescaler;
public:
	uint8_t bitRate() const;
	void setBitRate(uint8_t val);

	bool isInt() const;
	void clearInt();

	bool isAckEnabled() const;
	void enableAck();
	void disableAck();
	void setAckEnable(bool val);

	void start();
	void endStart();

	void stop();

	bool isWriteCollision() const;

	bool isEnabled() const;
	void enable();
	void disable();
	void setEnable(bool val);

	bool isIntEnabled() const;
	void enableInt();
	void disableInt();
	void setIntEnable(bool val);

	Status status() const;

	Prescaler prescaler() const;
	void setPrescaler(Prescaler val);

	bool isGeneralCallEnabled() const;
	void enableGeneralCall();
	void disableGeneralCall();
	void setGeneralCallEnable(bool val);

	uint8_t address() const;
	void setAddress(uint8_t val);

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325)
	uint8_t addressMask() const;
	void setAddressMask(uint8_t val);
#endif
};

#if defined(VE_ATmega32)
#include "ve_twi_atmega32.h"
#endif

/**
 * @brief Return Bit Rate value
 * @return Bit Rate value
 */
inline uint8_t TWI::bitRate() const
{
	return REG_(twbr);
}
/**
 * @brief Set Bit Rate value
 * @param[in] val New Bit Rate value
 */
inline void TWI::setBitRate(uint8_t val)
{
	REG_(twbr) = val;
}
/**
 * @brief Return Status value
 * @return Status value
 */
inline TWI::Status TWI::status() const
{
	return (Status) REG_(twsr).tws;
}
/**
 * @brief Return Prescaler value
 * @return Prescaler value
 */
inline TWI::Prescaler TWI::prescaler() const
{
	return (Prescaler) REG_(twsr).twps;
}
/**
 * @brief Set Prescaler value
 * @param[in] val New Prescaler value
 */
inline void TWI::setPrescaler(Prescaler val)
{
	REG_(twsr).twps = val;
}
/**
 * @brief Return true, if General Call is enabled
 * @return True, if General Call is enabled
 */
inline bool TWI::isGeneralCallEnabled() const
{
	return REG_(twar).twgce;
}
/**
 * @brief Enable General Call
 */
inline void TWI::enableGeneralCall()
{
	REG_(twar).twgce = true;
}
/**
 * @brief Disable General Call
 */
inline void TWI::disableGeneralCall()
{
	REG_(twar).twgce = false;
}
/**
 * @brief Set General Call Enable state
 * @param[in] val New state value
 */
inline void TWI::setGeneralCallEnable(bool val)
{
	REG_(twar).twgce = val;
}
/**
 * @brief Return Address value
 * @return Address value
 */
inline uint8_t TWI::address() const
{
	return REG_(twar).twa;
}
/**
 * @brief Set Address value
 * @param[in] val New Address value
 */
inline void TWI::setAddress(uint8_t val)
{
	REG_(twar).twa = val;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325)
/**
 * @brief Return true, if TWI Interrupt Flag is set
 * @return True, if TWI Interrupt Flag is set
 */
inline bool TWI::isInt() const
{
	return REG_(twcr).twint;
}
/**
 * @brief Clear TWI Interrupt Flag
 */
inline void TWI::clearInt()
{
	REG_(twcr).twint = true;
}
/**
 * @brief Return true, if Acknowledge is enabled
 * @return True, if Acknowledge is enabled
 */
inline bool TWI::isAckEnabled() const
{
	return REG_(twcr).twea;
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
inline void TWI::enableAck()
{
	REG_(twcr).twea = true;
}
/**
 * @brief Disable Acknowledge
 *
 * By writing the TWEA bit to zero, the device can be virtually
 * disconnected from the 2-wire Serial Bus temporarily. Address
 * recognition can then be resumed by writing the TWEA bit to one
 * again.
 */
inline void TWI::disableAck()
{
	REG_(twcr).twea = false;
}
/**
 * @brief Set Acknowledge Enable state
 * @param[in] val New state value
 */
inline void TWI::setAckEnable(bool val)
{
	REG_(twcr).twea = val;
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
inline void TWI::start()
{
	REG_(twcr).twsta = true;
}
/**
 * @brief Clear Start Transmition Bit
 */
inline void TWI::endStart()
{
	REG_(twcr).twsta = false;
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
inline void TWI::stop()
{
	REG_(twcr).twsto = true;
}
/**
 * @brief Return true, if Write Collision Flag is set
 * @return True, if Write Collision Flag is set
 */
inline bool TWI::isWriteCollision() const
{
	return REG_(twcr).twwc;
}
/**
 * @brief Return true, if the TWI is enabled
 * @return True, if the TWI is enabled
 */
inline bool TWI::isEnabled() const
{
	return REG_(twcr).twen;
}
/**
 * @brief Enable the TWI
 */
inline void TWI::enable()
{
	REG_(twcr).twen = true;
}
/**
 * @brief Disable the TWI
 */
inline void TWI::disable()
{
	REG_(twcr).twen = false;
}
/**
 * @brief Set TWI Enable state
 * @param[in] val New state value
 */
inline void TWI::setEnable(bool val)
{
	REG_(twcr).twen = val;
}
/**
 * @brief Return true, if TWI Interrupt is enabled
 * @return True, if TWI Interrupt is enabled
 */
inline bool TWI::isIntEnabled() const
{
	return REG_(twcr).twie;
}
/**
 * @brief Enable TWI Interrupt
 */
inline void TWI::enableInt()
{
	REG_(twcr).twie = true;
}
/**
 * @brief Disable TWI Interrupt
 */
inline void TWI::disableInt()
{
	REG_(twcr).twie = false;
}
/**
 * @brief Set TWI Interrupt Enable state
 * @param[in] val New state value
 */
inline void TWI::setIntEnable(bool val)
{
	REG_(twcr).twie = val;
}
/**
 * @brief Return Address Mask value
 * @return Address Mask value
 */
inline uint8_t TWI::addressMask() const
{
	return REG_(twamr).twam;
}
/**
 * @brief Set Address Mask
 * @param[in] val New Address Mask value
 */
inline void TWI::setAddressMask(uint8_t val)
{
	REG_(twamr).twam = val;
}
#endif

#if defined(VE_ATmega32)
inline bool TWI::isInt() const
{
	return DEV_TWICTRL.isInt();
}
inline void TWI::clearInt()
{
	DEV_TWICTRL.clearInt();
}
inline bool TWI::isAckEnabled() const
{
	return DEV_TWICTRL.isAckEnabled();
}
inline void TWI::enableAck()
{
	DEV_TWICTRL.enableAck();
}
inline void TWI::disableAck()
{
	DEV_TWICTRL.disableAck();
}
inline void TWI::setAckEnable(bool val)
{
	DEV_TWICTRL.setAckEnable(val);
}
inline void TWI::start()
{
	DEV_TWICTRL.start();
}
inline void TWI::endStart()
{
	DEV_TWICTRL.endStart();
}
inline void TWI::stop()
{
	DEV_TWICTRL.stop();
}
inline bool TWI::isWriteCollision() const
{
	return DEV_TWICTRL.isWriteCollision();
}
inline bool TWI::isEnabled() const
{
	return DEV_TWICTRL.isEnabled();
}
inline void TWI::enable()
{
	DEV_TWICTRL.enable();
}
inline void TWI::disable()
{
	DEV_TWICTRL.disable();
}
inline void TWI::setEnable(bool val)
{
	DEV_TWICTRL.setEnable(val);
}
inline bool TWI::isIntEnabled() const
{
	return DEV_TWICTRL.isIntEnabled();
}
inline void TWI::enableInt()
{
	DEV_TWICTRL.enableInt();
}
inline void TWI::disableInt()
{
	DEV_TWICTRL.disableInt();
}
inline void TWI::setIntEnable(bool val)
{
	DEV_TWICTRL.setIntEnable(val);
}
#endif

#endif /* TWI_H_ */
