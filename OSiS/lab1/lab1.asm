model small
.stack 100h         
.data 			

message1 db 'Enter input file name', 13, 10, '$'
message2 db 'Enter output file name', 13, 10, '$'
message3 db 'Error 404 not found', 13, 10, '$'
message4 db 'Warning! This file name is exist', 13, 10, '$'
file_input db 20 dup (0)
file_output db 20 dup (0)
buffer db 257 dup ('$')
read_size dw 0
start_r_w dw 0

.code

start:
	MOV AX, @data
	MOV DS, AX

	LEA SI, file_input
	LEA DX, message1
	MOV AH, 09h
	INT 21h

next_file_in:
	MOV AH, 01h			;ввод имени файла, где лежит текст
	INT 21h
	MOV AH, 0
	CMP AX, 13
	JZ endenter_file_in
	MOV [SI], AL
	INC SI
	JMP next_file_in

endenter_file_in:

	LEA SI, file_output
	LEA DX, message2
	MOV AH, 09h
	INT 21h

next_file_out:			;ввод имени файла, где будет лежать закодированное
	MOV AH, 01h
	INT 21h
	MOV AH, 0
	CMP AX, 13
	JZ endenter_file_out
	MOV [SI], AL
	INC SI
	JMP next_file_out

endenter_file_out:

	mov ah, 3Dh			;открытие файла
	mov al, 0
	lea dx, file_input
	xor cx, cx
	int 21h   
	jnc No_Error_file_name_input
	LEA DX, message3
	MOV AH, 09h
	INT 21h
	jmp the_end_of_file
No_Error_file_name_input:

	mov ah, 3Eh			;закрытие файла
	int 21h

	mov ah, 3Dh
	mov al, 0
	lea dx, file_output
	xor cx, cx
	int 21h   
	jc No_File_output_warning
	LEA DX, message4
	MOV AH, 09h
	INT 21h

	mov ah, 3Eh
	int 21h

No_File_output_warning:

	mov ah, 3Ch
	mov al, 1
	lea dx, file_output
	xor cx, cx
	int 21h

	mov ah, 3Eh	
	int 21h

start_of_read:


	lea si, buffer	
	mov ax, 257
next:
	mov [si], '$'		
	inc si
	dec ax
	cmp ax, 0
	jnz next			

	mov ah, 3Dh		
	mov al, 0			
	lea dx, file_input
	xor cx, cx
	int 21h

	mov bx, ax

	mov ax, 4201h	 
	mov cx, 0
	mov dx, start_r_w
	int 21h
		
	mov ah, 3Fh		
	lea dx, buffer
	mov cx, 256
	int 21h
	mov read_size, ax

	mov ah, 3Eh	
	int 21h

	lea si, buffer	
	mov ax, 257	
next_shifr:
	xor [si], 'D'	
	inc si
	dec ax
	cmp ax, 0
	jz end_shifr
	xor [si], 'o'	
	inc si
	dec ax
	cmp ax, 0
	jz end_shifr
	xor [si], 'v'	
	inc si
	dec ax
	cmp ax, 0
	jz end_shifr
	xor [si], 'n'	
	inc si
	dec ax
	cmp ax, 0
	jz end_shifr
	xor [si], 'a'	
	inc si
	dec ax
	cmp ax, 0
	jz end_shifr
	xor [si], 'r'	
	inc si
	dec ax
	cmp ax, 0
	jnz next_shifr

end_shifr:

	mov ax, read_size	
	cmp ax, 0
	jz the_end_of_file

	mov ah, 3Dh		
	mov al, 1		
	lea dx, file_output
	xor cx, cx
	int 21h

	mov ax, 4201h	
	mov cx, 0
	mov dx, start_r_w
	int 21h

	mov cx, read_size
	mov ah, 40h
	lea dx, buffer
	int 21h 

	add cx, start_r_w
	mov start_r_w, cx

	mov ah, 3Eh		
	int 21h

	jmp start_of_read

the_end_of_file:
	
	MOV AH, 4Ch	
	INT 21h
end start