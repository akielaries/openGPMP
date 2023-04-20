#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#include <xmmintrin.h> //Header for intrinsic functions

int main() {
    // Variables definition and initialization
    int MAX_DIM = 100;
    double a[MAX_DIM][MAX_DIM] __attribute__((aligned(16)));
    double b[MAX_DIM][MAX_DIM] __attribute__((aligned(16)));
    double c[MAX_DIM][MAX_DIM] __attribute__((aligned(16)));
    double d[MAX_DIM][MAX_DIM] __attribute__((aligned(16)));
    for (int i = 0; i < MAX_DIM; ++i) {
        for (int j = 0; j < MAX_DIM; ++j) {
            a[i][j] = 13; // Arbitrary initializations - Replace to test your
                          // multiplication
            b[i][j] = 22; // Arbitrary initializations - Replace to test your
                          // multiplication
            c[i][j] = 0;  // Necessary Initialization - Don't change
            d[i][j] = 0;  // Necessary Initialization - Don't change
        }
    }
    // Unoptimized Matrix Multiplication
    clock_t Time1 = clock();
    for (int i = 0; i < MAX_DIM; ++i) {
        for (int j = 0; j < MAX_DIM; ++j) {
            for (int k = 0; k < MAX_DIM; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    clock_t Time2 = clock();
    //=================================================================================================
    clock_t Time3 = clock();
    /*
    float *p1 ;float *p2;float *p3;
    p1 =&a[0];
    p2 =&b[0];
    p3 =&c[0];
    float* m; float* v; float* result;
    m =&a[0];
    v =&b[0];
    result =&c[0];

    */
    for (int i = 0; i < MAX_DIM; i += 1) {

        for (int j = 0; j < MAX_DIM; j += 4) {

            for (int k = 0; k < MAX_DIM; k += 2) {

                __m128d result = _mm_load_pd(&d[i][j]);

                __m128d a_line = _mm_load_pd(&a[i][k]);

                __m128d b_line0 = _mm_load_pd(&b[k][j + 0]);

                __m128d b_line1 = _mm_loadu_pd(&b[k][j + 1]);

                __m128d b_line2 = _mm_loadu_pd(&b[k][j + 2]);

                __m128d b_line3 = _mm_loadu_pd(&b[k][j + 3]);

                result = _mm_add_pd(
                    result,
                    _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0x00), b_line0));
                result = _mm_add_pd(
                    result,
                    _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0x55), b_line1));
                result = _mm_add_pd(
                    result,
                    _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0xaa), b_line2));
                result = _mm_add_pd(
                    result,
                    _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0xff), b_line3));
                _mm_store_pd(&d[i][j], result);
            }
        }
    }

    // YOUR CODE HERE
    clock_t Time4 = clock();
    // Calculate and print execution times
    double TotalTimeLoop = ((double)Time2 - (double)Time1) / CLOCKS_PER_SEC;
    double TotalTimeSIMD = ((double)Time4 - (double)Time3) / CLOCKS_PER_SEC;
    printf("Performance gain is %.7f \n", TotalTimeLoop / TotalTimeSIMD);
    printf(" Time taken by loop is %.7f \n", TotalTimeLoop);
    printf(" Time taken by SIMD optimized code is %.7f \n", TotalTimeSIMD);
    return 0;
}
