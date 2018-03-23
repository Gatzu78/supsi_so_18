//
// Created by Attilio, Antonio, Luciano & Stefano
//

#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

void dothings(){
    printf("now I'm there\n");
    sleep(3);
    longjmp(buf, 32);
    printf("This is never printed");
}
int main() {
    if(!setjmp(buf)){
        dothings();
    } else {
        printf("now I'm at bottom\n");
    }
    return 0;
}