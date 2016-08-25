#include "smap.h"

void SMAP_Init(SMAP* map, byte* mapPointer) {
	map->numEntries = *(uint16*)mapPointer;
	map->entries = (SMAP_ENTRY*)(mapPointer + 2);
}