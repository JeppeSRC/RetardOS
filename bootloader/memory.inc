%ifndef _MEM_MAP_
%define _MEM_MAP_


	MapMemory:
	;pusha
	;pushf
	xor bp, bp
	xor edi, edi
	mov di, 0x02
	xor eax, eax
	
	clc

	xor eax, eax
	xor ebx, ebx
	mov edx, 0x534D4150
	mov eax, 0xE820
	mov ecx, 24

	int 0x15

	jc .MapMemoryFailed

	mov edx, 0x534D4150
	cmp eax, edx
	jne .MapMemoryFailed

	test ebx, ebx
	je .MapMemoryFailed

	jmp .enttest

	.MapMemoryLoop:
		mov eax, 0xE820
		mov ecx, 24

		int 0x15

		jc .listFull
		mov edx, 0x534D4150

	.enttest:
		cmp ecx, 0
		je .skip


		mov ecx, DWORD [es:di + 8]
		or ecx, DWORD [es:di + 12]
		jz .skip

		inc bp
		add di, 24

	.skip:
		test ebx, ebx
		jne .MapMemoryLoop

	.listFull:
		mov WORD [es:00], bp
		clc
	



	.MapMemoryFailed:
	;popf
	;popa
	ret

%endif