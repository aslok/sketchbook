/**
 * @file ve_usi.h
 * @brief Universal Serial Interface (%USI) Header
 * @author andrey
 * @date 03.11.2012
 * @copyright GNU Public License
 */
#ifndef USI_H_
#define USI_H_

/**
 * @brief Universal Serial Interface (%USI)
 * @ingroup USI
 */
class USI: public AVR_USI
{
public:
	bool isStartConditionInt() const;
	void clearStartConditionInt();
	bool isCounterOverflowInt() const;
	void clearCounterOverflowInt();

	uint8_t spiMasterTransfer(uint8_t uch);
	uint8_t spiMasterTransferFast(uint8_t uch);
	void spiSlaveInit();
	uint8_t spiSlaveTransfer(uint8_t uch);
};
/**
 * @brief Return true, if Start Condition Interrupt Flag is set
 *
 * When Two-wire mode is selected, the USISIF Flag is set (to one) when a start
 * condition is detected. When output disable mode or Three-wire mode is selected,
 * the flag is set when the 4-bit counter is incremented.
 *
 * An interrupt will be generated when the flag is set while the USISIE bit in USICR
 * and the Global Interrupt Enable Flag are set. The flag will only be cleared by
 * writing a logical one to the USISIF bit. Clearing this bit will release the start
 * detection hold of USCL in Two-wire mode.
 *
 * A start condition interrupt will wake up the processor from all sleep modes.
 * @see USI::clearStartConditionInt()
 * @return True, if Start Condition Interrupt Flag is set
 */
inline bool USI::isStartConditionInt() const
{
	return REG_(usisr).usisif;
}
/**
 * @brief Clear Start Condition Interrupt Flag
 *
 * Clearing this bit will release the start detection hold of USCL in Two-wire mode.
 */
inline void USI::clearStartConditionInt()
{
	REG_(usisr).usisif = true;
}
/**
 * @brief Return true, if Counter Overflow Interrupt Flag is set
 *
 * This flag is set (one) when the 4-bit counter overflows (i.e., at the transition from
 * 15 to 0). An interrupt will be generated when the flag is set while the USIOIE bit in
 * USICR and the Global Interrupt Enable Flag are set.
 *
 * The flag will only be cleared if a one is written to the USIOIF bit. Clearing this bit
 * will release the counter overflow hold of SCL in Two-wire mode.
 *
 * A counter overflow interrupt will wake up the processor from Idle sleep mode.
 * @see USI::clearCounterOverflowInt()
 * @return True, if Counter Overflow Interrupt Flag is set
 */
inline bool USI::isCounterOverflowInt() const
{
	return REG_(usisr).usioif;
}
/**
 * @brief Clear Counter Overflow Interrupt Flag
 *
 * Clearing this bit will release the counter overflow hold of SCL in Two-wire mode.
 */
inline void USI::clearCounterOverflowInt()
{
	REG_(usisr).usioif = true;
}
/**
 * @brief Master %SPI transfer
 * @param[in] uch Byte to transfer
 * @return Byte, received from Slave device
 */
inline uint8_t USI::spiMasterTransfer(uint8_t uch)
{
	REG(usidr) = uch;
	REG_(usisr).usioif = true;
	uint8_t r16 = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
	do {
		REG(usicr) = r16;
		r16 = REG(usisr);
	} while(!REG_(usisr).usioif);
	return REG(usidr);
}
/**
 * @brief Master %SPI transfer with maximum speed (fsck = fck / 4)
 * @param[in] uch Byte to transfer
 * @return Byte, received from Slave device
 */
inline uint8_t USI::spiMasterTransferFast(uint8_t uch)
{
	REG(usidr) = uch;
	uint8_t r16 = _BV(USIWM0) | _BV(USITC);
	uint8_t r17 = _BV(USIWM0) | _BV(USITC) | _BV(USICLK);
	REG(usicr) = r16; // MSB
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16;
	REG(usicr) = r17;
	REG(usicr) = r16; // LSB
	REG(usicr) = r17;
	return REG(usidr);
}
/**
 * @brief Slave %SPI initialization
 */
inline void USI::spiSlaveInit()
{
	REG(usicr) = _BV(USIWM0) | _BV(USICS1);
}
/**
 * @brief Slave %SPI transfer
 * @param[in] uch Byte to transfer
 * @return Byte, received from Master device
 */
uint8_t USI::spiSlaveTransfer(uint8_t uch)
{
	REG(usidr) = uch;
	REG(usisr) = _BV(USIOIF);
	while(! REG_(usisr).usioif);
	return REG(usidr);
}
#endif /* USI_H_ */
