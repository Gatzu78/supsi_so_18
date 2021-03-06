//
// Created by attilio on 04/05/18.
//

#include "bthread.h"
#include "bthread_private.h"

__bthread_scheduler_private *bthread_get_scheduler() {
    static __bthread_scheduler_private * ourScheduler = NULL;
    if(ourScheduler == NULL){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
        ((__bthread_scheduler_private*) ourScheduler)->queue = NULL;
    }
    return ourScheduler;
}

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
    __bthread_private *  thread = malloc(sizeof(__bthread_private));
    thread->body = start_routine;
    thread->arg = arg;
    thread->state = __BTHREAD_UNINITIALIZED;
    if(attr != NULL){
        thread->attr = *attr;
    }
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    thread->tid = tqueue_enqueue(&scheduler->queue, thread);
    *bthread = thread->tid;
    scheduler->current_item = scheduler->queue;
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

void bthread_yield() {
    volatile __bthread_scheduler_private *scheduler = bthread_get_scheduler();
    volatile __bthread_private * thread = tqueue_get_data(scheduler->current_item);

    if (!save_context(thread->context)) {
            bthread_initialize_next();
            restore_context(scheduler->context);
    }
}

void bthread_exit(void *retval){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    thread->state = __BTHREAD_ZOMBIE;
    thread->retval = retval;
    bthread_yield();
}

static void bthread_create_cushion(__bthread_private* t_data){
    char cushion[CUSHION_SIZE];
    cushion[CUSHION_SIZE-1] = cushion[0];
    t_data->state = __BTHREAD_READY;
    bthread_exit(t_data->body(t_data->arg));
}

static void bthread_initialize_next(){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    volatile TQueue next = tqueue_at_offset(scheduler->current_item, 1);
    volatile __bthread_private * nextThread = tqueue_get_data(next);

    if(nextThread->state == __BTHREAD_UNINITIALIZED){
        scheduler->current_item = next;
        bthread_create_cushion(nextThread);
    }
}

static int bthread_reap_if_zombie(bthread_t bthread, void **retval){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    if(thread->state == __BTHREAD_ZOMBIE){
        thread->state = __BTHREAD_EXITED;
        if(retval != NULL){
            *retval = thread->retval;
        }
        return 1;
    }else{
        return 0;
    }

}

void bthread_cleanup(){

}
