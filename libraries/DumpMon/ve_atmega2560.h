/**
 * @file ve_atmega2560.h
 * @brief ATmega2560 Microcontroller specific definitions
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA2560_H_
#define ATMEGA2560_H_

/**
 * @defgroup ATmega2560 ATmega2560
 * @ingroup MCs
 * @brief ATmega640/1280/1281/2560/2561 Support
 * @{
 */
/**
 * @brief ATmega2560 Registers structure
 */
typedef struct _ATMEGA2560_AVR_DEV {
	AVR_GPIO	gpioa;					///< Port A General Purpose I/O Registers
	AVR_GPIO	gpiob;					///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioc;					///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiod;					///< Port D General Purpose I/O Registers
	AVR_GPIO	gpioe;					///< Port E General Purpose I/O Registers
	AVR_GPIO	gpiof;					///< Port F General Purpose I/O Registers
	AVR_GPIO	gpiog;					///< Port G General Purpose I/O Registers
	AVR_TIFR	tifr0;					///< Timer/Counter 0 Interrupt Flag Register
	AVR_TIFRW	tifr1;					///< Timer/Counter 1 Interrupt Flag Register
	AVR_TIFR	tifr2;					///< Timer/Counter 2 Interrupt Flag Register
	AVR_TIFRW	tifr3;					///< Timer/Counter 3 Interrupt Flag Register
	AVR_TIFRW	tifr4;					///< Timer/Counter 4 Interrupt Flag Register
	AVR_TIFRW	tifr5;					///< Timer/Counter 5 Interrupt Flag Register
	AVR_PCIFLAGS    pciflags;			///< Pin Change Interrupt Flag Registers
	AVR_EXTINTFLAGS	extintflags;		///< External Interrupt Flag Registers
	AVR_REG		gpior0;					///< General Purpose Register 0
	AVR_EEPROM	eeprom;					///< EEPROM Registers
	AVR_GTCCRS	gtccrs;					///< General Timer/Counter Control Registers
	AVR_TIMER	timer0;					///< Timer/Counter 0 Registers

	/// @cond
	AVR_REG		__reserved0;
	/// @endcond
	AVR_REG		gpior1;					///< General Purpose Register 1
	AVR_REG		gpior2;					///< General Purpose Register 2
	AVR_SPI		spi;					///< SPI Registers

	/// @cond
	AVR_REG		__reserved1;
	/// @endcond
	AVR_ANACOMP anacomp;				///< Analog Comparator Registers
	AVR_OCDR	ocdr;					///< On-Chip Debugger Data Register

	/// @cond
	AVR_REG		__reserved2;
	/// @endcond
	AVR_SLEEP	sleep;					///< Sleep Mode Registers
	AVR_MCU		mcu;					///< MCU Control Registers

	/// @cond
	AVR_REG		__reserved3;
	/// @endcond
	AVR_SPM		spm;					///< Store Program Memory Control Registers

	/// @cond
	AVR_REG		__reserved4[3];
	/// @endcond
	AVR_REG		rampz;					///< Extended Z-pointer Register for ELPM/SPM
	AVR_REG		eind;					///< Extended Index Register
	AVR_REGW	sp;						///< Stack Pointer Register
	AVR_SREG	sreg;					///< MCU Status Register
	AVR_WATCHDOG watchdog;				///< Watchdog Timer Control Register
	AVR_CLKPR	clkpr;					///< Clock Prescale Register

	/// @cond
	AVR_REG		__reserved5[2];
	/// @endcond
	AVR_POWER	power;					///< Power Reduction Registers
	AVR_REG		osccal;					///< Oscillator Calibration Register

	/// @cond
	AVR_REG		__reserved6;
	/// @endcond
	AVR_PCICTRL	pcictrl;				///< Pin Change Interrupt Control Registers
	AVR_EXTINTCTRL extintctrl;			///< External Interrupt Control Registers
	AVR_PCMSK   pcimsk0;				///< Pin Change Mask Register 0
	AVR_PCMSK   pcimsk1;				///< Pin Change Mask Register 1
	AVR_PCMSK   pcimsk2;				///< Pin Change Mask Register 2
	AVR_TIMSK	timsk0;					///< Timer/Counter Interrupt Mask Register 0
	AVR_TIMSKW	timsk1;					///< Timer/Counter Interrupt Mask Register 1
	AVR_TIMSK	timsk2;					///< Timer/Counter Interrupt Mask Register 2
	AVR_TIMSKW	timsk3;					///< Timer/Counter Interrupt Mask Register 3
	AVR_TIMSKW	timsk4;					///< Timer/Counter Interrupt Mask Register 4
	AVR_TIMSKW	timsk5;					///< Timer/Counter Interrupt Mask Register 5
	AVR_EXTMEM	extmem;					///< External Memory Control Registers

	/// @cond
	AVR_REG		__reserved7[2];
	/// @endcond
	AVR_AMUX	amux;					///< Analog Multiplexer Control Register
	AVR_TIMERW	timer1;					///< Timer/Counter 1 Registers

	/// @cond
	AVR_REG		__reserved8[2];
	/// @endcond
	AVR_TIMERW	timer3;					///< Timer/Counter 3 Registers

	/// @cond
	AVR_REG		__reserved9[2];
	/// @endcond
	AVR_TIMERW	timer4;					///< Timer/Counter 4 Registers

	/// @cond
	AVR_REG		__reserved10[2];
	/// @endcond
	AVR_TIMER	timer2;					///< Timer/Counter 2 Registers

	/// @cond
	AVR_REG		__reserved11;
	/// @endcond
	AVR_ASYNCST	asyncst;				///< Asynchronous Status Registers

	/// @cond
	AVR_REG		__reserved12;
	/// @endcond
	AVR_TWI		twi;					///< TWI Registers

	/// @cond
	AVR_REG		__reserved13[2];
	/// @endcond
	AVR_USART	usart0;					///< USART 0 Registers

	/// @cond
	AVR_REG		__reserved14;
	/// @endcond
	AVR_USART	usart1;					///< USART 1 Registers

	/// @cond
	AVR_REG		__reserved15;
	/// @endcond
	AVR_USART	usart2;					///< USART 2 Registers

	/// @cond
	AVR_REG		__reserved16[42];
	/// @endcond
	AVR_GPIO	gpioh;					///< Port H General Purpose I/O Registers
	AVR_GPIO	gpioj;					///< Port J General Purpose I/O Registers
	AVR_GPIO	gpiok;					///< Port K General Purpose I/O Registers
	AVR_GPIO	gpiol;					///< Port L General Purpose I/O Registers

	/// @cond
	AVR_REG		__reserved17[21];
	/// @endcond
	AVR_TIMERW	timer5;					///< Timer/Counter 5 Registers

	/// @cond
	AVR_REG		__reserved18[2];
	/// @endcond
	AVR_USART	usart3;					///< USART 3 Registers
} ATMEGA2560_AVR_DEV;
typedef ATMEGA2560_AVR_DEV AVR_DEV;		///< ATmega2560 Registers structure type
typedef ATMEGA2560_AVR_DEV* AVRP_DEV;	///< Pointer to ATmega2560 Registers structure type

#define DEV_TIMER0_OCA  DEV_GPIOB, 7	///< Timer/Counter 0 Compare Match A Output pin
#define DEV_TIMER0_OCB  DEV_GPIOG, 5	///< Timer/Counter 0 Compare Match B Output pin
#define DEV_TIMER1_OCA  DEV_GPIOB, 5	///< Timer/Counter 1 Compare Match A Output pin
#define DEV_TIMER1_OCB  DEV_GPIOB, 6	///< Timer/Counter 1 Compare Match B Output pin
#define DEV_TIMER1_OCC  DEV_GPIOB, 7	///< Timer/Counter 1 Compare Match C Output pin
#define DEV_TIMER2_OCA  DEV_GPIOB, 4	///< Timer/Counter 2 Compare Match A Output pin
#define DEV_TIMER2_OCB  DEV_GPIOH, 6	///< Timer/Counter 2 Compare Match B Output pin
#define DEV_TIMER3_OCA  DEV_GPIOE, 3	///< Timer/Counter 3 Compare Match A Output pin
#define DEV_TIMER3_OCB  DEV_GPIOE, 4	///< Timer/Counter 3 Compare Match B Output pin
#define DEV_TIMER3_OCC  DEV_GPIOE, 5	///< Timer/Counter 3 Compare Match C Output pin
#define DEV_TIMER4_OCA  DEV_GPIOH, 3	///< Timer/Counter 4 Compare Match A Output pin
#define DEV_TIMER4_OCB  DEV_GPIOH, 4	///< Timer/Counter 4 Compare Match B Output pin
#define DEV_TIMER4_OCC  DEV_GPIOH, 5	///< Timer/Counter 4 Compare Match C Output pin
#define DEV_TIMER5_OCA  DEV_GPIOL, 3	///< Timer/Counter 5 Compare Match A Output pin
#define DEV_TIMER5_OCB  DEV_GPIOL, 4	///< Timer/Counter 5 Compare Match B Output pin
#define DEV_TIMER5_OCC  DEV_GPIOL, 5	///< Timer/Counter 5 Compare Match C Output pin

#define DEV_SPI_SCK		DEV_GPIOB, 1	///< SPI SCK pin
#define DEV_SPI_MISO	DEV_GPIOB, 3	///< SPI MISO pin
#define DEV_SPI_MOSI	DEV_GPIOB, 2	///< SPI MOSI pin
#define DEV_SPI_SS		DEV_GPIOB, 0	///< SPI nSS pin

/**
 * @brief Some AVR-lib compatibility definitions...
 * @cond
 */
#define DOR         DOR0
#define FE          FE0
#define MPCM        MPCM0
#define PE          PE0
#define RXC         RXC0
#define RXCIE       RXCIE0
#define RXEN        RXEN0
#define TXC         TXC0
#define TXCIE       TXCIE0
#define TXEN        TXEN0
#define U2X         U2X0
#define UCPOL       UCPOL0
#define UCSRC       UCSRC0
#define UCSZ0       UCSZ00
#define UCSZ1       UCSZ01
#define UCSZ2       UCSZ02
#define UDRE        UDRE0
#define UDRIE       UDRIE0
#define UMSEL       UMSEL0
#define UPM0        UPM00
#define UPM1        UPM01
#define USBS        USBS0

#define USART_RXC_vect      USART0_RX_vect
#define USART_TXC_vect      USART0_TX_vect
#define USART_UDRE_vect     USART0_UDRE_vect

/**
 * @endcond
 * @}
 */
#endif /* ATMEGA2560_H_ */
