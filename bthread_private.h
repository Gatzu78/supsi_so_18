//
// Created by Neme on 13.04.18.
//

#ifndef SUPSI_SO_18_BTHREAD_PRIVATE_H
#define SUPSI_SO_18_BTHREAD_PRIVATE_H


#include <setjmp.h>
#define save_context(CONTEXT) setjmp(CONTEXT)
#define restore_context(CONTEXT) longjmp(CONTEXT, 1)
#define CUSHION_SIZE 10000

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

typedef unsigned long int bthread_t;

typedef struct {} bthread_attr_t;
typedef void *(*bthread_routine) (void *);


typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
} __bthread_scheduler_private;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    jmp_buf context;
    void* retval;
} __bthread_private;

__bthread_scheduler_private* bthread_get_scheduler();
void bthread_cleanup();
static void bthread_create_cushion(__bthread_private* t_data);
static void bthread_initialize_next();
static int bthread_reap_if_zombie(bthread_t bthread, void **retval);

#endif //SUPSI_SO_18_BTHREAD_PRIVATE_H
