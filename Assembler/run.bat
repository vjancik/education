@echo off

set fn=%1
echo Zpracovani souboru: %fn%.asm

if not exist %fn%.obj goto j1
del %fn%.obj

:j1
if not exist %fn%.exe goto j2
del %fn%.exe

:j2
if not exist %fn%.asm goto input_err

if not exist nasm.exe goto no_compiler

echo Preklad souboru "%fn%.asm" pomoci NASM
nasm -fobj %fn%.asm

if not exist %fn%.obj goto compile_err

if not exist alink.exe goto no_linker

echo Sestavoveni pomoci ALINK:
alink -oPE -subsys console %fn%.obj 

if not exist %fn%.exe goto link_err

echo -------------------------------------------------------------
echo Spusteni %fn%.exe:
echo -------------------------------------------------------------
%fn%.exe
echo -------------------------------------------------------------
goto exit

:input_err
	echo Soubor %fn%.asm neexistuje.
	goto exit
:no_compiler
	echo Nemohu nalezt program NASM.EXE.
	goto exit
:no_linker
	echo Nemohu nalezt program ALINK.EXE.
	goto exit
:compile_err
	echo Chyba pri prekladu programem NASM.EXE.
	goto exit
:link_err
	echo Chyba pri sestavovani programem ALINK.EXE.
:exit
    