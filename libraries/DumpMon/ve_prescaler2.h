/**
 * @file ve_prescaler2.h
 * @brief 8-bit Timer/Counter 2 Prescaler Header
 * @author andrey
 * @date 10.02.2012
 * @copyright GNU Public License
 */
#ifndef PRESCALER2_H_
#define PRESCALER2_H_

/**
 * @brief 8-bit Timer/Counter 2 Prescaler class
 * @ingroup Timers
 */
class Prescaler2
{
public:
	/**
	 * @brief Clock Select type
	 */
    typedef enum
    {
        Stopped = 0,			///< Stopped
        Prescaler_1 = 1,		///< System Clock /1
        Prescaler_8 = 2,		///< System Clock /8
        Prescaler_32 = 3,		///< System Clock /32
        Prescaler_64 = 4,		///< System Clock /64
        Prescaler_128 = 5,		///< System Clock /128
        Prescaler_256 = 6,		///< System Clock /256
        Prescaler_1024 = 7		///< System Clock /1024
    } ClkSelect;
public:
    static uint16_t prescaler(ClkSelect _cksel);
};

/**
 * @brief Return unsigned integer Prescaler value
 * @param[in] _cksel Prescaler value
 * @return Unsigned integer Prescaler value
 */
inline uint16_t Prescaler2::prescaler(ClkSelect _cksel)
{
    switch (_cksel)
    {
    case Prescaler_8:
        return 8;
    case Prescaler_32:
        return 32;
    case Prescaler_64:
        return 64;
    case Prescaler_128:
        return 128;
    case Prescaler_256:
        return 256;
    case Prescaler_1024:
        return 1024;
    default:
        return 1;
    }
}

#endif /* PRESCALER2_H_ */
