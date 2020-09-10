// Arquivo criado e disponibilizado para palestra MTS SP 2020
// Autor: Hélvio Junior (M4v3r1ck)
//
// gcc -m32 -o spawn spawn.c
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] ) {

	setuid(0);
    execve("/bin/sh", NULL, NULL);

}
