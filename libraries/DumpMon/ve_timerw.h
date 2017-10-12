/**
 * @file ve_timerw.h
 * @brief 16-bit Timer/Counter Header
 * @author andrey
 * @date 24.01.2012
 * @copyright GNU Public License
 */
#ifndef TIMERW_H_
#define TIMERW_H_

/**
 * @brief 16-bit Timer/Counter class
 * @ingroup Timers
 */
class TimerW: public AVR_TIMERW
{
public:
	/**
	 * @brief Compare Output Mode type
	 */
    typedef enum
    {
        Disconnected = 0,				///< Disconnected
		Toggle = 1,						///< Toggle on Compare Match
		Clear = 2,						///< Clear on Compare Match
		Set = 3							///< Set on Compare Match
    } CompOutMode;
    /**
     * @brief Wave Generation Mode type
     */
    typedef enum
    {
        Normal = 0,						///< Normal
        PhaseCorrect_8bit = 1,			///< Phase Correct PWM, 0x00FF is Top
        PhaseCorrect_9bit = 2,			///< Phase Correct PWM, 0x01FF is Top
        PhaseCorrect_10bit = 3,			///< Phase Correct PWM, 0x03FF is Top
        CTC_OCRA = 4,					///< Clear Timer on Compare Match (CTC), OCRA is Top
        FastPWM_8bit = 5,				///< Fast PWM, 0x00FF is Top
        FastPWM_9bit = 6,				///< Fast PWM, 0x01FF is Top
        FastPWM_10bit = 7,				///< Fast PWM, 0x03FF is Top
        PhaseFreqCorrect_ICR = 8,		///< Phase and Frequency Correct PWM, ICR is Top
        PhaseFreqCorrect_OCRA = 9,		///< Phase and Frequency Correct PWM, OCRA is Top
        PhaseCorrect_ICR = 10,			///< Phase Correct PWM, ICR is Top
        PhaseCorrect_OCRA = 11,			///< Phase Correct PWM, OCRA is Top
        CTC_ICR = 12,					///< Clear Timer on Compare Match (CTC), ICR is Top
        FastPWM_ICR = 14,				///< Fast PWM, ICR is Top
        FastPWM_OCRA = 15				///< Fast PWM, OCRA is Top
    } WaveGenMode;
    /**
     * @brief Input Capture Edge type
     */
    typedef enum
    {
        Falling = false,				///< Falling Edge
		Rising = true					///< Rising Edge
    } InCaptEdge;
    /**
     * @brief Clock Select type
     */
    typedef enum
    {
        Stopped = 0,					///< Stopped
        Prescaler_1 = 1,				///< Prescaler /1
        Prescaler_8 = 2,				///< Prescaler /8
        Prescaler_64 = 3,				///< Prescaler /64
        Prescaler_256 = 4,				///< Prescaler /256
        Prescaler_1024 = 5,				///< Prescaler /1024
        ExtClkFalling = 6,				///< External Clock Falling Edge
        ExtClkRising = 7				///< External Clock Rising Edge
    } ClkSelect;
public:
    uint16_t prescaler() const;

    uint16_t counter() const;
    void setCounter(uint16_t val);

    uint16_t outputCompareA() const;
    void setOutputCompareA(uint16_t val);

    uint16_t outputCompareB() const;
    void setOutputCompareB(uint16_t val);

    uint16_t inputCapture() const;
    void setInputCapture(uint16_t val);
    void setInputCaptureFreq(long val);

    CompOutMode compOutModeA() const;
    void setCompOutModeA(CompOutMode val);

    CompOutMode compOutModeB() const;
    void setCompOutModeB(CompOutMode val);

    WaveGenMode wavGenMode() const;
    void setWaveGenMode(WaveGenMode val);

    bool isNoiseCancelerActive() const;
    void noiseCancelerOn();
    void noiseCancelerOff();
    void setNoiseCancelerOn(bool val);

    InCaptEdge inputCaptureEdge() const;
    void setInputCaptureEdge(InCaptEdge val);

    ClkSelect clockSelect() const;
    void setClockSelect(ClkSelect val);

    void forceOutputCompareA();
    void forceOutputCompareB();

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
 	defined(VE_ATmega32U4)
    uint16_t outputCompareC() const;
    void setOutputCompareC(uint16_t val);

    CompOutMode compOutModeC() const;
    void setCompOutModeC(CompOutMode val);

    void forceOutputCompareC();
#endif
};

/**
 * @brief Return Prescaler value
 * @return Prescaler value
 */
inline uint16_t TimerW::prescaler() const
{
    switch (clockSelect())
    {
    case Prescaler_8:
        return 8;
    case Prescaler_64:
        return 64;
    case Prescaler_256:
        return 256;
    case Prescaler_1024:
        return 1024;
    default:
        return 1;
    }
}
/**
 * @brief Return Counter value
 * @return Counter value
 */
inline uint16_t TimerW::counter() const
{
    return REG_(tcnt);
}
/**
 * @brief Set Counter value
 * @param[in] val New Counter value
 */
inline void TimerW::setCounter(uint16_t val)
{
    REG_(tcnt) = val;
}
/**
 * @brief Return Output Compare A value
 * @return Output Compare A value
 */
inline uint16_t TimerW::outputCompareA() const
{
    return REG_(ocra);
}
/**
 * @brief Set Output Compare A value
 * @param[in] val New Output Compare A value
 */
inline void TimerW::setOutputCompareA(uint16_t val)
{
    REG_(ocra) = val;
}
/**
 * @brief Return Output Compare B value
 * @return Output Compare B value
 */
inline uint16_t TimerW::outputCompareB() const
{
    return REG_(ocrb);
}
/**
 * @brief Set Output Compare B value
 * @param[in] val New Output Compare B value
 */
inline void TimerW::setOutputCompareB(uint16_t val)
{
    REG_(ocrb) = val;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
 	defined(VE_ATmega32U4)
/**
 * @brief Return Output Compare C value
 * @return Output Compare C value
 */
inline uint16_t TimerW::outputCompareC() const
{
    return REG_(ocrc);
}
/**
 * @brief Set Output Compare C value
 * @param[in] val New Output Compare C value
 */
inline void TimerW::setOutputCompareC(uint16_t val)
{
    REG_(ocrc) = val;
}
#endif
/**
 * @brief Return Input Capture value
 * @return Input Capture value
 */
inline uint16_t TimerW::inputCapture() const
{
    return REG_(icr);
}
/**
 * @brief Set Input Capture value
 * @param[in] val New Input Capture value
 */
inline void TimerW::setInputCapture(uint16_t val)
{
    REG_(icr) = val;
}
/**
 * @brief Set Input Capture frequency
 * @param[in] val New Input Capture frequency value
 */
inline void TimerW::setInputCaptureFreq(long val)
{
    long _icr = F_CPU / prescaler();
    _icr = _icr / val;
    setInputCapture(_icr);
}
/**
 * @brief Return Compare Output Mode A value
 * @return Compare Output Mode A value
 */
inline TimerW::CompOutMode TimerW::compOutModeA() const
{
    return (TimerW::CompOutMode) REG_(tccra).coma;
}
/**
 * @brief Set Compare Output Mode A value
 * @param[in] val New Compare Output Mode A value
 */
inline void TimerW::setCompOutModeA(TimerW::CompOutMode val)
{
    REG_(tccra).coma = val;
}
/**
 * @brief Return Compare Output Mode B value
 * @return Compare Output Mode B value
 */
inline TimerW::CompOutMode TimerW::compOutModeB() const
{
    return (TimerW::CompOutMode) REG_(tccra).comb;
}
/**
 * @brief Set Compare Output Mode B value
 * @param[in] val New Compare Output Mode B value
 */
inline void TimerW::setCompOutModeB(TimerW::CompOutMode val)
{
    REG_(tccra).comb = val;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4)
/**
 * @brief Return Compare Output Mode C value
 * @return Compare Output Mode C value
 */
inline TimerW::CompOutMode TimerW::compOutModeC() const
{
    return (TimerW::CompOutMode) REG_(tccra).comc;
}
/**
 * @brief Set Compare Output Mode C value
 * @param[in] val New Compare Output Mode C value
 */
inline void TimerW::setCompOutModeC(TimerW::CompOutMode val)
{
    REG_(tccra).comc = val;
}
#endif

/**
 * @brief Return Wave Generation Mode value
 * @return Wave Generation Mode value
 */
inline TimerW::WaveGenMode TimerW::wavGenMode() const
{
	unsigned char wgm = (REG_(tccrb).wgmh << 2) | REG_(tccra).wgml;
    return (TimerW::WaveGenMode) wgm;
}
/**
 * @brief Set Wave Generation Mode value
 * @param[in] val New Wave Generation Mode value
 */
inline void TimerW::setWaveGenMode(WaveGenMode val)
{
    REG_(tccrb).wgmh = (val >> 2) & 0x03;
    REG_(tccra).wgml = val & 0x03;
}
/**
 * @brief Return true, if Noise Canceler is active
 * @return True, if Noise Canceler is active
 */
inline bool TimerW::isNoiseCancelerActive() const
{
    return REG_(tccrb).icnc;
}
/**
 * @brief Turn on Noise Canceler
 */
inline void TimerW::noiseCancelerOn()
{
    REG_(tccrb).icnc = true;
}
/**
 * @brief Turn off Noise Canceler
 */
inline void TimerW::noiseCancelerOff()
{
    REG_(tccrb).icnc = false;
}
/**
 * @brief Set Noise Canceler state
 * @param[in] val New state value
 */
inline void TimerW::setNoiseCancelerOn(bool val)
{
	REG_(tccrb).icnc = val;
}
/**
 * @brief Return Input Capture Edge value
 * @return Input Capture Edge value
 */
inline TimerW::InCaptEdge TimerW::inputCaptureEdge() const
{
    return (TimerW::InCaptEdge) REG_(tccrb).ices;
}
/**
 * @brief Set Input Capture Edge value
 * @param[in] val New Input Capture Edge value
 */
inline void TimerW::setInputCaptureEdge(TimerW::InCaptEdge val)
{
    REG_(tccrb).ices = val;
}
/**
 * @brief Return Clock Select value
 * @return Clock Select value
 */
inline TimerW::ClkSelect TimerW::clockSelect() const
{
    return (TimerW::ClkSelect) REG_(tccrb).cs;
}
/**
 * @brief Set Clock Select value
 * @param[in] val New Clock Select value
 */
inline void TimerW::setClockSelect(TimerW::ClkSelect val)
{
    REG_(tccrb).cs = val;
}

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega328P) || \
    defined(VE_ATmega2560) || \
    defined(VE_ATmega325) || \
    defined(VE_ATmega32U4)
/**
 * @brief Force Compare Match on Output Compare A
 */
inline void TimerW::forceOutputCompareA()
{
    REG_(tccrc).foca = true;
}
/**
 * @brief Force Compare Match on Output Compare B
 */
inline void TimerW::forceOutputCompareB()
{
    REG_(tccrc).focb = true;
}
#endif
#if defined(VE_ATmega32)
inline void TimerW::forceOutputCompareA()
{
    REG_(tccra).foca = true;
}
inline void TimerW::forceOutputCompareB()
{
    REG_(tccra).focb = true;
}
#endif

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega32U4)
/**
 * @brief Force Compare Match on Output Compare C
 */
inline void TimerW::forceOutputCompareC()
{
    REG_(tccrc).focc = true;
}
#endif

#endif /* TIMERW_H_ */
