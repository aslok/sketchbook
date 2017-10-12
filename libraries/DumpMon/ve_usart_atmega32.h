/**
 * @file ve_usart_atmega32.h
 * @brief ATmega32 _Usart Functions Header
 * @author andrey
 * @date 01.11.2012
 * @copyright GNU Public License
 */
#ifndef USART_ATMEGA32_H_
#define USART_ATMEGA32_H_

#define USART_UBRRH_MASK        (0x0F)			///< _Usart UBRRH Mask

/**
 * @brief Read UBRRH Register
 * @return UBRRH Register value
 *
 * ATmega32 only.
 */
inline uint8_t _Usart::readUBRRH() const
{
    return (UCSRC & USART_UBRRH_MASK);
}
/**
 * @brief Read UCSRC Register
 * @return UCSRC Register value
 *
 * ATmega32 only.
 */
inline uint8_t _Usart::readUCSRC() const
{
#if defined(SAFE_READ_UCSRC)
    register uint8_t sreg = SREG;
    disableInterrupts();
#endif
    uint8_t _ucsrc;
    __asm__ __volatile__ (
    		"in %0, %1\n\t"
            "in %0, %1"
            : "=r" (_ucsrc)
            : "I" (_SFR_IO_ADDR(UCSRC)));
#if defined(SAFE_READ_UCSRC)
    SREG = sreg;
#endif
    return _ucsrc;
}
/**
 * @brief Write UBRRH Register
 * @param[in] val New UBRRH Register value
 *
 * ATmega32 only.
 */
inline void _Usart::writeUBRRH(uint8_t val)
{
    UCSRC = val & ~_BV(URSEL);
}
/**
 * @brief Read UCSRC Register
 * @param[in] val New UCSRC Register value
 *
 * ATmega32 only.
 */
inline void _Usart::writeUCSRC(uint8_t val)
{
	UCSRC = val | _BV(URSEL);
}

#if !defined(__DOXYGEN__)
inline bool _Usart::isSynchronousMode() const
{
    return (readUCSRC() & _BV(UMSEL));
}

inline void _Usart::setSynchronousMode()
{
    writeUCSRC(readUCSRC() | _BV(UMSEL));
}

inline void _Usart::setAsynchronousMode()
{
    writeUCSRC(readUCSRC() & ~_BV(UMSEL));
    setClockPolarity(TXRisingXCK);
}
inline void _Usart::setSynchronousModeOn(bool val)
{
	if (val)
		setSynchronousMode();
	else
		setAsynchronousMode();
}

inline _Usart::Parity _Usart::parityMode() const
{
    return (_Usart::Parity) (readUCSRC() & USART_PARITY_MASK);
}

inline void _Usart::setParityMode(_Usart::Parity val)
{
    writeUCSRC((readUCSRC() & ~USART_PARITY_MASK) | val);
}

inline _Usart::StopBit _Usart::stopbitMode() const
{
    return (_Usart::StopBit) (readUCSRC() & USART_STOP_MASK);
}

inline void _Usart::setStopbitMode(_Usart::StopBit val)
{
    writeUCSRC((readUCSRC() & ~USART_STOP_MASK) | val);
}

inline uint8_t _Usart::charSize() const
{
    uint8_t val = REG_(ucsrb).ucsz2 ? 4 : 0;
    if (!val)
        val = (readUCSRC() & USART_CHARSIZE_MASK);
    val += 5;
    return val;
}

inline void _Usart::setCharSize(uint8_t val)
{
    uint8_t chsz;
    if (val < 9)
    {
        chsz = (val - 5) << 1;
        REG_(ucsrb).ucsz2 = false;
    }
    else
    {
        chsz = 3 << 1;
        REG_(ucsrb).ucsz2 = true;
    }
    writeUCSRC((readUCSRC() & ~USART_CHARSIZE_MASK) | chsz);
}

inline _Usart::ClockPolarity _Usart::clockPolarity() const
{
    return (_Usart::ClockPolarity) (readUCSRC() & USART_CKPOL_MASK);
}

inline void _Usart::setClockPolarity(_Usart::ClockPolarity val)
{
    writeUCSRC((readUCSRC() & ~USART_CKPOL_MASK) | val);
}

inline unsigned long _Usart::baudRate() const
{
    uint16_t _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
    uint16_t _ubrr = readUBRRH();
    _ubrr <<= 8;
    _ubrr += REG(ubrrl);
    _div *= ++_ubrr;
    long val = F_CPU;
    return val / _div;
}

inline void _Usart::setBaudRate(unsigned long val)
{
    uint16_t _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
    long _ldiv = _div * val;
    _ldiv = F_CPU / _ldiv;
    uint16_t _ubrr = _ldiv & 0x0FFF;
    --_ubrr;
    REG(ubrrl) = _ubrr & 0xFF;
    writeUBRRH((_ubrr >> 8) & 0x0F);
}
#endif	/* __DOXYGEN__ */

#endif /* USART_ATMEGA32_H_ */
