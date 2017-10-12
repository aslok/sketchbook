/**
 * @file ve_atmega325.h
 * @brief ATmega325 Microcontroller specific definitions
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA325_H_
#define ATMEGA325_H_

/**
 * @defgroup ATmega325 ATmega325
 * @ingroup MCs
 * @brief ATmega325/645 Support
 * @{
 */
/**
 * @brief ATmega325 Registers structure.
 */
typedef struct _ATMEGA325_AVR_DEV {
	AVR_GPIO	gpioa;				///< Port A General Purpose I/O Registers
	AVR_GPIO	gpiob;				///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioc;				///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiod;				///< Port D General Purpose I/O Registers
	AVR_GPIO	gpioe;				///< Port E General Purpose I/O Registers
	AVR_GPIO	gpiof;				///< Port F General Purpose I/O Registers
	AVR_GPIO	gpiog;				///< Port G General Purpose I/O Registers
	AVR_TIFR	tifr0;				///< Timer/Counter Interrupt Flag Register 0
	AVR_TIFRW	tifr1;				///< Timer/Counter Interrupt Flag Register 1
	AVR_TIFR	tifr2;				///< Timer/Counter Interrupt Flag Register 2

	/// @cond
	AVR_REG		__reserved0[4];
	/// @endcond
	AVR_EXTINTFLAGS	extintflags;	///< External Interrupt Flag Registers
	AVR_REG		gpior0;				///< General Purpose Register 0
	AVR_EEPROM	eeprom;				///< EEPROM Registers
	AVR_GTCCRS	gtccrs;				///< General Timer/Counter Control Registers
	AVR_TIMER	timer0;				///< Timer/Counter 0 Registers

	/// @cond
	AVR_REG		__reserved1[2];
	/// @endcond
	AVR_REG		gpior1;				///< General Purpose Register 1
	AVR_REG		gpior2;				///< General Purpose Register 2
	AVR_SPI		spi;				///< SPI Registers

	/// @cond
	AVR_REG		__reserved2;
	/// @endcond
	AVR_ANACOMP anacomp;			///< Analog Comparator Registers
	AVR_OCDR	ocdr;				///< On-Chip Debugger Registers

	/// @cond
	AVR_REG		__reserved3;
	/// @endcond
	AVR_SLEEP	sleep;				///< Sleep Mode Control Registers
	AVR_MCU		mcu;				///< MCU Control Registers

	/// @cond
	AVR_REG		__reserved4;
	/// @endcond
	AVR_SPM		spm;				///< Store Program Memory Control Registers

	/// @cond
	AVR_REG		__reserved5[5];
	/// @endcond
	AVR_REGW	sp;					///< Stack Pointer Register
	AVR_SREG	sreg;				///< MCU Status Register
	AVR_WATCHDOG watchdog;			///< Watchdog Timer Registers
	AVR_CLKPR	clkpr;				///< Clock Prescale Register

	/// @cond
	AVR_REG		__reserved6[2];
	/// @endcond
	AVR_POWER	power;				///< Power Reduction Registers

	/// @cond
	AVR_REG		__reserved7;
	/// @endcond
	AVR_REG		osccal;				///< Oscillator Calibration Register

	/// @cond
	AVR_REG		__reserved8[2];
	/// @endcond
	AVR_EXTINTCTRL extintctrl;		///< External Interrupt Control Registers

	/// @cond
	AVR_REG		__reserved9;
	/// @endcond
	AVR_PCMSK   pcimsk0;			///< Pin Change Interrupt Mask Register 0
	AVR_PCMSK   pcimsk1;			///< Pin Change Interrupt Mask Register 1
	AVR_PCMSK   pcimsk2;			///< Pin Change Interrupt Mask Register 2
	AVR_TIMSK	timsk0;				///< Timer/Counter Interrupt Mask Register 0
	AVR_TIMSKW	timsk1;				///< Timer/Counter Interrupt Mask Register 1
	AVR_TIMSK	timsk2;				///< Timer/Counter Interrupt Mask Register 2

	/// @cond
	AVR_REG		__reserved10[2];
	/// @endcond
	AVR_PCMSK	pcimsk3;			///< Pin Change Interrupt Mask Register 3

	/// @cond
	AVR_REG		__reserved11[4];
	/// @endcond
	AVR_AMUX	amux;				///< Analog Multiplexer Registers
	AVR_TIMERW	timer1;				///< Timer/Counter 1 Registers

	/// @cond
	AVR_REG		__reserved12[36];
	/// @endcond
	AVR_TIMER	timer2;				///< Timer/Counter 2 Registers

	/// @cond
	AVR_REG		__reserved13[2];
	/// @endcond
	AVR_ASYNCST	asyncst;			///< Asynchronous Status Registers

	/// @cond
	AVR_REG		__reserved14;
	/// @endcond
	AVR_USI		usi;				///< USI Registers

	/// @cond
	AVR_REG		__reserved15[5];
	/// @endcond
	AVR_USART	usart0;				///< USART 0 Registers

	/// @cond
	AVR_REG		__reserved16[17];
	/// @endcond
	AVR_GPIO	gpioh;				///< Port H General Purpose I/O Registers
	AVR_GPIO	gpioj;				///< Port J General Purpose I/O Registers
} ATMEGA325_AVR_DEV;
typedef ATMEGA325_AVR_DEV AVR_DEV;		///< ATmega325 Registers structure type.
typedef ATMEGA325_AVR_DEV* AVRP_DEV;	///< Pointer to ATmega325 Registers structure type.

#define DEV_TIMER0_OCA  DEV_GPIOB, 4	///< Timer/Counter 0  Compare Match A Output pin
#define DEV_TIMER1_OCA  DEV_GPIOB, 5	///< Timer/Counter 1  Compare Match A Output pin
#define DEV_TIMER1_OCB  DEV_GPIOB, 6	///< Timer/Counter 1  Compare Match B Output pin
#define DEV_TIMER2_OCA  DEV_GPIOB, 7	///< Timer/Counter 2  Compare Match A Output pin

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
#endif /* ATMEGA325_H_ */
