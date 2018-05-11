//
// Created by attilio on 04/05/18.
//

#include "bthread.h"
#include "bthread_private.h"

#define CUSHION_SIZE 10000
#define save_context(CONTEXT) setjmp(CONTEXT)
#define restore_context(CONTEXT) longjmp(CONTEXT, 1)

//var di supporto




__bthread_scheduler_private *bthread_get_scheduler() {
    static __bthread_scheduler_private * ourScheduler = NULL;
    if(ourScheduler == NULL){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
    }
    return ourScheduler;
}

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
    __bthread_private thread = {bthread, start_routine, arg, __BTHREAD_UNINITIALIZED, attr};
     tqueue_enqueue(bthread_get_scheduler()->queue,&thread);
}

int bthread_join(bthread_t bthread, void **retval) {
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    if (save_context(scheduler->context) == 0) {
        bthread_initialize_next();
        restore_context(scheduler->context);
    } else {
        __bthread_private* tp;
        do {
            if (bthread_reap_if_zombie(bthread, retval)) return 0;
            scheduler->current_item = tqueue_at_offset(scheduler->current_item, 1);
            tp = (__bthread_private*) tqueue_get_data(scheduler->current_item);
        } while (tp->state != __BTHREAD_READY);
        restore_context(tp->context);
    }
}

void bthread_yield(){

}

void bthread_exit(void *retval){

}

static void bthread_create_cushion(__bthread_private* t_data){

}

static void bthread_initialize_next(){

}

static int bthread_reap_if_zombie(bthread_t bthread, void **retval){

}
