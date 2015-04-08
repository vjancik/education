;**************************************************************
;
; Ukazkovy program -- IAS 2012/2013, FIT VUT Brno
;
;**************************************************************
; Preklad programu lze provest nasledovne:
;   nasm -fobj hello.asm
;   alink -oPE -subsys console hello.obj
; nebo pouze:
;   run.bat hello
;**************************************************************

%include 'rw32.inc'     ; natazeni knihovny rw32.inc

[segment .data use32]   ; definice zacatku datoveho segmentu
  
; testovaci retezec
sMessage db  "Hello World!",10,13,0
  
[segment .code use32]   ; definice zacatku kodoveho segementu
                        
prologue                ; makro -- inicializace programu
  
  ; vlastni program
  mov  esi,sMessage     
  call WriteString

epilogue                ; makro -- ukonceni programu