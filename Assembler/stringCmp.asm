%include 'rw32.inc'     ; loads library rw32.inc

%define LPCSTR        DWORD
%define LPVOID        DWORD ;long ptr to buffer

extern lstrcmp
extern lstrlen
extern GetStdHandle
extern WriteConsoleA
import lstrcmp Kernel32.dll
import lstrlen Kernel32.dll
import GetStdHandle Kernel32.dll
import WriteConsoleA Kernel32.dll

[segment .data use32]   ; defines the start of the data segment

 A: db "abcdefghijk",13,10,0
 lenA: equ $-A
 B: db "bcdefghijk",13,10,0
 lenB: equ $-B
 written: resb 4

; ******************************************************************
; ******************************************************************
[segment .code use32]   ; defines the start of the code segment


prologue


 push B
 push A
 call [lstrcmp]
 mov ecx,eax
 push dword -11
 call [GetStdHandle]
 mov edx,eax

 push LPVOID 0
 cmp ecx,0
 jg Bstring
 push written
 push dword lenA
 push A
 jmp endif
Bstring:
 push written
 push dword lenB
 push B
endif:
 push edx

 call [WriteConsoleA]

epilogue
