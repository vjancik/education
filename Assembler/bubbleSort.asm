%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segment

 array: dd 5,8,10,3,1,2
 len: equ $-array
 colon: db ","

; ******************************************************************
; ******************************************************************
[segment .code use32]   ; defines the start of the code segment

WriteArray:

 push ebp
 mov ebp,esp
 push ebx
 push ecx
 push esi
 pushfd
 sub esp,4

 mov esi, colon
 mov eax,[ebp+8]
 mov [ebp-4],eax
 mov ebx,[ebp+12]
 mov ecx,0
WALoop1:
 cmp ecx,ebx
 jz WAEnd
 mov eax,[ebp-4]
 add eax,ecx
 mov eax,[eax]
 call WriteUInt32
 call WriteString
 add ecx,4
 jmp WALoop1
WAEnd:
 call WriteNewLine
 add esp,4
 pop esi
 pop ecx
 pop ebx
 popfd
 mov esp,ebp
 pop ebp
 ret 4

Swap:

 push ebp
 mov ebp,esp
 pushfd
 push ebx
 push ecx

 mov eax,[ebp+8]
 mov ebx, [eax]
 mov ecx, [eax+4]
 mov [eax],ecx
 mov [eax+4],ebx

 pop ecx
 pop ebx
 popfd
 mov esp,ebp
 pop ebp
 ret 0

BubbleSort:
 push ebp
 mov ebp,esp
 pushfd
 push ebx
 push ecx
 push edx
 ;sub esp,8

 ;mov eax,[ebp+8]
 ;mov [ebp-4],eax
 ;mov eax,[ebp+12]
 ;mov [ebp-8],eax

 mov ecx,-4
BSLoop1:
 cmp ecx,[ebp+12]
 je BSEnd
 add ecx,4
 mov ebx,4
BSLoop2:
 ;sub ebx,4
 cmp ebx,[ebp+12]
 ;add ebx,4
 je BSLoop1
 add ebx,4

 mov eax,[ebp+8]
 add eax, ebx
 sub eax, 8
 mov eax, [eax]

; call WriteUInt32
; call WriteString

 mov edx,[ebp+8]
 add edx, ebx
 sub edx, 4
 mov edx, [edx]
 cmp eax,edx
 jg BSSwap
 jmp BSLoop2
BSSwap:
 mov eax,[ebp+8]
 add eax, ebx
 sub eax, 8
 push eax
 call Swap
 jmp BSLoop2
BSEnd:
 ;add esp,8
 pop edx
 pop ecx
 pop ebx
 popfd
 mov esp,ebp
 pop ebp
 ret 8


prologue
 mov esi,colon

 lea eax, [array]
 push eax
 ;call WriteUInt32
 ;call WriteNewLine
 call Swap

 mov eax, [array]
 ;call WriteUInt32
 ;call WriteNewLine

 mov eax, len
 push eax

 lea eax, [array]
 push eax
 call BubbleSort


 mov eax, len
 push eax
 Call WriteNewLine

 lea eax, [array]
 push eax
 call WriteArray

epilogue
