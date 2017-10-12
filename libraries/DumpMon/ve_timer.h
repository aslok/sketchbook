/**
 * @file ve_timer.h
 * @brief 8-bit Timer/Counter Header
 * @author andrey
 * @date 09.02.2012
 * @copyright GNU Public License
 */
#ifndef TIMER_H_
#define TIMER_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
#define TIMERT_TEMPLATE template<typename _avr_timerT, typename _PrescalerT>	///< TimerT template macro
#define TIMERT_PARENT _avr_timerT												///< TimerT parent type
#endif

#if defined(VE_ATmega32)
typedef struct {
	unsigned char reserved[8];
} __TimerTP;
typedef struct {
	AVR_REG ocra;
} __TimerTOCRA0;
typedef struct {
} __TimerTOCRA2;
#define TIMERT_TEMPLATE template<typename _avr_timerT, typename _avr_ocraT, typename _PrescalerT>
#define TIMERT_PARENT _avr_timerT, private __TimerTP, public _avr_ocraT
#endif

/**
 * @brief 8-bit Timer/Counter class template
 * @ingroup Timers
 */
TIMERT_TEMPLATE
class TimerT: public TIMERT_PARENT
{
public:
	/**
	 * @brief Compare Output Mode type
	 */
    typedef enum
    {
        Disconnected = 0,		///< Disconnected
        Toggle,					///< Toggle on Compare Match
        Clear,					///< Clear on Compare Match
        Set						///< Set on Compare Match
    } CompOutMode;
    /**
     * @brief Wave Generation Mode type
     */
    typedef enum
    {
        Normal = 0,				///< Normal
        PhaseCorrect,			///< Phase Correct PWM
        CTC,					///< Clear Timer on Compare Match (CTC)
        FastPWM,				///< Fast PWM
        PhaseCorrect_OCRA = 5,	///< Phase Correct PWM, OCRA is Top
        FastPWM_OCRA = 7		///< Fast PWM, OCRA is Top
    } WaveGenMode;
    typedef typename _PrescalerT::ClkSelect _ClkSelectT;	///< Clock Select type
public:
    /**
     * @brief Return unsigned integer Prescaler value
     * @return Unsigned integer Prescaler value
     */
    uint16_t prescaler() const
    {
        return _PrescalerT::prescaler(clockSelect());
    }
    /**
     * @brief Return Counter value
     * @return Counter value
     */
    uint8_t counter() const
    {
        return TREG_(tcnt);
    }
    /**
     * @brief Set Counter value
     * @param[in] val New Counter value
     */
    void setCounter(uint8_t val)
    {
        TREG_(tcnt) = val;
    }
    /**
     * @brief Return Output Compare Register A value
     * @return Output Compare Register A value
     */
    uint8_t outputCompareA() const
    {
        return TREG_(ocra);
    }
    /**
     * @brief Set Output Compare Register A value
     * @param[in] val New Output Compare Register A value
     */
    void setOutputCompareA(uint8_t val)
    {
        TREG_(ocra) = val;
    }
    /**
     * @brief Return Output Compare A Mode value
     * @return Output Compare A Mode value
     */
    CompOutMode compOutModeA() const
    {
        return (CompOutMode) TREG_(tccra).coma;
    }
    /**
     * @brief Set Output Compare A Mode value
     * @param[in] val New Output Compare A Mode value
     */
    void setCompOutModeA(CompOutMode val)
    {
        TREG_(tccra).coma = val;
    }

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
    /**
     * @brief Return Output Compare Register B value
     * @return Output Compare Register B value
     */
    uint8_t outputCompareB() const
    {
        return TREG_(ocrb);
    }
    /**
     * @brief Set Output Compare Register B value
     * @param[in] val New Output Compare Register B value
     */
    void setOutputCompareB(uint8_t val)
    {
        TREG_(ocrb) = val;
    }
    /**
     * @brief Return Output Compare B Mode value
     * @return Output Compare B Mode value
     */
    CompOutMode compOutModeB() const
    {
        return (CompOutMode) TREG_(tccra).comb;
    }
    /**
     * @brief Set Output Compare B Mode value
     * @param[in] val New Output Compare B Mode value
     */
    void setCompOutModeB(CompOutMode val)
    {
        TREG_(tccra).comb = val;
    }
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
    defined(VE_ATmega2560) || \
 	defined(VE_ATmega32U4) || \
 	defined(VE_ATmega644PA) || \
 	defined(VE_ATmega1284P)
    /**
     * @brief Return Wave Generation Mode value
     * @return Wave Generation Mode value
     */
    WaveGenMode wavGenMode() const
    {
        return (WaveGenMode) ((TREG_(tccrb).wgm2 << 2) | TREG_(tccra).wgm);
    }
    /**
     * @brief Set Wave Generation Mode value
     * @param[in] val New Wave Generation Mode value
     */
    void setWaveGenMode(WaveGenMode val)
    {
        TREG_(tccra).wgm = val & 3;
        TREG_(tccrb).wgm2 = (val & 4) ? 1 : 0;
    }
    /**
     * @brief Return Clock Select value
     * @return Clock Select value
     */
    _ClkSelectT clockSelect() const
    {
        return (_ClkSelectT) TREG_(tccrb).cs;
    }
    /**
     * @brief Set Clock Select value
     * @param[in] val New Clock Select value
     */
    void setClockSelect(_ClkSelectT val)
    {
        TREG_(tccrb).cs = val;
    }
#else
    WaveGenMode wavGenMode() const
    {
        return (WaveGenMode) ((TREG_(tccra).wgm1 << 1) | TREG_(tccra).wgm0);
    }
    void setWaveGenMode(WaveGenMode val)
    {
        TREG_(tccra).wgm0 = val & 1;
        TREG_(tccra).wgm1 = val >> 1;
    }
	_ClkSelectT clockSelect() const
	{
        return TREG_(tccra).cs;
    }
    void setClockSelect(_ClkSelectT val)
    {
        TREG_(tccra).cs = val;
    }
#endif
    /**
     * @brief Force Compare Match on Output Compare A
     *
     * The FOCA bit is only active when the WGM bits specify a non-PWM mode.
     * However, for ensuring compatibility with future devices, this bit must
     * be set to zero when TCCRB is written when operating in PWM mode.
     *
     * When writing a logical one to the FOCA bit, an immediate Compare Match
     * is forced on the Waveform Generation unit. The OCA output is changed
     * according to its COMA bits setting.
     *
     * Note that the FOCA bit is implemented as a strobe. Therefore it is the
     * value present in the COMA bits that determines the effect of the forced
     * compare.
     *
     * A FOCA strobe will not generate any interrupt, nor will it clear the timer
     * in CTC mode using OCRA as TOP.
     *
     * The FOCA bit is always read as zero.
     */
    void forceOutputCompareA()
    {
        TREG_(tccrb).foca = true;
    }
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega1284P)
    /**
     * @brief Force Compare Match on Output Compare B
     *
     * The FOCB bit is only active when the WGM bits specify a non-PWM mode.
     * However, for ensuring compatibility with future devices, this bit must
     * be set to zero when TCCRB is written when operating in PWM mode.
     *
     * When writing a logical one to the FOCB bit, an immediate Compare Match
     * is forced on the Waveform Generation unit. The OCB output is changed
     * according to its COMB bits setting.
     *
     * Note that the FOCB bit is implemented as a strobe. Therefore it is the
     * value present in the COMB bits that determines the effect of the forced
     * compare.
     *
     * A FOCB strobe will not generate any interrupt, nor will it clear the timer
     * in CTC mode using OCRB as TOP.
     *
     * The FOCB bit is always read as zero.
     */
    void forceOutputCompareB()
    {
        TREG_(tccrb).focb = true;
    }
#endif
};

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega325) || \
	defined(VE_ATmega32U4) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
typedef TimerT<AVR_TIMER, Prescaler0> Timer0;					///< Timer/Counter 0 class
typedef TimerT<AVR_TIMER, Prescaler2> Timer2;					///< Timer/Counter 2 class
#endif

#if defined(VE_ATmega32)
typedef TimerT<AVR_TIMER0, __TimerTOCRA0, Prescaler0> Timer0;
typedef TimerT<AVR_TIMER2, __TimerTOCRA2, Prescaler2> Timer2;
#endif

#endif /* TIMER_H_ */
