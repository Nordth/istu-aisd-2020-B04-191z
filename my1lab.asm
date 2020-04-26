.386
.model  flat,stdcall
option  casemap:none
 
    include \masm32\include\windows.inc
    include \masm32\include\masm32.inc
    include \masm32\include\kernel32.inc
    include \masm32\include\user32.inc
    include \masm32\macros\macros.asm
    includelib \masm32\lib\masm32.lib
    includelib \masm32\lib\kernel32.lib
    includelib \masm32\lib\user32.lib

.data
msg1        db  "Результат",0 ;Для вывода в окне
temp dw ?


a dd 11d
b dd 5d
rslt dd ?

.code
start:
mov eax, [a]
mov ebx, [b]
add eax, ebx
add eax, 30h
;invoke atodw, eax
mov [rslt], eax

invoke StdOut, addr rslt
invoke ExitProcess, 0
end start