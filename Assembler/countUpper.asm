%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segment

; ******************************************************************
X:		db 10
retazec:	db "ABCDefgASh",0
; ******************************************************************
[segment .code use32]   ; defines the start of the code segment

prologue               ; makro -- inicializace programu
 mov ax, 0
 mov cx, [X]
 mov ch, 0
 mov bx, 2
smicka1:
 cmp bx, cx
 ja konecsmicka1
 add ax,bx
 add bx,2
 jmp smicka1
konecsmicka1:
 call WriteUInt16
 call WriteNewLine

;druha poduloha
 mov ebx, 0
 mov ax, 0
 mov ecx, -1
citanie:
 inc ecx
 mov bl, [retazec+ecx]
 cmp bx, 65
 jb checkend
 cmp bx, 90
 ja checkend
 inc ax
checkend:
 cmp bx, 0
 je koniec
 jmp citanie
koniec:
 call WriteUInt16
 call WriteNewLine

epilogue                ; makro -- ukonceni programu
