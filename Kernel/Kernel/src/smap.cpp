#include "smap.h"

void SMAP_Init(SMAP* map, byte* mapPointer) {
	map->numEntries = *(uint16*)mapPointer;
	map->entries = (SMAP_ENTRY*)(mapPointer + 2);
}

void SMAP_Init(SMAP* map, KERNEL_BOOT_HEADER* kboot) {
	SMAP_Init(map, (byte*)kboot->smapAddress);
}