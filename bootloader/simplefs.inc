%ifndef _INC_SIMPLEFS_
%define _INC_SIMPLEFS_
absolute_sector: db 0
absolute_track: db 0
absolute_head: db 0

drive_number db 0

msgReadError: db ' Failed to read sector(s)', 0
msgFailedToFindFile: db ' Failed to find file! ', 0

readSectors:
	pusha
	xor bp, bp
	.reset:
		mov ah, 0x00
		mov dl, [drive_number]
		int 0x13
		jc .reset

	mov ah, 0x02
	mov ch, [absolute_track]
	mov cl, [absolute_sector]
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
	mov bl, byte [SectorsPerTrack]
	div bx
	inc dl
	mov byte [absolute_sector], dl

	xor dx, dx
	xor bx, bx
	mov bl, byte [Heads]
	div bx
	mov byte [absolute_head], dl

	mov byte [absolute_track], al
	pop bx
	pop dx
	ret

	%endif


