/**
 * @file ve_usbgen.h
 * @brief USB General Class Header
 * @author andrey
 * @date 09.12.2012
 * @copyright GNU Public License
 */
#ifndef USBGEN_H_
#define USBGEN_H_

/**
 *  @brief USB General class.
 *  @ingroup USB
 */
class UsbGen : public AVR_USBGEN
{
public:
	bool isPadRegEnabled() const;
	void enablePadReg();
	void disablePadReg();
	bool isEnabled() const;
	void enable();
	void disable();
	bool isClockDisabled() const;
	void disableClock();
	void enableClock();
	bool isPadEnabled() const;
	void enablePad();
	void disablePad();
	bool isTransIntEnabled() const;
	void enableTransInt();
	void disableTransInt();
	bool idStatus() const;
	bool vbus() const;
	bool isTransitionInt() const;
	void clearTransitionInt();
};
/**
 * @brief Return true, if USB pad regulator is enabled
 * @return True, if USB pad regulator is enabled
 */
inline bool UsbGen::isPadRegEnabled() const
{
	return REG_(uhwcon).uvrege;
}
/**
 * @brief Enable USB pad regulator
 */
inline void UsbGen::enablePadReg()
{
	REG_(uhwcon).uvrege = true;
}
/**
 * @brief Disable USB pad regulator
 */
inline void UsbGen::disablePadReg()
{
	REG_(uhwcon).uvrege = false;
}
/**
 * @brief Return true, if USB controller is enabled
 *
 * Call UsbGen::enable() to enable the USB controller.
 *
 * Call UsbGen::disable() to disable and reset the USB controller, to disable the USB
 * transceiver and to disable the USB controller clock inputs.
 * @return True, if USB controller is enabled
 */
inline bool UsbGen::isEnabled() const
{
	return REG_(usbcon).usbe;
}
/**
 * @brief Enable USB controller
 */
inline void UsbGen::enable()
{
	REG_(usbcon).usbe = true;
}
/**
 * @brief Disable USB controller
 */
inline void UsbGen::disable()
{
	REG_(usbcon).usbe = false;
}
/**
 * @brief Return true, if USB clock freezed
 *
 * Call UsbGen::disableClock() to disable the clock inputs (the ”Resume
 * Detection” is still active). This reduces the power consumption.
 *
 * Call UsbGen::enableClock() to enable the clock inputs.
 * @return True, if USB clock freezed
 */
inline bool UsbGen::isClockDisabled() const
{
	return REG_(usbcon).frzclk;
}
/**
 * @brief Freeze USB clock
 */
inline void UsbGen::disableClock()
{
	REG_(usbcon).frzclk = true;
}
/**
 * @brief Enable USB clock
 */
inline void UsbGen::enableClock()
{
	REG_(usbcon).frzclk = false;
}
/**
 * @brief Return true, if VBUS pad is enabled
 *
 * Note that this bit can be set/cleared even if UsbGen::isEnabled()==false.
 *
 * That allows the VBUS detection even if the USB controller is disabled.
 * @return True, if VBUS pad is enabled
 */
inline bool UsbGen::isPadEnabled() const
{
	return REG_(usbcon).otgpade;
}
/**
 * @brief Enable VBUS pad
 */
inline void UsbGen::enablePad()
{
	REG_(usbcon).otgpade = true;
}
/**
 * @brief Disable VBUS pad
 */
inline void UsbGen::disablePad()
{
	REG_(usbcon).otgpade = false;
}
/**
 * @brief Return true, if VBUS Transition Interrupt Enable Bit is set
 *
 * Call UsbGen::enableTransInt() to enable the VBUS Transition interrupt
 * generation.
 *
 * Call UsbGen::disableTransInt() to disable the VBUS Transition interrupt
 * generation.
 * @return True, if VBUS Transition Interrupt Enable Bit is set
 */
inline bool UsbGen::isTransIntEnabled() const
{
	return REG_(usbcon).vbuste;
}
/**
 * @brief Enable the VBUS Transition interrupt generation
 */
inline void UsbGen::enableTransInt()
{
	REG_(usbcon).vbuste = true;
}
/**
 * @brief Disable the VBUS Transition interrupt generation
 */
inline void UsbGen::disableTransInt()
{
	REG_(usbcon).vbuste = false;
}
/**
 * @brief Return ID status
 *
 * This bit is always read as “1”, it has been conserved for compatibility with
 * AT90USB64/128 (in which it indicates the value of the OTG ID pin).
 * @return ID status
 */
inline bool UsbGen::idStatus() const
{
	return REG_(usbsta).id;
}
/**
 * @brief Return true, if VBUS Flag is set
 *
 * The value read from this bit indicates the state of the VBUS pin.
 *
 * This bit can be used in device mode to monitor the USB bus connection state
 * of the application.
 * @return True, if VBUS Flag is set
 */
inline bool UsbGen::vbus() const
{
	return REG_(usbsta).vbus;
}
/**
 * @brief Return true, if IVBUS Transition Interrupt Flag is set
 *
 * Set by hardware when a transition (high to low, low to high) has been detected
 * on the VBUS pad.
 *
 * Shall be cleared by software.
 * @see UsbGen::clearTransitionInt()
 * @return True, if IVBUS Transition Interrupt Flag is set
 */
inline bool UsbGen::isTransitionInt() const
{
	return REG_(usbint).vbusti;
}
/**
 * @brief Clear IVBUS Transition Interrupt Flag
 */
inline void UsbGen::clearTransitionInt()
{
	REG_(usbint).vbusti = false;
}


#endif /* USBGEN_H_ */
