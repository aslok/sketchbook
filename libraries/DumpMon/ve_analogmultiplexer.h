/**
 * @file ve_analogmultiplexer.h
 * @brief Analog Comparator Multiplexed Input Header
 * @author andrey
 * @date 15.05.2012
 * @copyright GNU Public License
 */
#ifndef ANALOGMULTIPLEXER_H_
#define ANALOGMULTIPLEXER_H_

inline bool isADCEnabled();

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
    defined(VE_ATmega32U4) || \
    defined(VE_ATmega644PA) || \
    defined(VE_ATmega1284P)
#define ANALOGMUX_PARENT	AVR_AMUX	///< Analog Multiplexer parent class type
#endif

#if defined(VE_ATmega32)
typedef struct {
	unsigned char reserved[40];
} __AnalogMuxP;
#define ANALOGMUX_PARENT	AVR_AMUX, private __AnalogMuxP, public AVR_SFIORS
#endif

/**
 * @brief Analog Multiplexer class
 * @ingroup Analog
 */
class AnalogMux: public ANALOGMUX_PARENT
{
public:
	/**
	 * @brief Voltage Reference Select type
	 */
    typedef enum {
        AREF = 0,			///< AREF pin, Internal Vref turned off
        AVCC = 1,			///< AVCC with external capacitor at AREF pin
        Internal = 3		///< Internal 1.1V Voltage Reference with external capacitor at AREF pin
    } VoltageRef;

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P)
public:
    /**
     * @ingroup ATmega328P
     * @{
     */
    /**
     * @brief ATmega328P Digital Input Selection type
     */
    typedef enum {
        DI_ADC0 = 0,		///< ADC0
        DI_ADC1 = 1,		///< ADC1
        DI_ADC2 = 2,		///< ADC2
        DI_ADC3 = 3,		///< ADC3
        DI_ADC4 = 4,		///< ADC4
        DI_ADC5 = 5,		///< ADC5
        DI_AIN0 = 8,		///< AIN0
        DI_AIN1 = 9			///< AIN1
    } ATmega328P_DigitalInput;
    /**
     * @brief ATmega328P Digital Input Selection type
     */
    typedef ATmega328P_DigitalInput DigitalInput;
    /**
     * @brief ATmega328P Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,		///< ADC0
        ACNI_ADC1,			///< ADC1
        ACNI_ADC2,			///< ADC2
        ACNI_ADC3,			///< ADC3
        ACNI_ADC4,			///< ADC4
        ACNI_ADC5,			///< ADC5
        ACNI_ADC6,			///< ADC6
        ACNI_ADC7,			///< ADC7
        ACNI_AIN1			///< AIN1
    } ATmega328P_AnaCompNegInput;
    /**
     * @brief ATmega328P Analog Comparator Negative Input Selection type
     */
    typedef ATmega328P_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega328P Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,		///< ADC0 Single Ended Input
    	CH_ADC1,			///< ADC1 Single Ended Input
    	CH_ADC2,			///< ADC2 Single Ended Input
    	CH_ADC3,			///< ADC3 Single Ended Input
    	CH_ADC4,			///< ADC4 Single Ended Input
    	CH_ADC5,			///< ADC5 Single Ended Input
    	CH_ADC6,			///< ADC6 Single Ended Input
    	CH_ADC7,			///< ADC7 Single Ended Input
    	CH_TempSensor,		///< Temperature Sensor Single Ended Input
    	CH_1V1 = 14,		///< 1.1V Bandgap Vref Single Ended Input
    	CH_GND = 15			///< 0V (GND) Single Ended Input
    } ATmega328P_Channel;
    /**
     * @brief ATmega328P Analog Input Channel Selection
     */
    typedef ATmega328P_Channel Channel;
    /**
     * @}
     */
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560)
public:
    /**
     * @ingroup ATmega2560
     * @{
     */
    /**
     * @brief ATmega2560 Digital Input Selection type
     */
    typedef enum {
    	DI_ADC8,			///< ADC8
    	DI_ADC9,			///< ADC9
    	DI_ADC10,			///< ADC10
    	DI_ADC11,			///< ADC11
    	DI_ADC12,			///< ADC12
    	DI_ADC13,			///< ADC13
    	DI_ADC14,			///< ADC14
    	DI_ADC15,			///< ADC15
        DI_ADC0,			///< ADC0
        DI_ADC1,			///< ADC1
        DI_ADC2,			///< ADC2
        DI_ADC3,			///< ADC3
        DI_ADC4,			///< ADC4
        DI_ADC5,			///< ADC5
        DI_ADC6,			///< ADC6
        DI_ADC7,			///< ADC7
        DI_AIN0,			///< AIN0
        DI_AIN1				///< AIN1
    } ATmega2560_DigitalInput;
    /**
     * @brief ATmega2560 Digital Input Selection type
     */
    typedef ATmega2560_DigitalInput DigitalInput;
    /**
     * @brief ATmega2560 Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,		///< ADC0
        ACNI_ADC1,			///< ADC1
        ACNI_ADC2,			///< ADC2
        ACNI_ADC3,			///< ADC3
        ACNI_ADC4,			///< ADC4
        ACNI_ADC5,			///< ADC5
        ACNI_ADC6,			///< ADC6
        ACNI_ADC7,			///< ADC7
        ACNI_ADC8,			///< ADC8
        ACNI_ADC9,			///< ADC9
        ACNI_ADC10,			///< ADC10
        ACNI_ADC11,			///< ADC11
        ACNI_ADC12,			///< ADC12
        ACNI_ADC13,			///< ADC13
        ACNI_ADC14,			///< ADC14
        ACNI_ADC15,			///< ADC15
        ACNI_AIN1			///< AIN1
    } ATmega2560_AnaCompNegInput;
    /**
     * @brief ATmega2560 Analog Comparator Negative Input Selection type
     */
    typedef ATmega2560_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega2560 Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,		///< ADC0 Single Ended Input
    	CH_ADC1,			///< ADC1 Single Ended Input
    	CH_ADC2,			///< ADC2 Single Ended Input
    	CH_ADC3,			///< ADC3 Single Ended Input
    	CH_ADC4,			///< ADC4 Single Ended Input
    	CH_ADC5,			///< ADC5 Single Ended Input
    	CH_ADC6,			///< ADC6 Single Ended Input
    	CH_ADC7,			///< ADC7 Single Ended Input
    	CH_ADC0_ADC0_10x,	///< ADC0 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC1_ADC0_10x,	///< ADC1 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC0_ADC0_200x,	///< ADC0 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC1_ADC0_200x,	///< ADC1 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC2_ADC2_10x,	///< ADC2 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC3_ADC2_10x,	///< ADC3 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC2_ADC2_200x,	///< ADC2 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC3_ADC2_200x,	///< ADC3 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC0_ADC1,		///< ADC0 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC1,		///< ADC1 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC1,		///< ADC2 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC1,		///< ADC3 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC1,		///< ADC4 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC1,		///< ADC5 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC6_ADC1,		///< ADC6 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC7_ADC1,		///< ADC7 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC0_ADC2,		///< ADC0 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC2,		///< ADC1 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC2,		///< ADC2 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC2,		///< ADC3 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC2,		///< ADC4 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC2,		///< ADC5 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_1V1,				///< 1.1V Bandgap Vref Single Ended Input
    	CH_GND,				///< 0V (GND) Single Ended Input
    	CH_ADC8,			///< ADC8 Single Ended Input
    	CH_ADC9,			///< ADC9 Single Ended Input
    	CH_ADC10,			///< ADC10 Single Ended Input
    	CH_ADC11,			///< ADC11 Single Ended Input
    	CH_ADC12,			///< ADC12 Single Ended Input
    	CH_ADC13,			///< ADC13 Single Ended Input
    	CH_ADC14,			///< ADC14 Single Ended Input
    	CH_ADC15,			///< ADC15 Single Ended Input
    	CH_ADC8_ADC8_10x,	///< ADC8 Positive, ADC8 Negative Differential Input, 10x Gain
    	CH_ADC9_ADC8_10x,	///< ADC9 Positive, ADC8 Negative Differential Input, 10x Gain
    	CH_ADC8_ADC8_200x,	///< ADC8 Positive, ADC8 Negative Differential Input, 200x Gain
    	CH_ADC9_ADC8_200x,	///< ADC9 Positive, ADC8 Negative Differential Input, 200x Gain
    	CH_ADC10_ADC10_10x,	///< ADC10 Positive, ADC10 Negative Differential Input, 10x Gain
    	CH_ADC11_ADC10_10x,	///< ADC11 Positive, ADC10 Negative Differential Input, 10x Gain
    	CH_ADC10_ADC10_200x,///< ADC10 Positive, ADC10 Negative Differential Input, 200x Gain
    	CH_ADC11_ADC10_200x,///< ADC11 Positive, ADC10 Negative Differential Input, 200x Gain
    	CH_ADC8_ADC9,		///< ADC8 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC9_ADC9,		///< ADC9 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC10_ADC9,		///< ADC10 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC11_ADC9,		///< ADC11 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC12_ADC9,		///< ADC12 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC13_ADC9,		///< ADC13 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC14_ADC9,		///< ADC14 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC15_ADC9,		///< ADC15 Positive, ADC9 Negative Differential Input, 1x Gain
    	CH_ADC8_ADC10,		///< ADC8 Positive, ADC10 Negative Differential Input, 1x Gain
    	CH_ADC9_ADC10,		///< ADC9 Positive, ADC10 Negative Differential Input, 1x Gain
    	CH_ADC10_ADC10,		///< ADC10 Positive, ADC10 Negative Differential Input, 1x Gain
    	CH_ADC11_ADC10,		///< ADC11 Positive, ADC10 Negative Differential Input, 1x Gain
    	CH_ADC12_ADC10,		///< ADC12 Positive, ADC10 Negative Differential Input, 1x Gain
    	CH_ADC13_ADC10		///< ADC13 Positive, ADC10 Negative Differential Input, 1x Gain
    } ATmega2560_Channel;
    /**
     * @brief ATmega2560 Analog Input Channel Selection
     */
    typedef ATmega2560_Channel Channel;
    /**
     * @}
     */
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega325)
public:
    /**
     * @ingroup ATmega325
     * @{
     */
    /**
     * @brief ATmega325 Digital Input Selection type
     */
    typedef enum {
        DI_ADC0 = 0,		///< ADC0
        DI_ADC1,			///< ADC1
        DI_ADC2,			///< ADC2
        DI_ADC3,			///< ADC3
        DI_ADC4,			///< ADC4
        DI_ADC5,			///< ADC5
        DI_ADC6,			///< ADC6
        DI_ADC7,			///< ADC7
        DI_AIN0,			///< AIN0
        DI_AIN1				///< AIN1
    } ATmega325_DigitalInput;
    /**
     * @brief ATmega325 Digital Input Selection type
     */
    typedef ATmega325_DigitalInput DigitalInput;
    /**
     * @brief ATmega325 Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,		///< ADC0
        ACNI_ADC1,			///< ADC1
        ACNI_ADC2,			///< ADC2
        ACNI_ADC3,			///< ADC3
        ACNI_ADC4,			///< ADC4
        ACNI_ADC5,			///< ADC5
        ACNI_ADC6,			///< ADC6
        ACNI_ADC7,			///< ADC7
        ACNI_AIN1			///< AIN1
    } ATmega325_AnaCompNegInput;
    /**
     * @brief ATmega325 Analog Comparator Negative Input Selection type
     */
    typedef ATmega325_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega325 Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,		///< ADC0 Single Ended Input
    	CH_ADC1,			///< ADC1 Single Ended Input
    	CH_ADC2,			///< ADC2 Single Ended Input
    	CH_ADC3,			///< ADC3 Single Ended Input
    	CH_ADC4,			///< ADC4 Single Ended Input
    	CH_ADC5,			///< ADC5 Single Ended Input
    	CH_ADC6,			///< ADC6 Single Ended Input
    	CH_ADC7,			///< ADC7 Single Ended Input
    	CH_ADC0_ADC1 = 16,	///< ADC0 Positive, ADC1 Negative Differential Input
    	CH_ADC1_ADC1,		///< ADC1 Positive, ADC1 Negative Differential Input
    	CH_ADC2_ADC1,		///< ADC2 Positive, ADC1 Negative Differential Input
    	CH_ADC3_ADC1,		///< ADC3 Positive, ADC1 Negative Differential Input
    	CH_ADC4_ADC1,		///< ADC4 Positive, ADC1 Negative Differential Input
    	CH_ADC5_ADC1,		///< ADC5 Positive, ADC1 Negative Differential Input
    	CH_ADC6_ADC1,		///< ADC6 Positive, ADC1 Negative Differential Input
    	CH_ADC7_ADC1,		///< ADC7 Positive, ADC1 Negative Differential Input
    	CH_ADC0_ADC2,		///< ADC0 Positive, ADC2 Negative Differential Input
    	CH_ADC1_ADC2,		///< ADC1 Positive, ADC2 Negative Differential Input
    	CH_ADC2_ADC2,		///< ADC2 Positive, ADC2 Negative Differential Input
    	CH_ADC3_ADC2,		///< ADC3 Positive, ADC2 Negative Differential Input
    	CH_ADC4_ADC2,		///< ADC4 Positive, ADC2 Negative Differential Input
    	CH_ADC5_ADC2,		///< ADC5 Positive, ADC2 Negative Differential Input
    	CH_1V1,				///< 1.1V Bandgap Vref Single Ended Input
    	CH_GND				///< 0V (GND) Single Ended Input
    } ATmega325_Channel;
    /**
     * @brief ATmega325 Analog Input Channel Selection
     */
    typedef ATmega325_Channel Channel;
    /**
     * @}
     */
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32)
    /**
     * @ingroup ATmega32
     * @{
     */
    /**
     * @brief ATmega32 Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,		///< ADC0
        ACNI_ADC1,			///< ADC1
        ACNI_ADC2,			///< ADC2
        ACNI_ADC3,			///< ADC3
        ACNI_ADC4,			///< ADC4
        ACNI_ADC5,			///< ADC5
        ACNI_ADC6,			///< ADC6
        ACNI_ADC7,			///< ADC7
        ACNI_AIN1			///< AIN1
    } ATmega32_AnaCompNegInput;
    /**
     * @brief ATmega32 Analog Comparator Negative Input Selection type
     */
    typedef ATmega32_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega32 Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,		///< ADC0 Single Ended Input
    	CH_ADC1,			///< ADC1 Single Ended Input
    	CH_ADC2,			///< ADC2 Single Ended Input
    	CH_ADC3,			///< ADC3 Single Ended Input
    	CH_ADC4,			///< ADC4 Single Ended Input
    	CH_ADC5,			///< ADC5 Single Ended Input
    	CH_ADC6,			///< ADC6 Single Ended Input
    	CH_ADC7,			///< ADC7 Single Ended Input
    	CH_ADC0_ADC0_10x,	///< ADC0 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC1_ADC0_10x,	///< ADC1 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC0_ADC0_200x,	///< ADC0 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC1_ADC0_200x,	///< ADC1 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC2_ADC2_10x,	///< ADC2 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC3_ADC2_10x,	///< ADC3 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC2_ADC2_200x,	///< ADC2 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC3_ADC2_200x,	///< ADC3 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC0_ADC1,		///< ADC0 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC1,		///< ADC1 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC1,		///< ADC2 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC1,		///< ADC3 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC1,		///< ADC4 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC1,		///< ADC5 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC6_ADC1,		///< ADC6 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC7_ADC1,		///< ADC7 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC0_ADC2,		///< ADC0 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC2,		///< ADC1 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC2,		///< ADC2 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC2,		///< ADC3 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC2,		///< ADC4 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC2,		///< ADC5 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_1V22,			///< 1.22V Bandgap Vref Single Ended Input
    	CH_GND				///< 0V (GND) Single Ended Input
    } ATmega32_Channel;
    /**
     * @brief ATmega32 Analog Input Channel Selection
     */
    typedef ATmega32_Channel Channel;
    /**
     * @}
     */
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
    /**
     * @ingroup ATmega32U4
     * @{
     */
    /**
     * @brief ATmega32U4 Digital Input Selection type
     */
    typedef enum {
    	DI_ADC8  = 0,			///< ADC8
    	DI_ADC9  = 1,			///< ADC9
    	DI_ADC10 = 2,			///< ADC10
    	DI_ADC11 = 3,			///< ADC11
    	DI_ADC12 = 4,			///< ADC12
    	DI_ADC13 = 5,			///< ADC13
        DI_ADC0  = 8,			///< ADC0
        DI_ADC1  = 9,			///< ADC1
        DI_ADC4  = 12,			///< ADC4
        DI_ADC5  = 13,			///< ADC5
        DI_ADC6  = 14,			///< ADC6
        DI_ADC7  = 15,			///< ADC7
        DI_AIN0  = 16,			///< AIN0
    } ATmega32U4_DigitalInput;
    /**
     * @brief ATmega32U4 Digital Input Selection type
     */
    typedef ATmega32U4_DigitalInput DigitalInput;
    /**
     * @brief ATmega32U4 Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,			///< ADC0
        ACNI_ADC1 = 1,			///< ADC1
        ACNI_ADC4 = 4,			///< ADC4
        ACNI_ADC5 = 5,			///< ADC5
        ACNI_ADC6 = 6,			///< ADC6
        ACNI_ADC7 = 7,			///< ADC7
        ACNI_1V1  = 8			///< 1.1V Bandgap Voltage Reference
    } ATmega32U4_AnaCompNegInput;
    /**
     * @brief ATmega32U4 Analog Comparator Negative Input Selection type
     */
    typedef ATmega32U4_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega32U4 Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,			///< ADC0 Single Ended Input
    	CH_ADC1 = 1,			///< ADC1 Single Ended Input
    	CH_ADC4 = 4,			///< ADC4 Single Ended Input
    	CH_ADC5 = 5,			///< ADC5 Single Ended Input
    	CH_ADC6 = 6,			///< ADC6 Single Ended Input
    	CH_ADC7 = 7,			///< ADC7 Single Ended Input
    	CH_ADC1_ADC0_10x  = 9,	///< ADC1 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC1_ADC0_200x = 11,	///< ADC1 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC0_ADC1 = 16,		///< ADC0 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC1 = 20,		///< ADC4 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC1 = 21,		///< ADC5 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC6_ADC1 = 22,		///< ADC6 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC7_ADC1 = 23,		///< ADC7 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_1V1   = 30,			///< 1.1V Bandgap Vref Single Ended Input
    	CH_GND   = 31,			///< 0V (GND) Single Ended Input
    	CH_ADC8  = 32,			///< ADC8 Single Ended Input
    	CH_ADC9  = 33,			///< ADC9 Single Ended Input
    	CH_ADC10 = 34,			///< ADC10 Single Ended Input
    	CH_ADC11 = 35,			///< ADC11 Single Ended Input
    	CH_ADC12 = 36,			///< ADC12 Single Ended Input
    	CH_ADC13 = 37,			///< ADC13 Single Ended Input
    	CH_ADC1_ADC0_40x = 38,	///< ADC1 Positive, ADC0 Negative Differential Input, 40x Gain
    	CH_TempSensor    = 39,	///< Temperature Sensor Single Ended Input
    	CH_ADC4_ADC0_10x = 40,	///< ADC4 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC5_ADC0_10x = 41,	///< ADC5 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC6_ADC0_10x = 42,	///< ADC6 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC7_ADC0_10x = 43,	///< ADC7 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC4_ADC1_10x = 44,	///< ADC4 Positive, ADC1 Negative Differential Input, 10x Gain
    	CH_ADC5_ADC1_10x = 45,	///< ADC5 Positive, ADC1 Negative Differential Input, 10x Gain
    	CH_ADC6_ADC1_10x = 46,	///< ADC6 Positive, ADC1 Negative Differential Input, 10x Gain
    	CH_ADC7_ADC1_10x = 47,	///< ADC7 Positive, ADC1 Negative Differential Input, 10x Gain
    	CH_ADC4_ADC0_40x = 48,	///< ADC4 Positive, ADC0 Negative Differential Input, 40x Gain
    	CH_ADC5_ADC0_40x = 49,	///< ADC5 Positive, ADC0 Negative Differential Input, 40x Gain
    	CH_ADC6_ADC0_40x = 50,	///< ADC6 Positive, ADC0 Negative Differential Input, 40x Gain
    	CH_ADC7_ADC0_40x = 51,	///< ADC7 Positive, ADC0 Negative Differential Input, 40x Gain
    	CH_ADC4_ADC1_40x = 52,	///< ADC4 Positive, ADC1 Negative Differential Input, 40x Gain
    	CH_ADC5_ADC1_40x = 53,	///< ADC5 Positive, ADC1 Negative Differential Input, 40x Gain
    	CH_ADC6_ADC1_40x = 54,	///< ADC6 Positive, ADC1 Negative Differential Input, 40x Gain
    	CH_ADC7_ADC1_40x = 55,	///< ADC7 Positive, ADC1 Negative Differential Input, 40x Gain
    	CH_ADC4_ADC0_200x = 56,	///< ADC4 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC5_ADC0_200x = 57,	///< ADC5 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC6_ADC0_200x = 58,	///< ADC6 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC7_ADC0_200x = 59,	///< ADC7 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC4_ADC1_200x = 60,	///< ADC4 Positive, ADC1 Negative Differential Input, 200x Gain
    	CH_ADC5_ADC1_200x = 61,	///< ADC5 Positive, ADC1 Negative Differential Input, 200x Gain
    	CH_ADC6_ADC1_200x = 62,	///< ADC6 Positive, ADC1 Negative Differential Input, 200x Gain
    	CH_ADC7_ADC1_200x = 63	///< ADC7 Positive, ADC1 Negative Differential Input, 200x Gain
    } ATmega32U4_Channel;
    /**
     * @brief ATmega32U4 Analog Input Channel Selection
     */
    typedef ATmega32U4_Channel Channel;
    /**
     * @}
     */
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    /**
     * @ingroup ATmega1284
     * @{
     */
    /**
     * @brief ATmega1284 Digital Input Selection type
     */
    typedef enum {
		DI_ADC0 = 0,		///< ADC0
		DI_ADC1,			///< ADC1
		DI_ADC2,			///< ADC2
		DI_ADC3,			///< ADC3
		DI_ADC4,			///< ADC4
		DI_ADC5,			///< ADC5
		DI_ADC6,			///< ADC6
		DI_ADC7,			///< ADC7
		DI_AIN0,			///< AIN0
		DI_AIN1				///< AIN1
    } ATmega1284_DigitalInput;
    /**
     * @brief ATmega1284 Digital Input Selection type
     */
    typedef ATmega1284_DigitalInput DigitalInput;
    /**
     * @brief ATmega1284 Analog Comparator Negative Input Selection type
     */
    typedef enum {
        ACNI_ADC0 = 0,		///< ADC0
        ACNI_ADC1,			///< ADC1
        ACNI_ADC2,			///< ADC2
        ACNI_ADC3,			///< ADC3
        ACNI_ADC4,			///< ADC4
        ACNI_ADC5,			///< ADC5
        ACNI_ADC6,			///< ADC6
        ACNI_ADC7,			///< ADC7
        ACNI_AIN1			///< AIN1
    } ATmega1284_AnaCompNegInput;
    /**
     * @brief ATmega1284 Analog Comparator Negative Input Selection type
     */
    typedef ATmega1284_AnaCompNegInput AnaCompNegInput;
    /**
     * @brief ATmega32U4 Analog Input Channel Selection
     */
    typedef enum {
    	CH_ADC0 = 0,		///< ADC0 Single Ended Input
    	CH_ADC1,			///< ADC1 Single Ended Input
    	CH_ADC2,			///< ADC2 Single Ended Input
    	CH_ADC3,			///< ADC3 Single Ended Input
    	CH_ADC4,			///< ADC4 Single Ended Input
    	CH_ADC5,			///< ADC5 Single Ended Input
    	CH_ADC6,			///< ADC6 Single Ended Input
    	CH_ADC7,			///< ADC7 Single Ended Input
    	CH_ADC0_ADC0_10x,	///< ADC0 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC1_ADC0_10x,	///< ADC1 Positive, ADC0 Negative Differential Input, 10x Gain
    	CH_ADC0_ADC0_200x,	///< ADC0 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC1_ADC0_200x,	///< ADC1 Positive, ADC0 Negative Differential Input, 200x Gain
    	CH_ADC2_ADC2_10x,	///< ADC2 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC3_ADC2_10x,	///< ADC3 Positive, ADC2 Negative Differential Input, 10x Gain
    	CH_ADC2_ADC2_200x,	///< ADC2 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC3_ADC2_200x,	///< ADC3 Positive, ADC2 Negative Differential Input, 200x Gain
    	CH_ADC0_ADC1,		///< ADC0 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC1,		///< ADC1 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC1,		///< ADC2 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC1,		///< ADC3 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC1,		///< ADC4 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC1,		///< ADC5 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC6_ADC1,		///< ADC6 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC7_ADC1,		///< ADC7 Positive, ADC1 Negative Differential Input, 1x Gain
    	CH_ADC0_ADC2,		///< ADC0 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC1_ADC2,		///< ADC1 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC2_ADC2,		///< ADC2 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC3_ADC2,		///< ADC3 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC4_ADC2,		///< ADC4 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_ADC5_ADC2,		///< ADC5 Positive, ADC2 Negative Differential Input, 1x Gain
    	CH_1V1,				///< 1.1V Bandgap Vref Single Ended Input
    	CH_GND				///< 0V (GND) Single Ended Input
    } ATmega1284_Channel;
    /**
     * @brief ATmega1284 Analog Input Channel Selection
     */
    typedef ATmega1284_Channel Channel;
    /**
     * @}
     */
#endif

public:
    VoltageRef voltageReference() const;
    void setVoltageReference(VoltageRef ref);

    bool isLeftAjustResult() const;
    void setLeftAdjustResult(bool adj);

    Channel channel() const;
    void setChannel(Channel chnl);

    bool isEnabled() const;
    void enable();
    void disable();
    void setEnable(bool val);

    AnaCompNegInput anaCompNegInput() const;
    void setAnaCompNegInput(AnaCompNegInput acni);

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    bool digitalInputDisabled(DigitalInput dipin);
    void disableDigitalInput(DigitalInput dipin);
    void enableDigitalInput(DigitalInput dipin);
    void setDigitalInputDisable(DigitalInput dipin, bool val);
#endif
};
/**
 * @brief Return Voltage Reference Selection for the ADC
 * @return Voltage Reference Selection for the ADC.
 */
inline AnalogMux::VoltageRef AnalogMux::voltageReference() const
{
    return (VoltageRef) REG_(admux).refs;
}
/**
 * @brief Set Voltage Reference Selection for the ADC
 * @param[in] ref Voltage Reference Selection for the ADC.
 */
inline void AnalogMux::setVoltageReference(VoltageRef ref)
{
    REG_(admux).refs = (unsigned char) ref;
}
/**
 * @brief Return true, if A/D Result is left adjusted
 * @return True, if A/D Result is left adjusted.
 *
 * Otherwise it is right adjusted.
 */
inline bool AnalogMux::isLeftAjustResult() const
{
    return REG_(admux).adlar;
}
/**
 * @brief Set true, if A/D Result should be left adjusted
 * @param[in] adj True, if A/D Result should be left adjusted.
 *
 * Otherwise it will be right adjusted.
 */
inline void AnalogMux::setLeftAdjustResult(bool adj)
{
    REG_(admux).adlar = adj;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return true, if Analog Comparator Multiplexer is enabled
 * @return True, if Analog Comparator Multiplexer is enabled.
 */
inline bool AnalogMux::isEnabled() const
{
	return REG_(adcsrb).acme;
}
/**
 * @brief Enable Analog Comparator Multiplexer
 *
 * When enabled and the ADC is diabled, the ADC multiplexer selects the negative input
 * to the Analog Comparator.
 */
inline void AnalogMux::enable()
{
	REG_(adcsrb).acme = true;
}
/**
 * @brief Disable Analog Comparator Multiplexer
 *
 * When disabled, AIN1 is applied to the negative input of the Analog Comparator.
 */
inline void AnalogMux::disable()
{
	REG_(adcsrb).acme = false;
}
/**
 * @brief Set Analog Comparator Multiplexer Enable state
 * @param[in] val New state value
 */
inline void AnalogMux::setEnable(bool val)
{
	REG_(adcsrb).acme = val;
}
#endif

#if defined(VE_ATmega32)
inline bool AnalogMux::isEnabled() const
{
	return REG_(sfior).acme;
}
inline void AnalogMux::enable()
{
	REG_(sfior).acme = true;
}
inline void AnalogMux::disable()
{
	REG_(sfior).acme = false;
}
inline void AnalogMux::setEnable(bool val)
{
	REG_(sfior).acme = val;
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Return true, if Digital Input buffer on corresponding ADC pin is disabled
 * @param[in] pin ADC pin
 * @return True, if Digital Input buffer on corresponding ADC pin is disabled.
 */
inline bool AnalogMux::digitalInputDisabled(DigitalInput pin)
{
    return REGW(didr).isSet(pin);
}
/**
 * @brief Disable Digital Input buffer on corresponding ADC pin
 * @param[in] pin ADC pin
 */
inline void AnalogMux::disableDigitalInput(DigitalInput pin)
{
    REGW(didr).set(pin);
}
/**
 * @brief Enable Digital Input buffer on corresponding ADC pin
 * @param[in] pin ADC pin
 */
inline void AnalogMux::enableDigitalInput(DigitalInput pin)
{
    REGW(didr).reset(pin);
}
/**
 * @brief Set Digital Input Disable state
 * @param[in] pin ADC pin
 * @param[in] val New state value
 */
inline void AnalogMux::setDigitalInputDisable(DigitalInput pin, bool val)
{
	REGW(didr).setState(pin, val);
}
/**
 * @brief Return Analog Channel Selection
 * @return Analog Channel Selection.
 */
inline AnalogMux::Channel AnalogMux::channel() const
{
    return (Channel) REG_(admux).mux;
}
/**
 * @brief Set Analog Channel Selection
 * @param[in] chnl Analog Channel Selection.
 *
 * This function selects which analog inputs are connected to the ADC. If this value is changed
 * during a conversion, the change will not go in effect until this conversion is complete.
 */
inline void AnalogMux::setChannel(Channel chnl)
{
    REG_(admux).mux = chnl;
}
/**
 * @brief Return Analog Comparator Negative Input Selection
 * @return Analog Comparator Negative Input Selection.
 */
inline AnalogMux::AnaCompNegInput AnalogMux::anaCompNegInput() const
{
    if (! isEnabled())
        return ACNI_AIN1;
    if (isADCEnabled())
        return ACNI_AIN1;
    return (AnaCompNegInput) (REG_(admux).mux & 7);
}
/**
 * @brief Select Analog Comparator Negative Input
 * @param[in] acni Analog Comparator Negative Input Selection.
 */
inline void AnalogMux::setAnaCompNegInput(AnaCompNegInput acni)
{
	if (acni == ACNI_AIN1)
		REG_(adcsrb).acme = !isADCEnabled();
	else {
		enable();
		REG_(admux).mux = acni;
	}
}
#endif

#if defined(VE_ATmega2560)
inline bool AnalogMux::digitalInputDisabled(DigitalInput pin)
{
	if (pin < 16)
		return REGW(didr).isSet(pin);
	else
		return REGW(didr1).isSet(pin-16);
}
inline void AnalogMux::disableDigitalInput(DigitalInput pin)
{
	if (pin < 16)
		REGW(didr).set(pin);
	else
		REGW(didr1).set(pin-16);
}
inline void AnalogMux::enableDigitalInput(DigitalInput pin)
{
	if (pin < 16)
		REGW(didr).reset(pin);
	else
		REGW(didr1).reset(pin-16);
}
inline void AnalogMux::setDigitalInputDisable(DigitalInput pin, bool val)
{
	if (pin < 16)
		REGW(didr).setState(pin, val);
	else
		REGW(didr1).setState(pin-16, val);
}
inline AnalogMux::Channel AnalogMux::channel() const
{
	register uint8_t ret = REG_(adcsrb).mux5 ? 32 : 0;
	ret |= REG_(admux).mux;
    return (Channel) ret;
}
inline void AnalogMux::setChannel(Channel chnl)
{
    REG_(admux).mux = chnl & 31;
    REG_(adcsrb).mux5 = chnl & 32;
}
inline AnalogMux::AnaCompNegInput AnalogMux::anaCompNegInput() const
{
    if (! isEnabled())
        return ACNI_AIN1;
    if (isADCEnabled())
        return ACNI_AIN1;
    register uint8_t ret = REG_(adcsrb).mux5 ? 8 : 0;
    ret |= (REG_(admux).mux & 7);
    return (AnaCompNegInput) ret;
}
inline void AnalogMux::setAnaCompNegInput(AnaCompNegInput acni)
{
	if (acni == ACNI_AIN1)
		REG_(adcsrb).acme = !isADCEnabled();
	else {
		enable();
		REG_(admux).mux = acni & 7;
		REG_(adcsrb).mux5 = acni & 8;
	}
}
#endif

#if defined(VE_ATmega32)
inline AnalogMux::Channel AnalogMux::channel() const
{
    return (Channel) REG_(admux).mux;
}
inline void AnalogMux::setChannel(Channel chnl)
{
    REG_(admux).mux = chnl;
}
inline AnalogMux::AnaCompNegInput AnalogMux::anaCompNegInput() const
{
    if (! isEnabled())
        return ACNI_AIN1;
    if (isADCEnabled())
        return ACNI_AIN1;
    return (AnaCompNegInput) (REG_(admux).mux & 7);
}
inline void AnalogMux::setAnaCompNegInput(AnaCompNegInput acni)
{
	if (acni == ACNI_AIN1)
		REG_(sfior).acme = !isADCEnabled();
	else {
		enable();
		REG_(admux).mux = acni;
	}
}
#endif

#if defined(VE_ATmega32U4)
inline bool AnalogMux::digitalInputDisabled(DigitalInput pin)
{
	if (pin < 16)
		return REGW(didr).isSet(pin);
	else
		return REGW(didr1).isSet(pin-16);
}
inline void AnalogMux::disableDigitalInput(DigitalInput pin)
{
	if (pin < 16)
		REGW(didr).set(pin);
	else
		REGW(didr1).set(pin-16);
}
inline void AnalogMux::enableDigitalInput(DigitalInput pin)
{
	if (pin < 16)
		REGW(didr).reset(pin);
	else
		REGW(didr1).reset(pin-16);
}
inline void AnalogMux::setDigitalInputDisable(DigitalInput pin, bool val)
{
	if (pin < 16)
		REGW(didr).setState(pin, val);
	else
		REGW(didr1).setState(pin-16, val);
}
inline AnalogMux::Channel AnalogMux::channel() const
{
	register uint8_t ret = REG_(adcsrb).mux5 ? 32 : 0;
	ret |= REG_(admux).mux;
    return (Channel) ret;
}
inline void AnalogMux::setChannel(Channel chnl)
{
    REG_(admux).mux = chnl & 31;
    REG_(adcsrb).mux5 = chnl & 32;
}
inline AnalogMux::AnaCompNegInput AnalogMux::anaCompNegInput() const
{
    if (! isEnabled())
        return ACNI_1V1;
    if (isADCEnabled())
        return ACNI_1V1;
    register uint8_t ret = (REG_(admux).mux & 7);
    return (AnaCompNegInput) ret;
}
inline void AnalogMux::setAnaCompNegInput(AnaCompNegInput acni)
{
	if (acni == ACNI_1V1)
		REG_(adcsrb).acme = !isADCEnabled();
	else {
		enable();
		REG_(admux).mux = acni & 7;
		REG_(adcsrb).mux5 = 0;
	}
}
#endif

#endif /* ANALOGMULTIPLEXER_H_ */
