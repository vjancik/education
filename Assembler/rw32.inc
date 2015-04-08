;
; Podpurna knihovna funkci rw32.inc pro predmet IAS
; Verze: 2012.12.09
; Autor: Filip Orsag (orsag@fit.vutbr.cz)
;
; Knihovnu vkladejte na zacatek vaseho programu. Dostupne funkce jsou nasledujici:
;
; Cteni z klavesnice:
;	ReadChar
;		vstup:	nic
;		vystup:	AL = hodnota znaku
;		chovani: ceka na stisk klavesy, neceka na stisk ENTER, okamzite se vraci zpet s prislusnou navratovou hodnotou

;	ReadString
;		vstup:	EBX = maximalni pocet znaku, ktere mohou byt nacteny
;				EDI = adresa, kam se retezec nacte (musi byt rezervovano alespon EBX+1 bytu)
;		vystup:	retezec znaku ulozeny na adrese EDI
;		chovani: nacita znaky z klavesnice, dokud neni dosazeno poctu znaku odpovidajicimu hodnote v EBX
;				(dalsi znaky neni mozne zadat, znaky lze pouze smazat klavesou BACKSPACE), konec zadavani = stisk ENTER

;  ReadInt8
;		vstup:	nic
;		vystup:	AL = cislo z intervalu <-128, 127>
;		chovani: cte cislo z klvesnice, umozni zadat pouze cislice a znak '-' na zacatku cisla, umozni mazat klavesou BACKSPACE,
;				pokud neni zadana hodnota a je stisknut ENTER, pak je vracena hodnota 0, pri zadani '-' je vracena hodnota 0,
;				pri prekroceni kterekoliv povolene meze je vraceno bud maximum nebo minimum daneho rozsahu

;  ReadInt16
;		vstup:	nic
;		vystup:	AX = cislo z intervalu <-32768, 32767>
;		chovani: viz ReadInt8

;  ReadInt32
;		vstup:	nic
;		vystup:	EAX = cislo z intervalu <-2^31, 2^31 - 1>
;		chovani: viz ReadInt8

;  ReadUInt8
;		vstup:	nic
;		vystup:	AL = cislo z intervalu <0, 255>
;		chovani: viz ReadInt8 s tim rozdilem, ze neumozni zadat znak '-'

;  ReadUInt16
;		vstup:	nic
;		vystup:	AX = cislo z intervalu <0, 65535>
;		chovani: viz ReadInt8 s tim rozdilem, ze neumozni zadat znak '-'

;  ReadUInt32
;		vstup:	nic
;		vystup:	EAX = cislo z intervalu <0, 2^32 - 1>
;		chovani: viz ReadInt8 s tim rozdilem, ze neumozni zadat znak '-'

;  ReadFloat
;		vstup:	nic
;		vystup:	EAX = 32bitove realne cislo v plovouci radove carce (v jazyce C typ float)
;		chovani: viz ReadInt8, navic je dovoleno zadat jedenkrat znak '.' - desetinna carka

;  ReadDouble
;		vstup:	nic
;		vystup:	ST0 = 64bitove realne cislo v plovouci radove carce (v jazyce C typ double)
;		chovani: viz ReadInt8, navic je dovoleno zadat jedenkrat znak '.' - desetinna carka

;
; Vypis na obrazovku:
; 	WriteChar
;		vstup:	znak v AL
;		vystup:	vypise znak na obrazovku

; WriteNewLine
;		vstup:	nic
;		vystup:	vypise konec radku (MS-DOS varianta end of line = hodnoty 13, 10)

; WriteString
;		vstup:	ESI = ukazatel na retezec zakonceny hodnotou 0, ktery bude vypsan
;		vystup:	vypise retezec na obrazovku

; WriteBin8
;		vstup:	AL = cislo
;		vystup:	vypise cislo z AL na obrazovku v binarni podobe

; WriteBin16
;		vstup:	AX = cislo
;		vystup:	vypise cislo z AX na obrazovku v binarni podobe

; WriteBin32
;		vstup:	EAX = cislo
;		vystup:	vypise cislo z EAX na obrazovku v binarni podobe

; WriteInt8
;		vstup:	AL = cislo
;		vystup:	vypise cislo z AL na obrazovku v dekadicke forme se znamenkem

; WriteInt16
;		vstup:	AX = cislo
;		vystup:	vypise cislo z AX na obrazovku v dekadicke forme se znamenkem

; WriteInt32
;		vstup:	EAX = cislo
;		vystup:	vypise cislo z EAX na obrazovku v dekadicke forme se znamenkem

; WriteUInt8
;		vstup:	AL = cislo
;		vystup:	vypise cislo z AL na obrazovku v dekadicke forme bez znamenka

; WriteUInt16
;		vstup:	AX = cislo
;		vystup:	vypise cislo z AX na obrazovku v dekadicke forme bez znamenka

; WriteUInt32
;		vstup:	EAX = cislo
;		vystup:	vypise cislo z EAX na obrazovku v dekadicke forme bez znamenka

; WriteFlags
;		vstup:	nic (aktualni stav priznakoveho registru)
;		vystup:	vypise obsah registru priznaku na

; WriteFloat
;		vstup:	EAX = cislo (realne cislo s jednoduchou presnosti - float)
;		vystup:	vypise cislo z EAX na obrazovku ve forme realneho cisla

; WriteDouble
;		vstup:	ST(0) = cislo (realne cislo v koprocesoru, vypisuje se cislo s dvojitou presnosti - double)
;		vystup:	vypise cislo z ST(0) na obrazovku ve forme realneho cisla
;

bits 32
cpu X64

; Funkce standardni knihovny jazyka C (C Run-Time libraray) - msvcrt.dll:

extern printf
import printf msvcrt
extern wprintf
import wprintf msvcrt
extern _putch
import _putch msvcrt
extern _getch
import _getch msvcrt
extern strtoul
import strtoul msvcrt
extern strtol
import strtol msvcrt
extern strtod
import strtod msvcrt
extern _errno
import _errno msvcrt

extern ExitProcess
import ExitProcess kernel32.dll 
extern GetModuleHandleA
import GetModuleHandleA kernel32.dll 

; Makra

%macro prologue 0
..start:
	call [_errno]
	mov [errno],eax
	
	push dword 0
	call [GetModuleHandleA]
	mov [hInstance],eax 
%endmacro

%macro epilogue 0
	xor eax,eax
	push dword 0
	call [ExitProcess]
	ret
%endmacro

%macro string 2+
	%1: DB %2
	endof.%1: DB 0
	lenof.%1 EQU endof.%1 - %1
	sizeof.%1 EQU endof.%1 - %1
%endmacro

; Konstanty

%define EOL 13,10
%define MAX_UBYTE 0xFF
%define MAX_UWORD 0xFFFF
%define MAX_UDWORD 0xFFFFFFFF
%define MAX_SBYTE 0x0000007F
%define MAX_SWORD 0x00007FFF
%define MAX_SDWORD 0x7FFFFFFF
%define MIN_SBYTE 0xFFFFFF80
%define MIN_SWORD 0xFFFF8000
%define MIN_SDWORD 0x80000000
%define MAX_STRING_LENGTH 1024

%define READ_SIGNED 0x00000001
%define READ_FLOATING 0x00000002

; Klavesy ENTER a BACKSPACE

%define KB_ENTER 0x0D
%define KB_BACKSPACE 0x08

[section .rw32_data use32 class=DATA align=4]

string msg_EOL, EOL
string msg_EnterChar, 'Zadejte znak: '
string msg_EnterUInt, 'Zadejte cele cislo bez znamenka z intervalu <%u,%u>: '
string msg_EnterSInt, 'Zadejte cele cislo se znamenkem z intervalu <%d,%d>: '
string msg_EnterFloat, 'Zadejte realne cislo (napr. 1.5): '
string msg_EnterString, 'Zadejte text (maximum je %d znaku): '
string msg_NumberTooBig, 'Cislo je prilis velke, vracim maximalni moznou hodnotu.', EOL
string msg_NumberTooLow, 'Cislo je prilis male, vracim minimalni moznou hodnotu.', EOL

errno				dd 0
format_char			db "%c",0
format_string		db "%s",0
format_int			db "%d",0
format_uint			db "%u",0
format_float		db "%f",0
msg_Flags			db 'Flags: xxxx|OF|DF|IF|TF|SF|ZF|xx|AF|xx|PF|xx|CF|',13,10,'       xxxx| '
msg_FlagValues		db              'x| x| x| x| x| x| x| x| x| x| x| x|',EOL
	endof_msg_Flags db 0
	lenof_msg_Flags EQU endof_msg_Flags - msg_Flags
ioBuffer			times MAX_STRING_LENGTH db '!'
					db 0
hInstance			dd 0

[section .rw32_code use32 class=CODE]

;----------------
; Funkce getch
; Precte znak z klavesnice, vyuziva funkci _getch, zachovava obsah registru, krome EAX
;
getch:

	push ecx
	push edx

	call [_getch]

	pop edx
	pop ecx
	ret

;----------------
; Funkce ReadChar
; Precte znak z klavesnice, zachovava obsah registru, znak vraci v AL
;
ReadChar:

	push esi
	
	mov esi,msg_EnterChar
	call WriteString
	call getch
	call putch
	call WriteNewLine
	
	pop esi
	ret

;----------------
; Funkce ReadString
; Precte retezec znaku z klavesnice, obsah retezce je ukladan na adresu danou registrem EDI a je cteno maximalne EBX znaku
; Vraci pocet prectenych znaku v EAX
;
ReadString:
	
	push esi
	push edi
	push ebx
	push ecx
	
	push edx
	
		push ebx
		push msg_EnterString
			call [printf]
		add esp,8

	pop edx

	xor ecx,ecx
	cmp ebx,0
	je .done
	
.again:
	call getch

	cmp al,KB_ENTER
	je .done
	
	cmp al,KB_BACKSPACE
	je .backspace

	cmp ecx,ebx
	je .again
	
	call putch

	mov [edi + ecx],al
	inc ecx
	jmp .again

.backspace:
	cmp ecx,0
	je .again
	
	call putch
	mov al,' '
	call putch
	mov al,KB_BACKSPACE
	call putch
	
	dec ecx
	jmp .again
	
.done:
	mov [edi + ecx], byte 0
	call WriteNewLine
	mov eax,ecx
	
	pop ecx
	pop ebx
	pop edi
	pop esi
	ret

;----------------
; Funkce ReadNumberF
; Cte znamenkove cislo v plovouci radove carce z klavesnice, vysledek vraci v st(0)
;
ReadNumberF:
	push eax
	push ebx

	mov ebx,READ_SIGNED + READ_FLOATING
	call ReadNumber

	pop ebx
	pop eax
	ret

	
;----------------
; Funkce ReadNumberS
; Cte znamenkove cele cislo z klavesnice, vysledek vraci v EAX
;
ReadNumberS:
	push ebx
	
	mov ebx,READ_SIGNED
	call ReadNumber
	
	pop ebx
	ret

;----------------
; Funkce ReadNumberU
; Cte bezznamenkove cele cislo z klavesnice, vysledek vraci v EAX
;
ReadNumberU:
	push ebx
	
	mov ebx,0
	call ReadNumber
	
	pop ebx
	ret

ReadNumber:
	push ebx
	push ecx
	push edx
	
	xor ecx,ecx
	xor edx,edx

.again:
	call getch

	cmp al,KB_ENTER
	je .done

	cmp al,KB_BACKSPACE
	je .backspace

	test ebx,READ_SIGNED
	jz .unsigned

	cmp al,'-'
	jne .unsigned

	cmp ecx,0
	jne .again
	jmp .print

.unsigned:

	test ebx,READ_FLOATING
	jz .not_floating

	cmp edx,0
	ja .not_floating

	cmp al,'.'
	jne .not_floating
	inc edx
	jmp .print

.not_floating:

	cmp al,'0'
	jb .again
	
	cmp al,'9'
	ja .again

.print:
	call putch

	mov [ioBuffer + ecx],al
	inc ecx
	cmp ecx, MAX_STRING_LENGTH
	je .done
	jmp .again

.backspace:
	cmp ecx,0
	je .again
	call putch
	mov al,' '
	call putch
	mov al,KB_BACKSPACE
	call putch
	dec ecx
	mov al,[ioBuffer + ecx]
	cmp al,'.'
	jne .again
	xor edx,edx
	jmp .again

.done:
	cmp ecx,0
	jnz .not_empty
	mov [ioBuffer + ecx], byte '0'
	inc ecx

.not_empty:
	mov eax,0
	mov [ioBuffer + ecx], byte 0

	call WriteNewLine

	test ebx,READ_FLOATING
	jz .integer

	push dword 0
	push ioBuffer
	call [strtod]
	add esp,8
	jmp .return

.integer:
	push dword 10
	push dword 0
	push ioBuffer

	test ebx,READ_SIGNED
	jz .strtoul

	call [strtol]
	add esp,12
	jmp .return

.strtoul:
	call [strtoul]
	add esp,12

.return:

	pop edx
	pop ecx
	pop ebx
	ret

;----------------
; Funkce ReadIntX (8,16,32) {ReadInt8,ReadInt16,ReadInt32}
; Precte 8-, 16-, 32-bitovou celociselnou hodnotu se znamenkem z klavesnice
;
ReadInt8:
	push esi
	push edi
	push ebx
	mov ebx,MAX_SBYTE
	mov edi,MIN_SBYTE
	jmp ReadInt
	
ReadInt16:
	push esi
	push edi
	push ebx
	mov ebx,MAX_SWORD
	mov edi,MIN_SWORD
	jmp ReadInt

ReadInt32:
	push esi
	push edi
	push ebx
	mov ebx,MAX_SDWORD
	mov edi,MIN_SDWORD

ReadInt:
	push ecx
	push edx

	push ebx
	push edi
	push msg_EnterSInt
	call [printf]
	add esp,12

	pop edx
	pop ecx
	
	call ReadNumberS
	
	cmp eax,ebx
	jng .test_min
	
	mov esi,msg_NumberTooBig
	call WriteString
	mov eax,ebx
	jmp .return
	
.test_min:
	cmp eax,edi
	jnl .return

	mov esi,msg_NumberTooLow
	call WriteString
	mov eax,edi
	
.return:
	pop ebx
	pop edi
	pop esi
	ret

;----------------
; Funkce ReadUIntX (8,16,32) {ReadUInt8,ReadUInt16,ReadUInt32}
; Precte 8-, 16-, 32-bitovou celociselnou hodnotu bez znamenka z klavesnice
;
ReadUInt8:
	push esi
	push edi
	push ebx
	mov ebx,MAX_UBYTE
	mov edi,0
	jmp ReadUInt
	
ReadUInt16:
	push esi
	push edi
	push ebx
	mov ebx,MAX_UWORD
	mov edi,0
	jmp ReadUInt

ReadUInt32:
	push esi
	push edi
	push ebx
	mov ebx,MAX_UDWORD
	mov edi,0

ReadUInt:
	push ecx
	push edx

	push ebx
	push edi
	push msg_EnterUInt
	call [printf]
	add esp,12

	pop edx
	pop ecx
	
	call ReadNumberU
	
	cmp eax,ebx
	jna .test_min
	
	mov esi,msg_NumberTooBig
	call WriteString
	mov eax,ebx
	jmp .return
	
.test_min:
	cmp eax,edi
	jnb .return

	mov esi,msg_NumberTooLow
	call WriteString
	mov eax,edi
	
.return:
	pop ebx
	pop edi
	pop esi
	ret

;----------------
; Funkce ReadFloat
; Precte 32bitove realne cislo z klavesnice
;
ReadFloat:
	push esi

	mov esi,msg_EnterFloat
	call WriteString
	call ReadNumberF

	sub esp,4
	fstp dword [esp]
	pop eax

.return:

	pop esi
	ret

;----------------
; Funkce ReadDouble
; Precte 64bitove realne cislo z klavesnice
;
ReadDouble:
	push esi

	mov esi,msg_EnterFloat
	call WriteString
	call ReadNumberF

.return:

	pop esi
	ret

;----------------
; putch
; Vypise znak ulozeny v registru AL, pouziva funkci _putch a zachova obsah registru
;
;----------------
; WriteChar
; Vypise znak ulozeny v registru AL
;
WriteChar:
putch:

	push eax
	push ecx
	push edx
	
	movzx ecx,al
	push ecx
	push format_char
	call [printf]
	add esp,8
	
	pop edx
	pop ecx
	pop eax

	ret

putch_con:
; AL = Character

	push eax
	push ecx
	push edx
	
	push eax
	call [_putch]
	add esp,4
	
	pop edx
	pop ecx
	pop eax

	ret
    
;----------------
; WriteNewLine
; Vypise "End Of Line", tedy ASCII hodnoty CR, LF (13, 10)
;
WriteNewLine:

	push eax
	push ecx
	push edx
	
    push msg_EOL    
    call [printf]
	add esp,4

	pop edx
	pop ecx
	pop eax
	
	ret

;----------------
; Funkce WriteBinX (8, 16, 32) {WriteBin8, WriteBin16, WriteBin32}
; Vypise 8,16,32 bitu z registru AL, AX, EAX
;
WriteBin8:
    pushfd
    push ecx
    push eax

    mov ecx,8
    rcl eax,24
    jmp WriteBin

WriteBin16:
	pushfd
    push ecx
    push eax

    mov ecx,16
    rcl eax,16
    jmp WriteBin

WriteBin32:
	pushfd
    push ecx
    push eax

    mov ecx,32
	
WriteBin:

    push ebx
    push edi
	push esi

    cld
    mov edi,ioBuffer
    mov ebx,eax
    
.next_bit:
    rcl ebx,1
    setc al
    add al,'0'
    stosb
    loop .next_bit

	mov [edi], byte 0

	mov esi,ioBuffer
	call WriteString

	pop esi
    pop edi
    pop ebx
    pop eax
    pop ecx
    popfd
    ret

;----------------
; WriteString
; Vypise retezce ukonceneho 0 (ASCIIZ), jehoz adresa je ulozena v registru ESI
;
WriteString:

	push eax
	push ecx
	push edx

	push esi
	push format_string
	call [printf]
	add esp,8
	
	pop edx
	pop ecx
	pop eax
	
    ret
    
;----------------
; WriteFlags
; Vypise stav registru priznaku
;
WriteFlags:
    push eax
    push ebx
    push ecx
	push esi
	push edi

    pushfd
    pop ebx
    shl ebx,20

    mov ecx,12
    mov edi,msg_FlagValues
    
.cycle:
    rcl ebx,1
    setc al
    add al,'0'
    mov [edi],al
    add edi,3
    loop .cycle

	mov esi,msg_Flags
	call WriteString

	pop edi
	pop esi
    pop ecx
  	pop ebx
  	pop eax
    ret
    
;----------------
; Funkce WriteIntX (8,16,32) {WriteInt8,WriteInt16,WriteInt32}
; Vypise 8-, 16-, 32-bitovou celociselnou hodnotu se znamenkem z registru AL, AX, EAX
;
;----------------
; Funkce WriteUIntX (8,16,32) {WriteUInt8,WriteUInt16,WriteUInt32}
; Vypise 8-, 16-, 32-bitovou celociselnou hodnotu bez znamenka z registru AL, AX, EAX
;

WriteInt8:
	push eax
	movsx eax,al
	jmp WriteInt32_noeax

WriteUInt8:
	push eax
	movzx eax,al
	jmp WriteUInt32_noeax

WriteInt16:
	push eax
	movsx eax,ax
	jmp WriteInt32_noeax 

WriteUInt16:
	push eax
	movzx eax,ax
	jmp WriteUInt32_noeax

WriteInt32:
	push eax
WriteInt32_noeax:
	push ecx
	push edx

	push eax
	push dword format_int
	call [printf]
	add esp,8

	pop edx
	pop ecx
	pop eax
    ret

WriteUInt32:
	push eax
WriteUInt32_noeax:
	push ecx
	push edx

	push eax
	push dword format_uint
	call [printf]
	add esp,8
	
	pop edx
	pop ecx
	pop eax
    ret

;----------------
; Funkce WriteFloat
; Vypise 32-bitove realne cislo z registru EAX
;
WriteFloat:
	push ecx
	push edx
	
	push eax
	fld dword [esp]
	sub esp,4
	fstp qword [esp]
	push dword format_float
	call [printf]
	add esp,8
	pop eax
	
	pop edx
	pop ecx
	ret

;----------------
; Funkce WriteDouble
; Vypise 64-bitove realne cislo z registru koprocesoru st(0)
;
WriteDouble:
	push ecx
	push edx
	push eax

	sub esp,8
	fst qword [esp]
	push dword format_float
	call [printf]
	add esp,12

	pop eax
	pop edx
	pop ecx
	ret	