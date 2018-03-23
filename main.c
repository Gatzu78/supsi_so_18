//
// Created by Attilio, Antonio, Luciano & Stefano
//

#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>

/******************************************************************************************
*********** Signature of the jump functions ***********
int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);
void longjmp(jmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);

******************************************************************************************/


static jmp_buf buf;

void dothings() {

    printf("Now I'm here\n");
    sleep(3);
    longjmp(buf, 42);
    printf("This is never printed\n");
}

int main() {
    if (!setjmp(buf)) { // the first time returns 0
        dothings();
    } else {
        printf("Now I'm there\n");
    }
    return 1;
}