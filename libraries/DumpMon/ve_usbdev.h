/**
 * @file ve_usbdev.h
 * @brief USB Device Header
 * @author andrey
 * @date 09.12.2012
 * @copyright GNU Public License
 */
#ifndef USBDEV_H_
#define USBDEV_H_

/**
 * @brief USB Device class
 * @ingroup USB
 */
class UsbDevice : public AVR_USBDEV
{
public:
	/**
	 * @brief Mode type
	 */
	typedef enum {
		FullSpeed  = 0,		///< Full Speed Mode
		LowSpeed   = 1		///< Low Speed Mode
	} Mode;
public:
	bool isResetCPUEnabled() const;
	void enableResetCPU();
	void disableResetCPU();
	void setResetCPUEnable(bool val);

	Mode mode() const;
	void setMode(Mode val);

	void remoteWakeUp();
	bool isSentRemoteWakepUp() const;

	bool isDetached() const;
	void detach();
	void connect();

	bool upstreamResumeInt() const;
	void clearUpstreamResumeInt();

	bool endOfResumeInt() const;
	void clearEndOfResumeInt();

	bool wakeupCPUInt() const;
	void clearWakeupCPUInt();

	bool endOfResetInt() const;
	void clearEndOfResetInt();

	bool startOfFrameInt() const;

	bool suspendInt() const;
	void clearSuspendInt();

	bool isUpstreamResumeIntEnabled() const;
	void enableUpstreamResumeInt();
	void disableUpstreamResumeInt();
	void setUpstreamResumeIntEnable(bool val);

	bool isEndOfResumeIntEnabled() const;
	void enableEndOfResumeInt();
	void disableEndOfResumeInt();
	void setEndOfResumeIntEnable(bool val);

	bool isWakeupCPUIntEnabled() const;
	void enableWakeupCPUInt();
	void disableWakeupCPUInt();
	void setWakeupCPUIntEnable(bool val);

	bool isEndOfResetIntEnabled() const;
	void enableEndOfResetInt();
	void disableEndOfResetInt();
	void setEndOfResetIntEnable(bool val);

	bool isStartOfFrameIntEnabled() const;
	void enableStartOfFrameInt();
	void disableStartOfFrameInt();
	void setStartOfFrameIntEnable(bool val);

	bool isSuspendIntEnabled() const;
	void enableSuspendInt();
	void disableSuspendInt();
	void setSuspendIntEnable(bool val);

	bool isAddressEnabled() const;
	void enableAddress();

	unsigned char address() const;
	void setAddress(unsigned char val);

	unsigned int frameNumber() const;

	bool isFrameNumberCRCError() const;
};

/**
 * @brief Return true, if CPU Reset is enabled
 * @return True, if CPU Reset is enabled
 */
inline bool UsbDevice::isResetCPUEnabled() const
{
	return REG_(udcon).rstcpu;
}
/**
 * @brief Enable CPU Reset
 */
inline void UsbDevice::enableResetCPU()
{
	REG_(udcon).rstcpu = true;
}
/**
 * @brief Disable CPU Reset
 */
inline void UsbDevice::disableResetCPU()
{
	REG_(udcon).rstcpu = false;
}
/**
 * @brief Set CPU Reset Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setResetCPUEnable(bool val)
{
	REG_(udcon).rstcpu = val;
}
/**
 * @brief Return Mode value
 * @return Mode value
 */
inline UsbDevice::Mode UsbDevice::mode() const
{
	return (Mode) REG_(udcon).lsm;
}
/**
 * @brief Set Mode
 * @param[in] val New Mode value
 */
inline void UsbDevice::setMode(Mode val)
{
	REG_(udcon).lsm = val;
}
/**
 * @brief Send an “upstream-resume” to the host for a remote wake-up
 *
 * Set to send an “upstream-resume” to the host for a remote wake-up
 * (the SUSPI bit must be set).
 *
 * Cleared by hardware when signalling finished. Clearing by software
 * has no effect.
 */
inline void UsbDevice::remoteWakeUp()
{
	REG_(udcon).rmwkup = true;
}
/**
 * @brief Return true, if “upstream-resume” to the host has been sent
 * @return True, if “upstream-resume” to the host has been sent
 *
 * Cleared by hardware. Clearing by software has no effect.
 * @sa UsbDevice::remoteWakeUp()
 */
inline bool UsbDevice::isSentRemoteWakepUp() const
{
	return ! REG_(udcon).rmwkup;
}
/**
 * @brief Return true, if Detach Bit is set
 * @return True, if Detach Bit is set
 */
inline bool UsbDevice::isDetached() const
{
	return REG_(udcon).detach;
}
/**
 * @brief Set Detach Bit
 *
 * Set to physically detach the device (disconnect internal pull-up
 * on D+ or D-).
 */
inline void UsbDevice::detach()
{
	REG_(udcon).detach = true;
}
/**
 * @brief Clear Detach Bit
 *
 * Clear to reconnect the device.
 */
inline void UsbDevice::connect()
{
	REG_(udcon).detach = false;
}
/**
 * @brief Return true, if Upstream Resume Interrupt Flag is set
 * @return True, if Upstream Resume Interrupt Flag is set
 */
inline bool UsbDevice::upstreamResumeInt() const
{
	return REG_(udint).uprsmi;
}
/**
 * @brief Clear Upstream Resume Interrupt Flag
 *
 * Set by hardware when the USB controller is sending a resume signal
 * called “Upstream Resume”. This triggers an USB interrupt if UPRSME
 * is set.
 *
 * Shall be cleared by software (USB clocks must be enabled before).
 * Setting by software has no effect.
 */
inline void UsbDevice::clearUpstreamResumeInt()
{
	REG_(udint).uprsmi = false;
}
/**
 * @brief Return true, if End Of Resume Interrupt Flag is set
 * @return True, if End Of Resume Interrupt Flag is set
 */
inline bool UsbDevice::endOfResumeInt() const
{
	return REG_(udint).eorsmi;
}
/**
 * @brief Clear End Of Resume Interrupt Flag
 *
 * Set by hardware when the USB controller detects a good “End Of Resume”
 * signal initiated by the host. This triggers an USB interrupt if EORSME
 * is set.
 *
 * Shall be cleared by software. Setting by software has no effect.
 */
inline void UsbDevice::clearEndOfResumeInt()
{
	REG_(udint).eorsmi = false;
}
/**
 * @brief Return true, if Wake-up CPU Interrupt Flag is set
 * @return True, if Wake-up CPU Interrupt Flag is set
 */
inline bool UsbDevice::wakeupCPUInt() const
{
	return REG_(udint).wakeupi;
}
/**
 * @brief Clear Wake-up CPU Interrupt Flag
 *
 * Set by hardware when the USB controller is re-activated by a filtered
 * non-idle signal from the lines (not by an upstream resume). This
 * triggers an interrupt if WAKEUPE is set.
 *
 * Shall be cleared by software (USB clock inputs must be enabled before).
 * Setting by software has no effect.
 */
inline void UsbDevice::clearWakeupCPUInt()
{
	REG_(udint).wakeupi = false;
}
/**
 * @brief Return true, if End Of Reset Interrupt Flag is set
 * @return True, if End Of Reset Interrupt Flag is set
 */
inline bool UsbDevice::endOfResetInt() const
{
	return REG_(udint).eorsti;
}
/**
 * @brief Clear End Of Reset Interrupt Flag
 *
 * Set by hardware when an “End Of Reset” has been detected by the USB
 * controller. This triggers an USB interrupt if EORSTE is set.
 *
 * Shall be cleared by software. Setting by software has no effect.
 */
inline void UsbDevice::clearEndOfResetInt()
{
	REG_(udint).eorsti = false;
}
/**
 * @brief Return true, if Start Of Frame Interrupt Flag is set
 * @return True, if Start Of Frame Interrupt Flag is set
 *
 * Set by hardware when an USB “Start Of Frame” PID (SOF) has been detected
 * (every 1 ms). This triggers an USB interrupt if SOFE is set.
 */
inline bool UsbDevice::startOfFrameInt() const
{
	return REG_(udint).sofi;
}
/**
 * @brief Return true, if Suspend Interrupt Flag is set
 * @return True, if Suspend Interrupt Flag is set
 */
inline bool UsbDevice::suspendInt() const
{
	return REG_(udint).suspi;
}
/**
 * @brief Clear Suspend Interrupt Flag
 *
 * Set by hardware when an USB “Suspend” ‘idle bus for 3 frame periods:
 * a J state for 3 ms) is detected. This triggers an USB interrupt if
 * SUSPE is set.
 *
 * Shall be cleared by software. Setting by software has no effect.
 */
inline void UsbDevice::clearSuspendInt()
{
	REG_(udint).suspi = false;
}
/**
 * @brief Return true, if Upstream Resume Interrupt is enabled
 * @return True, if Upstream Resume Interrupt is enabled
 */
inline bool UsbDevice::isUpstreamResumeIntEnabled() const
{
	return REG_(udien).uprsme;
}
/**
 * @brief Enable Upstream Resume Interrupt
 */
inline void UsbDevice::enableUpstreamResumeInt()
{
	REG_(udien).uprsme = true;
}
/**
 * @brief Disable Upstream Resume Interrupt
 */
inline void UsbDevice::disableUpstreamResumeInt()
{
	REG_(udien).uprsme = false;
}
/**
 * @brief Set Upstream Resume Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setUpstreamResumeIntEnable(bool val)
{
	REG_(udien).uprsme = val;
}
/**
 * @brief Return true, if End Of Resume Interrupt is enabled
 * @return True, if End Of Resume Interrupt is enabled
 */
inline bool UsbDevice::isEndOfResumeIntEnabled() const
{
	return REG_(udien).eorsme;
}
/**
 * @brief Enable End Of Resume Interrupt
 */
inline void UsbDevice::enableEndOfResumeInt()
{
	REG_(udien).eorsme = true;
}
/**
 * @brief Disable End Of Resume Interrupt
 */
inline void UsbDevice::disableEndOfResumeInt()
{
	REG_(udien).eorsme = false;
}
/**
 * @brief Set End Of Resume Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setEndOfResumeIntEnable(bool val)
{
	REG_(udien).eorsme = val;
}
/**
 * @brief Return true, if Wake-up CPU Interrupt is enabled
 * @return True, if Wake-up CPU Interrupt is enabled
 */
inline bool UsbDevice::isWakeupCPUIntEnabled() const
{
	return REG_(udien).wakeupe;
}
/**
 * @brief Enable Wake-up CPU Interrupt
 */
inline void UsbDevice::enableWakeupCPUInt()
{
	REG_(udien).wakeupe = true;
}
/**
 * @brief Disable Wake-up CPU Interrupt
 */
inline void UsbDevice::disableWakeupCPUInt()
{
	REG_(udien).wakeupe = false;
}
/**
 * @brief Set Wake-up CPU Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setWakeupCPUIntEnable(bool val)
{
	REG_(udien).wakeupe = val;
}
/**
 * @brief Return true, if End Of Reset Interrupt is enabled
 * @return True, if End Of Reset Interrupt is enabled
 */
inline bool UsbDevice::isEndOfResetIntEnabled() const
{
	return REG_(udien).eorste;
}
/**
 * @brief Enable End Of Reset Interrupt
 */
inline void UsbDevice::enableEndOfResetInt()
{
	REG_(udien).eorste = true;
}
/**
 * @brief Disable End Of Reset Interrupt
 */
inline void UsbDevice::disableEndOfResetInt()
{
	REG_(udien).eorste = false;
}
/**
 * @brief Set End Of Reset Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setEndOfResetIntEnable(bool val)
{
	REG_(udien).eorste = val;
}
/**
 * @brief Return true, if Start Of Frame Interrupt is enabled
 * @return True, if Start Of Frame Interrupt is enabled
 */
inline bool UsbDevice::isStartOfFrameIntEnabled() const
{
	return REG_(udien).sofe;
}
/**
 * @brief Enable Start Of Frame Interrupt
 */
inline void UsbDevice::enableStartOfFrameInt()
{
	REG_(udien).sofe = true;
}
/**
 * @brief Disable Start Of Frame Interrupt
 */
inline void UsbDevice::disableStartOfFrameInt()
{
	REG_(udien).sofe = false;
}
/**
 * @brief Set Start Of Frame Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setStartOfFrameIntEnable(bool val)
{
	REG_(udien).sofe = val;
}
/**
 * @brief Return true, if Suspend Interrupt is enabled
 * @return True, if Suspend Interrupt is enabled
 */
inline bool UsbDevice::isSuspendIntEnabled() const
{
	return REG_(udien).suspe;
}
/**
 * @brief Enable Suspend Interrupt
 */
inline void UsbDevice::enableSuspendInt()
{
	REG_(udien).suspe = true;
}
/**
 * @brief Disable Suspend Interrupt
 */
inline void UsbDevice::disableSuspendInt()
{
	REG_(udien).suspe = false;
}
/**
 * @brief Set Suspend Interrupt Enable state
 * @param[in] val New state value
 */
inline void UsbDevice::setSuspendIntEnable(bool val)
{
	REG_(udien).suspe = val;
}
/**
 * @brief Return true, if USB Address is enabled
 * @return True, if USB Address is enabled
 */
inline bool UsbDevice::isAddressEnabled() const
{
	return REG_(udaddr).adden;
}
/**
 * @brief Enable USB Address
 *
 * Set to activate the UADD (USB address).
 *
 * Cleared by hardware. Clearing by software has no effect.
 */
inline void UsbDevice::enableAddress()
{
	REG_(udaddr).adden = true;
}
/**
 * @brief Return USB Address value
 * @return USB Address value
 */
inline unsigned char UsbDevice::address() const
{
	return REG_(udaddr).uadd;
}
/**
 * @brief Set USB Address
 * @param[in] val New USB Address value
 */
inline void UsbDevice::setAddress(unsigned char val)
{
	REG_(udaddr).uadd = val;
}
/**
 * @brief Return Frame Number value
 * @return Frame Number value
 *
 * Set by hardware. These bits are the 11-bits Frame Number
 * information. They are provided in the last received SOF
 * packet. FNUM is updated if a corrupted SOF is received.
 */
inline unsigned int UsbDevice::frameNumber() const
{
	return REGW(udfnum);
}
/**
 * @brief Return true, if Frame Number CRC Error Flag is set
 * @return True, if Frame Number CRC Error Flag is set
 *
 * Set by hardware when a corrupted Frame Number in start of frame
 * packet is received.
 *
 * This bit and the SOFI interrupt are updated at the same time.
 */
inline bool UsbDevice::isFrameNumberCRCError() const
{
	return REG_(udmfn).fncerr;
}

#endif /* USBDEV_H_ */
