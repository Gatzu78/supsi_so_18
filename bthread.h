//
// Created by Neme on 13.04.18.
//

#ifndef SUPSI_SO_18_BTHREAD_H
#define SUPSI_SO_18_BTHREAD_H

#include "tqueue.h"
#include "bthread_private.h"

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int bthread_join(bthread_t bthread, void **retval);
void bthread_yield();
void bthread_exit(void *retval);


#endif //SUPSI_SO_18_BTHREAD_H
