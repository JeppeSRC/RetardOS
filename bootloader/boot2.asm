BITS 16

;%define _BREAK

%ifdef _BREAK
%define BREAK xchg bx, bx
%else
%define BREAK
%endif

%define KERNEL_RMODE_LOC 0x820
%define KERNEL_PMODE_LOC 0x100000

jmp start

%include "simplefs.inc"

gdt_data: 
	dd 0                ; null descriptor
	dd 0 

; gdt code:	            ; code descriptor
	dw 0FFFFh           ; limit low
	dw 0                ; base low
	db 0                ; base middle
	db 10011010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high

; gdt data:	            ; data descriptor
	dw 0FFFFh           ; limit low (Same as code)10:56 AM 7/8/2007
	dw 0                ; base low
	db 0                ; base middle
	db 10010010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high
	
end_of_gdt:
gdtr: 
	dw end_of_gdt - gdt_data - 1
	dd gdt_data+0x7E00			

VolumeLable: db '                  ' 	
Version: dw 0x0000					
Disktype: db 0x00					
ReservedSectors: db 0x00			
SectorsPerFAT: db 0x00				
RootDirSectors: db 0x00			
RootEntries: dw 0x00
BytesPerSector: dw 0x000			
Tracks: db 0x00						
SectorsPerTrack: db 0x00			
Heads: db 0x00			
Formatted: db 0

KernelFileName: db 'kernel.sys                      '
KernelFileSize: dd 0
KernelSig: db 'PE'
KernelCodeSig: db '.text'
KernelRDataSig: db '.rdata'
KernelDataSig: db '.data'
KernelRelocationTalbleSig: db '.reloc' 

msgLoadingKernel: db ' Loading kernel !', 0

print:
	push ax
	loopPrint:
		lodsb
		cmp al, 0
		je donePrint
		mov ah, 0x0E
		int 0x10
		jmp loopPrint

	donePrint:
		pop ax
		ret

start:
	xor ax, ax
	mov ax, 0x7E0
	mov gs, ax
	mov fs, ax

	xor cx, cx
	mov cx, 0x10

	xor esi, esi
	pop si

	xor di, di
	mov di, VolumeLable

	rep movsw
	
	xor ax, ax
	mov ax, 0x7E0
	mov ds, ax

	xor eax, eax
	mov al, byte [SectorsPerFAT]
	add al, byte [ReservedSectors]

	call LBACHS

LoadRootDir:
	xor eax, eax
	mov ax, KERNEL_RMODE_LOC
	mov es, ax
	xor bx, bx

	xor eax, eax
	mov al, byte [RootDirSectors]

	call readSectors

	xor cx, cx
	mov cx, word [RootEntries]
	xor di, di

FindFile:
	push cx
	mov cx, 0xA
	xor si, si
	mov si, KernelFileName
	push di
	rep cmpsb
	pop di
	je .found
	add di, 0x28
	pop cx
	loop FindFile
	mov si, msgFailedToFindFile
	call print
	hlt

	.found:
		mov bx, di
		add bx, 0x20
		xor eax, eax
		xor ecx, ecx
		mov eax, dword [es:bx]
		add bx, 0x04
		mov ecx, dword [es:bx]

		mov dword [KernelFileSize], eax

		xor ebx, ebx
		mov bx, word [BytesPerSector]
		div ebx

		cmp edx, 0
		je LoadFile
		
		inc eax
		
		
	LoadFile:

		mov si, msgLoadingKernel
		call print

		xchg eax, ecx
		;eax Start sector
		;ecx Number of sectors
		xor bx, bx

		loopLoadFile:

			call LBACHS

			mov al, 0x01

			call readSectors

			add bx, 0x1fe
			mov ax, word [es:bx]

			loop loopLoadFile


		mov ax, 0x7E0
		mov es, ax

		cli

		xor ax, ax
		in al, 0x92
		or al, 0x02
		out 0x92, al

		cli
		pusha
		lgdt [gdtr]
		popa

		cli
		mov eax, cr0
		or eax, 0x01
		mov cr0, eax	


		jmp 0x08:PMode+0x7E00
		hlt
	
BITS 32

PMode:


	xor ax, ax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov esp, 0x90000


CopyKernel:
	

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	mov eax, KERNEL_RMODE_LOC
	mov ebx, 0x10
	mul ebx
	mov esi, eax
	mov edi, KERNEL_PMODE_LOC

	mov ecx, dword [KernelFileSize+0x7E00]

	rep movsb

TestKernel:
	mov ebx, [KERNEL_PMODE_LOC+0x3C]
	add ebx, KERNEL_PMODE_LOC
	mov edi, ebx
	mov esi, KernelSig+0x7E00

	cmpsw 
	jne BadKernel

Relocation:
	BREAK
	push ebx

	;Find the first relocation table

	mov eax, ebx

	.relocLoop:

	inc eax
	mov esi, eax
	mov edi, KernelCodeSig+0x7E00
	mov ecx, 0x05

	rep cmpsb
	jne .relocLoop 

	BREAK
	;code section
	mov ebx, eax
	mov esi, ebx
	mov edi, KernelCodeSig+0x7E00
	mov ecx, 0x05

	rep cmpsb
	jne BadKernel

	call MoveSection

	;rdata section
	add ebx, 0x28
	mov esi, ebx
	mov edi, KernelRDataSig+0x7E00
	mov ecx, 0x06

	rep cmpsb
	jne BadKernel

	call MoveSection

	;data section
	add ebx, 0x28
	mov esi, ebx
	mov edi, KernelDataSig+0x7E00
	mov ecx, 0x5

	rep cmpsb
	jne BadKernel

	call MoveSection

	;reloc section
	add ebx, 0x28
	mov esi, ebx
	mov edi, KernelRelocationTalbleSig+0x7E00
	mov ecx, 0x06

	rep cmpsb
	jne ExecuteKernel

	call MoveSection

ExecuteKernel:
BREAK
	pop ebx
	add ebx, 0x28
	mov ebp, dword [ebx]
	add ebx, 0xC
	mov eax, dword [ebx]
	add ebp, eax

	call ebp

	cli
	hlt


BadKernel:
	cli
	hlt

MoveSection:
	mov edi, dword [ebx+0x0C]
	mov ecx, dword [ebx+0x10]
	mov esi, dword [ebx+0x14]

	add edi, KERNEL_PMODE_LOC
	add esi, KERNEL_PMODE_LOC

	rep movsb

	ret