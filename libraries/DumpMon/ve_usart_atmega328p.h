/**
 * @file ve_usart_atmega328p.h
 * @brief ATmega328P _Usart Functions Header
 * @author andrey
 * @date 01.11.2012
 * @copyright GNU Public License
 */
#ifndef USART_ATMEGA328P_H_
#define USART_ATMEGA328P_H_

/**
 * @brief Return true, if Synchronous Mode is set
 * @return True, if Synchronous Mode is set
 */
inline bool _Usart::isSynchronousMode() const
{
	return (REG_(ucsrc).umsel == 1);
}
/**
 * @brief Set Synchronous Mode
 */
inline void _Usart::setSynchronousMode()
{
	REG_(ucsrc).umsel = 1;
}
/**
 * @brief Set Asynchronous Mode
 */
inline void _Usart::setAsynchronousMode()
{
	REG_(ucsrc).umsel = 0;
}
/**
 * @brief Set Synchronous Mode state
 * @param[in] val New state value
 */
inline void _Usart::setSynchronousModeOn(bool val)
{
	REG_(ucsrc).umsel = (val ? 1 : 0);
}
/**
 * @brief Return true, if Master SPI Mode is set
 * @return True, if Master SPI Mode is set
 */
inline bool _Usart::isMasterSPIMode() const
{
	return (REG_(ucsrc).umsel == 3);
}
/**
 * @brief Set Master SPI Mode
 */
inline void _Usart::setMasterSPIMode()
{
	REG_(ucsrc).umsel = 3;
}
/**
 * @brief Return Parity Mode value
 * @return Parity Mode value
 */
inline _Usart::Parity _Usart::parityMode() const
{
	return (Parity) REG_(ucsrc).upm;
}
/**
 * @brief Set Parity Mode
 * @param[in] val New Parity Mode value
 */
inline void _Usart::setParityMode(Parity val)
{
	REG_(ucsrc).upm = val;
}
/**
 * @brief Return Stop Bit Mode value
 * @return Stop Bit Mode value
 */
inline _Usart::StopBit _Usart::stopbitMode() const
{
	return (StopBit) REG_(ucsrc).usbs;
}
/**
 * @brief Set Stop Bit Mode
 * @param[in] val New Stop Bit Mode value
 */
inline void _Usart::setStopbitMode(StopBit val)
{
	REG_(ucsrc).usbs = val;
}
/**
 * @brief Return Character Size value
 * @return Character Size value
 */
inline uint8_t _Usart::charSize() const
{
	return REG_(ucsrc).ucsz;
}
/**
 * @brief Set Character Size
 * @param[in] val New Character Size value
 */
inline void _Usart::setCharSize(uint8_t val)
{
	REG_(ucsrc).ucsz = val;
}
/**
 * @brief Return Clock Polarity value
 * @return Clock Polarity value
 */
inline _Usart::ClockPolarity _Usart::clockPolarity() const
{
	return (ClockPolarity) REG_(ucsrc).ucpol;
}
/**
 * @brief Set Clock Polarity
 * @param[in] val New Clock Polarity value
 */
inline void _Usart::setClockPolarity(ClockPolarity val)
{
	REG_(ucsrc).ucpol = val;
}
/**
 * @brief Return Baud Rate value
 * @return Baud Rate value
 */
inline unsigned long _Usart::baudRate() const
{
	unsigned char _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
	unsigned long ret = F_CPU / _div;
	ret /= REG_(ubrr) + 1;
	return ret;
}
/**
 * @brief Set Baud Rate
 * @param[in] val Baud Rate value
 */
inline void _Usart::setBaudRate(unsigned long val)
{
	unsigned char _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
	unsigned long _ubrr = F_CPU / _div;
	_ubrr /= val;
	REG(ubrr) = --_ubrr;
}


#endif /* USART_ATMEGA328P_H_ */
