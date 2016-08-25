#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <sys.h>
#include <cmos.h>
#include "smap.h"

#define BREAK __asm xchg bx, bx

void _cdecl kmain(byte* smapPointer) {
	_clr();

	SMAP smap;
	SMAP_Init(&smap, smapPointer);

	_print("Reading Memory map\n\n");

	_printf("MemoryMap Entries: %u\n\n", smap.numEntries);

	uint32 total = 0;

	for (uint16 i = 0; i < smap.numEntries; i++) {
		SMAP_ENTRY e = smap.entries[i];

		if (e.type == 1 || e.type == 3) total += e.lengthLow;

		_printf("base: %h | length: %h | type: %u\n", e.baseAddressLow, e.lengthLow, e.type);
	}

	_printf("\nTotal available memory: %u MB\n", total / 1024 / 1024);

	__asm cli
	__asm hlt
}
