//
// Created by attilio on 04/05/18.
//

#include "bthread.h"

//var di supporto
static __bthread_scheduler_private * ourScheduler;
int isSchedulerInitialized = 0;


__bthread_scheduler_private *bthread_get_scheduler() {
    if(!isSchedulerInitialized){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
        isSchedulerInitialized = 1;
    }
    return ourScheduler;
}

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
    __bthread_private thread = {bthread, start_routine, arg, __BTHREAD_UNINITIALIZED, attr};
     ///
     ///continuare da qui
     ///
}

int bthread_join(bthread_t bthread, void **retval){

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
