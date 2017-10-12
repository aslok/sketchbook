template <typename T> inline Print & operator << (Print &s, T n) { s.print(n); return s; }
#include "MemoryExplorer.h"

//
//	Запрашивает 2 куска памяти 200 байтов и 1 байт
//	Результаты помещает в параметры
// Возвращает true если память успешно выделилась.
//
static bool Get2MemoryBlocks(byte **block200, byte **block1) {
    *block200 = (byte *) malloc(200);
    if (*block200) {
	*block1 = (byte *) malloc(1);
	if (!*block1) free(*block200);
    }
    return *block200 && *block1;
}

void setup() {
    Serial.begin(115200);
    Serial << "*** Memory fragmentation test ***\n";
    byte *p[20], *ps[20];
    int8_t counter = 0;
    //
    // Запрашиваем пары блоков по 200 байтов и по 1 байту пока зватает памяти
    //
    for (; counter < 20 && Get2MemoryBlocks(& p[counter], & ps[counter]); counter ++);
    Serial << "counter = " << counter << "\n";
    //
    //	Успешно запросили counter пар блоков. Больше уже не лезет.
    // Теперь освобождаем все запрошенные блоки по 200 байтов
    //
    for (int8_t i=0; i < counter; i++) free(p[i]);
    //
    //	пытаемся запросить 250 байтов
    //
    byte *p250 = (byte *) malloc(250);
    if (p250) Serial << "250 bytes - succsess\n";
    else  Serial << "250 bytes - failure\n";

    memoryReport("Fragmentation");
}

void loop() {}
//
// РЕЗУЛЬТАТ
//	*** Memory fragmentation test ***
//	counter = 6
//	250 bytes - failure
//	---- Memory report: Fragmentation
//	HEAP:@02BA(698)-@0871(2161);
//	Unallocated from:@078E(1934);
//	Stack pointer: @08F1(2289)
//	Free List:
//		Block at:@02BA(698); Size:200
//		Block at:@0388(904); Size:200
//		Block at:@0456(1110); Size:200
//		Block at:@0524(1316); Size:200
//		Block at:@05F2(1522); Size:200
//		Block at:@06C0(1728); Size:200
//	-----
