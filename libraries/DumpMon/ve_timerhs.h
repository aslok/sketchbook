/**
 * @file ve_timerhs.h
 * @brief 10-bit High Speed Timer/Counter Header
 * @author andrey
 * @date 05.12.2012
 * @copyright GNU Public License
 */
#ifndef TIMERHS_H_
#define TIMERHS_H_

#if defined(__DOXYGEN__) || \
	defined(VE_ATmega32U4)
/// @cond
typedef struct {
	unsigned char reserved[10];
} TIMERHS_reserved;
/// @endcond
#define TIMERHS_PARENT		AVR_TIMERHS, private TIMERHS_reserved, public AVR_TIMERHS_OC	///< TimerHS parent type
#endif

/**
 * @brief 10-bit High Speed Timer/Counter class
 * @ingroup Timers
 */
class TimerHS : public TIMERHS_PARENT
{
public:
	/**
	 * @brief Compare Output Mode type
	 */
    typedef enum
    {
        Disconnected = 0,			///< Disconnected
        Toggle = 1,					///< Toggle on Compare Match
        Clear  = 2,					///< Clear on Compare Match
        Set    = 3					///< Set on Compare Match
    } CompOutMode;
    /**
     * @brief Dead Time Prescaler type
     */
    typedef enum
    {
    	DIV_1 = 0,					///< /1
    	DIV_2 = 1,					///< /2
    	DIV_4 = 2,					///< /4
    	DIV_8 = 3					///< /8
    } DeadTimePrescaler;
    /**
     * @brief Prescaler type
     */
    typedef enum
    {
    	Stopped = 0,				///< Stopped
    	Clock_DIV_1 = 1,			///< /1
    	Clock_DIV_2 = 2,			///< /2
    	Clock_DIV_4 = 3,			///< /4
    	Clock_DIV_8 = 4,			///< /8
    	Clock_DIV_16 = 5,			///< /16
    	Clock_DIV_32 = 6,			///< /32
    	Clock_DIV_64 = 7,			///< /64
    	Clock_DIV_128 = 8,			///< /128
    	Clock_DIV_256 = 9,			///< /256
    	Clock_DIV_512 = 10,			///< /512
    	Clock_DIV_1024 = 11,		///< /1024
    	Clock_DIV_2048 = 12,		///< /2048
    	Clock_DIV_4096 = 13,		///< /4096
    	Clock_DIV_8192 = 14,		///< /8192
    	Clock_DIV_16384 = 15		///< /16384
    } Prescaler;
    /**
     * @brief Edge Select type
     */
    typedef enum
    {
    	Falling = 0,				///< Falling Edge
    	Rising = 1					///< Rising Edge
    } EdgeSelect;
    /**
     * @brief Wave Generation Mode type
     */
    typedef enum
    {
        FastPWM = 0,				///< Fast PWM
        PhaseFreqCorrect = 1,		///< Phase and Frequency Correct
        SingleSlopePWM6  = 2,		///< Single-Slope PWM6
        DualSlopePWM6    = 3		///< Double-Slope PWM6
    } WaveGenMode;
    /**
     * @brief Ouput Compare Override Enable Bit type
     */
    typedef enum
    {
    	nOCA = 1,					///< nOCA
    	OCA  = 2,					///< OCA
    	nOCB = 4,					///< nOCB
    	OCB  = 8,					///< OCB
    	nOCD = 16,					///< nOCD
    	OCD  = 32					///< OCD
    } OutCompOverrideEnableBit;
    /**
     * @brief 10-bit Register Access class
     */
    class TenBitReg : public Reg
    {
    public:
    	void write(uint16_t val, TimerHS& timhs);
    	uint16_t read(const TimerHS& timhs);
    };
public:
    CompOutMode compOutModeA() const;
    void setCompOutModeA(CompOutMode val);

    CompOutMode compOutModeB() const;
    void setCompOutModeB(CompOutMode val);

    CompOutMode compOutModeD() const;
    void setCompOutModeD(CompOutMode val);

    void forceOutputCompareA();
    void forceOutputCompareB();
    void forceOutputCompareD();

    bool isPWMAEnabled() const;
    void enablePWMA();
    void disablePWMA();
    void setPWMAEnable(bool val);

    bool isPWMBEnabled() const;
    void enablePWMB();
    void disablePWMB();
    void setPWMBEnable(bool val);

    bool isPWMDEnabled() const;
    void enablePWMD();
    void disablePWMD();
    void setPWMDEnable(bool val);

    bool isPWMInversionModeEnabled() const;
    void enablePWMInversionMode();
    void disablePWMInversionMode();
    void setPWMInversionModeEnable(bool val);

    void resetPrescaler();

    DeadTimePrescaler deadTimePrescaler() const;
    void setDeadTimePrescaler(DeadTimePrescaler val);

    Prescaler clockSelect() const;
    void setClockSelect(Prescaler val);

    CompOutMode compOutModeShadowA() const;
    void setCompOutModeShadowA(CompOutMode val);

    CompOutMode compOutModeShadowB() const;
    void setCompOutModeShadowB(CompOutMode val);

    bool isFaultProtIntEnabled() const;
    void enableFaultProtInt();
    void disableFaultProtInt();
    void setFaultProtIntEnable(bool val);

    bool isFaultProtModeEnabled() const;
    void enableFaultProtMode();
    void disableFaultProtMode();
    void setFaultProtModeEnable(bool val);

    bool isFaultProtNoiseCancelerOn() const;
    void setFaultProtNoiseCancelerOn();
    void setFaultProtNoiseCancelerOff();
    void setFaultProtNoiseCancelerState(bool val);

    EdgeSelect faultProtEdgeSelect() const;
    void setFaultProtEdgeSelect(EdgeSelect val);

    bool isFaultProtAnalogCompEnabled() const;
    void enableFaultProtAnalogComp();
    void disableFaultProtAnalogComp();
    void setFaultProtAnalogCompEnable(bool val);

    bool isFaultProtInt() const;
    void clearFaultProtInt();

    WaveGenMode wavGenMode() const;
    void setWavGenMode(WaveGenMode val);

    bool isRegisterUpdateLocked() const;
    void lockRegisterUpdate();
    void unlockRegisterUpdate();
    void setRegisterUpdateLock(bool val);

    bool isEnhancedModeOn() const;
    void setEnhancedModeOn();
    void setEnhancedModeOff();
    void setsetEnhancedModeState(bool val);

    bool isOutCompOverrideEnableOn(OutCompOverrideEnableBit bit) const;
    void setOutCompOverrideEnableOn(OutCompOverrideEnableBit bit);
    void setOutCompOverrideEnableOff(OutCompOverrideEnableBit bit);
    void setOutCompOverrideEnable(OutCompOverrideEnableBit bit, bool val);

    static TenBitReg& tenBitReg(Reg& reg);

    uint16_t counter() const;
    void setCounter(uint16_t val);

    uint16_t outputCompareA() const;
    void setOutputCompareA(uint16_t val);

    uint16_t outputCompareB() const;
    void setOutputCompareB(uint16_t val);

    uint16_t outputCompareC() const;
    void setOutputCompareC(uint16_t val);

    uint16_t outputCompareD() const;
    void setOutputCompareD(uint16_t val);

    unsigned char deadTimeOCx() const;
    void setDeadTimeOCx(unsigned char val);

    unsigned char deadTimeNOCx() const;
    void setDeadTimeNOCx(unsigned char val);
};

/**
 * @brief Return Comparator A Output Mode value
 * @return Comparator A Output Mode value
 */
inline TimerHS::CompOutMode TimerHS::compOutModeA() const
{
    return (CompOutMode) REG_(tccra).coma;
}
/**
 * @brief Set Comparator A Output Mode value
 * @param[in] val New Comparator A Output Mode value
 */
inline void TimerHS::setCompOutModeA(CompOutMode val)
{
    REG_(tccra).coma = val;
}
/**
 * @brief Return Comparator B Output Mode value
 * @return Comparator B Output Mode value
 */
inline TimerHS::CompOutMode TimerHS::compOutModeB() const
{
    return (CompOutMode) REG_(tccra).coma;
}
/**
 * @brief Set Comparator B Output Mode value
 * @param[in] val New Comparator B Output Mode value
 */
inline void TimerHS::setCompOutModeB(CompOutMode val)
{
    REG_(tccra).coma = val;
}
/**
 * @brief Return Comparator D Output Mode value
 * @return Comparator D Output Mode value
 */
inline TimerHS::CompOutMode TimerHS::compOutModeD() const
{
	return (CompOutMode) REG_(tccrc).comd;
}
/**
 * @brief Set Comparator D Output Mode value
 * @param[in] val New Comparator D Output Mode value
 */
inline void TimerHS::setCompOutModeD(CompOutMode val)
{
	REG_(tccrc).comd = val;
}
/**
 * @brief Force Output Compare Match A
 *
 * Writing a logical one to this bit forces a change in the
 * Waveform Output (OCWA) and the Output Compare pin (OCA)
 * according to the values already set in COMA bits.
 *
 * If COMA bits written in the same cycle as FOCA, the new
 * settings will be used.
 *
 * The Force Output Compare bit can be used to change the
 * output pin value regardless of the timer value. The automatic
 * action programmed in COMA bits takes place as if a compare
 * match had occurred, but no interrupt is generated.
 *
 * The FOCA bit is always read as zero.
 */
inline void TimerHS::forceOutputCompareA()
{
    REG_(tccra).foca = true;
}
/**
 * @brief Force Output Compare Match B
 *
 * Writing a logical one to this bit forces a change in the
 * Waveform Output (OCWB) and the Output Compare pin (OCB)
 * according to the values already set in COMB bits.
 *
 * If COMB bits written in the same cycle as FOCB, the new
 * settings will be used.
 *
 * The Force Output Compare bit can be used to change the
 * output pin value regardless of the timer value. The automatic
 * action programmed in COMB bits takes place as if a compare
 * match had occurred, but no interrupt is generated.
 *
 * The FOCB bit is always read as zero.
 */
inline void TimerHS::forceOutputCompareB()
{
    REG_(tccra).focb = true;
}
/**
 * @brief Force Compare Match on Output Compare D
 *
 * Writing a logical one to this bit forces a change in the
 * Waveform Output (OCWD) and the Output Compare pin (OCD)
 * according to the values already set in COMD bits.
 *
 * If COMD bits written in the same cycle as FOCD, the new
 * settings will be used.
 *
 * The Force Output Compare bit can be used to change the
 * output pin value regardless of the timer value. The automatic
 * action programmed in COMD bits takes place as if a compare
 * match had occurred, but no interrupt is generated.
 *
 * The FOCD bit is always read as zero.
 */
inline void TimerHS::forceOutputCompareD()
{
	REG_(tccrc).focd = true;
}
/**
 * @brief Return true, if Pulse Width Modulator A is enabled
 * @return True, if Pulse Width Modulator A is enabled
 */
inline bool TimerHS::isPWMAEnabled() const
{
	return REG_(tccra).pwma;
}
/**
 * @brief Enable Pulse Width Modulator A
 *
 * When set (one) this bit enables PWM mode based on comparator
 * OCRA.
 */
inline void TimerHS::enablePWMA()
{
	REG_(tccra).pwma = true;
}
/**
 * @brief Disable Pulse Width Modulator A
 */
inline void TimerHS::disablePWMA()
{
	REG_(tccra).pwma = false;
}
/**
 * @brief Set Pulse Width Modulator A Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setPWMAEnable(bool val)
{
	REG_(tccra).pwma = val;
}
/**
 * @brief Return true, if Pulse Width Modulator B is enabled
 * @return True, if Pulse Width Modulator B is enabled
 */
inline bool TimerHS::isPWMBEnabled() const
{
	return REG_(tccra).pwmb;
}
/**
 * @brief Enable Pulse Width Modulator B
 *
 * When set (one) this bit enables PWM mode based on comparator
 * OCRB.
 */
inline void TimerHS::enablePWMB()
{
	REG_(tccra).pwmb = true;
}
/**
 * @brief Disable Pulse Width Modulator B
 */
inline void TimerHS::disablePWMB()
{
	REG_(tccra).pwmb = false;
}
/**
 * @brief Set Pulse Width Modulator B Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setPWMBEnable(bool val)
{
	REG_(tccra).pwmb = val;
}
/**
 * @brief Return true, if Pulse Width Modulator D is enabled
 * @return True, if Pulse Width Modulator D is enabled
 */
inline bool TimerHS::isPWMDEnabled() const
{
	return REG_(tccrc).pwmd;
}
/**
 * @brief Enable Pulse Width Modulator D
 *
 * When set (one) this bit enables PWM mode based on comparator
 * OCRD.
 */
inline void TimerHS::enablePWMD()
{
	REG_(tccrc).pwmd = true;
}
/**
 * @brief Disable Pulse Width Modulator D
 */
inline void TimerHS::disablePWMD()
{
	REG_(tccrc).pwmd = false;
}
/**
 * @brief Set Pulse Width Modulator D Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setPWMDEnable(bool val)
{
	REG_(tccrc).pwmd = val;
}
/**
 * @brief Return true, if PWM Inversion Mode is selected
 * @return True, if PWM Inversion Mode is selected
 */
inline bool TimerHS::isPWMInversionModeEnabled() const
{
	return REG_(tccrb).pwmx;
}
/**
 * @brief Select PWM Inversion Mode
 *
 * When this bit is set (one), the PWM Inversion Mode is selected
 * and the Dead Time Generator outputs, OCx and nOCx are inverted.
 */
inline void TimerHS::enablePWMInversionMode()
{
	REG_(tccrb).pwmx = true;
}
/**
 * @brief Deselect PWM Inversion Mode
 */
inline void TimerHS::disablePWMInversionMode()
{
	REG_(tccrb).pwmx = false;
}
/**
 * @brief Set PWM Inversion Mode Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setPWMInversionModeEnable(bool val)
{
	REG_(tccrb).pwmx = val;
}
/**
 * @brief Reset Prescaler
 *
 * When this bit is set (one), the Timer/Counter4 prescaler
 * (TCNT4 is unaffected) will be reset. The bit will be cleared
 * by hardware after the operation is performed.
 *
 * Writing a zero to this bit will have no effect. This bit will
 * always read as zero.
 */
inline void TimerHS::resetPrescaler()
{
	REG_(tccrb).psr = true;
}
/**
 * @brief Return Dead Time Prescaler value
 * @return Dead Time Prescaler value
 */
inline TimerHS::DeadTimePrescaler TimerHS::deadTimePrescaler() const
{
	return (DeadTimePrescaler) REG_(tccrb).dtps;
}
/**
 * @brief Set Dead Time Prescaler value
 * @param[in] val New Dead Time Prescaler value
 */
inline void TimerHS::setDeadTimePrescaler(DeadTimePrescaler val)
{
	REG_(tccrb).dtps = val;
}
/**
 * @brief Return Clock Select value
 * @return Clock Select value
 */
inline TimerHS::Prescaler TimerHS::clockSelect() const
{
	return (Prescaler) REG_(tccrb).cs;
}
/**
 * @brief Set Clock Select value
 * @param[in] val New Clock Select value
 */
inline void TimerHS::setClockSelect(Prescaler val)
{
	REG_(tccrb).cs = val;
}
/**
 * @brief Return Comparator A Output Mode shadow value
 * @return Comparator A Output Mode shadow value
 */
inline TimerHS::CompOutMode TimerHS::compOutModeShadowA() const
{
	return (CompOutMode) REG_(tccrc).comas;
}
/**
 * @brief Set Comparator A Output Mode shadow value
 * @param[in] val New Comparator A Output Mode shadow value
 */
inline void TimerHS::setCompOutModeShadowA(CompOutMode val)
{
	REG_(tccrc).comas = val;
}
/**
 * @brief Return Comparator B Output Mode shadow value
 * @return Comparator B Output Mode shadow value
 */
inline TimerHS::CompOutMode TimerHS::compOutModeShadowB() const
{
	return (CompOutMode) REG_(tccrc).combs;
}
/**
 * @brief Set Comparator B Output Mode shadow value
 * @param[in] val New Comparator B Output Mode shadow value
 */
inline void TimerHS::setCompOutModeShadowB(CompOutMode val)
{
	REG_(tccrc).combs = val;
}
/**
 * @brief Return true, if Fault Protection Interrupt is enabled
 * @return True, if Fault Protection Interrupt is enabled
 */
inline bool TimerHS::isFaultProtIntEnabled() const
{
	return REG_(tccrd).fpie;
}
/**
 * @brief Enable Fault Protection Interrupt
 */
inline void TimerHS::enableFaultProtInt()
{
	REG_(tccrd).fpie = true;;
}
/**
 * @brief Disable Fault Protection Interrupt
 */
inline void TimerHS::disableFaultProtInt()
{
	REG_(tccrd).fpie = false;
}
/**
 * @brief Set Fault Protection Interrupt Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setFaultProtIntEnable(bool val)
{
	REG_(tccrd).fpie = val;
}
/**
 * @brief Return true, if Fault Protection Mode is enabled
 * @return True, if Fault Protection Mode is enabled
 */
inline bool TimerHS::isFaultProtModeEnabled() const
{
	return REG_(tccrd).fpen;
}
/**
 * @brief Enable Fault Protection Mode
 */
inline void TimerHS::enableFaultProtMode()
{
	REG_(tccrd).fpen = true;
}
/**
 * @brief Disable Fault Protection Mode
 */
inline void TimerHS::disableFaultProtMode()
{
	REG_(tccrd).fpen = false;
}
/**
 * @brief Set Fault Protection Mode state
 * @param[in] val New state value
 */
inline void TimerHS::setFaultProtModeEnable(bool val)
{
	REG_(tccrd).fpen = val;
}
/**
 * @brief Return true, if Fault Protection Noise Canceler is on
 * @return True, if Fault Protection Noise Canceler is on
 */
inline bool TimerHS::isFaultProtNoiseCancelerOn() const
{
	return REG_(tccrd).fpnc;
}
/**
 * @brief Activate Fault Protection Noise Canceler
 *
 * When the noise canceler is activated, the input from the Fault
 * Protection Pin (INT0) is filtered. The filter function requires
 * four successive equal valued samples of the INT0 pin for changing
 * its output. The Fault Protection is therefore delayed by four
 * Oscillator cycles when the noise canceler is enabled.
 */
inline void TimerHS::setFaultProtNoiseCancelerOn()
{
	REG_(tccrd).fpnc = true;
}
/**
 * @brief Deactivate Fault Protection Noise Canceler
 */
inline void TimerHS::setFaultProtNoiseCancelerOff()
{
	REG_(tccrd).fpnc = false;
}
/**
 * @brief Set Fault Protection Noise Canceler state
 * @param[in] val New state value
 */
inline void TimerHS::setFaultProtNoiseCancelerState(bool val)
{
	REG_(tccrd).fpnc = val;
}
/**
 * @brief Return Fault Protection Edge Select value
 * @return Fault Protection Edge Select value
 */
inline TimerHS::EdgeSelect TimerHS::faultProtEdgeSelect() const
{
	return (EdgeSelect) REG_(tccrd).fpes;
}
/**
 * @brief Select Fault Protection Edge
 * @param[in] val Fault Protection Edge Select value
 *
 * This bit selects which edge on the Fault Protection pin (INT0) is used
 * to trigger a fault event.
 */
inline void TimerHS::setFaultProtEdgeSelect(EdgeSelect val)
{
	REG_(tccrd).fpes = val;
}
/**
 * @brief Return true, if Fault Protection Analog Comparator is enabled
 * @return True, if Fault Protection Analog Comparator is enabled
 */
inline bool TimerHS::isFaultProtAnalogCompEnabled() const
{
	return REG_(tccrd).fpac;
}
/**
 * @brief Enable Fault Protection Analog Comparator
 *
 * When written logic one, this bit enables the Fault Protection
 * function in Timer/Counter to be triggered by the Analog Comparator.
 *
 * The comparator output is in this case directly connected to the Fault
 * Protection front-end logic, making the comparator utilize the noise
 * canceler and edge select features of the Timer/Counter Fault Protection
 * interrupt.
 *
 * When written logic zero, no connection between the Analog Comparator and
 * the Fault Protection function exists. To make the comparator trigger the
 * Timer/Counter Fault Protection interrupt, the Fault Protection Interrupt
 * must be enabled.
 * @sa TimerHS::enableFaultProtInt()
 */
inline void TimerHS::enableFaultProtAnalogComp()
{
	REG_(tccrd).fpac = true;
}
/**
 * @brief Disable Fault Protection Analog Comparator
 */
inline void TimerHS::disableFaultProtAnalogComp()
{
	REG_(tccrd).fpac = false;
}
/**
 * @brief Set Fault Protection Analog Comparator Enable state
 * @param[in] val New state value
 */
inline void TimerHS::setFaultProtAnalogCompEnable(bool val)
{
	REG_(tccrd).fpac = val;
}
/**
 * @brief Return true, if Fault Protection Interrupt Flag is set
 * @return True, if Fault Protection Interrupt Flag is set
 *
 * When the FPIE bit is set (one), the Fault Protection Interrupt
 * is enabled. Activity on the pin will cause an interrupt request
 * even, if the Fault Protection pin is configured as an output.
 * The corresponding interrupt of Fault Protection Interrupt Request
 * is executed from the Fault Protection Interrupt Vector.
 *
 * The bit FPF is cleared by hardware when executing the corresponding
 * interrupt handling vector. Alternatively, FPF is cleared after a
 * synchronization clock cycle by writing a logical one to the flag.
 * When the SREG I-bit, FPIE4 and FPF4 are set, the Fault Interrupt is
 * executed.
 * @sa TimerHS::enableFaultProtInt()
 * @sa TimerHS::clearFaultProtInt()
 */
inline bool TimerHS::isFaultProtInt() const
{
	return REG_(tccrd).fpf;
}
/**
 * @brief Clear Fault Protection Interrupt Flag
 */
inline void TimerHS::clearFaultProtInt()
{
	REG_(tccrd).fpf = true;
}
/**
 * @brief Return Wave Generation Mode value
 * @return Wave Generation Mode value
 */
inline TimerHS::WaveGenMode TimerHS::wavGenMode() const
{
	return (WaveGenMode) REG_(tccrd).wgm;
}
/**
 * @brief Set Wave Generation Mode value
 * @param[in] val New Wave Generation Mode value
 */
inline void TimerHS::setWavGenMode(WaveGenMode val)
{
	REG_(tccrd).wgm = val;
}
/**
 * @brief Return true, if Register Update is locked
 * @return True, if Register Update is locked
 */
inline bool TimerHS::isRegisterUpdateLocked() const
{
	return REG_(tccre).tlock;
}
/**
 * @brief Lock Register Update
 *
 * This bit controls the Compare registers update. When this bit
 * is set, writing to the Compare registers will not affect the
 * output, however the values are stored and will be updated to
 * the Compare registers when the TLOCK bit will be cleared.
 * @sa TimerHS::unlockRegisterUpdate()
 */
inline void TimerHS::lockRegisterUpdate()
{
	REG_(tccre).tlock = true;
}
/**
 * @brief Unlock Register Update
 */
inline void TimerHS::unlockRegisterUpdate()
{
	REG_(tccre).tlock = false;
}
/**
 * @brief Set Register Update Lock state
 * @param[in] val New state value
 */
inline void TimerHS::setRegisterUpdateLock(bool val)
{
	REG_(tccre).tlock = val;
}
/**
 * @brief Return true, if Enhanced Compare/PWM Mode is on
 * @return True, if Enhanced Compare/PWM Mode is on
 */
inline bool TimerHS::isEnhancedModeOn() const
{
	return REG_(tccre).enhc;
}
/**
 * @brief Turn on Enhanced Compare/PWM Mode
 *
 * When this bit is set, the Waveform Generation Module works in
 * enhanced mode: the compare registers OCRA/B/D can welcome one
 * more accuracy bit, while the LSB determines on which clock edge
 * the Compare condition is signaled and the output pin level is
 * updated.
 */
inline void TimerHS::setEnhancedModeOn()
{
	REG_(tccre).enhc = true;
}
/**
 * @brief Turn off Enhanced Compare/PWM Mode
 */
inline void TimerHS::setEnhancedModeOff()
{
	REG_(tccre).enhc = false;
}
/**
 * @brief Set Enhanced Compare/PWM Mode state
 * @param[in] val New satte value
 */
inline void TimerHS::setsetEnhancedModeState(bool val)
{
	REG_(tccre).enhc = val;
}
/**
 * @brief Return true, if Output Compare Override Enable Bit is set
 * @return True, if Output Compare Override Enable Bit is set
 */
inline bool TimerHS::isOutCompOverrideEnableOn(OutCompOverrideEnableBit bit) const
{
	return (REG_(tccre).ocoe & bit);
}
/**
 * @brief Set Output Compare Override Enable Bit
 * @param[in] bit Bit mask
 */
inline void TimerHS::setOutCompOverrideEnableOn(OutCompOverrideEnableBit bit)
{
	REG_(tccre).ocoe |= bit;
}
/**
 * @brief Clear Output Compare Override Enable Bit
 * @param[in] bit Bit mask
 */
inline void TimerHS::setOutCompOverrideEnableOff(OutCompOverrideEnableBit bit)
{
	REG_(tccre).ocoe &= ~bit;
}
/**
 * @brief Set Output Compare Override Enable Bit state
 * @param[in] bit Bit mask
 * @param[in] val New state value
 */
inline void TimerHS::setOutCompOverrideEnable(OutCompOverrideEnableBit bit, bool val)
{
	REG_(tccre).ocoe = (REG_(tccre).ocoe & ~bit) | (val ? bit : 0);
}
/**
 * @brief Return 10-bit Register Access object
 * @param[in] reg Reference to register
 * @return 10-bit Register Access object
 */
inline TimerHS::TenBitReg& TimerHS::tenBitReg(Reg& reg)
{
	TimerHS::TenBitReg *p = (TimerHS::TenBitReg *) &reg;
	return *p;
}
/**
 * @brief Write value to a 10-bit Register
 * @param[in] val Value to write
 * @param[in] timhs Reference to register
 */
inline void TimerHS::TenBitReg::write(uint16_t val, TimerHS& timhs)
{
	register uint8_t high = (val >> 8) & 3;
	register uint8_t sreg = SREG;
	disableInterrupts();
	REG(timhs.tcnth) = high;
	*((Reg*) this) = val;
	SREG = sreg;
}
/**
 * @brief Read value from a 10-bit Register
 * @param[in] timhs Reference to register
 * @return Value from register
 */
inline uint16_t TimerHS::TenBitReg::read(const TimerHS& timhs)
{
	register uint8_t sreg = SREG;
	disableInterrupts();
	register uint16_t ret = *((Reg*) this);
	ret |= REG(timhs.tcnth) << 8;
	SREG = sreg;
	return ret;
}
/**
 * @brief Return Counter value
 * @return Counter value
 */
inline uint16_t TimerHS::counter() const
{
	return tenBitReg(REG(tcnt)).read(*this);
}
/**
 * @brief Set Counter value
 * @param[in] val New Counter value
 */
inline void TimerHS::setCounter(uint16_t val)
{
	tenBitReg(REG(tcnt)).write(val, *this);
}
/**
 * @brief Return Output Compare Register A value
 * @return Output Compare Register A value
 */
inline uint16_t TimerHS::outputCompareA() const
{
	return tenBitReg(REG(oca)).read(*this);
}
/**
 * @brief Set Output Compare Register A value
 * @param[in] val New Output Compare Register A value
 */
inline void TimerHS::setOutputCompareA(uint16_t val)
{
	tenBitReg(REG(oca)).write(val, *this);
}
/**
 * @brief Return Output Compare Register B value
 * @return Output Compare Register B value
 */
inline uint16_t TimerHS::outputCompareB() const
{
	return tenBitReg(REG(ocb)).read(*this);
}
/**
 * @brief Set Output Compare Register B value
 * @param[in] val New Output Compare Register B value
 */
inline void TimerHS::setOutputCompareB(uint16_t val)
{
	tenBitReg(REG(ocb)).write(val, *this);
}
/**
 * @brief Return Output Compare Register C value
 * @return Output Compare Register C value
 */
inline uint16_t TimerHS::outputCompareC() const
{
	return tenBitReg(REG(occ)).read(*this);
}
/**
 * @brief Set Output Compare Register C value
 * @param[in] val New Output Compare Register C value
 */
inline void TimerHS::setOutputCompareC(uint16_t val)
{
	tenBitReg(REG(occ)).write(val, *this);
}
/**
 * @brief Return Output Compare Register D value
 * @return Output Compare Register D value
 */
inline uint16_t TimerHS::outputCompareD() const
{
	return tenBitReg(REG(ocd)).read(*this);
}
/**
 * @brief Set Output Compare Register D value
 * @param[in] val New Output Compare Register D value
 */
inline void TimerHS::setOutputCompareD(uint16_t val)
{
	tenBitReg(REG(ocd)).write(val, *this);
}
/**
 * @brief Return Dead Time Value for OCx Output
 * @return Dead Time Value for OCx Output
 */
inline unsigned char TimerHS::deadTimeOCx() const
{
	return REG_(dt).dth;
}
/**
 * @brief Set Dead Time Value for OCx Output
 * @param[in] val New Dead Time Value for OCx Output
 */
inline void TimerHS::setDeadTimeOCx(unsigned char val)
{
	REG_(dt).dtl = val;
}
/**
 * @brief Return Dead Time Value for nOCx Output
 * @return Dead Time Value for nOCx Output
 */
inline unsigned char TimerHS::deadTimeNOCx() const
{
	return REG_(dt).dtl;
}
/**
 * @brief Set Dead Time Value for nOCx Output
 * @param[in] val New Dead Time Value for nOCx Output
 */
inline void TimerHS::setDeadTimeNOCx(unsigned char val)
{
	REG_(dt).dtl = val;
}

#endif /* TIMERHS_H_ */
