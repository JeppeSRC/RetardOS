
#include "math64.h"


uint64 uint64div(uint64 divident, uint32 divider, uint32* remainder) {
	uint32 dividentHigh = (uint32)((divident >> 32) & 0xFFFFFFFF);
	uint32 dividentLow = (uint32)(divident & 0xFFFFFFFF);

	__asm {
	


		push dividentLow
		mov eax, dividentHigh
		xor edx, edx
		div divider
		xchg eax, [esp]
		div divider

		mov ecx, dword ptr remainder
		or ecx, ecx
		jz skip

		mov dword ptr [ecx], edx

		skip:

		pop edx

		mov dividentHigh, edx
		mov dividentLow, eax
	};


	return (uint64)(((uint64)dividentHigh << 32) | dividentLow);
}