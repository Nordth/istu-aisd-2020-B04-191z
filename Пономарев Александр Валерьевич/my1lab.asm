.486 ;процессор для выполнения
.model flat, stdcall 
.data
m   db  "a1s3108g", 0 ;;Даннные как строка
c1  dw  0 ;;Слово
 
.code ;;парвила
start proc near ;;обьявление процедуры
    lea esi, m ;;отдаем в esi данные
    xor bx, bx ;;смещение в массиве на 1
;;цикл 1   
m1: mov al, byte ptr [esi]
    ; сравнение 
    cmp al, "1"
    ; если не равно переходим на М3
    jne m3
    ; увеличение на 1 или смешение на 1
    inc bx
;;цикл 2   
m3: mov al, byte ptr [esi] ;указываем на адрес памяти по элементу
; сравниваем
    cmp al, "3"
    ; если не равно то переходим на М2
    jne m2
    ; смещение на 1
    inc bx
; цикл 3
m2: inc esi ;если равно 0
    cmp al,0
    jne m1
    mov c1,bx 
    lea esi,m
    mov edi,esi
; цикл 4
m6: lodsb
    test al,al
    jz ex
    cmp al,'0'
    jc m4
    cmp al,'9'
    ja m4
    jmp m6
; цилк 5
m4: stosb
    jmp m6
    ; выполнить
ex: mov esi,edi
; цикл
m5: lodsb
    test al,al
    jz ex1
    mov al,0
    stosb
    jmp m5
; выполнить
ex1:ret
; код закончен
start endp
; программа завершина
end start