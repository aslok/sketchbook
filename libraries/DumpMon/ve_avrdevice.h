/**
 * @file ve_avrdevice.h
 * @brief AVR8 Devices Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef AVRDEVICE_H_
#define AVRDEVICE_H_

/**
 * @addtogroup Devices
 * @{
 */

#define PDEV	((AVRP_DEV) 0x20)									///< Pointer to the Device structure
#define DEV		(*PDEV)												///< Reference to the Device structure

#define DEV_GPIOA		OBJ((GPIO*) &(DEV.gpioa))					///< Reference to the General Purpose I/O Port A
#define DEV_GPIOB		OBJ((GPIO*) &(DEV.gpiob))					///< Reference to the General Purpose I/O Port B
#define DEV_GPIOC		OBJ((GPIO*) &(DEV.gpioc))					///< Reference to the General Purpose I/O Port C
#define DEV_GPIOD		OBJ((GPIO*) &(DEV.gpiod))					///< Reference to the General Purpose I/O Port D
#define DEV_GPIOE		OBJ((GPIO*) &(DEV.gpioe))					///< Reference to the General Purpose I/O Port E
#define DEV_GPIOF		OBJ((GPIO*) &(DEV.gpiof))					///< Reference to the General Purpose I/O Port F
#define DEV_GPIOG		OBJ((GPIO*) &(DEV.gpiog))					///< Reference to the General Purpose I/O Port G
#define DEV_GPIOH		OBJ((GPIO*) &(DEV.gpioh))					///< Reference to the General Purpose I/O Port H
#define DEV_GPIOJ		OBJ((GPIO*) &(DEV.gpioj))					///< Reference to the General Purpose I/O Port J
#define DEV_GPIOK		OBJ((GPIO*) &(DEV.gpiok))					///< Reference to the General Purpose I/O Port K
#define DEV_GPIOL		OBJ((GPIO*) &(DEV.gpiol))					///< Reference to the General Purpose I/O Port L
#define DEV_USART0		OBJ((_Usart*) &(DEV.usart0))				///< Reference to the USART 0
#define DEV_USART1		OBJ((_Usart*) &(DEV.usart1))				///< Reference to the USART 1
#define DEV_USART2		OBJ((_Usart*) &(DEV.usart2))				///< Reference to the USART 2
#define DEV_USART3		OBJ((_Usart*) &(DEV.usart3))				///< Reference to the USART 3
#define DEV_SREG		OBJ((AVRP_SREG) &(DEV.sreg))				///< Reference to the Status Register
#define DEV_TIMER0		OBJ((Timer0*) &(DEV.timer0))				///< Reference to the Timer/Counter 0

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
#define DEV_TICTRL0		OBJ((TimerIntCtrl*) &(DEV.timsk0))			///< Reference to the Timer Interrupt Control 0
#define DEV_TICTRL1		OBJ((TimerIntCtrlW*) &(DEV.timsk1))			///< Reference to the Timer Interrupt Control 1
#define DEV_TICTRL2		OBJ((TimerIntCtrl*) &(DEV.timsk2))			///< Reference to the Timer Interrupt Control 2
#define DEV_POWER		OBJ((Power*) &(DEV.power))					///< Reference to the Power Reduction Control
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32)
#define DEV_TICTRL0		OBJ((TimerIntCtrl0*) &(DEV.timsk0))			///< Reference to the Timer Interrupt Control 0
#define DEV_TICTRL2		OBJ((TimerIntCtrl2*) &(DEV.timsk0))			///< Reference to the Timer Interrupt Control 2
#define DEV_TWICTRL		OBJ((TWIControl*) &(DEV.twcr))				///< Reference to the TWI Control
#endif

#define DEV_TIFLAGS0	OBJ((TimerIntFlags*) &(DEV.tifr0))			///< Reference to the Timer Interrupt Flags 0
#define DEV_TIMER1		OBJ((TimerW*) &(DEV.timer1))				///< Reference to the Timer/Counter 1
#define DEV_TIFLAGS1	OBJ((TimerIntFlagsW*) &(DEV.tifr1))			///< Reference to the Timer Interrupt Flags 1
#define DEV_TIMER2		OBJ((Timer2*) &(DEV.timer2))				///< Reference to the Timer/Counter 2
#define DEV_TIFLAGS2	OBJ((TimerIntFlags*) &(DEV.tifr2))			///< Reference to the Timer Interrupt Flags 2
#define DEV_TIMER3		OBJ((TimerW*) &(DEV.timer3))				///< Reference to the Timer/Counter 3
#define DEV_TICTRL3		OBJ((TimerIntCtrlW*) &(DEV.timsk3))			///< Reference to the Timer Interrupt Control 3
#define DEV_TIFLAGS3	OBJ((TimerIntFlagsW*) &(DEV.tifr3))			///< Reference to the Timer Interrupt Flags 3

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560)
#define DEV_TIMER4		OBJ((TimerW*) &(DEV.timer4))				///< Reference to the Timer/Counter 4
#define DEV_TICTRL4		OBJ((TimerIntCtrlW*) &(DEV.timsk4))			///< Reference to the Timer Interrupt Control 4
#define DEV_TIFLAGS4	OBJ((TimerIntFlagsW*) &(DEV.tifr4))			///< Reference to the Timer Interrupt Flags 4
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
#define DEV_TIMER4		OBJ((TimerHS*) &(DEV.timer4))				///< Reference to the Timer/Counter 4
#define DEV_TICTRL4		OBJ((TimerIntCtrlHS*) &(DEV.timsk4))		///< Reference to the Timer Interrupt Control 4
#define DEV_TIFLAGS4	OBJ((TimerIntFlagsHS*) &(DEV.tifr4))		///< Reference to the Timer Interrupt Flags 4
#endif

#define DEV_TIMER5		OBJ((TimerW*) &(DEV.timer5))				///< Reference to the Timer/Counter 5
#define DEV_TICTRL5		OBJ((TimerIntCtrlW*) &(DEV.timsk5))			///< Reference to the Timer Interrupt Control 5
#define DEV_TIFLAGS5	OBJ((TimerIntFlagsW*) &(DEV.tifr5))			///< Reference to the Timer Interrupt Flags 5
#define DEV_ADC     	OBJ((ADConv*) &(DEV.amux))					///< Reference to the ADC
#define DEV_ANAMUX		OBJ((AnalogMux*) &(DEV.amux))				///< Reference to the Analog Comparator Multiplexer
#define DEV_ANACOMP		OBJ((AnalogComp*) &(DEV.anacomp))			///< Reference to the Analog Comparator
#define DEV_ASYNCST		OBJ((AsyncStatus*) &(DEV.asyncst))			///< Reference to the Asynchronous Status
#define DEV_EEPROM		OBJ((EEPROM*) &(DEV.eeprom))				///< Reference to the EEPROM
#define DEV_SPM			OBJ((StoreProgMem*) &(DEV.spm))				///< Reference to the Store Program Memory
#define DEV_EXTINTCTRL	OBJ((ExtIntControl*) &(DEV.extintctrl))		///< Reference to the External Interrupts Control
#define DEV_EXTINTFLAGS OBJ((ExtIntFlags*) &(DEV.extintflags))		///< Reference to the External Interrupts Flags
#define DEV_GTCTRL		OBJ((GeneralTimerControl*) &(DEV.gtccrs))	///< Reference to the General Timer/Counter Control
#define DEV_MCU			OBJ((MCUControl*) &(DEV.mcu))				///< Reference to the MCU
#define DEV_PCICTRL		OBJ((PinChangeControl*) &(DEV.pcictrl))		///< Reference to the Pin Change Interrupts Control
#define DEV_PCIFLAGS	OBJ((PinChangeFlags*) &(DEV.pciflags))		///< Reference to the Pin Change Interrupts Flags
#define DEV_PCIMASK0	OBJ((PinChangeMask*) &(DEV.pcimsk0))		///< Reference to the Pin Change Interrupts Mask 0
#define DEV_PCIMASK1	OBJ((PinChangeMask*) &(DEV.pcimsk1))		///< Reference to the Pin Change Interrupts Mask 1
#define DEV_PCIMASK2	OBJ((PinChangeMask*) &(DEV.pcimsk2))		///< Reference to the Pin Change Interrupts Mask 2
#define DEV_PCIMASK3	OBJ((PinChangeMask*) &(DEV.pcimsk3))		///< Reference to the Pin Change Interrupts Mask 3
#define DEV_RCCTRL		OBJ((OscControl*) &(DEV.rc))				///< Reference to the Oscillator Control
#define DEV_SLEEP		OBJ((SleepControl*) &(DEV.sleep))			///< Reference to the Sleep Mode Control
#define DEV_SPI			OBJ((SPI*) &(DEV.spi))						///< Reference to the SPI
#define DEV_TWI			OBJ((TWI*) &(DEV.twi))						///< Reference to the TWI
#define DEV_WATCHDOG	OBJ((Watchdog*) &(DEV.watchdog))			///< Reference to the Watchdog Timer
#define DEV_XMEM		OBJ((ExtMemory*) &(DEV.extmem))				///< Reference to the External Memory Interface
#define DEV_PLL			OBJ((PLL*) &(DEV.pll))						///< Reference to the PLL
#define DEV_CLKSEL		OBJ((ClockSwitch*) &(DEV.clksel))			///< Reference to the Clock Switch
#define DEV_USBGEN		OBJ((UsbGen*) &(DEV.usbgen))				///< Reference to the USB General
#define DEV_USBDEV		OBJ((UsbDevice*) &(DEV.usbdev))				///< Reference to the USB Device
#define DEV_USBEP		OBJ((UsbEndpoint*) &(DEV.usbep))			///< Reference to the USB Endpoint

/**
 * @}
 */
#endif /* AVRDEVICE_H_ */
