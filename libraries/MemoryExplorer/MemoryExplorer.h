#ifndef	MEMORY_EXPLRORER_H
#define	MEMORY_EXPLRORER_H

#include <arduino.h>

extern char *__brkval;

class Pointer : public Printable {
public:
    Pointer(const void * ptr = NULL) : m_ptr(ptr) {}

    size_t printTo(Print& p) const {
	char szBuffer[13];
	sprintf(szBuffer, "@%04X(%d)", (unsigned)m_ptr, (unsigned)m_ptr);
	return  p.print(szBuffer);
    }
    
private:
    const void * m_ptr;
};

//
//	Возвращает текущее значение указателя стека
// как беззнаковое целое и макрос для печати указателя стека
//
static inline unsigned getSP(void) { return (unsigned)(SP); }
#define SP_Pointer	(Pointer((void*)SP))

//
//	Возвращает текущее значение адрес "конца" кучи
// как беззнаковое целое и как Pointer для печати
//
static inline unsigned heapEnd(void) { return (__malloc_heap_end) ? (unsigned)__malloc_heap_end : SP - __malloc_margin; }
#define	HE_Pointer	(Pointer((__malloc_heap_end) ? __malloc_heap_end : (void *)(SP - __malloc_margin)))
//
//	Возвращает текущее значение адреса "начала" кучи
//
static inline unsigned heapStart(void) { return (unsigned)__malloc_heap_start; }
#define	HS_Pointer	(Pointer(__malloc_heap_start))
//
// Возвращает текущее значение адреса начала ещё нераспределённого куска памяти
//
static inline unsigned newSoil(void) { return (unsigned)(__brkval ? __brkval : __malloc_heap_start); }
#define	NS_Pointer	(Pointer(__brkval ? __brkval : __malloc_heap_start))


extern void memoryReport(const char *title);

#endif	//	MEMORY_EXPLRORER_H
