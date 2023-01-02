#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <time.h>
#include <iostream>
#include <omp.h>

int main() {

    int i = 0;

    clock_t start, end;
    double total;
    start = clock();


    //#pragma omp parallel
    while(i < 900900900) {
        i++;
    }
    std::cout << "i = " << i << std::endl;

    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "TIME: " << total << std::endl;

    return 0;

}


