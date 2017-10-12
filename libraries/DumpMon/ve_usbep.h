/**
 * @file ve_usbep.h
 * @brief USB Endpoint Header
 * @author andrey
 * @date 09.12.2012
 * @copyright GNU Public License
 */
#ifndef USBDEVEP_H_
#define USBDEVEP_H_

/**
 * @brief USB Endpoint class
 * @ingroup USB
 */
class UsbEndpoint : public AVR_USBEP
{
public:
	/**
	 * @brief Endpoint Type type
	 */
	typedef enum {
		Control     = 0,		///< Control
		Isochronous = 1,		///< Isochronous
		Bulk        = 2,		///< Bulk
		Interrupt   = 3			///< Interrupt
	} Type;
	/**
	 * @brief Direction type
	 */
	typedef enum {
		OUT = 0,				///< Output
		IN = 1					///< Input
	} Dir;
	/**
	 * @brief Size type
	 */
	typedef enum {
		Size_8bytes   = 0,		///< 8 Bytes
		Size_16bytes  = 1,		///< 16 Bytes
		Size_32bytes  = 2,		///< 32 Bytes
		Size_64bytes  = 3,		///< 64 Bytes
		Size_128bytes = 4,		///< 128 Bytes
		Size_256bytes = 5,		///< 256 Bytes
		Size_512bytes = 6		///< 512 Bytes
	} Size;
	/**
	 * @brief Bank type
	 */
	typedef enum {
		Single = 0,				///< Single
		Double = 1				///< Double
	} Bank;
	/**
	 * @brief PID type
	 */
	typedef enum {
		Data0 = 0,				///< Data 0
		Data1 = 1				///< Data 1
	} PID;
	/**
	 * @brief Busy Banks type
	 */
	typedef enum {
		AllFree     = 0,		///< All Banks are Free
		Busy_1bank  = 1,		///< 1 Bank is Busy
		Busy_2banks = 2			///< 2 Banks are Busy
	} BusyBanks;
	/**
	 * @brief Current Bank type
	 */
	typedef enum {
		Bank0 = 0,				///< Bank 0
		Bank1 = 1				///< Bank 1
	} CurrBank;
public:
	unsigned char number() const;
	void setNumber(unsigned char val);

	void resetEndpointFIFO(unsigned char ep);

	void requestSTALL();
	bool isSETUPReceived() const;
	void disableSTALLHandshake();

	void resetDataToggle();

	bool isEnabled() const;
	void enable();
	void disable();
	void setEnable(bool val);

	Type type() const;
	void setType(Type val);

	Dir direction() const;
	void setDirection(Dir val);

	Size size() const;
	void setSize(Size val);

	Bank bank() const;
	void setBank(Bank val);

	bool isMemoryAllocated() const;
	void allocateMemory();
	void freeMemory();

	bool isConfigurationOK() const;
	bool isOverflowErrorInt() const;
	void clearOverflowErrorInt();
	bool isUnderflowErrorInt() const;
	void clearUnderflowErrorInt();
	PID pid() const;
	BusyBanks busyBanks() const;
	Dir controlDirection() const;
	CurrBank currentBank() const;
	bool isFIFOControlInt() const;
	void clearFIFOControlInt();
	bool isNAKINReceivedInt() const;
	void clearNAKINReceivedInt();
	bool isReadWriteAllowed() const;
	bool isNAKOUTReceivedInt() const;
	void clearNAKOUTReceivedInt();
	bool isSETUPReceivedInt() const;
	void clearSETUPReceivedInt();
	bool isOUTDataReceivedInt() const;
	void clearOUTDataReceivedInt();
	void killLastWrittenBank();
	bool isStalledInt() const;
	void clearStalledInt();
	bool isTransmitterReadyInt() const;
	void clearTransmitterReadyInt();
	bool isFlowErrorIntEnabled() const;
	void enableFlowErrorInt();
	void disableFlowErrorInt();
	bool isNAKINReceivedIntEnabled() const;
	void enableNAKINReceivedInt();
	void disableNAKINReceivedInt();
	bool isNAKOUTReceivedIntEnabled() const;
	void enableNAKOUTReceivedInt();
	void disableNAKOUTReceivedInt();
	bool isSETUPReceivedIntEnabled() const;
	void enableSETUPReceivedInt();
	void disableSETUPReceivedInt();
	bool isOUTDataReceivedIntEnabled() const;
	void enableOUTDataReceivedInt();
	void disableOUTDataReceivedInt();
	bool isStalledIntEnabled() const;
	void enableStalledInt();
	void disableStalledInt();
	bool isTransmitterReadyIntEnabled() const;
	void enableTransmitterReadyInt();
	void disableTransmitterReadyInt();
	UsbEndpoint& operator >> (unsigned char &uch);
	UsbEndpoint& operator >> (char &uch);
	UsbEndpoint& operator << (unsigned char uch);
	UsbEndpoint& operator << (char uch);
	unsigned int byteCount() const;
	bool isInt(unsigned char ep) const;
};

/**
 * @brief Return Endpoint Number value
 * @return Endpoint Number value
 */
inline unsigned char UsbEndpoint::number() const
{
	return REG(uenum);
}
/**
 * @brief Set Endpoint Number
 * @param[in] val New Endpoint Number value
 *
 * Load by software to select the number of the endpoint which shall be
 * accessed by the CPU.
 *
 * 0b111 is forbidden.
 */
inline void UsbEndpoint::setNumber(unsigned char val)
{
	REG(uenum) = val & 7;
}
/**
 * @brief Reset Endpoint %FIFO
 * @param[in] ep %FIFO Number
 *
 * Set to reset the selected endpoint %FIFO prior to any other operation,
 * upon hardware reset or when an USB bus reset has been received.
 */
inline void UsbEndpoint::resetEndpointFIFO(unsigned char ep)
{
	REG(uenum) |= _BV(ep);
	REG(uenum) &= ~_BV(ep);
}
/**
 * @brief Request STALL Handshake
 *
 * Set to request a STALL answer to the host for the next handshake.
 *
 * Cleared by hardware when a new SETUP is received. Clearing by software
 * has no effect.
 */
inline void UsbEndpoint::requestSTALL()
{
	REG_(ueconx).stallrq = true;
}
/**
 * @brief Return true, if a new SETUP is received
 * @return True, if a new SETUP is received
 */
inline bool UsbEndpoint::isSETUPReceived() const
{
	return ! REG_(ueconx).stallrq;
}
/**
 * @brief Disable STALL Handshake
 *
 * Set to disable the STALL handshake mechanism.
 *
 * Cleared by hardware immediately after the set. Clearing by software has
 * no effect.
 */
inline void UsbEndpoint::disableSTALLHandshake()
{
	REG_(ueconx).stallrqc = true;
}
/**
 * @brief Reset Data Toggle
 *
 * Set to automatically clear the data toggle sequence:
 *  * For OUT endpoint: the next received packet will have the data toggle 0.
 *  * For IN endpoint: the next packet to be sent will have the data toggle 0.
 *
 *  Cleared by hardware instantaneously. The firmware does not have to wait
 *  that the bit is cleared. Clearing by software has no effect.
 */
inline void UsbEndpoint::resetDataToggle()
{
	REG_(ueconx).rstdt = true;
}
/**
 * @brief Return true, if the Endpoint is enabled
 * @return True, if the Endpoint is enabled
 */
inline bool UsbEndpoint::isEnabled() const
{
	return REG_(ueconx).epen;
}
/**
 * @brief Enable the Endpoint
 *
 * Set to enable the endpoint according to the device configuration. Endpoint 0
 * shall always be enabled after a hardware or USB reset and participate in the
 * device configuration.
 */
inline void UsbEndpoint::enable()
{
	REG_(ueconx).epen = true;
}
/**
 * @brief Disable the Endpoint
 *
 * Endpoint 0 shall always be enabled after a hardware or USB reset and participate
 * in the device configuration.
 */
inline void UsbEndpoint::disable()
{
	REG_(ueconx).epen = false;
}
/**
 * @brief Set Endpoint Enable state
 * @param[in] val New state value
 */
inline void UsbEndpoint::setEnable(bool val)
{
	REG_(ueconx).epen = val;
}
/**
 * @brief Return Endpoint type
 * @return Endpoint type
 */
inline UsbEndpoint::Type UsbEndpoint::type() const
{
	return (Type) REG_(uecfg0x).eptype;
}
/**
 * @brief Set Endpoint type
 * @param[in] val New type value
 */
inline void UsbEndpoint::setType(Type val)
{
	REG_(uecfg0x).eptype = val;
}
/**
 * @brief Return Endpoint direction
 * @return Endpoint direction
 */
inline UsbEndpoint::Dir UsbEndpoint::direction() const
{
	return (Dir) REG_(uecfg0x).epdir;
}
/**
 * @brief Set Endpoint direction
 * @param[in] val New direction value
 */
inline void UsbEndpoint::setDirection(Dir val)
{
	REG_(uecfg0x).epdir = val;
}
/**
 * @brief Return Endpoint size
 * @return Endpoint size
 */
inline UsbEndpoint::Size UsbEndpoint::size() const
{
	return (Size) REG_(uecfg1x).epsize;
}
/**
 * @brief Set Endpoint size
 * @param[in] val New size value
 */
inline void UsbEndpoint::setSize(Size val)
{
	REG_(uecfg1x).epsize = val;
}
/**
 * @brief Return Endpoint bank
 * @return Endpoint bank
 */
inline UsbEndpoint::Bank UsbEndpoint::bank() const
{
	return (Bank) REG_(uecfg1x).epbk;
}
/**
 * @brief Set Endpoint bank
 * @param[in] val New bank value
 */
inline void UsbEndpoint::setBank(Bank val)
{
	REG_(uecfg1x).epbk = val;
}
/**
 * @brief Return true, if Endpoint memory allocated
 * @return True, if Endpoint memory allocated
 */
inline bool UsbEndpoint::isMemoryAllocated() const
{
	return REG_(uecfg1x).alloc;
}
/**
 * @brief Allocate Endpoint memory
 */
inline void UsbEndpoint::allocateMemory()
{
	REG_(uecfg1x).alloc = true;
}
/**
 * @brief Free Endpoint memory
 */
inline void UsbEndpoint::freeMemory()
{
	REG_(uecfg1x).alloc = false;
}
/**
 * @brief Return true, if Endpoint configuration is OK
 *
 * Set by hardware when the endpoint X size parameter UsbEndpoint::setSize() and
 * the bank parametrization UsbEndpoint::setBank() are correct compared to the max
 * %FIFO capacity and the max number of allowed bank.
 *
 * This bit is updated when Endpoint memory is allocated.
 *
 * If this bit is cleared, the user should reprogram Endpoint with correct size
 * value and bank number.
 * @see UsbEndpoint::allocateMemory()
 * @return True, if Endpoint configuration is OK
 */
inline bool UsbEndpoint::isConfigurationOK() const
{
	return REG_(uesta0x).cfgok;
}
/**
 * @brief Return true, if Overflow Error Interrupt Flag is set
 *
 * Set by hardware when an overflow error occurs in an isochronous endpoint. An
 * interrupt (EPINTx) is triggered (if enabled).
 *
 * Shall be cleared by software. Setting by software has no effect.
 * @see UsbEndpoint::clearOverflowErrorInt()
 * @return True, if Overflow Error Interrupt Flag is set
 */
inline bool UsbEndpoint::isOverflowErrorInt() const
{
	return REG_(uesta0x).overfi;
}
/**
 * @brief Clear Overflow Error Interrupt Flag
 */
inline void UsbEndpoint::clearOverflowErrorInt()
{
	REG_(uesta0x).overfi = false;
}
/**
 * @brief Return true, if Underflow Error Interrupt Flag is set
 *
 * Set by hardware when an underflow error occurs in an isochronous endpoint. An
 * interrupt (EPINTx) is triggered (if enabled).
 *
 * Shall be cleared by software. Setting by software has no effect.
 * @see UsbEndpoint::clearUnderflowErrorInt()
 * @return True, if Underflow Error Interrupt Flag is set
 */
inline bool UsbEndpoint::isUnderflowErrorInt() const
{
	return REG_(uesta0x).underfi;
}
/**
 * @brief Clear Underflow Error Interrupt Flag
 */
inline void UsbEndpoint::clearUnderflowErrorInt()
{
	REG_(uesta0x).underfi = false;
}
/**
 * @brief Return Data Toggle Sequencing Flag
 *
 * Set by hardware to indicate the PID data of the current bank:
 * - 0b00 Data0
 * - 0b01 Data1
 * - 0b1x Reserved.
 *
 * For OUT transfer, this value indicates the last data toggle received on the
 * current bank.
 *
 * For IN transfer, it indicates the Toggle that will be used for the next packet
 * to be sent. This is not relative to the current bank.
 * @return Data Toggle Sequencing Flag
 */
inline UsbEndpoint::PID UsbEndpoint::pid() const
{
	return (PID) REG_(uesta0x).dtseq;
}
/**
 * @brief Return Busy Bank Flag
 *
 * Set by hardware to indicate the number of busy bank.
 *
 * For IN endpoint, it indicates the number of busy bank(s), filled by the user,
 * ready for IN transfer.
 *
 * For OUT endpoint, it indicates the number of busy bank(s) filled by OUT transaction
 * from the host.
 * - 0b00 All banks are free
 * - 0b01 1 busy bank
 * - 0b10 2 busy banks
 * - 0b11 Reserved.
 * @return Busy Bank Flag
 */
inline UsbEndpoint::BusyBanks UsbEndpoint::busyBanks() const
{
	return (BusyBanks) REG_(uesta0x).nbusybk;
}
/**
 * @brief Return Control Direction (Flag, and bit for debug purpose)
 *
 * Set by hardware after a SETUP packet, and gives the direction of the following
 * packet:
 * - 1 for IN endpoint
 * - 0 for OUT endpoint.
 *
 * Can not be set or cleared by software.
 * @return Control Direction Flag
 */
inline UsbEndpoint::Dir UsbEndpoint::controlDirection() const
{
	return (Dir) REG_(uesta1x).ctrldir;
}
/**
 * @brief Return Current Bank Flag (all endpoints except Control endpoint)
 *
 * Set by hardware to indicate the number of the current bank:
 * - 0b00 Bank0
 * - 0b01 Bank1
 * - 0b1x Reserved.
 *
 * Can not be set or cleared by software.
 * @return Current Bank Flag
 */
inline UsbEndpoint::CurrBank UsbEndpoint::currentBank() const
{
	return (CurrBank) REG_(uesta1x).currbk;
}
/**
 * @brief Return true, if %FIFO Control Bit is set
 *
 * For OUT and SETUP Endpoint:
 * - Set by hardware when a new OUT message is stored in the current bank, at
 * the same time than RXOUT or RXSTP.
 * - Clear to free the current bank and to switch to the following bank.
 * Setting by software has no effect.
 *
 * For IN Endpoint:
 * - Set by hardware when the current bank is free, at the same time than TXIN.
 * - Clear to send the %FIFO data and to switch the bank. Setting by software has
 * no effect.
 * @see UsbEndpoint::clearFIFOControlInt()
 * @return True, if %FIFO Control Bit is set
 */
inline bool UsbEndpoint::isFIFOControlInt() const
{
	return REG_(ueintx).fifocon;
}
/**
 * @brief Clear %FIFO Control Bit
 */
inline void UsbEndpoint::clearFIFOControlInt()
{
	REG_(ueintx).fifocon = false;
}
/**
 * @brief Return true, if NAK IN Received Interrupt Flag is set
 *
 * Set by hardware when a NAK handshake has been sent in response of a IN request
 * from the host. This triggers an USB interrupt if NAKINE is sent.
 *
 * Shall be cleared by software. Setting by software has no effect.
 * @see UsbEndpoint::clearNAKINReceivedInt()
 * @return True, if NAK IN Received Interrupt Flag is set
 */
inline bool UsbEndpoint::isNAKINReceivedInt() const
{
	return REG_(ueintx).nakini;
}
/**
 * @brief Clear NAK IN Received Interrupt Flag
 */
inline void UsbEndpoint::clearNAKINReceivedInt()
{
	REG_(ueintx).nakini = false;
}
/**
 * @brief Return true, if Read/Write Allowed Flag is set
 *
 * Set by hardware to signal:
 * - for an IN endpoint: the current bank is not full i.e. the firmware can push
 * data into the %FIFO,
 * - for an OUT endpoint: the current bank is not empty, i.e. the firmware can read
 * data from the %FIFO.
 *
 * The bit is never set if STALLRQ is set, or in case of error.
 *
 * Cleared by hardware otherwise.
 *
 * This bit shall not be used for the control endpoint.
 * @return True, if Read/Write Allowed Flag is set
 */
inline bool UsbEndpoint::isReadWriteAllowed() const
{
	return REG_(ueintx).rwal;
}
/**
 * @brief Return true, if NAK OUT Received Interrupt Flag is set
 *
 * Set by hardware when a NAK handshake has been sent in response of a OUT/PING
 * request from the host. This triggers an USB interrupt if NAKOUTE is sent.
 *
 * Shall be cleared by software. Setting by software has no effect.
 * @see UsbEndpoint::clearNAKOUTReceivedInt()
 * @return True, if NAK OUT Received Interrupt Flag is set
 */
inline bool UsbEndpoint::isNAKOUTReceivedInt() const
{
	return REG_(ueintx).nakouti;
}
/**
 * @brief Clear NAK OUT Received Interrupt Flag
 */
inline void UsbEndpoint::clearNAKOUTReceivedInt()
{
	REG_(ueintx).nakouti = false;
}
/**
 * @brief Return true, if Received SETUP Interrupt Flag is set
 *
 * Set by hardware to signal that the current bank contains a new valid SETUP
 * packet. An interrupt (EPINTx) is triggered (if enabled).
 *
 * Shall be cleared by software to handshake the interrupt. Setting by software
 * has no effect.
 *
 * This bit is inactive (cleared) if the endpoint is an IN endpoint.
 * @see UsbEndpoint::clearSETUPReceivedInt()
 * @return True, if Received SETUP Interrupt Flag is set
 */
inline bool UsbEndpoint::isSETUPReceivedInt() const
{
	return REG_(ueintx).rxstpi;
}
/**
 * @brief Clear Received SETUP Interrupt Flag
 */
inline void UsbEndpoint::clearSETUPReceivedInt()
{
	REG_(ueintx).rxstpi = false;
}
/**
 * @brief Return true, if Received OUT Data Interrupt Flag is set
 *
 * Set by hardware to signal that the current bank contains a new packet. An interrupt
 * (EPINTx) is triggered (if enabled).
 *
 * Shall be cleared by software to handshake the interrupt. Setting by software has
 * no effect.
 * @see UsbEndpoint::clearOUTDataReceivedInt()
 * @return True, if Received OUT Data Interrupt Flag is set
 */
inline bool UsbEndpoint::isOUTDataReceivedInt() const
{
	return REG_(ueintx).rxouti;
}
/**
 * @brief Clear Received OUT Data Interrupt Flag
 */
inline void UsbEndpoint::clearOUTDataReceivedInt()
{
	REG_(ueintx).rxouti = false;
}
/**
 * @brief Kill last written bank.
 *
 * Cleared by hardware when the bank is killed. Clearing by software has no effect.
 */
inline void UsbEndpoint::killLastWrittenBank()
{
	REG_(ueintx).rxouti = false;
}
/**
 * @brief Return true, if STALLEDI Interrupt Flag is set
 *
 * Set by hardware to signal that a STALL handshake has been sent, or that a CRC
 * error has been detected in a OUT isochronous endpoint.
 *
 * Shall be cleared by software. Setting by software has no effect.
 * @see UsbEndpoint::clearStalledInt()
 * @return True, if STALLEDI Interrupt Flag is set
 */
inline bool UsbEndpoint::isStalledInt() const
{
	return REG_(ueintx).stalledi;
}
/**
 * @brief Clear STALLEDI Interrupt Flag
 */
inline void UsbEndpoint::clearStalledInt()
{
	REG_(ueintx).stalledi = false;
}
/**
 * @brief Return true, if Transmitter Ready Interrupt Flag is set
 *
 * Set by hardware to signal that the current bank is free and can be filled. An
 * interrupt (EPINTx) is triggered (if enabled).
 *
 * Shall be cleared by software to handshake the interrupt. Setting by software has
 * no effect.
 *
 * This bit is inactive (cleared) if the endpoint is an OUT endpoint.
 * @see UsbEndpoint::clearTransmitterReadyInt()
 * @return True, if Transmitter Ready Interrupt Flag is set
 */
inline bool UsbEndpoint::isTransmitterReadyInt() const
{
	return REG_(ueintx).txini;
}
/**
 * @brief Clear Transmitter Ready Interrupt Flag
 */
inline void UsbEndpoint::clearTransmitterReadyInt()
{
	REG_(ueintx).txini = false;
}
/**
 * @brief Return true, if Flow Error Interrupt Enable Flag is set
 *
 * Call UsbEndpoint::enableFlowErrorInt() to enable an endpoint interrupt (EPINTx)
 * when OVERFI or UNDERFI are sent.
 *
 * Call UsbEndpoint::disableFlowErrorInt() to disable an endpoint interrupt
 * (EPINTx) when OVERFI or UNDERFI are sent.
 * @return True, if Flow Error Interrupt Enable Flag is set
 */
inline bool UsbEndpoint::isFlowErrorIntEnabled() const
{
	return REG_(ueienx).flerre;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when OVERFI or UNDERFI are sent
 */
inline void UsbEndpoint::enableFlowErrorInt()
{
	REG_(ueienx).flerre = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when OVERFI or UNDERFI are sent
 */
inline void UsbEndpoint::disableFlowErrorInt()
{
	REG_(ueienx).flerre = false;
}
/**
 * @brief Return true, if NAK IN Interrupt Enable Bit is set
 *
 * Call UsbEndpoint::enableNAKINReceivedInt() to enable an endpoint interrupt
 * (EPINTx) when NAKINI is set.
 *
 * Call UsbEndpoint::disableNAKINReceivedInt() to disable an endpoint interrupt
 * (EPINTx) when NAKINI is set.
 * @return True, if NAK IN Interrupt Enable Bit is set
 */
inline bool UsbEndpoint::isNAKINReceivedIntEnabled() const
{
	return REG_(ueienx).nakine;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when NAKINI is set
 */
inline void UsbEndpoint::enableNAKINReceivedInt()
{
	REG_(ueienx).nakine = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when NAKINI is set
 */
inline void UsbEndpoint::disableNAKINReceivedInt()
{
	REG_(ueienx).nakine = false;
}
/**
 * @brief Return true, if NAK OUT Interrupt Enable Bit is set
 *
 * Call UsbEndpoint::enableNAKOUTReceivedInt() to enable an endpoint
 * interrupt (EPINTx) when NAKOUTI is set.
 *
 * Call UsbEndpoint::disableNAKOUTReceivedInt() to disable an endpoint
 * interrupt (EPINTx) when NAKOUTI is set.
 * @return True, if NAK OUT Interrupt Enable Bit is set
 */
inline bool UsbEndpoint::isNAKOUTReceivedIntEnabled() const
{
	return REG_(ueienx).nakoute;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when NAKOUTI is set
 */
inline void UsbEndpoint::enableNAKOUTReceivedInt()
{
	REG_(ueienx).nakoute = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when NAKOUTI is set
 */
inline void UsbEndpoint::disableNAKOUTReceivedInt()
{
	REG_(ueienx).nakoute = false;
}
/**
 * @brief Return true, if Received SETUP Interrupt Enable Flag is set
 *
 * Call UsbEndpoint::enableSETUPReceivedInt() to enable an endpoint
 * interrupt (EPINTx) when RXSTPI is sent.
 *
 * Call UsbEndpoint::disableSETUPReceivedInt() to disable an endpoint
 * interrupt (EPINTx) when RXSTPI is sent.
 * @return True, if Received SETUP Interrupt Enable Flag is set
 */
inline bool UsbEndpoint::isSETUPReceivedIntEnabled() const
{
	return REG_(ueienx).rxstpe;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when RXSTPI is sent
 */
inline void UsbEndpoint::enableSETUPReceivedInt()
{
	REG_(ueienx).rxstpe = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when RXSTPI is sent
 */
inline void UsbEndpoint::disableSETUPReceivedInt()
{
	REG_(ueienx).rxstpe = false;
}
/**
 * @brief Return true, if Received OUT Data Interrupt Enable Flag is set
 *
 * Call UsbEndpoint::enableOUTDataReceivedInt() to enable an endpoint
 * interrupt (EPINTx) when RXOUTI is sent.
 *
 * Call UsbEndpoint::disableOUTDataReceivedInt() to disable an endpoint
 * interrupt (EPINTx) when RXOUTI is sent.
 * @return True, if Received OUT Data Interrupt Enable Flag is set
 */
inline bool UsbEndpoint::isOUTDataReceivedIntEnabled() const
{
	return REG_(ueienx).rxoute;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when RXOUTI is sent
 */
inline void UsbEndpoint::enableOUTDataReceivedInt()
{
	REG_(ueienx).rxoute = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when RXOUTI is sent
 */
inline void UsbEndpoint::disableOUTDataReceivedInt()
{
	REG_(ueienx).rxoute = false;
}
/**
 * @brief Return true, if Stalled Interrupt Enable Flag is set
 *
 * Call UsbEndpoint::enableStalledInt() to enable an endpoint interrupt
 * (EPINTx) when STALLEDI is sent.
 *
 * Call UsbEndpoint::disableStalledInt() to disable an endpoint interrupt
 * (EPINTx) when STALLEDI is sent.
 * @return True, if Stalled Interrupt Enable Flag is set
 */
inline bool UsbEndpoint::isStalledIntEnabled() const
{
	return REG_(ueienx).stallede;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when STALLEDI is sent
 */
inline void UsbEndpoint::enableStalledInt()
{
	REG_(ueienx).stallede = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when STALLEDI is sent
 */
inline void UsbEndpoint::disableStalledInt()
{
	REG_(ueienx).stallede = false;
}
/**
 * @brief Return true, if Transmitter Ready Interrupt Enable Flag is set
 *
 * Call UsbEndpoint::enableTransmitterReadyInt() to enable an endpoint interrupt (EPINTx) when TXINI is sent.
 *
 * Call UsbEndpoint::disableTransmitterReadyInt() to disable an endpoint interrupt (EPINTx) when TXINI is sent.
 * @return True, if Transmitter Ready Interrupt Enable Flag is set
 */
inline bool UsbEndpoint::isTransmitterReadyIntEnabled() const
{
	return REG_(ueienx).txine;
}
/**
 * @brief Enable an endpoint interrupt (EPINTx) when TXINI is sent
 */
inline void UsbEndpoint::enableTransmitterReadyInt()
{
	REG_(ueienx).txine = true;
}
/**
 * @brief Disable an endpoint interrupt (EPINTx) when TXINI is sent
 */
inline void UsbEndpoint::disableTransmitterReadyInt()
{
	REG_(ueienx).txine = false;
}
/**
 * @brief Stream unsigned character from %FIFO selected by EPNUM
 * @param[out] uch Reference to unsigned character variable
 * @return Reference to this UsbEndpoint
 */
inline UsbEndpoint& UsbEndpoint::operator >> (unsigned char &uch)
{
	uch = REG(uedatx);
	return (*this);
}
/**
 * @brief Stream character from %FIFO selected by EPNUM
 * @param[out] uch Reference to character variable
 * @return Reference to this UsbEndpoint
 */
inline UsbEndpoint& UsbEndpoint::operator >> (char &uch)
{
	uch = REG(uedatx);
	return (*this);
}
/**
 * @brief Stream unsigned character to %FIFO selected by EPNUM
 * @param[in] uch Unsigned character value
 * @return Reference to this UsbEndpoint
 */
inline UsbEndpoint& UsbEndpoint::operator << (unsigned char uch)
{
	REG(uedatx) = uch;
	return (*this);
}
/**
 * @brief Stream character to %FIFO selected by EPNUM
 * @param[in] ch Character value
 * @return Reference to this UsbEndpoint
 */
inline UsbEndpoint& UsbEndpoint::operator << (char ch)
{
	REG(uedatx) = ch;
	return (*this);
}
/**
 * @brief Return Byte count of the %FIFO
 *
 * Set by the hardware. BYCT[10:0] is:
 * - (for IN endpoint) increased after each writing into the endpoint
 * and decremented after each byte sent,
 * - (for OUT endpoint) increased after each byte sent by the host, and
 * decremented after each byte read by the software.
 * @return Byte count of the %FIFO
 */
inline unsigned int UsbEndpoint::byteCount() const
{
	return REGW(uebcx);
}
/**
 * @brief Return true, if Endpoint Interrupt Bit is set
 *
 * Set by hardware when an interrupt is triggered by the UEINTX register
 * and if the corresponding endpoint interrupt enable bit is set.
 *
 * Cleared by hardware when the interrupt source is served.
 * @param[in] ep Interrupt number
 * @return True, if Endpoint Interrupt Bit is set
 */
inline bool UsbEndpoint::isInt(unsigned char ep) const
{
	return REG(ueint) & _BV(ep);
}

#endif /* USBDEVEP_H_ */
