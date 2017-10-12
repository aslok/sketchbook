/**
 * @file ve_atmega32.h
 * @brief ATmega32 Microcontroller specific definitions
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/**
 * @defgroup ATmega32 ATmega32
 * @ingroup MCs
 * @brief ATmega16/32 Support
 * @{
 */

#if defined(__DOXYGEN__)
#define SAFE_READ_UCSRC					///< Define to safe read UCSRC Register
#endif

/**
 * @brief ATmega32 Registers structure
 */
typedef struct _ATMEGA32_AVR_DEV {
	AVR_TWI		twi;					///< TWI Registers
	AVR_AMUX	amux;					///< Analog Multiplexer Control Register
	AVR_ANACOMP anacomp;				///< Analog Comparator Registers
	AVR_USART	usart0;					///< USART 0 Registers
	AVR_SPI		spi;					///< SPI Registers
	AVR_GPIO	gpiod;					///< Port D General Purpose I/O Registers
	AVR_GPIO	gpioc;					///< Port C General Purpose I/O Registers
	AVR_GPIO	gpiob;					///< Port B General Purpose I/O Registers
	AVR_GPIO	gpioa;					///< Port A General Purpose I/O Registers
	AVR_EEPROM	eeprom;					///< EEPROM Registers
	AVR_UCSRC	ucsrc;					///< USART Control and Status Register C
	AVR_WATCHDOG watchdog;				///< Watchdog Timer Control Register
	AVR_ASYNCST	asyncst;				///< Asynchronous Status Registers
	AVR_TIMER2	timer2;					///< Timer/Counter 2 Registers
	AVR_TIMERW	timer1;					///< Timer/Counter 1 Registers
	AVR_SFIOR	sfior;					///< Special Function I/O Register
	AVR_REG		osccal;					///< Oscillator Calibration Register
	AVR_TIMER0	timer0;					///< Timer/Counter 0 Registers
	AVR_MCU		mcu;					///< MCU Control Registers
	AVR_TWCR	twcr;					///< TWI Control Register
	AVR_SPM		spm;					///< Store Program Memory Control Registers
	AVR_TIFR	tifr;					///< Timer/Counter Interrupt Flag Register
	AVR_TIMSK0	timsk0;					///< Timer/Counter Interrupt Mask Register 0
	AVR_EXTINTFLAGS	extintflags;		///< External Interrupt Flag Registers
	AVR_REG		ocr0;					///< Timer/Counter 0 Output Compare Register
	AVR_REGW	sp;						///< Stack Pointer Register
	AVR_SREG	sreg;					///< MCU Status Register
} ATMEGA32_AVR_DEV;
typedef ATMEGA32_AVR_DEV AVR_DEV;		///< ATmega32 Registers structure type
typedef ATMEGA32_AVR_DEV* AVRP_DEV;		///< Pointer to ATmega32 Registers structure type

#define DEV_TIMER0_OCA  DEV_GPIOB, 3	///< Timer/Counter 0 Compare Match A Output pin
#define DEV_TIMER1_OCA  DEV_GPIOD, 5	///< Timer/Counter 1 Compare Match A Output pin
#define DEV_TIMER1_OCB  DEV_GPIOD, 4	///< Timer/Counter 1 Compare Match B Output pin
#define DEV_TIMER2_OCA  DEV_GPIOD, 7	///< Timer/Counter 2 Compare Match A Output pin

#define DEV_SPI_SCK		DEV_GPIOB, 7	///< SPI SCK pin
#define DEV_SPI_MISO	DEV_GPIOB, 6	///< SPI MISO pin
#define DEV_SPI_MOSI	DEV_GPIOB, 5	///< SPI MOSI pin
#define DEV_SPI_SS		DEV_GPIOB, 4	///< SPI nSS pin

/**
 * @}
 */
#endif /* ATMEGA32_H_ */
