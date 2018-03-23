//
// Created by Attilio, Antonio, Luciano & Stefano
//

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

/******************************************************************************************
*********** Signature of the jump functions ***********
int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);
void longjmp(jmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);

******************************************************************************************/


static jmp_buf main_buf, dothing_buf;

void dothings() {
    int z = 1313;
    if (!setjmp(dothing_buf)) {
        printf("Now I'm here, z=%d\n", z);
        longjmp(main_buf, 42);
    } else {
        printf("Now I'm back here, z=%d\n", z);
        exit(0);
    }
}

void cushion(){
    char data_cushion[1000];
    data_cushion[999]=1;
    dothings();
}

int main() {
    if (!setjmp(main_buf)) { // the first time returns 0
        cushion();
    } else {
        longjmp(dothing_buf,17);
    }
    return 2;
}