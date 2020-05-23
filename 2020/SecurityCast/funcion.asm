; Arquivo pertencente ao treinamento de Desenvolvimento de Exploit
; Autor: Hélvio Junior (M4v3r1ck)
;
; Proibida a reprodução ou publicação deste material sem prévia autorização expressa
;
;Filename: function.asm
;
;Procedimento de montagem
; nasm function.asm -o function
; shellcodetester function.asm --break-point
; gdb -q ./function-shellcodetester

[BITS 32]

SECTION .text
    global _start

_start:
                        ; Prólogo da função
    push    ebp         ; salva o frame antigo
    mov     ebp, esp    ; inicializa um novo frame

                        ; Coloca os parametros na pilha em ordem reversa
    push    3
    push    2
    push    1

                        ; Alguns compiladores adicionam o espaço na pilha 
                        ; posteriormente copiam os dados diretamente
    ; sub esp, 12
    ; mov [ebp-4], 3   : ou mov [esp+8], 3
    ; mov [ebp-8], 2   : ou mov [esp+4], 2
    ; mov [ebp-12], 1  : ou mov [esp], 1

    call    func1       ; chama a função func1
    add     esp, 12     ; remove os argumentos da pilha
    
    pop ebp             ; restaura o frame antigo

    ret                 ; return


func1:
    push    ebp         ; salva o frame antigo
    mov     ebp, esp    ; inicializa um novo frame

    mov eax, 0x00000000
    ;xor eax,eax
    add eax, [esp + 8]
    add eax, [esp + 12]
    add eax, [esp + 16]

    pop ebp             ; restaura o frame antigo

    ret                 ; return


