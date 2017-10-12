/**
 * @file ve_usart_atmega325.h
 * @brief ATmega325 _Usart Functions Header
 * @author andrey
 * @date 01.11.2012
 * @copyright GNU Public License
 */
#ifndef USART_ATMEGA325_H_
#define USART_ATMEGA325_H_

#if !defined(__DOXYGEN__)
inline bool _Usart::isSynchronousMode() const
{
    return REG_(ucsrc).umsel;
}

inline void _Usart::setSynchronousMode()
{
    REG_(ucsrc).umsel = true;
}

inline void _Usart::setAsynchronousMode()
{
    REG_(ucsrc).umsel = false;
}
inline void _Usart::setSynchronousModeOn(bool val)
{
	REG_(ucsrc).umsel = val;
}
inline _Usart::Parity _Usart::parityMode() const
{
    return (_Usart::Parity) REG_(ucsrc).upm;
}

inline void _Usart::setParityMode(_Usart::Parity val)
{
    REG_(ucsrc).upm = val;
}

inline _Usart::StopBit _Usart::stopbitMode() const
{
    return (_Usart::StopBit) REG_(ucsrc).usbs;
}

inline void _Usart::setStopbitMode(_Usart::StopBit val)
{
    REG_(ucsrc).usbs = val;
}

inline uint8_t _Usart::charSize() const
{
    uint8_t ret = ((REG_(ucsrb).ucsz2 ? 1 : 0) << 2);
    if (ret)
        return 9;
    else
        return REG_(ucsrc).ucsz + 5;
}

inline void _Usart::setCharSize(uint8_t val)
{
    REG_(ucsrb).ucsz2 = ((val - 5) & 0x04);
    if (val == 9)
        REG_(ucsrc).ucsz = 3;
    else
        REG_(ucsrc).ucsz = (val - 5) & 0x03;
}

inline _Usart::ClockPolarity _Usart::clockPolarity() const
{
    return (_Usart::ClockPolarity) REG_(ucsrc).ucpol;
}

inline void _Usart::setClockPolarity(_Usart::ClockPolarity val)
{
    REG_(ucsrc).ucpol = val;
}

inline unsigned long _Usart::baudRate() const
{
    uint16_t _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
    _div *= REGW(ubrr) + 1;
    long val = F_CPU;
    return val / _div;
}

inline void _Usart::setBaudRate(unsigned long val)
{
    uint16_t _div = isSynchronousMode() ? 2 : isDoubleSpeed() ? 8 : 16;
    long _ldiv = _div * val;
    _ldiv = F_CPU / _ldiv;
    REGW(ubrr) = _ldiv & 0x0FFF;
}
#endif /* __DOXYGEN__ */

#endif /* USART_ATMEGA325_H_ */
