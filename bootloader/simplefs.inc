%ifndef _INC_SIMPLEFS_
%define _INC_SIMPLEFS_
absolute_sector: db 0
absolute_track: dw 0
absolute_head: db 0

drive_number db 0

msgReadError: db ' Failed to read sector(s)', 0
msgFailedToFindFile: db ' Failed to find file! ', 0

%if 1

readSectors:
	pusha
	xor bp, bp
	.reset:
		mov ah, 0x00
		mov dl, [drive_number]
		int 0x13
		jc .reset

	mov ah, 0x02
	mov cx, WORD [absolute_track]
	and cx, 255
	shl cx, 8
	mov dx, WORD [absolute_track]
	and dx, 768
	shr dx, 2
	or cx, dx
	or cl, [absolute_sector]
	mov dh, [absolute_head]
	mov dl, [drive_number]
	int 0x13
	jnc .read_done
	inc bp
	cmp bp, 0x03
	jne .reset

	.read_error:
		mov si, msgReadError
		call print

	.read_done:
		popa
		ret

LBACHS:
	push dx
	push bx
	xor bx, bx
	xor dx, dx
	mov bl, BYTE [SectorsPerTrack]
	div bx
	inc dl
	mov BYTE [absolute_sector], dl

	xor dx, dx
	xor bx, bx
	mov bl, BYTE [Heads]
	div bx
	mov BYTE [absolute_head], dl

	mov WORD [absolute_track], ax
	pop bx
	pop dx
	ret

%else

DISK_ADDRESS:
	db 10
	db 0
COUNT: dw 0
ADDR: dw 0
OFF:  dw 0
LBA: dw 0
LBAE: dw 0
	

readSectors:

	mov WORD [COUNT], cx
	mov WORD [LBA], ax
	mov WORD [ADDR], es
	mov WORD [OFF], bx

	mov si, DISK_ADDRESS
	mov ah, 0x42
	mov dl, [drive_number]
	int 0x13

	ret

%endif

%endif


