/**
 * @file ve_avrdef_atmega2560.h
 * @brief ATmega2560 Register structure definitions
 * @author andrey
 * @date 20.12.2012
 * @copyright GNU Public License
 */
#ifndef AVRDEF_ATMEGA2560_H_
#define AVRDEF_ATMEGA2560_H_

/**
 * @addtogroup ATmega2560
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
 * @brief 8-bit Timer/Counter Interrupt Flag Register
 */
typedef struct _AVR_TIFR
{
    volatile bool tov  :1;		///< Overflow Flag
    volatile bool ocfa :1;		///< Output Compare A Flag
    volatile bool ocfb :1;		///< Output Compare B Flag
} AVR_TIFR;
typedef AVR_TIFR* AVRP_TIFR;	///< Pointer to 8-bit Timer/Counter Interrupt Flag Register type

DECLARE_REGT(TIFR);				///< 8-bit Timer/Counter Interrupt Flag Register declaration

/**
 * @brief 16-bit Timer/Counter Interrupt Flag Register
 */
typedef struct _AVR_TIFRW_C
{
    volatile bool tov  :1;		///< Overflow Flag
    volatile bool ocfa :1;		///< Output Compare A Flag
    volatile bool ocfb :1;		///< Output Compare B Flag
    volatile bool ocfc :1;		///< Output Compare C Flag

    /// @cond
    unsigned int reserved: 1;
    /// @endcond
    volatile bool icf  :1;		///< Input Capture Flag
} AVR_TIFRW_C;
typedef AVR_TIFRW_C AVR_TIFRW;	///< 16-bit Timer/Counter Interrupt Flag Register type
typedef AVR_TIFRW* AVRP_TIFRW;	///< Pointer to 16-bit Timer/Counter Interrupt Flag Register type

DECLARE_REGT(TIFRW);			///< 16-bit Timer/Counter Interrupt Flag Register declaration

/**
 * @brief Pin Change Interrupt Flag Register
 */
typedef struct _AVR_PCIFR
{
    volatile bool pcif0 :1;		///< Pin Change Interrupt Flag
    volatile bool pcif1 :1;		///< Pin Change Interrupt Flag
    volatile bool pcif2 :1;		///< Pin Change Interrupt Flag
} AVR_PCIFR;
typedef AVR_PCIFR* AVRP_PCIFR;	///< Pointer to Pin Change Interrupt Flag Register type

DECLARE_REGT(PCIFR);			///< Pin Change Interrupt Flag Register declaration

/**
 * @brief Pin Change Interrupt Flags registers structure
 */
typedef struct _AVR_PCIFLAGS
{
	PCIFR_REG pcifr;			///< Pin Change Interrupt Flags Register
} AVR_PCIFLAGS;
typedef AVR_PCIFLAGS* AVRP_PCIFLAGS;	///< Pointer to Pin Change Interrupt Flags Register type

/**
 * @brief Pin Change Interrupt Control Register
 */
typedef struct _ATmega2560_AVR_PCICR
{
    bool pcie0 :1;				///< Pin Change Interrupt Enable 0
    bool pcie1 :1;				///< Pin Change Interrupt Enable 1
    bool pcie2 :1;				///< Pin Change Interrupt Enable 2
} ATmega2560_AVR_PCICR;
typedef ATmega2560_AVR_PCICR AVR_PCICR;		///< Pin Change Interrupt Control Register type
typedef AVR_PCICR* AVRP_PCICR;				///< Pointer to Pin Change Interrupt Control Register type

DECLARE_REGT(PCICR);						///< Pin Change Interrupt Control Register declaration

/**
 * @brief Pin Change Interrupt Control registers structure
 */
typedef struct _AVR_PCICTRL
{
	PCICR_REG pcicr;				///< Pin Change Interrupt Control Register
} AVR_PCICTRL;
typedef AVR_PCICTRL* AVRP_PCICTRL;	///< Pointer to Pin Change Interrupt Control registers structure type

/**
 * @brief External Interrupt Control Register
 */
typedef struct _ATmega2560_AVR_EIMSK
{
    bool int0 :1;				///< External Interrupt Request Enable
    bool int1 :1;				///< External Interrupt Request Enable
    bool int2 :1;				///< External Interrupt Request Enable
    bool int3 :1;				///< External Interrupt Request Enable
    bool int4 :1;				///< External Interrupt Request Enable
    bool int5 :1;				///< External Interrupt Request Enable
    bool int6 :1;				///< External Interrupt Request Enable
    bool int7 :1;				///< External Interrupt Request Enable
} ATmega2560_AVR_EIMSK;
typedef ATmega2560_AVR_EIMSK AVR_EIMSK;	///< External Interrupt Control Register type
typedef AVR_EIMSK* AVRP_EIMSK;			///< Pointer to External Interrupt Control Register type

DECLARE_REGT(EIMSK);					///< External Interrupt Control Register declaration

/**
 * @brief External Interrupt Flag Register
 */
typedef struct _ATmega2560_AVR_EIFR
{
    volatile bool intf0 :1;				///< External Interrupt Flag
    volatile bool intf1 :1;				///< External Interrupt Flag
    volatile bool intf2 :1;				///< External Interrupt Flag
    volatile bool intf3 :1;				///< External Interrupt Flag
    volatile bool intf4 :1;				///< External Interrupt Flag
    volatile bool intf5 :1;				///< External Interrupt Flag
    volatile bool intf6 :1;				///< External Interrupt Flag
    volatile bool intf7 :1;				///< External Interrupt Flag
} ATmega2560_AVR_EIFR;
typedef ATmega2560_AVR_EIFR AVR_EIFR;	///< External Interrupt Flag Register type
typedef AVR_EIFR* AVRP_EIFR;			///< Pointer to External Interrupt Flag Register type

DECLARE_REGT(EIFR);						///< External Interrupt Flag Register declaration

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
typedef struct _AVR_EECR
{
    volatile bool eere  :1;		///< EEPROM Read Enable
    volatile bool eepe  :1;		///< EEPROM Programming Enable
    bool eempe :1;				///< EEPROM Master Programming Enable
    bool eerie :1;				///< EEPROM Ready Interrupt Enable
    bool eepm  :2;				///< EEPROM Programming Mode
} AVR_EECR;
typedef AVR_EECR* AVRP_EECR;	///< Pointer to EEPROM Control Register type

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
	GTCCR_REG gtccr;			///< General Timer/Counter Control Register
} AVR_GTCCRS;
typedef AVR_GTCCRS* AVRP_GTCCRS;	///< Pointer to General Timer/Counter Control registers structure type

/**
 * @brief 8-bit Timer/Counter Control Register A
 */
typedef struct _AVR_TCCRA
{
    unsigned char wgm :2;		///< Waveform Generation Mode

    /// @cond
    unsigned char reserved :2;
    /// @endcond
    unsigned char comb :2;		///< Compare Match Output B Mode
    unsigned char coma :2;		///< Compare Match Output A Mode
} AVR_TCCRA;
typedef AVR_TCCRA* AVRP_TCCRA;	///< Pointer to 8-bit Timer/Counter Control Register A type

DECLARE_REGT(TCCRA);			///< 8-bit Timer/Counter Control Register A declaration

/**
 * @brief 8-bit Timer/Counter Control Register B
 */
typedef struct _AVR_TCCRB
{
    unsigned char cs :3;		///< Clock Select
    unsigned char wgm2 :1;		///< Waveform Generation Mode

    /// @cond
    unsigned char reserved :2;
    /// @endcond
    bool focb :1;				///< Force Output Compare B
    bool foca :1;				///< Force Output Compare A
} AVR_TCCRB;
typedef AVR_TCCRB* AVRP_TCCRB;	///< Pointer to 8-bit Timer/Counter Control Register B type

DECLARE_REGT(TCCRB);			///< 8-bit Timer/Counter Control Register B declaration

/**
 * @brief 8-bit Timer/Counter registers structure
 */
typedef struct _AVR_TIMER
{
    TCCRA_REG tccra;			///< Timer/Counter Control Register A
    TCCRB_REG tccrb;			///< Timer/Counter Control Register B
    AVR_REG   tcnt;				///< Timer/Counter Register
    AVR_REG   ocra;				///< Timer/Counter Output Compare Register A
    AVR_REG   ocrb;				///< Timer/Counter Output Compare Register B
} AVR_TIMER;
typedef AVR_TIMER* AVRP_TIMER; 	///< Pointer to 8-bit Timer/Counter registers structure type

/**
 * @brief 16-bit Timer/Counter Control Register A
 */
typedef struct _AVR_TCCRWA_C
{
    unsigned char wgml :2;			///< Waveform Generation Mode LSB
    unsigned char comc :2;			///< Compare Output Mode for Channel C
    unsigned char comb :2;			///< Compare Output Mode for Channel B
    unsigned char coma :2;			///< Compare Output Mode for Channel A
} AVR_TCCRWA_C;
typedef AVR_TCCRWA_C AVR_TCCRWA;	///< 16-bit Timer/Counter Control Register A type
typedef AVR_TCCRWA* AVRP_TCCRWA;	///< Pointer to 16-bit Timer/Counter Control Register A type

DECLARE_REGT(TCCRWA);				///< 16-bit Timer/Counter Control Register A declaration

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
 * @brief 16-bit Timer/Counter Control Register C
 */
typedef struct _AVR_TCCRWC_C
{
	/// @cond
    unsigned char reserved :5;
    /// @endcond
    bool focc :1;					///< Force Output Compare for Channel C
    bool focb :1;					///< Force Output Compare for Channel B
    bool foca :1;					///< Force Output Compare for Channel A
} AVR_TCCRW_C;
typedef AVR_TCCRW_C AVR_TCCRWC;		///< 16-bit Timer/Counter Control Register C type
typedef AVR_TCCRWC* AVRP_TCCRWC;	///< Pointer to 16-bit Timer/Counter Control Register C type

DECLARE_REGT(TCCRWC);				///< 16-bit Timer/Counter Control Register C declaration

/**
 * @brief 16-bit Timer/Counter Registers structure
 */
typedef struct _AVR_TIMERW_C
{
    TCCRWA_REG tccra;				///< 16-bit Timer/Counter Control Register A
    TCCRWB_REG tccrb;				///< 16-bit Timer/Counter Control Register B
    TCCRWC_REG tccrc;				///< 16-bit Timer/Counter Control Register C

    /// @cond
    AVR_REG    reserved;
    /// @endcond
    volatile AVR_REGW tcnt;			///< 16-bit Timer/Counter
    volatile AVR_REGW icr;			///< 16-bit Timer/Counter Input Capture Register
    AVR_REGW   ocra;				///< 16-bit Timer/Counter Output Compare Register A
    AVR_REGW   ocrb;				///< 16-bit Timer/Counter Output Compare Register B
    AVR_REGW   ocrc;				///< 16-bit Timer/Counter Output Compare Register C
} AVR_TIMERW_C;
typedef AVR_TIMERW_C AVR_TIMERW;	///< 16-bit Timer/Counter Registers structure type
typedef AVR_TIMERW* AVRP_TIMERW;	///< Pointer to 16-bit Timer/Counter Registers structure type

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
typedef struct _AVR_MCUSR
{
    bool porf  :1;				///< Power-on Reset Flag
    bool extrf :1;				///< External Reset Flag
    bool borf  :1;				///< Brown-out Reset Flag
    bool wdrf  :1;				///< Watchdog Reset Flag
    bool jtrf  :1;				///< JTAG Reset Flag
} AVR_MCUSR;
typedef AVR_MCUSR* AVRP_MCUSR;	///< Pointer to Microcontroller Unit Status Register type

DECLARE_REGT(MCUSR);			///< Microcontroller Unit Status Register declaration

/**
 * @brief Microcontroller Unit Control Register
 */
typedef struct _AVR_MCUCR
{
    volatile unsigned char iv  :2;		///< Interrupt Vector Select

    /// @cond
    unsigned char reserved :2;
    /// @endcond
    bool pud   :1;						///< Pull-up Disable

    /// @cond
    unsigned char reserved_ :2;
    /// @endcond
    volatile bool jtd   :1;				///< JTAG Interface Disable
} AVR_MCUCR;
typedef AVR_MCUCR* AVRP_MCUCR;			///< Pointer to Microcontroller Unit Control Register type

DECLARE_REGT(MCUCR);					///< Microcontroller Unit Control Register declaration

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
 * @brief Store Program Memory Control and Status Register
 */
typedef struct _AVR_SPMCSR_SIGRD
{
    volatile bool selfprgen :1;	///< Self Programming Enable
    bool pgers  :1;				///< Page Erase
    bool pgwrt  :1;				///< Page Write
    bool blbset :1;				///< Boot Lock Bit Set
    bool rwwsre :1;				///< Read-While-Write Section Read Enable
    bool sigrd  :1;				///< Signature Row Read
    volatile bool rwwsb  :1;	///< Read-While-Write Section Busy
    bool spmie  :1;				///< SPM Interrupt Enable
} AVR_SPMCSR_SIGRD;
typedef AVR_SPMCSR_SIGRD AVR_SPMCSR;	///< Store Program Memory Control and Status Register type
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
typedef struct _AVR_WDTCSR
{
    unsigned char wdp :3;			///< Watchdog Timer Prescaler
    bool wde :1;					///< Watchdog System Reset Enable
    bool wce :1;					///< Watchdog Change Enable
    unsigned char wdp3 :1;			///< Watchdog Timer Prescaler Bit 3
    bool wdie :1;					///< Watchdog Interrupt Enable
    volatile bool wdif :1;			///< Watchdog Interrupt Flag
} AVR_WDTCSR;
typedef AVR_WDTCSR* AVRP_WDTCSR;	///< Pointer to Watchdog Timer Control and Status Register type

DECLARE_REGT(WDTCSR);				///< Watchdog Timer Control and Status Register declaration

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
 * @brief Power Reduction Register 0
 */
typedef struct _ATmega2560_AVR_PRR0
{
    bool pradc :1;					///< Power Reduction ADC
    bool prusart0 :1;				///< Power Reduction USART0
    bool prspi :1;					///< Power Reduction Serial Peripheral Interface
    bool prtim1 :1;					///< Power Reduction Timer/Counter 1

    /// @cond
    bool reserved :1;
    /// @endcond
    bool prtim0 :1;					///< Power Reduction Timer/Counter 0
    bool prtim2 :1;					///< Power Reduction Timer/Counter 2
    bool prtwi :1;					///< Power Reduction TWI
} ATmega2560_AVR_PRR0;
typedef ATmega2560_AVR_PRR0 AVR_PRR0;	///< Power Reduction Register 0 type
typedef AVR_PRR0* AVRP_PRR0;			///< Pointer to Power Reduction Register 0 type

DECLARE_REGT(PRR0);						///< Power Reduction Register 0 declaration

/**
 * @brief Power Reduction Register 1
 */
typedef struct _ATmega2560_AVR_PRR1
{
    bool prusart1 :1;				///< Power Reduction USART1
    bool prusart2 :1;				///< Power Reduction USART2
    bool prusart3 :1;				///< Power Reduction USART3
    bool prtim3 :1;					///< Power Reduction Timer/Counter 3
    bool prtim4 :1;					///< Power Reduction Timer/Counter 4
    bool prtim5 :1;					///< Power Reduction Timer/Counter 5
} ATmega2560_AVR_PRR1;
typedef ATmega2560_AVR_PRR1 AVR_PRR1;	///< Power Reduction Register 1 type
typedef AVR_PRR1* AVRP_PRR1;			///< Pointer to Power Reduction Register 1 type

DECLARE_REGT(PRR1);						///< Power Reduction Register 1 declaration

/**
 * @brief Power Reduction Registers structure
 */
typedef struct _AVR_POWER
{
    PRR0_REG prr0;					///< Power Reduction Register 0
    PRR1_REG prr1;					///< Power Reduction Register 1
} AVR_POWER;
typedef AVR_POWER* AVRP_POWER;		///< Pointer to Power Reduction Registers structure type

/**
 * @brief External Interrupt Control Register A
 */
typedef struct _AVR_EICRA
{
    unsigned char isc0 :2;			///< External Interrupt 0 Sense Control Bits
    unsigned char isc1 :2;			///< External Interrupt 1 Sense Control Bits
    unsigned char isc2 :2;			///< External Interrupt 2 Sense Control Bits
    unsigned char isc3 :2;			///< External Interrupt 3 Sense Control Bits
} AVR_EICRA;
typedef AVR_EICRA* AVRP_EICRA;				///< Pointer to External Interrupt Control Register A type

DECLARE_REGT(EICRA);						///< External Interrupt Control Register A declaration

/**
 * @brief External Interrupt Control Register B
 */
typedef struct _AVR_EICRB
{
    unsigned char isc4 :2;			///< External Interrupt 4 Sense Control Bits
    unsigned char isc5 :2;			///< External Interrupt 5 Sense Control Bits
    unsigned char isc6 :2;			///< External Interrupt 6 Sense Control Bits
    unsigned char isc7 :2;			///< External Interrupt 7 Sense Control Bits
} AVR_EICRB;
typedef AVR_EICRB* AVRP_EICRB;				///< Pointer to External Interrupt Control Register B type

DECLARE_REGT(EICRB);						///< External Interrupt Control Register B declaration

/**
 * @brief External Interrupt Control registers structure
 */
typedef struct _AVR_EXTINTCTRL_AB
{
	EICRA_REG eicra;				///< External Interrupt Control Register A
	EICRB_REG eicrb;				///< External Interrupt Control Register B
} AVR_EXTINTCTRL_AB;
typedef AVR_EXTINTCTRL_AB AVR_EXTINTCTRL; 	///< External Interrupt Control registers structure type
typedef AVR_EXTINTCTRL* AVRP_EXTINTCTRL; 	///< Pointer to External Interrupt Control registers structure type

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
 * @brief Pin Change Interrupt Mask registers structure
 */
typedef struct _AVR_PCIMASK
{
	PCMSK_REG pcmsk0;			///< Pin Change Interrupt Mask Register
	PCMSK_REG pcmsk1;			///< Pin Change Interrupt Mask Register
	PCMSK_REG pcmsk2;			///< Pin Change Interrupt Mask Register
} AVR_PCIMASK;
typedef AVR_PCIMASK* AVRP_PCIMASK;	///< Pointer to Pin Change Interrupt Mask registers structure type

/**
 * @brief 8-bit Timer/Counter Mask Register
 */
typedef struct _AVR_TIMSK
{
    bool toie :1;				///< Overflow Interrupt Enable
    bool ociea :1;				///< Output Compare A Match Interrupt Enable
    bool ocieb :1;				///< Output Compare B Match Interrupt Enable
} AVR_TIMSK;
typedef AVR_TIMSK* AVRP_TIMSK;	///< Pointer to 8-bit Timer/Counter Mask Register type

DECLARE_REGT(TIMSK);			///< 8-bit Timer/Counter Mask Register declaration

/**
 * @brief 16-bit Timer/Counter Mask Register
 */
typedef struct _AVR_TIMSKW_C
{
    bool toie :1;				///< Overflow Interrupt Enable
    bool ociea :1;				///< Output Compare A Match Interrupt Enable
    bool ocieb :1;				///< Output Compare B Match Interrupt Enable
    bool ociec :1;				///< Output Compare C Match Interrupt Enable

    /// @cond
    unsigned char reserved :1;
    /// @endcond
    bool icie :1;				///< Input Capture Interrupt Enable
} AVR_TIMSKW_C;
typedef AVR_TIMSKW_C AVR_TIMSKW;	///< 16-bit Timer/Counter Mask Register type
typedef AVR_TIMSKW* AVRP_TIMSKW;	///< Pointer to 16-bit Timer/Counter Mask Register type

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
 * @brief ADC Control and Status Register B
 */
typedef struct _ATmega2560_AVR_ADCSRB {
	unsigned char adts :3;			///< ADC Auto Trigger Source
	bool mux5 :1;					///< Analog Channel and Gain Selection Bit 5

	/// @cond
	unsigned char reserved :2;
	/// @endcond
	bool acme  :1;					///< Analog Comparator Multiplexer Enable
} ATmega2560_AVR_ADCSRB;
typedef ATmega2560_AVR_ADCSRB AVR_ADCSRB;	///< ADC Control and Status Register B type
typedef AVR_ADCSRB* AVRP_ADCSRB;			///< Pointer to ADC Control and Status Register B type

DECLARE_REGT(ADCSRB);						///< ADC Control and Status Register B declaration

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
typedef struct _AVR_AMUX
{
    volatile AVR_REGW   adc;		///< The ADC Data Register
    ADCSRA_REG adcsra;				///< ADC Control and Status Register A
    ADCSRB_REG adcsrb;				///< ADC Control and Status Register B
    ADMUX_REG  admux;				///< ADC Multiplexer Selection Register
    AVR_REGW   didr;				///< Digital Input Disable Register
    AVR_REG    didr1;				///< Digital Input Disable Register
} AVR_AMUX;
typedef AVR_AMUX* AVRP_AMUX;			///< Pointer to Analog Multiplexer Registers structure type

/**
 * @brief Asynchronous Status Register
 */
typedef struct _AVR_ASSR
{
    volatile bool tcr2bub :1;		///< Timer/Counter Control Register 2B Update Busy
    volatile bool tcr2aub :1;		///< Timer/Counter Control Register 2A Update Busy
    volatile bool ocr2bub :1;		///< Output Compare Register 2B Update Busy
    volatile bool ocr2aub :1;		///< Output Compare Register 2A Update Busy
    volatile bool tcn2ub :1;		///< Timer/Counter 2 Update Busy
    bool as2 :1;					///< Asynchronous Timer/Counter 2
    bool exclk :1;					///< Enable External Clock Input
} AVR_ASSR;
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
typedef struct _AVR_TWI
{
    AVR_REG    twbr;				///< TWI Bit Rate Register
    TWSR_REG   twsr;				///< TWI Status Register
    TWAR_REG   twar;				///< TWI (Slave) Address Register
    volatile AVR_REG twdr;			///< TWI Data Register
    TWCR_REG   twcr;				///< TWI Control Register
    TWAMR_REG  twamr;				///< TWI (Slave) Address Mask Register
} AVR_TWI;
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
typedef struct _AVR_UCSRC_MSPIM
{
	bool ucpol :1;					///< Clock Polarity
	unsigned char ucsz :2;			///< Character Size
	bool usbs :1;					///< Stop Bit Select
	unsigned char upm :2;			///< Parity Mode
	unsigned char umsel :2;			///< USART Mode Select
} AVR_UCSRC_MSPIM;
typedef AVR_UCSRC_MSPIM AVR_UCSRC;	///< USART Control and Status Register C type
typedef AVR_UCSRC* AVRP_UCSRC;		///< Pointer to USART Control and Status Register C type

DECLARE_REGT(UCSRC);				///< USART Control and Status Register C declaration

/**
 * @brief USART registers structure
 */
typedef struct _AVR_USART
{
    UCSRA_REG ucsra;				///< USART Control and Status Register A
    UCSRB_REG ucsrb;				///< USART Control and Status Register B
    UCSRC_REG ucsrc;				///< USART Control and Status Register C

    /// @cond
    AVR_REG   reserved;
    /// @endcond
    AVR_REGW  ubrr;					///< USART Baud Rate Register
    volatile AVR_REG   udr;			///< USART Data Register
} AVR_USART, *AVRP_USART;
typedef AVR_USART* AVRP_USART;		///< Pointer to USART registers structure type

/**
 * @brief External Memory Control Register A
 */
typedef struct _AVR_XMCRA
{
	unsigned char srw0: 2;			///< Wait-state Select Bits for Lower Sector
	unsigned char srw1: 2;			///< Wait-state Select Bits for Upper Sector
	unsigned char srl: 3;			///< Wait-state Sector Limit
	bool sre: 1;					///< External SRAM/XMEM Enable
} AVR_XMCRA;
typedef AVR_XMCRA* AVRP_XMCRA;		///< Pointer to External Memory Control Register A type

DECLARE_REGT(XMCRA);				///< External Memory Control Register A declaration

/**
 * @brief External Memory Control Register B
 */
typedef struct _AVR_XMCRB
{
	unsigned char xmm: 3;			///< External Memory High Mask

	/// @cond
	unsigned char reserved: 4;
	/// @endcond
	bool xmbk: 1;					///< External Memory Bus-keeper Enable
} AVR_XMCRB;
typedef AVR_XMCRB* AVRP_XMCRB;		///< Pointer to External Memory Control Register B type

DECLARE_REGT(XMCRB);				///< External Memory Control Register B declaration

/**
 * @brief External Memory Control registers structure
 */
typedef struct _AVR_EXTMEM
{
	XMCRA_REG xmcra;				///< External Memory Control Register A
	XMCRB_REG xmcrb;				///< External Memory Control Register B
} AVR_EXTMEM;
typedef AVR_EXTMEM* AVRP_EXTMEM;	///< Pointer to External Memory Control registers structure type

/**
 * @}
 */
#endif /* AVRDEF_ATMEGA2560_H_ */
