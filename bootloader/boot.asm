BITS 16

;%define _BREAK

%ifdef _BREAK
%define BREAK xchg bx, bx
%else
%define BREAK
%endif
jmp start

VolumeLable: db 'TESTVOLUME        ' 	
Version: dw 0x0101					
Disktype: db 0x01 
ReservedSectors: db 0x01	
SectorsPerFAT: db 0x07		
RootDirSectors: db 0x0F
RootEntries: dw 0xC0
BytesPerSector: dw 0x200
Tracks: db 0x50					
SectorsPerTrack: db 0x12			
Heads: db 0x02			
Formatted: db 0

msgText: db 'Starting', 0
msgSwicth: db ' Loading ', 0
msgReading: db ' Reading ', 0
msgFileFound: db ' File Found ', 0

Stage2FileName: db 'boot2.bin                       ', 0

rootDir_location: db 0

%include "simplefs.inc"

print:
	push ax
	mov ah, 0x0E
	.print_loop:
		lodsb
		cmp al, 0
		je .print_done
		int 0x10
		jmp .print_loop
	.print_done:
		pop ax
		ret

start:

	BREAK
	mov ax, 0x7C0
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ds, ax

	xor ax, ax
	mov ss, ax
	mov sp, 0xFFFF
	BREAK

	mov [drive_number], dl

	mov si, msgText
	call print
	mov si, msgSwicth
	call print

	BREAK

	xor ax, ax
	mov al, byte [ReservedSectors]
	add al, byte [SectorsPerFAT]

	mov byte [rootDir_location], al

	call LBACHS

	BREAK

	xor bx, bx
	mov ax, 0x7E0
	mov es, ax
	xor ax, ax
	mov al, byte [RootDirSectors]
	call readSectors

	BREAK

	FindFile:
		mov cx, [RootEntries]
		xor di, di
		.findFileLoop:
		push cx
		mov cx, 0x9
		mov si, Stage2FileName
		push di
		rep cmpsb
		pop di
		je LoadFile
		pop cx
		add di, 0x28
		loop .findFileLoop
		mov si, msgFailedToFindFile
		jmp Error

	LoadFile:
		mov si, msgFileFound
		call print
		BREAK
		mov bx, dx
		add bx, 0x20
		xor ax, ax
		xor cx, cx
		mov ax, word [es:bx]
		add bx, 0x04
		mov cx, word [es:bx]
		push cx

		mov bx, word [BytesPerSector]
		sub bx, 0x02

		xor dx, dx
		div bx

		cmp dx, 0
		ja .oddSectors

		jmp .loadFileDone	

		.oddSectors:
			inc ax
			jmp .loadFileDone


		.loadFileDone:
			BREAK
			pop cx
			
			mov dx, cx
			xor ecx, ecx
			mov cl, al

			xor bx, bx
			BREAK
		LoadFileSectors:
		; dx which sector
		; cx how many sectors

			xor ax, ax
			mov ax, dx
			call LBACHS
			xor ax, ax
			mov al, 0x01

			call readSectors

			add bx, 0x1FE

			xor dx, dx
			mov dx, word [es:bx]

			loop LoadFileSectors


		xor ax, ax
		xor cx, cx
		mov ax, es
		mov cx, 0x10
		mul cx

		push VolumeLable

		BREAK

		jmp ax
	
	Error:

		call print

	hlt

times 510-($-$$) db 0
dw 0xAA55




