; ******************************************************************
; IAS - 2. cviceni
; ******************************************************************
; Zadání:
; 1) Look over the variables in the data segment
; 2) With the help of the AND instruction find out,
;    whether the third number in dArray is odd                            (0,5 bodu)
; 3) Compute a+5*b-(c+1)*d/4 in wholenumbers, where a is the first number 
;    in the field d array, b second ...
;    Pro dìlení/násobení konstantou 2,4,nebo 8 použijte instrukce posunu (1 bod)
; 4) Spoèítejte minimum v dArray, implementujte jako cyklus
;    (poèet položek v poli je pevnì dán)                                 (1 bod)
; 5) Hlídejte pøeteèení a podteèení (všude, kde je to nutné),
;    pøípadnì zajistìte, aby k nìmu nemohlo dojít (a vysvìtlete proè) (0,5 bodu)
; Výsledky vytisknìte na obrazovku
; ******************************************************************
; Preklad programu lze provest nasledovne:
;   nasm -fobj cv2.asm
;   alink -oPE -subsys console cv2.obj
; nebo pomoci davky run.bat:
;   run.bat cv2
; ******************************************************************
 
%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segments
 
; ******************************************************************
sMsg:      db "Autor: Viktor Janèík - ",0 ; Výpis na obrazovku
sMsg2:     db "Vysledok operacie a+5*b-(c+1)*d/4 je: ",0
sMsgSude:  db "Cislo je sude.",10,13,0
sMsgLiche: db "Cislo je liche.",10,13,0
sMsgMax:   db "Najmensie cislo je: ",0
sNL:       db 10,13,0
sLogin:    db "xjanci09",10,13,0  ; Zde do uvozovek vepište váš login
dArray:    db 3, 11, 11, 16, 5    ; Pole
 
; ******************************************************************
 
[segment .code use32]   ; defines the start of the code segment
                       
prologue                ; makro -- inicializace programu
 
  mov esi, sMsg
  call WriteString
  mov esi, sLogin
  call WriteString
  mov ax,[dArray+2]
  mov ah, 0
  inc ax
  mov bx,[dArray+3]
  mov bh, 0
  imul bx
  mov cx,4
  idiv cx
  mov bx,ax             ; tu je (c+1)*d/4
  mov ax,[dArray+1]
  mov ah,0
  mov cx,5
  imul ax,cx
  mov cx,[dArray]
  mov ch,0
  add ax,cx
  sub ax,bx
  mov esi,sMsg2
  call WriteString
  call WriteUInt16
  mov esi,sNL
  call WriteString
  mov ax,[dArray+2]
  mov ah,0
  AND ax,1
  jz sude
  mov esi,sMsgLiche
  jmp continue
sude:
  mov esi,sMsgSude
continue:
  call WriteString
  mov ecx,0
  mov edx,4
  mov ax,200
  mov bx,0
  jmp cyklus
rewmin:
  mov ax,bx
  inc ecx
  cmp edx,ecx
  jg cyklus
  jmp continue2
cyklus:
  mov bx,[dArray+ecx]
  mov bh,0
  cmp bx,ax
  js  rewmin
  inc ecx
  cmp edx,ecx
  jg cyklus
continue2:
  mov esi,sMsgMax  
  call WriteString
  call WriteUInt16
  mov esi,sNL
  call WriteString
 
; PODULOHA 5 - K preteceniu nemoze dojst, pretoze pracujeme s velmi malymi cislami v 16 bitovych
; registroch ktore maju rozsah od <-32767;32768> v doplnkovom kode. Pre kontrolu by sme kontrolovali
; CF a OF registre, pricom CF XOR OF znaci platnu aritmeticku operaciu
epilogue                ; makro -- ukonceni programu
 
; ******************************************************************
