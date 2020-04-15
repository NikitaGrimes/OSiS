model small
.stack 100h         
.data 		

n db 10, 13, "$"
old_handler_off DW ?
old_handler_seg DW ?

.code

new_handler proc far
	mov ah, 00h
	int 16h

	cmp al, 32
	jz space

	mov ah, 02h
	mov dl, al
	int 21h

	space:
	iret
new_handler endp


start:
MOV AX, @data
MOV DS, AX
mov ah, 35h
mov al, 01h;
int 21h
mov cs:old_handler_off, bx
mov cs:old_handler_seg, es

mov ah, 25h
mov al, 01h
mov dx, seg new_handler
mov ds, dx
lea dx, new_handler
int 21h

next1:
	mov ah, 01h
	int 21h
jmp next1

MOV AH, 4Ch
INT 21h
end start