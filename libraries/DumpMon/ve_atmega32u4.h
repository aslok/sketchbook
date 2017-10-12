/**
 * @file ve_atmega32u4.h
 * @brief ATmega32U4 Microcontroller specific definitions
 * @author andrey
 * @date 28.11.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA32U4_H_
#define ATMEGA32U4_H_

/**
 * @defgroup ATmega32U4 ATmega32U4
 * @ingroup MCs
 * @brief ATmega16U4/32U4 Support
 * @{
 */
/**
 * @brief ATmega32U4 Registers structure.
 */
typedef struct _ATMEGA32U4_AVR_DEV {
	/// @cond
	AVR_REG		__reserved0[3];
	/// @endcond
	AVR_GPIO	gpiob;					///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioc;					///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiod;					///< Port D General Purpose I/O Registers
	AVR_GPIO	gpioe;					///< Port E General Purpose I/O Registers
	AVR_GPIO	gpiof;					///< Port F General Purpose I/O Registers

	/// @cond
	AVR_REG		__reserved1[3];
	/// @endcond
	AVR_TIFR	tifr0;					///< Timer/Counter Interrupt Flag Register 0
	AVR_TIFRW	tifr1;					///< Timer/Counter Interrupt Flag Register 1
	AVR_TIFR	tifr2;					///< Timer/Counter Interrupt Flag Register 2
	AVR_TIFRW	tifr3;					///< Timer/Counter Interrupt Flag Register 3
	AVR_TIFRHS	tifr4;					///< Timer/Counter Interrupt Flag Register 4

	/// @cond
	AVR_REG		__reserved3;
	/// @endcond
	AVR_PCIFLAGS    pciflags;			///< Pin Change Interrupt Flag Registers
	AVR_EXTINTFLAGS	extintflags;		///< External Interrupt Flag Registers
	AVR_REG		gpior0;					///< General Purpose Register 0
	AVR_EEPROM	eeprom;					///< EEPROM Registers
	AVR_GTCCRS	gtccrs;					///< General Timer/Counter Control Registers
	AVR_TIMER	timer0;					///< Timer/Counter 0 Registers
	AVR_PLL		pll;					///< PLL Control and Status Register
	AVR_REG		gpior1;					///< General Purpose Register 1
	AVR_REG		gpior2;					///< General Purpose Register 2
	AVR_SPI		spi;					///< SPI Registers

	/// @cond
	AVR_REG		__reserved4;
	/// @endcond
	AVR_ANACOMP anacomp;				///< Analog Comparator Registers
	AVR_REG		ocdr;					///< On-Chip Debugger Register
	AVR_PLLFRQ	pllfrq;					///< PLL Frequency Control Register
	AVR_SLEEP	sleep;					///< Sleep Mode Control Register
	AVR_MCU		mcu;					///< MCU Control Registers

	/// @cond
	AVR_REG		__reserved5;
	/// @endcond
	AVR_SPM		spm;					///< Store Program Memory Control Register

	/// @cond
	AVR_REG		__reserved6[3];
	/// @endcond
	AVR_REG		rampz;					///< Extended Z-pointer Register for ELPM/SPM

	/// @cond
	AVR_REG		__reserved7;
	/// @endcond
	AVR_REGW	sp;						///< Stack Pointer Register
	AVR_SREG	sreg;					///< MCU Status Register
	AVR_WATCHDOG watchdog;				///< Watchdog Timer Register
	AVR_CLKPR	clkpr;					///< Clock Prescale Register

	/// @cond
	AVR_REG		__reserved8[2];
	/// @endcond
	AVR_POWER	power;					///< Power Reduction Register
	AVR_REG		osccal;					///< Oscillator Calibration Register
	AVR_RC		rc;						///< RC Oscillator Control Register
	AVR_PCICTRL	pcictrl;				///< Pin Change Interrupt Control Registers
	AVR_EXTINTCTRL extintctrl;			///< External Interrupt Control Registers
	AVR_PCMSK   pcimsk0;				///< Pin Change Mask Register 0

	/// @cond
	AVR_REG		__reserved9[2];
	/// @endcond
	AVR_TIMSK	timsk0;					///< Timer/Counter Interrupt Mask Register 0
	AVR_TIMSKW	timsk1;					///< Timer/Counter Interrupt Mask Register 1
	AVR_TIMSK	timsk2;					///< Timer/Counter Interrupt Mask Register 2
	AVR_TIMSKW	timsk3;					///< Timer/Counter Interrupt Mask Register 3
	AVR_TIMSKHS	timsk4;					///< Timer/Counter Interrupt Mask Register 4

	/// @cond
	AVR_REG		__reserved11[5];
	/// @endcond
	AVR_AMUX	amux;					///< Analog Multiplexer Registers
	AVR_TIMERW	timer1;					///< Timer/Counter 1 Registers

	/// @cond
	AVR_REG		__reserved12[2];
	/// @endcond
	AVR_TIMERW	timer3;					///< Timer/Counter 3 Registers

	/// @cond
	AVR_REG		__reserved13[18];
	/// @endcond
	AVR_TIMER	timer2;					///< Timer/Counter 2 Registers

	/// @cond
	AVR_REG		__reserved14[3];
	/// @endcond
	AVR_TWI		twi;					///< TWI Registers
	AVR_TIMERHS timer4;					///< Timer/Counter 4 Registers
	AVR_CLKSEL	clksel;					///< Clock Selection Registers
	AVR_USART	usart1;					///< USART 1 Registers
	AVR_TIMERHS_OC timer4oc;			///< Timer/Counter 4 Output Compare Registers

	/// @cond
	AVR_REG		__reserved15[2];
	/// @endcond
	AVR_USBGEN	usbgen;					///< USB General Registers

	/// @cond
	AVR_REG		__reserved16[5];
	/// @endcond
	AVR_USBDEV	usbdev;					///< USB Device Registers

	/// @cond
	AVR_REG		__reserved17;
	/// @endcond
	AVR_USBEP 	usbep;					///< USB Device End Point Registers
} ATMEGA32U4_AVR_DEV;
typedef ATMEGA32U4_AVR_DEV AVR_DEV;		///< ATmega32U4 Registers structure type
typedef ATMEGA32U4_AVR_DEV* AVRP_DEV;	///< Pointer to ATmega32U4 Registers structure type

#define DEV_TIMER0_OCA   DEV_GPIOB, 7	///< Timer/Counter 0 Compare Match A Output pin
#define DEV_TIMER0_OCB   DEV_GPIOD, 0	///< Timer/Counter 0 Compare Match B Output pin
#define DEV_TIMER1_OCA   DEV_GPIOB, 5	///< Timer/Counter 1 Compare Match A Output pin
#define DEV_TIMER1_OCB   DEV_GPIOB, 6	///< Timer/Counter 1 Compare Match B Output pin
#define DEV_TIMER1_OCC   DEV_GPIOB, 7	///< Timer/Counter 1 Compare Match C Output pin
#define DEV_TIMER2_OCA   DEV_GPIOB, 4	///< Timer/Counter 2 Compare Match A Output pin
#define DEV_TIMER2_OCB   DEV_GPIOD, 1	///< Timer/Counter 2 Compare Match B Output pin
#define DEV_TIMER3_OCA   DEV_GPIOC, 6	///< Timer/Counter 3 Compare Match A Output pin
#define DEV_TIMER4_OCA   DEV_GPIOC, 7	///< Timer/Counter 4 Compare Match A Output pin
#define DEV_TIMER4_nOCA  DEV_GPIOC, 6	///< Timer/Counter 4 Compare Match A Not Output pin
#define DEV_TIMER4_OCB   DEV_GPIOB, 6	///< Timer/Counter 4 Compare Match B Output pin
#define DEV_TIMER4_nOCB  DEV_GPIOB, 5	///< Timer/Counter 4 Compare Match B Not Output pin
#define DEV_TIMER4_OCD   DEV_GPIOD, 7	///< Timer/Counter 4 Compare Match D Output pin
#define DEV_TIMER4_nOCD  DEV_GPIOD, 6	///< Timer/Counter 4 Compare Match D Not Output pin

#define DEV_SPI_SCK		DEV_GPIOB, 1	///< SPI SCK pin
#define DEV_SPI_MISO	DEV_GPIOB, 3	///< SPI MISO pin
#define DEV_SPI_MOSI	DEV_GPIOB, 2	///< SPI MOSI pin
#define DEV_SPI_SS		DEV_GPIOB, 0	///< SPI nSS pin

/**
 * @}
 */
#endif /* ATMEGA32U4_H_ */
