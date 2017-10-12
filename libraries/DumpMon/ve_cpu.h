/**
 * @file ve_cpu.h
 * @brief CPU Functions Header
 * @author andrey
 * @date 23.01.2012
 * @copyright GNU Public License
 */
#ifndef CPU_H_
#define CPU_H_

/**
 * @addtogroup CPUfunc
 * @{
 */

/**
 * @brief Return true, if Interrupts are enabled
 * @return True, if Interrupts are enabled
 */
inline bool isInterruptsEnabled()
{
	return DEV_SREG.intEn;
}
/**
 * @brief Enable Interrupts
 */
inline void enableInterrupts()
{
	sei();
}
/**
 * @brief Disable Interrupts
 */
inline void disableInterrupts()
{
	cli();
}
/**
 * @brief Return true, if Half-Carry Flag is set
 * @return True, if Half-Carry Flag is set
 */
inline bool isHalfCarry()
{
    return DEV_SREG.halfCarry;
}
/**
 * @brief Set Half-Carry Flag
 */
inline void setHalfCarry()
{
	__asm__ __volatile__("seh");
}
/**
 * @brief Clear Half-Carry Flag
 */
inline void clearHalfCarry()
{
	__asm__ __volatile__("clh");
}
/**
 * @brief Return true, if Sign Flag is set
 * @return True, if Sign Flag is set
 */
inline bool isSign()
{
    return DEV_SREG.sign;
}
/**
 * @brief Set Sign Flag
 */
inline void setSign()
{
	__asm__ __volatile__("ses");
}
/**
 * @brief Clear Sign Flag
 */
inline void clearSign()
{
	__asm__ __volatile__("cls");
}
/**
 * @brief Return true, if Two-Complement Overflow Flag is set
 * @return True, if Two-Complement Overflow Flag is set
 */
inline bool isTwoCompOverflow()
{
	return DEV_SREG.twoCompOvf;
}
/**
 * @brief Set Two-Complement Overflow Flag
 */
inline void setTwoCompOverflow()
{
	__asm__ __volatile__("sev");
}
/**
 * @brief Clear Two-Complement Overflow Flag
 */
inline void clearTwoCompOverflow()
{
	__asm__ __volatile__("clv");
}
/**
 * @brief Return true, if Negative Flag is set
 * @return True, if Negative Flag is set
 */
inline bool isNegative()
{
    return DEV_SREG.negative;
}
/**
 * @brief Set Negative Flag
 */
inline void setNegative()
{
	__asm__ __volatile__("sen");
}
/**
 * @brief Clear Negative Flag
 */
inline void clearNegative()
{
	__asm__ __volatile__("cln");
}
/**
 * @brief Return true, if Zero Flag is set
 * @return True, if Zero Flag is set
 */
inline bool isZero()
{
    return DEV_SREG.zero;
}
/**
 * @brief Set Zero Flag
 */
inline void setZero()
{
	__asm__ __volatile__("sez");
}
/**
 * @brief Clear Zero Flag
 */
inline void clearZero()
{
	__asm__ __volatile__("clz");
}
/**
 * @brief Return true, if Carry Flag is set
 * @return True, if Carry Flag is set
 */
inline bool isCarry()
{
    return DEV_SREG.carry;
}
/**
 * @brief Set Carry Flag
 */
inline void setCarry()
{
	__asm__ __volatile__("sec");
}
/**
 * @brief Clear Carry Flag
 */
inline void clearCarry()
{
	__asm__ __volatile__("clc");
}
/**
 * @}
 */
#endif /* CPU_H_ */
