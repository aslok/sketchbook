/**
 * @file ve_generaltimercontrol.h
 * @brief General Timer/Counter Control Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef GENERALTIMERCONTROL_H_
#define GENERALTIMERCONTROL_H_

/**
 * @brief General Timer/Counter Control class
 * @ingroup Timers
 */
class GeneralTimerControl : public AVR_GTCCRS
{
public:
	bool isSynchronizationModeOn() const;
	void synchronizationModeOn();
	void synchronizationModeOff();
	void setSynchronizationMode(bool val);

	void timer0PrescalerReset();
	void timer2PrescalerReset();
};

/**
 * @brief Return true, if Synchronization Mode is on
 * @return True, if Synchronization Mode is on
 */
inline bool GeneralTimerControl::isSynchronizationModeOn() const
{
	return REG_(gtccr).tsm;
}
/**
 * @brief Turn Synchronization Mode on
 */
inline void GeneralTimerControl::synchronizationModeOn()
{
	REG_(gtccr).tsm = true;
}
/**
 * @brief Turn Synchronization Mode off
 */
inline void GeneralTimerControl::synchronizationModeOff()
{
	REG_(gtccr).tsm = false;
}
/**
 * @brief Set Turn Synchronization Mode state
 * @param[in] val New state value
 */
inline void GeneralTimerControl::setSynchronizationMode(bool val)
{
	REG_(gtccr).tsm = val;
}
/**
 * @brief Reset Timer/Counter 0 Prescaler
 */
inline void GeneralTimerControl::timer0PrescalerReset()
{
	REG_(gtccr).psrsync = true;
}
/**
 * @brief Reset Timer/Counter 2 Prescaler
 */
inline void GeneralTimerControl::timer2PrescalerReset()
{
	REG_(gtccr).psrasy = true;
}

#endif /* GENERALTIMERCONTROL_H_ */
