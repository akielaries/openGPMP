#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <time.h>
#include <omp.h>

int main() {
    
    // spawn threads
    #pragma omp parallel 
    {
        int nthreads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("Number of threads = %d\n", nthreads);
        printf("Thread id = %d\n", thread_id);
    } // insert barrier

    // return 0;

}


