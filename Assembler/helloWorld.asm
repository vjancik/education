%include 'rw32.inc'     ; loads the library rw32.inc

[segment .data use32]   ; defines the start of the data segment
  
sMessage db  "Hello World!",10,13,0
  
[segment .code use32]   ; defines the start of the code segment
                        
prologue                ; program initialization macro
  
  ; vlastni program
  mov  esi,sMessage     
  call WriteString

epilogue                ; program end macro
