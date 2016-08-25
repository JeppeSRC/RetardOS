#include "sys.h"
#include "stdio.h"
#include "cmos.h"

unsigned char _inb(uint16 port) {
	unsigned char v = 0;
	__asm {
		push eax
		xor al, al
		mov dx, port
		in al, dx
		mov v, al
		pop eax
	};

	return v;
}

uint16 _inw(uint16 port) {
	uint16 v = 0;
	__asm {
		push eax
		xor ax, ax
		mov dx, port
		in ax, dx
		mov v, ax
		pop eax
	}

	return v;
}

uint32 _ind(uint16 port) {
	uint32 v = 0;
	__asm {
		push eax
		xor eax, eax
		mov dx, port
		in eax, dx
		mov v, eax
		pop eax
	}
}

void _outb(uint16 port, uint8 value) {
	__asm {
		push eax
		mov al, value
		mov dx, port
		out dx, al
		pop eax
	};
}

void _outw(uint16 port, uint16 value) {
	__asm {
		push eax
		mov ax, value
		mov dx, port
		out dx, ax
		pop eax
	}
}

void _outd(uint16 port, uint32 value) {
	__asm {
		push eax
		mov eax, value
		mov dx, port
		out dx, eax
		pop eax
	}
}

void _inb(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		in al, dx
		mov ecx, DWORD PTR byteStruct
		mov BYTE PTR [ecx], al
		pop eax
	}
}

void _inw(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		in ax, dx
		mov ecx, DWORD PTR byteStruct
		mov WORD PTR [ecx], ax
		pop eax
	}
}

void _ind(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		in eax, dx
		mov ecx, DWORD PTR byteStruct
		mov DWORD PTR [ecx], eax
		pop eax
	}
}

void _outb(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		mov al, BYTE PTR byteStruct
		out dx, al
		pop eax
	}
}

void _outw(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		mov ax, WORD PTR byteStruct
		out dx, ax
		pop eax
	}
}

void _outd(uint16 port, void* byteStruct) {
	__asm {
		push eax
		mov dx, port
		mov eax, DWORD PTR byteStruct
		out dx, eax
		pop eax
	}
}


void _sleep(uint32 timeInSeconds) {
	uint32 minutes = timeInSeconds / 60;
	uint32 seconds = timeInSeconds % 60;
	uint32 hours = minutes / 60;
	minutes = minutes % 60;

	uint32 prevSec = 0;

	CMOS_RTC_Time time;

	CMOS_RTC_GetCurrentTime(&time);

	prevSec = time.seconds;

	while (true) {

		CMOS_RTC_GetCurrentTime(&time);

		if (time.seconds != prevSec) {
			prevSec = time.seconds;

			if (seconds == 0) {
				seconds = 60;
	
				if (minutes == 0) {
					minutes = 60;

					if (hours == 0) break;

					hours--;
				}

				minutes--;
			}

			seconds--;

		}

	}
}