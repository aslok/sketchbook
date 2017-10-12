/**
 * @file ve_usart.h
 * @brief USART Header
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef USART_H_
#define USART_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325) || \
    defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)

#define USART_PARITY_NONE       (0)			///< Parity None
#define USART_PARITY_EVEN       (1)			///< Parity Even
#define USART_PARITY_ODD        (2)			///< Parity Odd

#define USART_STOP_1BIT         (false)		///< 1 Stop Bit
#define USART_STOP_2BIT         (true)		///< 2 Stop Bits

#define USART_CKPOL_TXRISING    (false)		///< Clock Polarity TX Rising
#define USART_CKPOL_TXFALLING   (true)		///< Clock Polarity TX Falling

#endif

#if defined(VE_ATmega32)
#define USART_PARITY_NONE       (0)
#define USART_PARITY_EVEN       (_BV(UPM1))
#define USART_PARITY_ODD        (_BV(UPM1) | _BV(UPM0))
#define USART_PARITY_MASK       (_BV(UPM1) | _BV(UPM0))

#define USART_STOP_1BIT         (0)
#define USART_STOP_2BIT         (_BV(USBS))
#define USART_STOP_MASK         (_BV(USBS))

#define USART_CHARSIZE_MASK     (_BV(UCSZ1) | _BV(UCSZ0))

#define USART_CKPOL_TXRISING    (0)
#define USART_CKPOL_TXFALLING   (_BV(UCPOL))
#define USART_CKPOL_MASK        (_BV(UCPOL))
#endif

/**
 * @brief USART class
 * @ingroup VE_AVR
 */
class _Usart: public AVR_USART
{
public:
	/**
	 * @brief Parity type
	 */
    typedef enum
    {
        ParityNone = USART_PARITY_NONE,		///< None
        ParityEven = USART_PARITY_EVEN,		///< Even
        ParityOdd = USART_PARITY_ODD		///< Odd
    } Parity;
    /**
     * @brief Stop Bit type
     */
    typedef enum
    {
        Stop1Bit = USART_STOP_1BIT,			///< 1 Stop Bit
		Stop2Bit = USART_STOP_2BIT			///< 2 Stop Bits
    } StopBit;
    /**
     * @brief Clock Polarity type
     */
    typedef enum
    {
        TXRisingXCK = USART_CKPOL_TXRISING,		///< TX Rising
        TXFallingXCK = USART_CKPOL_TXFALLING	///< TX Falling
    } ClockPolarity;
public:
    bool isReceiveComplete() const;

    bool isTransmitComplete() const;
    void setTransmitComplete();

    bool isDataRegisterEmpty() const;

    bool isFrameError() const;

    bool isDataOverRun() const;

    bool isParityError() const;

    bool isDoubleSpeed() const;
    void setDoubleSpeed();
    void setSingleSpeed();
    void setDoubleSpeedOn(bool val);

    bool isMultiProcComMode() const;
    void setMultiProcComModeOn();
    void setMultiProcComModeOff();
    void setMultiProcComMode(bool val);

    bool isRxCompleteInterruptEnabled() const;
    void rxCompleteInterruptEnable();
    void rxCompleteInterruptDisable();
    void setRxCompleteInterruptEnable(bool val);

    bool isTxCompleteInterruptEnabled() const;
    void txCompleteInterruptEnable();
    void txCompleteInterruptDisable();
    void setTxCompleteInterruptEnable(bool val);

    bool isDataRegEmptyInterruptEnabled() const;
    void dataRegEmptyInterruptEnable();
    void dataRegEmptyInterruptDisable();
    void setDataRegEmptyInterruptEnable(bool val);

    bool isReceiverEnabled() const;
    void receiverEnable();
    void receiverDisable();
    void setReceiverEnable(bool val);

    bool isTransmitterEnabled() const;
    void transmitterEnable();
    void transmitterDisable();
    void setTransmitterEnable(bool val);

    bool isSynchronousMode() const;
    void setSynchronousMode();
    void setAsynchronousMode();
    void setSynchronousModeOn(bool val);

    Parity parityMode() const;
    void setParityMode(Parity val);

    StopBit stopbitMode() const;
    void setStopbitMode(StopBit val);

    uint8_t charSize() const;
    void setCharSize(uint8_t val);

    ClockPolarity clockPolarity() const;
    void setClockPolarity(ClockPolarity val);

    unsigned long baudRate() const;
    void setBaudRate(unsigned long val);

    _Usart& operator >>(uint8_t& _data);
    _Usart& operator >>(char& _data);
    _Usart& operator <<(uint8_t _data);
    _Usart& operator <<(char _data);
    _Usart& operator <<(const char *_str);

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32)
    uint8_t readUBRRH() const;
    uint8_t readUCSRC() const;
    void writeUBRRH(uint8_t val);
    void writeUCSRC(uint8_t val);
#endif
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    bool isMasterSPIMode() const;
    void setMasterSPIMode();
#endif
};

#if defined(VE_ATmega32)
#include "ve_usart_atmega32.h"
#endif
#if defined(VE_ATmega325)
#include "ve_usart_atmega325.h"
#endif
#if defined(VE_ATmega328P) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
#include "ve_usart_atmega328p.h"
#endif

/**
 * @brief Return true, if Receive Complete Flag is set
 * @return True, if Receive Complete Flag is set
 */
inline bool _Usart::isReceiveComplete() const
{
    return REG_(ucsra).rxc;
}
/**
 * @brief Return true, if Transmit Complete Flag is set
 * @return True, if Transmit Complete Flag is set
 */
inline bool _Usart::isTransmitComplete() const
{
    return REG_(ucsra).txc;
}
/**
 * @brief Set Transmit Complete Flag
 */
inline void _Usart::setTransmitComplete()
{
    REG_(ucsra).txc = true;
}
/**
 * @brief Return true, if Data Register Empty Flag is set
 * @return True, if Data Register Empty Flag is set
 */
inline bool _Usart::isDataRegisterEmpty() const
{
    return REG_(ucsra).udre;
}
/**
 * @brief Return true, if Frame Error Flag is set
 * @return True, if Frame Error Flag is set
 */
inline bool _Usart::isFrameError() const
{
    return REG_(ucsra).fe;
}
/**
 * @brief Return true, if Data Over Run Flag is set
 * @return True, if Data Over Run Flag is set
 */
inline bool _Usart::isDataOverRun() const
{
    return REG_(ucsra).dor;
}
/**
 * @brief Return true, if Parity Error Flag is set
 * @return True, if Parity Error Flag is set
 */
inline bool _Usart::isParityError() const
{
    return REG_(ucsra).upe;
}
/**
 * @brief Return true, if Double Speed Mode is on
 * @return True, if Double Speed Mode is on
 */
inline bool _Usart::isDoubleSpeed() const
{
    return REG_(ucsra).u2x;
}
/**
 * @brief Set Double Speed Mode
 */
inline void _Usart::setDoubleSpeed()
{
    REG_(ucsra).u2x = true;
}
/**
 * @brief Set Single Speed Mode
 */
inline void _Usart::setSingleSpeed()
{
    REG_(ucsra).u2x = false;
}
/**
 * @brief Set Double Speed Mode state
 * @param[in] val New state value
 */
inline void _Usart::setDoubleSpeedOn(bool val)
{
	REG_(ucsra).u2x = val;
}
/**
 * @brief Return true, if Multi-Processor Communication Mode is on
 * @return True, if Multi-Processor Communication Mode is on
 */
inline bool _Usart::isMultiProcComMode() const
{
    return REG_(ucsra).mpcm;
}
/**
 * @brief Turn on Multi-Processor Communication Mode
 */
inline void _Usart::setMultiProcComModeOn()
{
    REG_(ucsra).mpcm = true;
}
/**
 * @brief Turn off Multi-Processor Communication Mode
 */
inline void _Usart::setMultiProcComModeOff()
{
    REG_(ucsra).mpcm = false;
}
/**
 * @brief Set Multi-Processor Communication Mode state
 * @param[in] val New state value
 */
inline void _Usart::setMultiProcComMode(bool val)
{
	REG_(ucsra).mpcm = val;
}
/**
 * @brief Return true, if RX Complete Interrupt is enabled
 * @return True, if RX Complete Interrupt is enabled
 */
inline bool _Usart::isRxCompleteInterruptEnabled() const
{
    return REG_(ucsrb).rxcie;
}
/**
 * @brief Enable RX Complete Interrupt
 */
inline void _Usart::rxCompleteInterruptEnable()
{
    REG_(ucsrb).rxcie = true;
}
/**
 * @brief Disable RX Complete Interrupt
 */
inline void _Usart::rxCompleteInterruptDisable()
{
    REG_(ucsrb).rxcie = false;
}
/**
 * @brief Set RX Complete Interrupt Enable state
 * @param[in] val New state value
 */
inline void _Usart::setRxCompleteInterruptEnable(bool val)
{
    REG_(ucsrb).rxcie = val;
}
/**
 * @brief Return true, if TX Complete Interrupt is enabled
 * @return True, if TX Complete Interrupt is enabled
 */
inline bool _Usart::isTxCompleteInterruptEnabled() const
{
    return REG_(ucsrb).txcie;
}
/**
 * @brief Enable TX Complete Interrupt
 */
inline void _Usart::txCompleteInterruptEnable()
{
    REG_(ucsrb).txcie = true;
}
/**
 * @brief Disable TX Complete Interrupt
 */
inline void _Usart::txCompleteInterruptDisable()
{
    REG_(ucsrb).txcie = false;
}
/**
 * @brief Set TX Complete Interrupt Enable state
 * @param[in] val New state value
 */
inline void _Usart::setTxCompleteInterruptEnable(bool val)
{
    REG_(ucsrb).txcie = val;
}
/**
 * @brief Return true, if Data Register Empty Interrupt is enabled
 * @return True, if Data Register Empty Interrupt is enabled
 */
inline bool _Usart::isDataRegEmptyInterruptEnabled() const
{
    return REG_(ucsrb).udrie;
}
/**
 * @brief Enable Data Register Empty Interrupt
 */
inline void _Usart::dataRegEmptyInterruptEnable()
{
    REG_(ucsrb).udrie = true;
}
/**
 * @brief Disable Data Register Empty Interrupt
 */
inline void _Usart::dataRegEmptyInterruptDisable()
{
    REG_(ucsrb).udrie = false;
}
/**
 * @brief Set Data Register Empty Interrupt Enable state
 * @param[in] val New state value
 */
inline void _Usart::setDataRegEmptyInterruptEnable(bool val)
{
    REG_(ucsrb).udrie = val;
}
/**
 * @brief Return true, if Receiver is enabled
 * @return True, if Receiver is enabled
 */
inline bool _Usart::isReceiverEnabled() const
{
    return REG_(ucsrb).rxen;
}
/**
 * @brief Enable Receiver
 */
inline void _Usart::receiverEnable()
{
    REG_(ucsrb).rxen = true;
}
/**
 * @brief Disable Receiver
 */
inline void _Usart::receiverDisable()
{
    REG_(ucsrb).rxen = false;
}
/**
 * @brief Set Receiver Enable state
 * @param[in] val New state value
 */
inline void _Usart::setReceiverEnable(bool val)
{
    REG_(ucsrb).rxen = val;
}
/**
 * @brief Return true, if Transmitter is enabled
 * @return True, if Transmitter is enabled
 */
inline bool _Usart::isTransmitterEnabled() const
{
    return REG_(ucsrb).txen;
}
/**
 * @brief Enable Transmitter
 */
inline void _Usart::transmitterEnable()
{
    REG_(ucsrb).txen = true;
}
/**
 * @brief Disable Transmitter
 */
inline void _Usart::transmitterDisable()
{
    REG_(ucsrb).txen = false;
}
/**
 * @brief Set Transmitter Enable state
 * @param[in] val New state value
 */
inline void _Usart::setTransmitterEnable(bool val)
{
    REG_(ucsrb).txen = val;
}
/**
 * @brief Receive data byte in blocking mode
 * @param[out] _data Reference to data byte
 * @return Reference to this _Usart
 */
inline _Usart& _Usart::operator >>(uint8_t& _data)
{
	while (!isReceiveComplete());
    _data = REG(udr);
    return (*this);
}
/**
 * @brief Receive data character in blocking mode
 * @param[out] _data Reference to data character
 * @return Reference to this _Usart
 */
inline _Usart& _Usart::operator >>(char& _data)
{
	while (!isReceiveComplete());
    _data = REG(udr);
    return (*this);
}
/**
 * @brief Transmit data byte in blocking mode
 * @param[in] _data Data byte
 * @return Reference to this _Usart
 */
inline _Usart& _Usart::operator <<(uint8_t _data)
{
    while (!isDataRegisterEmpty());
    REG(udr) = _data;
    return (*this);
}
/**
 * @brief Transmit data character in blocking mode
 * @param[in] _data Data character
 * @return Reference to this _Usart
 */
inline _Usart& _Usart::operator <<(char _data)
{
    while (!isDataRegisterEmpty());
    REG(udr) = _data;
    return (*this);
}
/**
 * @brief Transmit string in blocking mode
 * @param[in] _str Pointer to the string
 * @return Reference to this _Usart
 */
inline _Usart& _Usart::operator <<(const char *_str)
{
    const char *p = _str;
    while(*p) {
        (*this) << (*p);
        ++p;
    }
    return (*this);
}

#endif /* USART_H_ */
