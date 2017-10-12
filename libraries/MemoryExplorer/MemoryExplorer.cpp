#include <arduino.h>
#include "MemoryExplorer.h"


typedef struct __freelist {
    size_t _size;
    struct __freelist *_next;
} FreeList;

extern FreeList *__flp;
extern char *__brkval;

int getNumberOfBlocksInFreeList() {
    FreeList *fp;
    int i;
    for(i=0,fp=__flp;fp;fp=fp->_next,i++);
    return i;
}


void memoryReport(const char * title) {
    Serial.print("---- Memory report: ");
    Serial.println(title);
    Serial.print("HEAP:");
    Serial.print(HS_Pointer);
    Serial.print('-');
    Serial.print(HE_Pointer);
    Serial.print(";\nUnallocated from:");
    Serial.print(NS_Pointer);
    Serial.print(";\nStack pointer: ");
    Serial.println(SP_Pointer);
    Serial.print("Free List:");
    FreeList *ptr = __flp;
    if (!ptr) Serial.print(" EMPTY");
    while (ptr) {
	Serial.print("\n\tBlock at:");
	Serial.print(Pointer(ptr));
	Serial.print("; Size:");
	Serial.print(ptr->_size);
	ptr = ptr->_next;
    }
    Serial.print("\n-----\n");
}
