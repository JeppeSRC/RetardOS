#include <sys.h>

unsigned char _inb(unsigned short port) {
	unsigned char v = 0;
	__asm {
		xor ax, ax
		mov dx, port
		in al, dx
		mov v, al
	};

	return v;
}

void _outb(unsigned short port, unsigned char value) {
	__asm {
		mov al, value
		mov dx, port
		out dx, al
	};
}