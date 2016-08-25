#include "memory.h"
#include "stddef.h"

void _memset(void* _dst, uint8 _value, uint32 _size) {
	__asm {
		mov ecx, _size
		mov al, _value
		mov ebx, _dst
		loopMemset:
		mov [ebx], al
		inc ebx
		loop loopMemset
	}
}

void _memcpy(void* _dst, const void* _src, uint32 _size) {
	__asm {
		mov ecx, _size
		mov esi, _src
		mov edi, _dst
		rep movsb
	}
}