; ******************************************************************
; IAS - 7. lab - Wednesday
; ******************************************************************
;                                                  
; Assignment:
; =======
;
; 1) Calculate barrel volume.                                              (1B)
;
;    Find the diameter and the height of the barrel with the help of functions for reading floats
;    from rw.inc(ReadFloat/ReadDouble). Print out the result.
;
;          Pi * d^2  
;    V  = ---------- * v
;             4  
;    V - volume, d - diameter, v - height
;
;   
; 2) Find with the help of functions from rw.inc 5 numbers (ReadFloat)                 (1B)
;    and save them to to array_single.
;    Subsequently find the smallest number in this field and print it out on the screen.
;
; 3) Calculate the tangent of X: tg(X), where X is a value loaded by using         (1B)
;    ReadDouble in degrees.
;    Careful! Instructions FSIN a FCOS work with arguments in radians.
;
;   (angle X in radians) = (ange X in degrees) * Pi / 180°
;
;                sin(X)
;     tg(X)  = ----------
;                cos(X)
;
;    Output the result to the screen.
;
;**************************************************************
; Can be compiled as follows:
;   nasm -fobj helloworld.asm
;   alink -oPE -subsys console helloworld.obj
; or by using run.bat:
;   run.bat hello
;**************************************************************

%include 'rw32.inc'     ; loads library rw32.inc

[segment .data use32]   ; defines the start of the data segment

; ******************************************************************

array_double: RESQ 10    ; reserves memory for 10 doubles (64-bit float)
array_single: RESD 10    ; reserves memory for 10 singles (32-bit float)

r_double: dq 0.0

d: dq 2.0
v: dq 1.0
four: dq 4.0
halfpi: dq 180.0

x: resq 1
sinx: resq 1
cosx: resq 1

min: resq 1

dump: resq 1

; ******************************************************************
[segment .code use32]   ; defines the start of the code segment

; *******************************************************************


                        
prologue   		; initialization macro

; zde doplnte vas kod
 
;first part
 
; fld qword [v] 
; fld qword [d]
call ReadDouble
call ReadDouble
 fldpi
 fld qword [four]

 fdivp st1
 fmul st1
 fmulp st1
 fmulp st1

 call WriteDouble
 call WriteNewLine

 finit

;second part

 mov ebx, 0
loop:
 call ReadDouble
 fstp qword [array_double+ebx]
 add ebx,8
 cmp ebx,40
 jne loop

mov ebx, 8
fld qword [array_double]
fstp qword [min]
loop2:
 fld qword [array_double+ebx]
 fld qword [min]
 fcomp st1
 FSTSW AX
 SAHF
 fstp qword [dump]
 fstp qword [dump]
 ja newmin
 add ebx,8
 cmp ebx,40
 jne loop2
 je end
newmin:
 fld qword [array_double+ebx]
 fstp qword [min]
 add ebx,8
 cmp ebx,40
 jne loop2
end:
 fld qword [min]
 call WriteDouble
 call WriteNewLine

 finit

; third part

 call ReadDouble
 fldpi
 fld qword [halfpi]

 fdivp st1
 fmulp st1

 fstp qword [x]

 fld qword [x]
 fsin
 fstp qword [sinx]
 
 fld qword[x]
 fcos
 fstp qword [cosx]

 fld qword [sinx]
 fld qword [cosx]

 fdivp st1

 call WriteDouble
 call WriteNewLine

 
epilogue                ; macro -- end program

; ******************************************************************
