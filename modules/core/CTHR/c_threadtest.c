/**
 * threadpool_test.c, copyright 2001 Steve Gribble
 * Just a regression test for the threadpool code.
 */
#include "c_threadpool.h"
#include "extra.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int errno;
extern int add_memory_access(memaddr_t addr, line_type_e type,
                             pthread_t thread);

void dispatch_to_me(void *arg) {
    int seconds = (int)arg;
    fprintf(stdout, "  in dispatch %d\n", seconds);
    fprintf(stdout, "  done dispatch %d\n", seconds);
}
int main(int argc, char **argv) {
    threadpool tp;
    int i = 0;
    construct_locksmith(122);

    /*
      locksmith_add_memory_access(pthread_self(),2,3,4,5);
      locksmith_add_lock_to_thread(1);
    */

    tp = create_threadpool(7);
    for (; i < 16; i++) {
        dispatch(tp, dispatch_to_me, (void *)i);
    }
    fprintf(stdout, "**main** done first\n");
    sleep(1);
    fprintf(stdout, "\n\n");
    for (i = 0; i < 12; i++) {
        dispatch(tp, dispatch_to_me, (void *)i);
    }
    fprintf(stdout, "**main done second\n");
    destroy_locksmith();
    destroy_threadpool(tp);
    sleep(5);
    exit(-1);
}
