//
// C++ Interface: ucdefs
//
// Description: Parameters of microcontrollers.
//
//
// Author: Andrey Sharoyko <vanyamboe@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef UCDEFS_H_
#define UCDEFS_H_

#if defined(VE_ATmega328P)

#define DUMP_ARDUINO

#define DUMP_FLASH_ADDR_LEN     4
#define DUMP_RAM_ADDR_LEN       3
#define DUMP_EEPROM_ADDR_LEN    3
#define DUMP_ADDR_TYPE          unsigned int
#define DUMP_REG_ADDR_TYPE      unsigned char

#elif defined(VE_ATmega2560)

#define DUMP_MEGA

#define DUMP_FLASH_ADDR_LEN     5
#define DUMP_RAM_ADDR_LEN       4
#define DUMP_EEPROM_ADDR_LEN    4
#define DUMP_ADDR_TYPE          unsigned long
#define DUMP_REG_ADDR_TYPE      unsigned int

#elif defined(VE_ATmega32U4)

#define DUMP_LEONARDO

#define DUMP_FLASH_ADDR_LEN     4
#define DUMP_RAM_ADDR_LEN       3
#define DUMP_EEPROM_ADDR_LEN    3
#define DUMP_ADDR_TYPE          unsigned int
#define DUMP_REG_ADDR_TYPE      unsigned char

#elif defined(VE_ATmega644PA)

#define DUMP_SANGUINO

#define DUMP_FLASH_ADDR_LEN     4
#define DUMP_RAM_ADDR_LEN       4
#define DUMP_EEPROM_ADDR_LEN    3
#define DUMP_ADDR_TYPE          unsigned int
#define DUMP_REG_ADDR_TYPE      unsigned char

#elif defined(VE_ATmega1284P)

#define DUMP_DAIDUINO

#define DUMP_FLASH_ADDR_LEN     5
#define DUMP_RAM_ADDR_LEN       4
#define DUMP_EEPROM_ADDR_LEN    4
#define DUMP_ADDR_TYPE          unsigned long
#define DUMP_REG_ADDR_TYPE      unsigned char

#else
//#   error "TODO: Add board type support here."
#endif

#endif /* UCDEFS_H_ */
