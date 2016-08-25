#pragma once

#include "stddef.h"

struct SMAP_ENTRY {
	union {
		uint64 baseAddress;
		struct {
			uint32 baseAddressLow;
			uint32 baseAddressHigh;
		};
	};
	union {
		uint64 length;
		struct {
			uint32 lengthLow;
			uint32 lengthHigh;
		};
	};
	
	uint32 type;
	uint32 extended;
};

struct SMAP {
	uint16 numEntries;
	SMAP_ENTRY* entries;
};

void SMAP_Init(SMAP* map, byte* mapPointer);

