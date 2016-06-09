#include <memory.h>

void _memset(void* _dst, unsigned char _value, unsigned int _size) {
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

void _memcpy(void* _dst, const void* _src, unsigned int _size) {
	__asm {
		mov ecx, _size
		mov esi, _src
		mov edi, _dst
		rep movsb
	}
}