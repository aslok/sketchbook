/**
 * @file ve_avrdef_atmega32.h
 * @brief ATmega32 Register structure definitions
 * @author andrey
 * @date 20.12.2012
 * @copyright GNU Public License
 */
#ifndef AVRDEF_ATMEGA32_H_
#define AVRDEF_ATMEGA32_H_

/**
 * @addtogroup ATmega32
 * @{
 */
/**
 * @brief General Purpose I/O registers structure
 */
typedef struct _AVR_GPIO
{
    volatile AVR_REG pin;		///< Input Pins Address
    AVR_REG ddr;				///< Data Direction Register
    AVR_REG port;				///< Data Register
} AVR_GPIO;
typedef AVR_GPIO* AVRP_GPIO;	///< Pointer to General Purpose I/O registers structure type

/**
 * @brief ATmega32 Timer/Counter Interrupt Flag Register
 */
typedef struct _ATmega32_AVR_TIFR
{
    volatile bool tov0  :1;		///< Overflow Flag
    volatile bool ocf0 :1;		///< Output Compare Flag
    volatile bool tov1  :1;		///< Overflow Flag
    volatile bool ocfb1 :1;		///< Output Compare A Flag
    volatile bool ocfa1 :1;		///< Output Compare B Flag
    volatile bool icf1 :1;		///< Input Capture Flag
    volatile bool tov2  :1;		///< Overflow Flag
    volatile bool ocf2 :1;		///< Output Compare Flag
} ATmega32_AVR_TIFR, *AVRP_TIFR;
typedef ATmega32_AVR_TIFR AVR_TIFR;		///< 8-bit Timer/Counter Interrupt Flag Register type
typedef AVR_TIFR* AVRP_TIFR;			///< Pointer to 8-bit Timer/Counter Interrupt Flag Register type

DECLARE_REGT(TIFR);						///< 8-bit Timer/Counter Interrupt Flag Register declaration

/**
 * @brief External Interrupt Flag Register
 */
typedef struct _ATmega32_AVR_EIFR
{
	/// @cond
    unsigned char reserved :5;
	/// @endcond
    volatile bool intf2 :1;				///< External Interrupt Interrupt Flag
    volatile bool intf0 :1;				///< External Interrupt Interrupt Flag
    volatile bool intf1 :1;				///< External Interrupt Interrupt Flag
} ATmega32_AVR_EIFR;
typedef ATmega32_AVR_EIFR AVR_EIFR;		///< External Interrupt Flag Register type
typedef AVR_EIFR* AVRP_EIFR;			///< Pointer to External Interrupt Flag Register type

DECLARE_REGT(EIFR);						///< External Interrupt Flag Register declaration

/**
 * @brief External Interrupt Control Register
 */
typedef struct _ATmega32_AVR_EIMSK
{
    volatile bool ivce :1;		///< Interrupt Vector Change Enable
    bool ivsel :1;				///< Interrupt Vector Select

    /// @cond
    unsigned char reserved :3;
    /// @endcond
    bool int2 :1;				///< External Interrupt Request Enable
    bool int0 :1;				///< External Interrupt Request Enable
    bool int1 :1;				///< External Interrupt Request Enable
} ATmega32_AVR_EIMSK;
typedef ATmega32_AVR_EIMSK AVR_EIMSK;	///< External Interrupt Control Register type
typedef AVR_EIMSK* AVRP_EIMSK;			///< Pointer to External Interrupt Control Register type

DECLARE_REGT(EIMSK);					///< External Interrupt Control Register declaration

#define gicr eimsk						///< General Interrupt Control Register macro

/**
 * @brief External Interrupt Control registers structure
 */
typedef struct _AVR_EXTINTFLAGS
{
	EIFR_REG  eifr;				///< External Interrupt Flag Register
	EIMSK_REG eimsk;			///< External Interrupt Mask Register
} AVR_EXTINTFLAGS;
typedef AVR_EXTINTFLAGS* AVRP_EXTINTFLAGS;	///< Pointer to External Interrupt Control registers structure type

/**
 * @brief EEPROM Control Register
 */
typedef struct _W_AVR_EECR
{
    volatile bool eere  :1;		///< EEPROM Read Enable
    volatile bool eewe  :1;		///< EEPROM Write Enable
    bool eemwe :1;				///< EEPROM Master Write Enable
    bool eerie :1;				///< EEPROM Ready Interrupt Enable
} W_AVR_EECR;
typedef W_AVR_EECR AVR_EECR;	///< EEPROM Control Register type
typedef AVR_EECR* AVRP_EECR;	///< Pointer to EEPROM Control Register type

#define eepe eewe				///< EEPROM Programming Enable macro
#define eempe eemwe				///< EEPROM Master Programming Enable macro

DECLARE_REGT(EECR);				///< EEPROM Control Register declaration

/**
 * @brief EEPROM Registers structure
 */
typedef struct _AVR_EEPROM
{
	EECR_REG  eecr;				///< EEPROM Control Register
    volatile AVR_REG   eedr;	///< EEPROM Data Register
    AVR_REGW  eear;				///< EEPROM Address Register
} AVR_EEPROM;
typedef AVR_EEPROM* AVRP_EEPROM;	///< Pointer to EEPROM Registers structure type

/**
 * @brief General Timer/Counter Control Register
 */
typedef struct _AVR_GTCCR
{
    volatile bool psrsync :1;	///< Prescaler Reset for Synchronous Timer/Counters
    volatile bool psrasy  :1;	///< Prescaler Reset for Asynchronous Timer/Counters

    /// @cond
    unsigned char reserved :5;
    /// @endcond
    bool tsm     :1;			///< Timer/Counter Synchronization Mode
} AVR_GTCCR;
typedef AVR_GTCCR* AVRP_GTCCR;	///< Pointer to General Timer/Counter Control Register type

DECLARE_REGT(GTCCR);			///< General Timer/Counter Control Register declaration

/**
 * @brief General Timer/Counter Control registers structure
 */
typedef struct _AVR_GTCCRS
{
	GTCCR_REG gtccr;				///< General Timer/Counter Control Register
} AVR_GTCCRS;
typedef AVR_GTCCRS* AVRP_GTCCRS;	///< Pointer to General Timer/Counter Control registers structure type

/**
 * @brief 8-bit Timer/Counter Control Register A
 */
typedef struct _ATmega32_AVR_TCCRA
{
    unsigned char cs :3;				///< Clock Select
    unsigned char wgm1 :1;				///< Waveform Generation Mode Bit 1
    unsigned char coma :2;				///< Compare Match Output A Mode
    unsigned char wgm0 :1;				///< Waveform Generation Mode Bit 0
    bool foca :1;						///< Force Output Compare A
} ATmega32_AVR_TCCRA, *AVRP_TCCRA;
typedef ATmega32_AVR_TCCRA AVR_TCCRA;	///< 8-bit Timer/Counter Control Register A type
typedef AVR_TCCRA* AVRP_TCCRA;			///< Pointer to 8-bit Timer/Counter Control Register A type

DECLARE_REGT(TCCRA);					///< 8-bit Timer/Counter Control Register A declaration

/**
 * @brief 8-bit Timer/Counter 0 registers structure
 */
typedef struct _ATmega32_AVR_TIMER0
{
    AVR_REG   tcnt;						///< Timer/Counter Register
    TCCRA_REG tccra;					///< Timer/Counter Control Register A
} ATmega32_AVR_TIMER0;
typedef ATmega32_AVR_TIMER0 AVR_TIMER0;	///< 8-bit Timer/Counter 0 Control Register B type
typedef AVR_TIMER0* AVRP_TIMER0;		///< Pointer to 8-bit Timer/Counter 0 Control Register B type

/**
 * @brief 8-bit Timer/Counter 2 registers structure
 */
typedef struct _ATmega32_AVR_TIMER2
{
    AVR_REG   ocra;						///< Timer/Counter Output Compare Register A
    AVR_REG   tcnt;						///< Timer/Counter Register
    TCCRA_REG tccra;					///< Timer/Counter Control Register A
} ATmega32_AVR_TIMER2;
typedef ATmega32_AVR_TIMER2 AVR_TIMER2;	///< 8-bit Timer/Counter 2 Control Register B type
typedef AVR_TIMER2* AVRP_TIMER2;		///< Pointer to 8-bit Timer/Counter 2 Control Register B type

/**
 * @brief 16-bit Timer/Counter Control Register A
 */
typedef struct _ATmega32_AVR_TCCRWA
{
    unsigned char wgml :2;			///< Waveform Generation Mode LSB
    bool focb :1;					///< Force Output Compare for Channel B
    bool foca :1;					///< Force Output Compare for Channel A
    unsigned char comb :2;			///< Compare Output Mode for Channel B
    unsigned char coma :2;			///< Compare Output Mode for Channel A
} ATmega32_AVR_TCCRWA, *AVRP_TCCRWA;
typedef ATmega32_AVR_TCCRWA AVR_TCCRWA;		///< 16-bit Timer/Counter Control Register A type
typedef AVR_TCCRWA* AVRP_TCCRWA;			///< Pointer to 16-bit Timer/Counter Control Register A type

DECLARE_REGT(TCCRWA);						///< 16-bit Timer/Counter Control Register A declaration

/**
 * @brief 16-bit Timer/Counter Control Register B
 */
typedef struct _AVR_TCCRWB
{
    unsigned char cs :3;			///< Clock Select
    unsigned char wgmh :2;			///< Waveform Generation Mode MSB

    /// @cond
    bool reserved :1;
    /// @endcond
    bool ices :1;					///< Input Capture Edge Select
    bool icnc :1;					///< Input Capture Noise Canceler
} AVR_TCCRWB;
typedef AVR_TCCRWB* AVRP_TCCRWB;	///< Pointer to 16-bit Timer/Counter Control Register B type

DECLARE_REGT(TCCRWB);				///< 16-bit Timer/Counter Control Register B declaration

/**
 * @brief 16-bit Timer/Counter Registers structure
 */
typedef struct _ATmega32_AVR_TIMERW
{
    volatile AVR_REGW icr;			///< 16-bit Timer/Counter Input Capture Register
    AVR_REGW   ocrb;				///< 16-bit Timer/Counter Output Compare Register B
    AVR_REGW   ocra;				///< 16-bit Timer/Counter Output Compare Register A
    volatile AVR_REGW tcnt;			///< 16-bit Timer/Counter
    TCCRWB_REG tccrb;				///< 16-bit Timer/Counter Control Register B
    TCCRWA_REG tccra;				///< 16-bit Timer/Counter Control Register A
} ATmega32_AVR_TIMERW;
typedef ATmega32_AVR_TIMERW AVR_TIMERW;		///< 16-bit Timer/Counter Registers structure type
typedef AVR_TIMERW* AVRP_TIMERW;			///< Pointer to 16-bit Timer/Counter Registers structure type

/**
 * @brief SPI Control Register
 */
typedef struct _AVR_SPCR
{
    unsigned char spr :2;		///< SPI Clock Rate Select
    unsigned char cpha :1;		///< Clock Phase
    unsigned char cpol :1;		///< Clock Polarity
    bool mstr :1;				///< Master/Slave Select
    unsigned char dord :1;		///< Data Order
    bool spe  :1;				///< SPI Enable
    bool spie :1;				///< SPI Interrupt Enable
} AVR_SPCR;
typedef AVR_SPCR* AVRP_SPCR;	///< Pointer to SPI Control Register type

DECLARE_REGT(SPCR);				///< SPI Control Register declaration

/**
 * @brief SPI Status Register
 */
typedef struct _AVR_SPSR
{
    bool spi2x :1;				///< Double SPI Speed Bit

    /// @cond
    unsigned char reserved :5;
    /// @endcond
    volatile bool wcol :1;		///< Write COLlision Flag
    volatile bool spif :1;		///< SPI Interrupt Flag
} AVR_SPSR;
typedef AVR_SPSR* AVRP_SPSR;	///< Pointer to SPI Status Register type

DECLARE_REGT(SPSR);				///< SPI Status Register declaration

/**
 * @brief SPI Registers structure
 */
typedef struct _AVR_SPI
{
    SPCR_REG spcr;				///< SPI Control Register
    SPSR_REG spsr;				///< SPI Status Register
    volatile AVR_REG  spdr;		///< SPI Data Register
} AVR_SPI;
typedef AVR_SPI* AVRP_SPI;		///< Pointer to SPI Registers structure type

/**
 * @brief Analog Comparator Control and Status Register
 */
typedef struct _AVR_ACSR
{
    unsigned char acis :2;		///< Analog Comparator Interrupt Mode Select
    bool acic :1;				///< Analog Comparator Input Capture Enable
    bool acie :1;				///< Analog Comparator Interrupt Enable
    bool aci :1;				///< Analog Comparator Interrupt Flag
    bool aco :1;				///< Analog Comparator Output
    unsigned char acbg :1;		///< Analog Comparator Bandgap Select
    bool acd :1;				///< Analog Comparator Disable
} AVR_ACSR;
typedef AVR_ACSR* AVRP_ACSR;	///< Pointer to Analog Comparator Control and Status Register type

DECLARE_REGT(ACSR);				///< Analog Comparator Control and Status Register declaration

/**
 * @brief Analog Comparator Registers structure
 */
typedef struct _AVR_ANACOMP
{
    ACSR_REG acsr;				///< Analog Comparator Control and Status Register
} AVR_ANACOMP;
typedef AVR_ANACOMP* AVRP_ANACOMP;	///< Pointer to Analog Comparator Registers structure type

/**
 * @brief On-Chip Debugger Register
 */
typedef struct _AVR_OCDR
{
	unsigned char ocdr :7;		///< On-Chip Debugger Register
	volatile bool idrd :1;		///< I/O Debug Register Dirty
} AVR_OCDR;
typedef AVR_OCDR* AVRP_OCDR;	///< Pointer to On-Chip Debugger Register type

/**
 * @brief Sleep Mode Control Register
 */
typedef struct _AVR_SMCR
{
    bool se          :1;		///< Sleep Enable
    unsigned char sm :3;		///< Sleep Mode Select Bits
} AVR_SMCR;
typedef AVR_SMCR* AVRP_SMCR;	///< Pointer to Sleep Mode Control Register type

DECLARE_REGT(SMCR);				///< Sleep Mode Control Register declaration

/**
 * @brief Sleep Mode Control registers structure
 */
typedef struct _AVR_SLEEP
{
	SMCR_REG smcr;				///< Sleep Mode Control Register
} AVR_SLEEP;
typedef AVR_SLEEP* AVRP_SLEEP;	///< Pointer to Sleep Mode Control Register type

/**
 * @brief Microcontroller Unit Status Register
 */
typedef struct _ATmega32_AVR_MCUSR
{
    bool porf  :1;				///< Power-on Reset Flag
    bool extrf :1;				///< External Reset Flag
    bool borf  :1;				///< Brown-out Reset Flag
    bool wdrf  :1;				///< Watchdog Reset Flag
    bool jtrf  :1;				///< JTAG Reset Flag

    /// @cond
    unsigned char reserved :1;
    /// @endcond
    unsigned char isc2 :1;		///< External Interrupt 2 Sense Control Bits
    volatile bool jtd   :1;		///< JTAG Interface Disable
} ATmega32_AVR_MCUSR;
typedef ATmega32_AVR_MCUSR AVR_MCUSR;	///< Microcontroller Unit Status Register type
typedef AVR_MCUSR* AVRP_MCUSR;			///< Pointer to Microcontroller Unit Status Register type

DECLARE_REGT(MCUSR);					///< Microcontroller Unit Status Register declaration

/**
 * @brief Microcontroller Unit Control Register
 */
typedef struct _ATmega32_AVR_MCUCR
{
    unsigned char isc0  :2;			///< External Interrupt 0 Sense Control Bits
    unsigned char isc1  :2;			///< External Interrupt 1 Sense Control Bits
    unsigned char sm :3;			///< Sleep Mode Select Bits
    bool se          :1;			///< Sleep Enable
} ATmega32_AVR_MCUCR, *AVRP_MCUCR;
typedef ATmega32_AVR_MCUCR AVR_MCUCR;	///< Sleep Mode Control Register type
typedef AVR_MCUCR* AVRP_MCUCR;			///< Pointer to Sleep Mode Control Register type

DECLARE_REGT(MCUCR);					///< Microcontroller Unit Control Register declaration

#define _AVR_EXTINTCTRL _AVR_MCU		///< External Interrupts Control Registers structure macro
#define AVR_EXTINTCTRL  AVR_MCU			///< External Interrupts Control Registers structure macro
#define AVRP_EXTINTCTRL AVRP_MCU		///< Pointer to External Interrupts Control Registers structure macro

#define eicra mcucr				///< External Interrupts Control Register A macro
#define eicrb mcusr				///< External Interrupts Control Register B macro

/**
 * @brief Microcontroller Unit Registers structure
 */
typedef struct _AVR_MCU
{
    MCUSR_REG mcusr;			///< Microcontroller Unit Status Register
    MCUCR_REG mcucr;			///< Microcontroller Unit Control Register
} AVR_MCU;
typedef AVR_MCU* AVRP_MCU;		///< Pointer to Microcontroller Unit Registers structure type

/**
 * @brief Special Function I/O Register
 */
typedef struct _AVR_SFIOR
{
	volatile bool psr10 :1;		///< Prescaler Reset Timer/Counter 1 and Timer/Counter 0
	volatile bool psr2 :1;		///< Prescaler Reset Timer/Counter 2
	bool pud :1;				///< Pull-up disable
	bool acme :1;				///< Analog Comparator Multiplexer Enable

	/// @cond
	unsigned char reserved :1;
	/// @endcond
	unsigned char adts :3;		///< ADC Auto Trigger Source
} AVR_SFIOR;
typedef AVR_SFIOR* AVRP_SFIOR;	///< Pointer to Special Function I/O Register type

DECLARE_REGT(SFIOR);			///< Special Function I/O Register declaration

/**
 * @brief Special Function I/O registers structure
 */
typedef struct _AVR_SFIORS
{
	SFIOR_REG sfior;				///< Special Function I/O Register
} AVR_SFIORS;
typedef AVR_SFIORS* AVRP_SFIORS;	///< Pointer to Special Function I/O registers structure type

/**
 * @brief Store Program Memory Control and Status Register
 */
typedef struct _AVR_SPMCSR
{
    volatile bool selfprgen :1;	///< Self Programming Enable
    bool pgers  :1;				///< Page Erase
    bool pgwrt  :1;				///< Page Write
    bool blbset :1;				///< Boot Lock Bit Set
    bool rwwsre :1;				///< Read-While-Write Section Read Enable

    /// @cond
    bool reserved :1;
    /// @endcond
    volatile bool rwwsb  :1;	///< Read-While-Write Section Busy
    bool spmie  :1;				///< SPM Interrupt Enable
} AVR_SPMCSR;
typedef AVR_SPMCSR* AVRP_SPMCSR;		///< Pointer to Store Program Memory Control and Status Register type

DECLARE_REGT(SPMCSR);					///< Store Program Memory Control and Status Register declaration

/**
 * @brief Store Program Memory registers structure
 */
typedef struct _AVR_SPM
{
	SPMCSR_REG spmcsr;			///< Store Program Memory Control and Status Register
} AVR_SPM;
typedef AVR_SPM* AVRP_SPM;		///< Pointer to Store Program Memory registers structure type

/**
 * @brief Status Register
 */
typedef struct _AVR_SREG
{
    volatile bool carry :1;			///< Carry Flag
    volatile bool zero :1;			///< Zero Flag
    volatile bool negative :1;		///< Negative Flag
    volatile bool twoCompOvf :1;	///< Two's Complement Overflow Flag
    volatile bool sign :1;			///< Sign Bit
    volatile bool halfCarry :1;		///< Half Carry Flag
    bool bitCopy :1;				///< Bit Copy Storage
    bool intEn :1;					///< Global Interrupts Enable
} AVR_SREG;
typedef AVR_SREG* AVRP_SREG;		///< Pointer to Status Register type

/**
 * @brief Watchdog Timer Control and Status Register
 */
typedef struct _ATmega32_AVR_WDTCSR
{
    unsigned char wdp :3;			///< Watchdog Timer Prescaler
    bool wde :1;					///< Watchdog System Reset Enable
    bool wdce :1;					///< Watchdog Change Enable
} ATmega32_AVR_WDTCSR;
typedef ATmega32_AVR_WDTCSR AVR_WDTCSR;	///< Watchdog Timer Control and Status Register type
typedef AVR_WDTCSR* AVRP_WDTCSR;		///< Pointer to Watchdog Timer Control and Status Register type

#define WDCE WDTOE						///< Watchdog Turn-off Enable Bit macro

DECLARE_REGT(WDTCSR);					///< Watchdog Timer Control and Status Register declaration

/**
 * @brief Watchdog Timer registers structure
 */
typedef struct _AVR_WATCHDOG
{
	volatile WDTCSR_REG wdtcsr;			///< Watchdog Timer Control and Status Register
} AVR_WATCHDOG;
typedef AVR_WATCHDOG* AVRP_WATCHDOG;	///< Pointer to Watchdog Timer registers structure type

/**
 * @brief Clock Prescale registers structure
 */
typedef struct _AVR_CLKPR
{
	volatile AVR_REG clkpr;			///< Clock Prescale Register
} AVR_CLKPR;
typedef AVR_CLKPR* AVRP_CLKPR;		///< Pointer to Clock Prescale registers structure type

/**
 * @brief Pin Change Interrupt Mask Register
 */
typedef struct _AVR_PCMSK
{
	bool pcint0 :1;				///< Pin Change Enable Mask
	bool pcint1 :1;				///< Pin Change Enable Mask
	bool pcint2 :1;				///< Pin Change Enable Mask
	bool pcint3 :1;				///< Pin Change Enable Mask
	bool pcint4 :1;				///< Pin Change Enable Mask
	bool pcint5 :1;				///< Pin Change Enable Mask
	bool pcint6 :1;				///< Pin Change Enable Mask
	bool pcint7 :1;				///< Pin Change Enable Mask
} AVR_PCMSK;
typedef AVR_PCMSK* AVRP_PCMSK;	///< Pointer to Pin Change Interrupt Mask Register type

DECLARE_REGT(PCMSK);			///< Pin Change Interrupt Mask Register declaration

/**
 * @brief 8-bit Timer/Counter 0 Mask Register
 */
typedef struct _AVR_TIMSK_A
{
    bool toie :1;				///< Overflow Interrupt Enable
    bool ociea :1;				///< Output Compare A Match Interrupt Enable
} AVR_TIMSK_A;
typedef AVR_TIMSK_A AVR_TIMSK0;		///< 8-bit Timer/Counter 0 Mask Register type
typedef AVR_TIMSK0* AVRP_TIMSK0;	///< Pointer to 8-bit Timer/Counter 0 Mask Register type

DECLARE_REGT(TIMSK0);				///< 8-bit Timer/Counter Mask Register declaration

/**
 * @brief 8-bit Timer/Counter 2 Mask Register
 */
typedef struct _AVR_TIMSK2
{
	/// @cond
    unsigned char reserved : 6;
    /// @endcond
    bool toie :1;				///< Overflow Interrupt Enable
    bool ociea :1;				///< Output Compare A Match Interrupt Enable
} AVR_TIMSK2;
typedef AVR_TIMSK2* AVRP_TIMSK2;	///< Pointer to 8-bit Timer/Counter 2 Mask Register type

DECLARE_REGT(TIMSK2);				///< 8-bit Timer/Counter 2 Mask Register declaration

/**
 * @brief 16-bit Timer/Counter Mask Register
 */
typedef struct _AVR_TIMSKW1
{
	/// @cond
    unsigned char reserved : 2;
    /// @endcond
    bool toie :1;				///< Overflow Interrupt Enable
    bool ociea :1;				///< Output Compare A Match Interrupt Enable
    bool ocieb :1;				///< Output Compare B Match Interrupt Enable
    bool icie :1;				///< Input Capture Interrupt Enable
} AVR_TIMSKW1;
typedef AVR_TIMSKW1 AVR_TIMSKW;		///< 16-bit Timer/Counter 1 Mask Register type
typedef AVR_TIMSKW* AVRP_TIMSKW;	///< Pointer to 16-bit Timer/Counter 1 Mask Register type

DECLARE_REGT(TIMSKW);				///< 16-bit Timer/Counter Mask Register declaration

/**
 * @brief ADC Control and Status Register A
 */
typedef struct _AVR_ADCSRA {
	unsigned char adps :3;			///< ADC Prescaler Select Bits
	bool adie  :1;					///< ADC Interrupt Enable
	volatile bool adif  :1;			///< ADC Interrupt Flag
	bool adate :1;					///< ADC Auto Trigger Enable
	bool adsc  :1;					///< ADC Start Conversion
	bool aden  :1;					///< ADC Enable
} AVR_ADCSRA;
typedef AVR_ADCSRA* AVRP_ADCSRA;	///< Pointer to ADC Control and Status Register A type

DECLARE_REGT(ADCSRA);				///< ADC Control and Status Register A declaration

/**
 * @brief Analog Multiplexer Selection Register
 */
typedef struct _AVR_ADMUX
{
    unsigned char mux :5;			///< Analog Channel and Gain Selection Bits
    bool adlar :1;					///< ADC Left Adjust Result
    unsigned char refs :2;			///< Reference Selection Bits
} AVR_ADMUX;
typedef AVR_ADMUX* AVRP_ADMUX;		///< Pointer to Analog Multiplexer Selection Register type

DECLARE_REGT(ADMUX);				///< Analog Multiplexer Selection Register declaration

/**
 * @brief Analog Multiplexer Registers structure
 */
typedef struct _ATmega32_AVR_AMUX
{
    volatile AVR_REGW   adc;		///< The ADC Data Register
    ADCSRA_REG adcsra;				///< ADC Control and Status Register A
    ADMUX_REG  admux;				///< ADC Multiplexer Selection Register
} ATmega32_AVR_AMUX;
typedef ATmega32_AVR_AMUX AVR_AMUX;		///< Analog Multiplexer Registers structure type
typedef AVR_AMUX* AVRP_AMUX;			///< Pointer to Analog Multiplexer Registers structure type

/**
 * @brief Asynchronous Status Register
 */
typedef struct _ATmega32_AVR_ASSR
{
    volatile bool tcr2aub :1;		///< Timer/Counter Control Register 2A Update Busy
    volatile bool ocr2aub :1;		///< Output Compare Register 2A Update Busy
    volatile bool tcn2ub :1;		///< Timer/Counter 2 Update Busy
    bool as2 :1;					///< Asynchronous Timer/Counter 2
} ATmega32_AVR_ASSR;
typedef ATmega32_AVR_ASSR AVR_ASSR;	///< Asynchronous Status Register type
typedef AVR_ASSR* AVRP_ASSR;		///< Pointer to Asynchronous Status Register type

DECLARE_REGT(ASSR);					///< Asynchronous Status Register declaration

/**
 * @brief Asynchronous Status Registers structure
 */
typedef struct _AVR_ASYNCST
{
    ASSR_REG   assr;				///< Asynchronous Status Register
} AVR_ASYNCST;
typedef AVR_ASYNCST* AVRP_ASYNCST;	///< Pointer to Asynchronous Status Registers structure type

/**
 * @brief Two-Wire Status Register
 */
typedef struct _AVR_TWSR
{
    unsigned char twps :2;			///< TWI Prescaler Bits

    /// @cond
    unsigned char reserved :1;
    /// @endcond
    volatile unsigned char tws :5;	///< TWI Status
} AVR_TWSR;
typedef AVR_TWSR* AVRP_TWSR;		///< Pointer to Two-Wire Status Register type

DECLARE_REGT(TWSR);					///< Two-Wire Status Register declaration

/**
 * @brief Two-Wire Address Register
 */
typedef struct _AVR_TWAR
{
	bool twgce :1;					///< TWI General Call Recognition Enable Bit
    unsigned char twa :7;			///< TWI (Slave) Address Register
} AVR_TWAR;
typedef AVR_TWAR* AVRP_TWAR;		///< Pointer to Two-Wire Address Register type

DECLARE_REGT(TWAR);					///< Two-Wire Address Register declaration

/**
 * @brief Two-Wire Control Register
 */
typedef struct _AVR_TWCR
{
	bool twie :1;					///< TWI Interrupt Enable

	/// @cond
    unsigned char reserved :1;
    /// @endcond
	bool twen :1;					///< TWI Enable Bit
	volatile bool twwc :1;			///< TWI Write Collision Flag
	bool twsto :1;					///< TWI STOP Condition Bit
	bool twsta :1;					///< TWI START Condition Bit
	bool twea :1;					///< TWI Enable Acknowledge Bit
	volatile bool twint :1;			///< TWI Interrupt Flag
} AVR_TWCR;
typedef AVR_TWCR* AVRP_TWCR;		///< Pointer to Two-Wire Control Register type

DECLARE_REGT(TWCR);					///< Two-Wire Control Register declaration

/**
 * @brief Two-Wire Address Mask Register
 */
typedef struct _AVR_TWAMR
{
	/// @cond
    unsigned char reserved :1;
    /// @endcond
    unsigned char twam :7;			///< TWI Address Mask
} AVR_TWAMR;
typedef AVR_TWAMR* AVRP_TWAMR;		///< Pointer to Two-Wire Address Mask Register type

DECLARE_REGT(TWAMR);				///< Two-Wire Address Mask Register declaration

/**
 * @brief Two-Wire registers structure
 */
typedef struct _ATmega32_AVR_TWI
{
    AVR_REG    twbr;				///< TWI Bit Rate Register
    TWSR_REG   twsr;				///< TWI Status Register
    TWAR_REG   twar;				///< TWI (Slave) Address Register
    volatile AVR_REG twdr;			///< TWI Data Register
} ATmega32_AVR_TWI;
typedef ATmega32_AVR_TWI AVR_TWI;	///< Two-Wire registers structure type
typedef AVR_TWI* AVRP_TWI;			///< Pointer to Two-Wire registers structure type

/**
 * @brief USART Control and Status Register A
 */
typedef struct _AVR_UCSRA
{
    bool mpcm :1;					///< Multi-processor Communication Mode
    bool u2x :1;					///< Double the USART Transmission Speed
    volatile bool upe :1;			///< USART Parity Error
    volatile bool dor :1;			///< Data OverRun
    volatile bool fe :1;			///< Frame Error
    volatile bool udre :1;			///< USART Data Register Empty
    volatile bool txc :1;			///< USART Transmit Complete
    volatile bool rxc :1;			///< USART Receive Complete
} AVR_UCSRA;
typedef AVR_UCSRA* AVRP_UCSRA;		///< Pointer to USART Control and Status Register A type

DECLARE_REGT(UCSRA);				///< USART Control and Status Register A declaration

/**
 * @brief USART Control and Status Register B
 */
typedef struct _AVR_UCSRB
{
    bool txb8 :1;					///< Transmit Data Bit 8
    bool rxb8 :1;					///< Receive Data Bit 8
    bool ucsz2 :1;					///< Character Size
    bool txen :1;					///< Transmitter Enable
    bool rxen :1;					///< Receiver Enable
    bool udrie :1;					///< USART Data Register Empty Interrupt Enable
    bool txcie :1;					///< TX Complete Interrupt Enable
    bool rxcie :1;					///< RX Complete Interrupt Enable
} AVR_UCSRB;
typedef AVR_UCSRB* AVRP_UCSRB;		///< Pointer to USART Control and Status Register B type

DECLARE_REGT(UCSRB);				///< USART Control and Status Register B declaration

/**
 * @brief USART Control and Status Register C
 */
typedef struct _ATmega32_AVR_UCSRC
{
	bool ucpol :1;					///< Clock Polarity
	unsigned char ucsz :2;			///< Character Size
	bool usbs :1;					///< Stop Bit Select
	unsigned char upm :2;			///< Parity Mode
	unsigned char umsel :1;			///< USART Mode Select
    bool ursel :1;					///< UCSRC Register Select
} ATmega32_AVR_UCSRC;
typedef ATmega32_AVR_UCSRC AVR_UCSRC;	///< USART Control and Status Register C type
typedef AVR_UCSRC* AVRP_UCSRC;			///< Pointer to USART Control and Status Register C type

DECLARE_REGT(UCSRC);				///< USART Control and Status Register C declaration

/**
 * @brief USART registers structure
 */
typedef struct _ATmega32_AVR_USART
{
    AVR_REG   ubrrl;				///< USART Baud Rate Register LSB
    UCSRB_REG ucsrb;				///< USART Control and Status Register B
    UCSRA_REG ucsra;				///< USART Control and Status Register A
    volatile AVR_REG   udr;			///< USART Data Register
} ATmega32_AVR_USART;
typedef ATmega32_AVR_USART AVR_USART;	///< USART registers structure type
typedef AVR_USART* AVRP_USART;			///< Pointer to USART registers structure type

/**
 * @}
 */
#endif /* AVRDEF_ATMEGA32_H_ */
