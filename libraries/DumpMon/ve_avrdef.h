/**
 * @file ve_avrdef.h
 * @brief AVR8 definitions
 * @author andrey
 * @date 21.01.2012
 * @copyright GNU Public License
 */
#ifndef AVRDEF_H_
#define AVRDEF_H_

/**
 * @brief Boot section attribute macro
 */
#define BOOT_SECTION __attribute__((section (".boot")))

/**
 * @brief Reference to an object macro
 */
#define OBJ(_pstruct)   (*(_pstruct))

/**
 * @brief NOP assembler command
 *
 * No Operation. Go to execute the next command.
 */
#define nop()           _NOP()
#if defined(__DOXYGEN__) || \
	!defined(cli)
/**
 * @brief CLI assembler command
 *
 * Clear Interrupts flag. It disables interrupts globally.
 */
# define cli()          __builtin_avr_cli()
#endif
#if defined(__DOXYGEN__) || \
	!defined(sei)
/**
 * @brief SEI assembler command
 *
 * Set Interrupts flag. It enables interrupts globally.
 */
# define sei()          __builtin_avr_sei()
#endif

#if defined(__DOXYGEN__) || \
	!defined(UNUSED)
/**
 * @brief Portable unused parameter macro
 */
#define UNUSED(x) ((void)(x))
#endif

#endif /* AVRDEF_H_ */
