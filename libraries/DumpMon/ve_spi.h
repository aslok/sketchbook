/**
 * @file ve_spi.h
 * @brief Serial Peripheral Interface (SPI) Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef SPI_H_
#define SPI_H_

/**
 * @brief Serial Peripheral Interface (%SPI) class
 * @ingroup VE_AVR
 */
class SPI: public AVR_SPI
{
public:
	/**
	 * @brief Data Order type
	 */
	typedef enum {
		MSB_FIRST = 0,		///< MSB First
		LSB_FIRST			///< LSB First
	} DataOrder;
	/**
	 * @brief Clock Polarity type
	 */
	typedef enum {
		SCK_LOW = 0,		///< SCK Low
		SCK_HIGH			///< SCK High
	} CPol;
	/**
	 * @brief Clock Phase type
	 */
	typedef enum {
		LEAD_SAMPLE = 0,	///< Sample on Leading Edge
		LEAD_SETUP			///< Sample on Trailing Edge
	} CPha;
	/**
	 * @brief Clock Rate type
	 */
	typedef enum {
		DIV_4 = 0,			///< System Clock /4
		DIV_16,				///< System Clock /16
		DIV_64,				///< System Clock /64
		DIV_128				///< System Clock /128
	} Rate;
public:
	bool isIntEnabled() const;
	void enableInt();
	void disableInt();
	void setIntEnable(bool val);

	bool isEnabled() const;
	void enable();
	void disable();
	void setEnable(bool val);

	DataOrder dataOrder() const;
	void setDataOrder(DataOrder val);

	bool isMaster() const;
	void setMaster(bool ssOutput = true);
	void setSlave();

	CPol clockPolarity() const;
	void setClockPolarity(CPol val);

	CPha clockPhase() const;
	void setClockPhase(CPha val);

	Rate rate() const;
	void setRate(Rate val);

	bool isInt() const;
	void clearInt();

	bool isWriteCollision() const;
	void clearWriteCollision();

	bool isDoubleSpeed() const;
	void setDoubleSpeed();
	void setSingleSpeed();
	void setSpeedDouble(bool val);

	uint8_t read();
	uint8_t write(uint8_t data);
};

/**
 * @brief Return true, if SPI Interrupt is enabled
 * @return True, if SPI Interrupt is enabled
 */
inline bool SPI::isIntEnabled() const
{
	return REG_(spcr).spie;
}
/**
 * @brief Enable SPI Interrupt
 */
inline void SPI::enableInt()
{
	REG_(spcr).spie = true;
}
/**
 * @brief Disable SPI Interrupt
 */
inline void SPI::disableInt()
{
	REG_(spcr).spie = false;
}
/**
 * @brief Set SPI Interrupt Enable state
 * @param[in] val New state value
 */
inline void SPI::setIntEnable(bool val)
{
	REG_(spcr).spie = val;
}
/**
 * @brief Return true, if the SPI is enabled
 * @return True, if the SPI is enabled
 */
inline bool SPI::isEnabled() const
{
	return REG_(spcr).spe;
}
/**
 * @brief Enable the SPI
 */
inline void SPI::enable()
{
	REG_(spcr).spe = true;
}
/**
 * @brief Disable the SPI
 */
inline void SPI::disable()
{
	REG_(spcr).spe = false;
}
/**
 * @brief Set SPI Enable state
 * @param[in] val New state value
 */
inline void SPI::setEnable(bool val)
{
	REG_(spcr).spe = val;
}
/**
 * @brief Return Data Order value
 * @return Data Order value
 */
inline SPI::DataOrder SPI::dataOrder() const
{
	return (DataOrder) REG_(spcr).dord;
}
/**
 * @brief Set Data Order value
 * @param[in] val New Data Order value
 */
inline void SPI::setDataOrder(DataOrder val)
{
	REG_(spcr).dord = val;
}
/**
 * @brief Return true, if Master SPI Mode is selected
 * @return True, if Master SPI Mode is selected
 */
inline bool SPI::isMaster() const
{
	return REG_(spcr).mstr;
}
/**
 * @brief Select Master SPI Mode
 * @param[in] ssOutput Use nSS pin
 */
inline void SPI::setMaster(bool ssOutput)
{
	setModeInput(DEV_SPI_MISO);
	setModeOutput(DEV_SPI_SCK);
	setModeOutput(DEV_SPI_MOSI);
	if (ssOutput)
		setModeOutput(DEV_SPI_SS);
	else
		setModeInput(DEV_SPI_SS);
	REG_(spcr).mstr = true;
}
/**
 * @brief Select Slave SPI Mode
 */
inline void SPI::setSlave()
{
	setModeOutput(DEV_SPI_MISO);
	setModeInput(DEV_SPI_SCK);
	setModeInput(DEV_SPI_MOSI);
	setModeInput(DEV_SPI_SS);
	REG_(spcr).mstr = false;
}
/**
 * @brief Return Clock Polarity value
 * @return Clock Polarity value
 */
inline SPI::CPol SPI::clockPolarity() const
{
	return (CPol) REG_(spcr).cpol;
}
/**
 * @brief Set Clock Polarity value
 * @param[in] val New Clock Polarity value
 */
inline void SPI::setClockPolarity(CPol val)
{
	REG_(spcr).cpol = val;
}
/**
 * @brief Return Clock Phase value
 * @return Clock Phase value
 */
inline SPI::CPha SPI::clockPhase() const
{
	return (CPha) REG_(spcr).cpha;
}
/**
 * @brief Set Clock Phase value
 * @param[in] val New Clock Phase value
 */
inline void SPI::setClockPhase(CPha val)
{
	REG_(spcr).cpha = val;
}
/**
 * @brief Return Clock Rate value
 * @return Clock Rate value
 */
inline SPI::Rate SPI::rate() const
{
	return (Rate) REG_(spcr).spr;
}
/**
 * @brief Set Clock Rate value
 * @param[in] val New Clock Rate value
 */
inline void SPI::setRate(Rate val)
{
	REG_(spcr).spr = val;
}
/**
 * @brief Return true, if SPI Interrupt Flag is set
 * @return True, if SPI Interrupt Flag is set
 */
inline bool SPI::isInt() const
{
	return REG_(spsr).spif;
}
/**
 * @brief Clear SPI Interrupt Flag
 */
inline void SPI::clearInt()
{
	register uint8_t dummy = REG_(spsr).spif;
	dummy = REG_(spdr);
	UNUSED(dummy);
}
/**
 * @brief Return true, if Write Collision Flag is set
 * @return True, if Write Collision Flag is set
 *
 * The Write Collision Flag is set if the SPI Data Register (SPDR)
 * is written during a data transfer.
 */
inline bool SPI::isWriteCollision() const
{
	return REG_(spsr).wcol;
}
/**
 * @brief Clear Write Collision Flag
 */
inline void SPI::clearWriteCollision()
{
	register uint8_t dummy = REG_(spsr).wcol;
	dummy = REG_(spdr);
	UNUSED(dummy);
}
/**
 * @brief Return true, if SPI Frequency is doubled
 * @return True, if SPI Frequency is doubled
 */
inline bool SPI::isDoubleSpeed() const
{
	return REG_(spsr).spi2x;
}
/**
 * @brief Set Double Speed
 *
 * When this bit is written logic one the SPI speed (SCK Frequency)
 * will be doubled when the SPI is in Master mode. This means that
 * the minimum SCK period will be two CPU clock periods.
 *
 * When the SPI is configured as Slave, the SPI is only guaranteed
 * to work at fosc/4 or lower.
 */
inline void SPI::setDoubleSpeed()
{
	REG_(spsr).spi2x = true;
}
/**
 * @brief Set Single Speed
 */
inline void SPI::setSingleSpeed()
{
	REG_(spsr).spi2x = false;
}
/**
 * @brief Set Speed Double state
 * @param[in] val New state value
 */
inline void SPI::setSpeedDouble(bool val)
{
	REG_(spsr).spi2x = val;
}
/**
 * @brief Read data character in blocking mode
 * @return Data character
 */
inline uint8_t SPI::read()
{
	while(! isInt());
	return REG_(spdr);
}
/**
 * @brief Write data character in blocking mode
 * @return Data character that read
 */
inline uint8_t SPI::write(uint8_t data)
{
	REG_(spdr) = data;
	return read();
}

#endif /* SPI_H_ */
