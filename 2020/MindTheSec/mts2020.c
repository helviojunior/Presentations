// Arquivo criado e disponibilizado para palestra MTS SP 2020
// Autor: Hélvio Junior (M4v3r1ck)
//
// Filename: mts2020.c
//
// Compilação
//
// Compilar com MX habilitado
// gcc -O0 -Wl,-z,norelro,-z,now -no-pie -m32 -Wl,--section-start=.text=0x72740000 -o mts2020 mts2020.c
//
// Compilar sem MX habilitado
// gcc -O0 -Wl,-z,norelro,-z,now -no-pie -fno-stack-protector -z execstack -m32 -Wl,--section-start=.text=0x72740000 -o mts2020 mts2020.c
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define T1 "/bin/sh"

void Function1(char *Input);
void Exp1Func(char *Input);

int main( int argc, char *argv[] ) {

    int RecvLen = 0;
    char *RecvBuf;
    int i;

    const char Usage[94] = "Usage: %s cmd value\n\nAvailable comands:\n    MTS2020 [value]\n\n\n";
    if ( argc < 3) {
        printf(Usage, argv[0]);
        return 1;
    }
    RecvLen = strlen(argv[2]);
    RecvBuf = argv[2];

    printf("Are you able to spawn a shell?\n%s = %p\n", T1, T1);
    if (strncmp(argv[1], "MTS2020", 7) == 0){
        char *XP1Buf = malloc(1000);
        memset(XP1Buf, 0, 1000);
        strncpy(XP1Buf, argv[2], 1000);
        Exp1Func(XP1Buf);
        printf("MTS2020 COMPLETE\n");
    } else {
        printf("UNKNOWN COMMAND\n");
        return 2;
    }

}

// Funcoes vulneraveis
void Function1(char *Input) {
    char Buffer2S[140];
    strcpy(Buffer2S, Input);
}

// Nas funcoes abaixo o fato de ser criado um buffer vazio faz com que no ESP tenha pelo menos este espaco do buffer criado
void Exp1Func(char *Input) {
    char TmpBuffer1S[10000]; 
    Function1(Input);
}

void tmp1() {
    __asm__("jmp *%esp\n\t"
        "jmp *%eax\n\t"
        "pop %eax\n\t"
        "pop %eax\n\t"
        "ret");
}

void tmp2() {
    __asm__("jmp *%esp\n\t"
        "jmp *%ecx\n\t"
        "pop %ebx\n\t"
        "pop %ebx\n\t"
        "ret");
}

void tmp3() {
    __asm__("jmp *%esp\n\t"
        "jmp *%ebx\n\t"
        "pop %ebp\n\t"
        "pop %ebp\n\t"
        "ret");
}

void tmp4() {
    __asm__("jmp *%esp\n\t"
        "jmp *%edi\n\t"
        "pop %ebx\n\t"
        "pop %ebx\n\t"
        "ret");
}

void tmp5() {
    __asm__("call *%esp\n\t"
        "jmp *%edx\n\t"
        "pop %ecx\n\t"
        "pop %edx\n\t"
        "ret");
}

void tmp6() {
    __asm__("call *%esp\n\t"
        "jmp *%esi\n\t"
        "pop %ecx\n\t"
        "pop %eax\n\t"
        "ret");
}

void tmp7() {
    __asm__("mov %esp, %eax\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp8() {
    __asm__("mov %esp, %ebx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp9() {
    __asm__("mov %esp, %ecx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp10() {
    __asm__("mov %esp, %ecx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp11() {
    __asm__("mov %esp, %edx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp12() {
    __asm__("mov %esp, %esi\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp13() {
    __asm__("mov %esp, %edi\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp14() {
    __asm__("xor %eax, %eax\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp15() {
    __asm__("xor %ebx, %ebx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp16() {
    __asm__("xor %ecx, %ecx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp17() {
    __asm__("xor %edx, %edx\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp18() {
    __asm__("xor %edi, %edi\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp19() {
    __asm__("xor %esi, %esi\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n");
}

void tmp20() {
    __asm__("add $0xb, %eax\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n");
}

void tmp21() {
    __asm__("add $0x17, %eax\n\t"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n"
        "ret\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "int $0x80\n");
}