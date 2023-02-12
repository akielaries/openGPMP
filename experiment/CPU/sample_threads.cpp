#include <omp.h>
#include <pthread.h> /* pthread functions and data structures */
#include <stdio.h>   /* standard I/O routines                 */
#include <time.h>

/* function to be executed by the new thread */
void *do_loop(void *data) {
    int i;                   /* counter, to print numbers */
    int j;                   /* counter, for delay        */
    int me = *((int *)data); /* thread identifying number */

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 500000; j++) /* delay loop */
            ;
        printf("'%d' - Got '%d'\n", me, i);
    }

    /* terminate the thread */
    pthread_exit(NULL);
}

/* like any C program, program's execution begins in main */
int run() {
    // time the function
    clock_t t;
    t = clock();

    int       thr_id;   /* thread ID for the newly created thread */
    pthread_t p_thread; /* thread's structure                     */
    int       a = 1;    /* thread 1 identifying number            */
    int       b = 2;    /* thread 2 identifying number            */

    /* create a new thread that will execute 'do_loop()' */
    thr_id = pthread_create(&p_thread, NULL, do_loop, (void *)&a);
    /* run 'do_loop()' in the main thread as well */
    do_loop((void *)&b);

    /* NOT REACHED */
    return 0;
}

int main() {
    // clock_t t;
    // t = clock();
    double d_time = omp_get_wtime();
    run();
    d_time = omp_get_wtime() - d_time;
    printf("Time taken: %f second \n", d_time);

    // end time
    // t = clock() - t;
    // return time in seconds
    // double final_time = ((double)t) / CLOCKS_PER_SEC;
    // printf("Decoded in: %f seconds\n", final_time);

    return 0;
}
