CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
project(supsi_so_18)
set(CMAKE_C_STANDARD 99)
add_executable(supsi_so_18 bthreads_test.c bthread_private.h bthread.h tqueue.c tqueue.h bthread.c )
