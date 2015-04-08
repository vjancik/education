%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segment
 
; ******************************************************************	
; ****************************************************************** 
[segment .code use32]   ; defines the start of the code segment

FuncStack:
 push ebp
 mov ebp,esp
 pushfd
 sub esp,8
 
 mov eax,[ebp+12]
 shl eax,1
 mov [ebp-8], eax

 mov eax,[ebp+8]
 shl eax,2
 mov [ebp-12], eax

 add eax,[ebp-8]
 
 add esp,8
 popfd
 mov esp,ebp
 pop ebp
 ret 8

                       
prologue
 mov ebx, 98
 push dword 4
 push dword 2
 call FuncStack
 call WriteUInt32
 call WriteNewLine
 mov eax,ebx
 call WriteUInt32
 call WriteNewLine

epilogue               
