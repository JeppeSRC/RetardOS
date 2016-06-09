#include "memory.h"
#include "string.h"
#include "stdio.h"

#define BREAK __asm xchg bx, bx

void _cdecl kmain() {
	_clr();

	_print("Loading....\n");

	__asm cli
	__asm hlt
}