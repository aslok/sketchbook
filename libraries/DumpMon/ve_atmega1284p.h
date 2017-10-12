/**
 * @file ve_atmega1284p.h
 * @brief ATmega1284P Microcontroller specific definitions
 * @author andrey
 * @date 20.12.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA1284P_H_
#define ATMEGA1284P_H_

/**
 * @defgroup ATmega1284P ATmega1284P
 * @ingroup MCs
 * @brief ATmega1284/1284P Support
 * @{
 */
/**
 * @brief ATmega1284P Registers structure
 */
typedef struct _ATMEGA1284P_AVR_DEV {
	AVR_GPIO	gpioa;					///< Port A General Purpose I/O Registers
	AVR_GPIO	gpiob;					///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioc;					///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiod;					///< Port D General Purpose I/O Registers

	/// @cond
	AVR_REG		__reserved0[9];
	/// @endcond
	AVR_TIFR	tifr0;					///< Timer/Counter 0 Interrupt Flag Register
	AVR_TIFRW	tifr1;					///< Timer/Counter 1 Interrupt Flag Register
	AVR_TIFR	tifr2;					///< Timer/Counter 2 Interrupt Flag Register
	AVR_TIFRW	tifr3;					///< Timer/Counter 3 Interrupt Flag Register

	/// @cond
	AVR_REG		__reserved1[2];
	/// @endcond
	AVR_PCIFLAGS    pciflags;			///< Pin Change Interrupt Flag Registers
	AVR_EXTINTFLAGS	extintflags;		///< External Interrupt Flag Registers
	AVR_REG		gpior0;					///< General Purpose Register 0
	AVR_EEPROM	eeprom;					///< EEPROM Registers
	AVR_GTCCRS	gtccrs;					///< General Timer/Counter Control Registers
	AVR_TIMER	timer0;					///< Timer/Counter 0 Registers

	/// @cond
	AVR_REG		__reserved2;
	/// @endcond
	AVR_REG		gpior1;					///< General Purpose Register 1
	AVR_REG		gpior2;					///< General Purpose Register 2
	AVR_SPI		spi;					///< SPI Registers

	/// @cond
	AVR_REG		__reserved3;
	/// @endcond
	AVR_ANACOMP anacomp;				///< Analog Comparator Registers
	AVR_OCDR	ocdr;					///< On-Chip Debugger Data Register

	/// @cond
	AVR_REG		__reserved4;
	/// @endcond
	AVR_SLEEP	sleep;					///< Sleep Mode Registers
	AVR_MCU		mcu;					///< MCU Control Registers

	/// @cond
	AVR_REG		__reserved5;
	/// @endcond
	AVR_SPM		spm;					///< Store Program Memory Control Registers

	/// @cond
	AVR_REG		__reserved6[5];
	/// @endcond
	AVR_REGW	sp;						///< Stack Pointer Register
	AVR_SREG	sreg;					///< MCU Status Register
	AVR_WATCHDOG watchdog;				///< Watchdog Timer Control Register
	AVR_CLKPR	clkpr;					///< Clock Prescale Register

	/// @cond
	AVR_REG		__reserved7[2];
	/// @endcond
	AVR_POWER	power;					///< Power Reduction Registers
	AVR_REG		osccal;					///< Oscillator Calibration Register

	/// @cond
	AVR_REG		__reserved9;
	/// @endcond
	AVR_PCICTRL	pcictrl;				///< Pin Change Interrupt Control Registers
	AVR_EXTINTCTRL extintctrl;			///< External Interrupt Control Registers

	/// @cond
	AVR_REG		__reserved10;
	/// @endcond
	AVR_PCMSK   pcimsk0;				///< Pin Change Mask Register 0
	AVR_PCMSK   pcimsk1;				///< Pin Change Mask Register 1
	AVR_PCMSK   pcimsk2;				///< Pin Change Mask Register 2
	AVR_TIMSK	timsk0;					///< Timer/Counter Interrupt Mask Register 0
	AVR_TIMSKW	timsk1;					///< Timer/Counter Interrupt Mask Register 1
	AVR_TIMSK	timsk2;					///< Timer/Counter Interrupt Mask Register 2
	AVR_TIMSKW	timsk3;					///< Timer/Counter Interrupt Mask Register 3

	/// @cond
	AVR_REG		__reserved11;
	/// @endcond
	AVR_PCMSK   pcimsk3;				///< Pin Change Mask Register 3

	/// @cond
	AVR_REG		__reserved12[4];
	/// @endcond
	AVR_AMUX	amux;					///< Analog Multiplexer Control Register
	AVR_TIMERW	timer1;					///< Timer/Counter 1 Registers

	/// @cond
	AVR_REG		__reserved13[4];
	/// @endcond
	AVR_TIMERW	timer3;					///< Timer/Counter 3 Registers

	/// @cond
	AVR_REG		__reserved14[20];
	/// @endcond
	AVR_TIMER	timer2;					///< Timer/Counter 2 Registers

	/// @cond
	AVR_REG		__reserved15;
	/// @endcond
	AVR_ASYNCST	asyncst;				///< Asynchronous Status Registers

	/// @cond
	AVR_REG		__reserved16;
	/// @endcond
	AVR_TWI		twi;					///< TWI Registers

	/// @cond
	AVR_REG		__reserved17[2];
	/// @endcond
	AVR_USART	usart0;					///< USART 0 Registers

	/// @cond
	AVR_REG		__reserved18;
	/// @endcond
	AVR_USART	usart1;					///< USART 1 Registers
} ATMEGA1284P_AVR_DEV;
typedef ATMEGA1284P_AVR_DEV AVR_DEV;		///< ATmega1284P Registers structure type
typedef ATMEGA1284P_AVR_DEV* AVRP_DEV;		///< Pointer to ATmega1284P Registers structure type

#define DEV_TIMER0_OCA  DEV_GPIOB, 3	///< Timer/Counter 0 Compare Match A Output pin
#define DEV_TIMER0_OCB  DEV_GPIOB, 4	///< Timer/Counter 0 Compare Match B Output pin
#define DEV_TIMER1_OCA  DEV_GPIOD, 5	///< Timer/Counter 1 Compare Match A Output pin
#define DEV_TIMER1_OCB  DEV_GPIOD, 4	///< Timer/Counter 1 Compare Match B Output pin
#define DEV_TIMER2_OCA  DEV_GPIOD, 7	///< Timer/Counter 2 Compare Match A Output pin
#define DEV_TIMER2_OCB  DEV_GPIOD, 6	///< Timer/Counter 2 Compare Match B Output pin
#define DEV_TIMER3_OCA  DEV_GPIOB, 6	///< Timer/Counter 3 Compare Match A Output pin
#define DEV_TIMER3_OCB  DEV_GPIOB, 7	///< Timer/Counter 3 Compare Match B Output pin

#define DEV_SPI_SCK		DEV_GPIOB, 7	///< SPI SCK pin
#define DEV_SPI_MISO	DEV_GPIOB, 6	///< SPI MISO pin
#define DEV_SPI_MOSI	DEV_GPIOB, 5	///< SPI MOSI pin
#define DEV_SPI_SS		DEV_GPIOB, 4	///< SPI nSS pin

/**
 * @}
 */
#endif /* ATMEGA1284P_H_ */
