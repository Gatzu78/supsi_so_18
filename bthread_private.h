//
// Created by Neme on 13.04.18.
//

#ifndef SUPSI_SO_18_BTHREAD_PRIVATE_H
#define SUPSI_SO_18_BTHREAD_PRIVATE_H

#include <setjmp.h>
#include "bthread.h"

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    jmp_buf context;
    void* retval;
} __bthread_private;

#endif //SUPSI_SO_18_BTHREAD_PRIVATE_H