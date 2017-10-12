/**
 * @file ve_atmega328p.h
 * @brief ATmega328P Microcontroller specific definitions
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA328_H_
#define ATMEGA328_H_

/**
 * @defgroup ATmega328P ATmega328P
 * @ingroup MCs
 * @brief ATmega48PA/88PA/168PA/328P Support
 * @{
 */
/**
 * @brief ATmega328P Registers structure.
 */
typedef struct _ATmega328P_AVR_DEV {
	/// @cond
	AVR_REG		__reserved0[3];
	/// @endcond
	AVR_GPIO	gpiob;					///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioc;					///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiod;					///< Port D General Purpose I/O Registers

	/// @cond
	AVR_REG		__reserved1[9];
	/// @endcond
	AVR_TIFR	tifr0;					///< Timer/Counter Interrupt Flag Register 0
	AVR_TIFRW	tifr1;					///< Timer/Counter Interrupt Flag Register 1
	AVR_TIFR	tifr2;					///< Timer/Counter Interrupt Flag Register 2

	/// @cond
	AVR_REG		__reserved2[3];
	/// @endcond
	AVR_PCIFLAGS    pciflags;			///< Pin Change Interrupt Flag Registers
	AVR_EXTINTFLAGS	extintflags;		///< External Interrupt Flag Registers
	AVR_REG		gpior0;					///< General Purpose Register 0
	AVR_EEPROM	eeprom;					///< EEPROM Registers
	AVR_GTCCRS	gtccrs;					///< General Timer/Counter Control Registers
	AVR_TIMER	timer0;					///< Timer/Counter 0 Registers

	/// @cond
	AVR_REG		__reserved3;
	/// @endcond
	AVR_REG		gpior1;					///< General Purpose Register 1
	AVR_REG		gpior2;					///< General Purpose Register 2
	AVR_SPI		spi;					///< SPI Registers

	/// @cond
	AVR_REG		__reserved4;
	/// @endcond
	AVR_ANACOMP anacomp;				///< Analog Comparator Registers

	/// @cond
	AVR_REG		__reserved5[2];
	/// @endcond
	AVR_SLEEP	sleep;					///< Sleep Mode Control Registers
	AVR_MCU		mcu;					///< MCU Control Registers

	/// @cond
	AVR_REG		__reserved6;
	/// @endcond
	AVR_SPM		spm;					///< Store Program Memory Control Registers

	/// @cond
	AVR_REG		__reserved7[5];
	/// @endcond
	AVR_REGW	sp;						///< Stack Pointer Register
	AVR_SREG	sreg;					///< MCU Status Register
	AVR_WATCHDOG watchdog;				///< Watchdog Timer Registers
	AVR_CLKPR	clkpr;					///< Clock Prescale Registers

	/// @cond
	AVR_REG		__reserved8[2];
	/// @endcond
	AVR_POWER	power;					///< Power Reduction Registers

	/// @cond
	AVR_REG		__reserved9;
	/// @endcond
	AVR_REG		osccal;					///< Oscillator Calibration Register

	/// @cond
	AVR_REG		__reserved10;
	/// @endcond
	AVR_PCICTRL	pcictrl;				///< Pin Change Interrupt Control Registers
	AVR_EXTINTCTRL extintctrl;			///< External Interrupt Control Registers

	/// @cond
	AVR_REG		__reserved11;
	/// @endcond
	AVR_PCMSK   pcimsk0;				///< Pin Change Interrupt Mask Register 0
	AVR_PCMSK   pcimsk1;				///< Pin Change Interrupt Mask Register 1
	AVR_PCMSK   pcimsk2;				///< Pin Change Interrupt Mask Register 2
	AVR_TIMSK	timsk0;					///< Timer/Counter Interrupt Mask Register 0
	AVR_TIMSKW	timsk1;					///< Timer/Counter Interrupt Mask Register 1
	AVR_TIMSK	timsk2;					///< Timer/Counter Interrupt Mask Register 2

	/// @cond
	AVR_REG		__reserved12[7];
	/// @endcond
	AVR_AMUX	amux;					///< Analog Multiplexer Registers
	AVR_TIMERW	timer1;					///< Timer/Counter 1 Registers

	/// @cond
	AVR_REG		__reserved13[36];
	/// @endcond
	AVR_TIMER	timer2;					///< Timer/Counter 2 Registers

	/// @cond
	AVR_REG		__reserved14;
	/// @endcond
	AVR_ASYNCST	asyncst;				///< Asynchronous Status Registers

	/// @cond
	AVR_REG		__reserved15;
	/// @endcond
	AVR_TWI		twi;					///< TWI Registers

	/// @cond
	AVR_REG		__reserved16[2];
	/// @endcond
	AVR_USART	usart0;					///< USART 0 Registers
} ATmega328P_AVR_DEV, *AVRP_DEV;
typedef ATmega328P_AVR_DEV AVR_DEV;		///< ATmega328P Registers structure type
typedef ATmega328P_AVR_DEV* AVRP_DEV;	///< Pointer to ATmega328P Registers structure type


#define DEV_TIMER0_OCA  DEV_GPIOD, 6	///< Timer/Counter 0 Compare Match A Output pin
#define DEV_TIMER0_OCB  DEV_GPIOD, 5	///< Timer/Counter 0 Compare Match B Output pin
#define DEV_TIMER1_OCA  DEV_GPIOB, 1	///< Timer/Counter 1 Compare Match A Output pin
#define DEV_TIMER1_OCB  DEV_GPIOB, 2	///< Timer/Counter 1 Compare Match B Output pin
#define DEV_TIMER2_OCA  DEV_GPIOB, 3	///< Timer/Counter 2 Compare Match A Output pin

#define DEV_SPI_SCK		DEV_GPIOB, 5	///< SPI SCK pin
#define DEV_SPI_MISO	DEV_GPIOB, 4	///< SPI MISO pin
#define DEV_SPI_MOSI	DEV_GPIOB, 3	///< SPI MOSI pin
#define DEV_SPI_SS		DEV_GPIOB, 2	///< SPI nSS pin

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
/**
 * @endcond
 * @}
 */
#endif /* ATMEGA328_H_ */
