/**
 * @file ve_storeprogrammemory.h
 * @brief Store Program Memory Header
 * @author andrey
 * @date 24.10.2012
 * @copyright GNU Public License
 */
#ifndef STOREPROGRAMMEMORY_H_
#define STOREPROGRAMMEMORY_H_

bool eeprom_isBusyWrite();

/**
 * @brief Store Program Memory class
 * @ingroup VE_AVR
 */
class StoreProgMem : public AVR_SPM
{
public:
	bool isInterruptEnabled() const;
	void enableInterrupt();
	void disableInterrupt();
	void setInterruptEnable(bool val);

	bool isSectionBusy() const;
	bool isSectionReadEnabled() const;
	bool isSelfProgEnabled() const;
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
	void signatureRowRead();
#endif
	void pageWrite();
	void pageErase();
	void doSPM(uint8_t spmcrval);
};

/**
 * @brief Return true, if SPM Interrupt is enabled
 * @return True, if SPM Interrupt is enabled
 */
inline bool StoreProgMem::isInterruptEnabled() const
{
	return REG_(spmcsr).spmie;
}
/**
 * @brief Enable SPM Interrupt
 */
inline void StoreProgMem::enableInterrupt()
{
	REG_(spmcsr).spmie = true;
}
/**
 * @brief Disable SPM Interrupt
 */
inline void StoreProgMem::disableInterrupt()
{
	REG_(spmcsr).spmie = false;
}
/**
 * @brief Set SPM Interrupt Enable state
 * @param[in] val New state value
 */
inline void StoreProgMem::setInterruptEnable(bool val)
{
	REG_(spmcsr).spmie = val;
}
/**
 * @brief Return true, if Read-While-Write Section Busy Flag is set
 * @return True, if Read-While-Write Section Busy Flag is set
 *
 * When a Self-Programming (Page Erase or Page Write) operation to
 * the RWW section is initiated, the RWWSB will be set (one) by hardware.
 * When the RWWSB bit is set, the RWW section cannot be accessed.
 *
 * The RWWSB bit will be cleared if the RWWSRE bit is written to one
 * after a Self-Programming operation is completed. Alternatively the
 * RWWSB bit will automatically be cleared if a page load operation is
 * initiated.
 */
inline bool StoreProgMem::isSectionBusy() const
{
	return REG_(spmcsr).rwwsb;
}
/**
 * @brief Return true, if Read-While-Write Section Read Enable Flag is set
 * @return True, if Read-While-Write Section Read Enable Flag is set
 *
 * When programming (Page Erase or Page Write) to the RWW section, the RWW
 * section is blocked for reading (the RWWSB will be set by hardware).
 *
 * To re-enable the RWW section, the user software must wait until the
 * programming is completed (SPMEN will be cleared). Then, if the RWWSRE bit
 * is written to one at the same time as SPMEN, the next SPM instruction
 * within four clock cycles re-enables the RWW section.
 *
 * The RWW section cannot be re-enabled while the Flash is busy with a Page
 * Erase or a Page Write (SPMEN is set).
 *
 * If the RWWSRE bit is written while the Flash is being loaded, the Flash
 * load operation will abort and the data loaded will be lost.
 */
inline bool StoreProgMem::isSectionReadEnabled() const
{
	return REG_(spmcsr).rwwsre;
}
/**
 * @brief Return true, if Store Program Memory instruction is enabled
 * @return True, if Store Program Memory instruction is enabled
 */
inline bool StoreProgMem::isSelfProgEnabled() const
{
	return REG_(spmcsr).selfprgen;
}
#if defined(__DOXYGEN__) || \
	defined(VE_ATmega2560) || \
	defined(VE_ATmega644PA) || \
	defined(VE_ATmega1284P)
/**
 * @brief Set Signature Row Read Bit
 */
inline void StoreProgMem::signatureRowRead()
{
	doSPM(_BV(SPMEN) | _BV(SIGRD));
}
#endif
/**
 * @brief Set Page Write Bit
 */
inline void StoreProgMem::pageWrite()
{
	doSPM(_BV(SPMEN) | _BV(PGWRT));
}
/**
 * @brief Set Page Erase Bit
 */
inline void StoreProgMem::pageErase()
{
	doSPM(_BV(SPMEN) | _BV(PGERS));
}
/**
 * @brief Do SPM Instruction
 * @param[in] spmcrval SPM command bit set
 */
inline BOOT_SECTION void StoreProgMem::doSPM(uint8_t spmcrval)
{
	while(isSelfProgEnabled());
	register unsigned char sreg = SREG;
	disableInterrupts();
	while(eeprom_isBusyWrite());
	REG(spmcsr) = spmcrval;
	asm volatile("spm");
	SREG = sreg;
}

#endif /* STOREPROGRAMMEMORY_H_ */
