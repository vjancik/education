; ******************************************************************
; IAS - 2. cviceni
; ******************************************************************
; Zadání:
; 1) Look over the variables in the data segment
; 2) With the help of the AND instruction find out,
;    whether the third number in dArray is odd                                       (0,5 point)
; 3) Compute a+5*b-(c+1)*d/4 in wholenumbers, where a is the first number 
;    in the field d array, b second ...
;    For the multiplication/divison by a constant 2,4 or 8, use the shift operation  (1 point)
; 4) Find the minimum element inside dArray, implement as a cycle
;    (the number of elements inside the array is fixed)                              (1 point)
; 5) Beware of overflow and underflow (check everywhere, where necessary),
;    optionally make sure, it can't happen at all (and explain why)                  (0,5 point)
; Print the results to the screen
; ******************************************************************
 
%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segments
 
; ******************************************************************
sMsg:      db "Autor: XXXXXX XXXXXX - ",0 ; 
sMsg2:     db "Vysledok operacie a+5*b-(c+1)*d/4 je: ",0
sMsgSude:  db "Cislo je sude.",10,13,0
sMsgLiche: db "Cislo je liche.",10,13,0
sMsgMax:   db "Najmensie cislo je: ",0
sNL:       db 10,13,0
sLogin:    db "XXXXXXXX",10,13,0 
dArray:    db 3, 11, 11, 16, 5   
 
; ******************************************************************
 
[segment .code use32]   ; defines the start of the code segment
                       
prologue     
 
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
  mov bx,ax             ; (c+1)*d/4
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
 
epilogue 
 
; ******************************************************************
