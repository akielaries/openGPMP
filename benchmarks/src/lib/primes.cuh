/**
 * Primality test GPU methods header
 */
#ifndef __PRIMES_CUH__
#define __PRIMES_CUH__


#define TRIALS_PER_THREAD 4096
#define BLOCKS 256
#define THREADS 256
#define PI 3.1415926535 // known value of pi

#include <cuda.h>
#include <curand_kernel.h>

/**
 * @brief Driver for CUDA Miller Rabin method
 * @param 
 * @param 
 */
void run_gpu_miller_rabin(const uint32_t *input, 
                          bool *output, 
                          int iters,
                          int threads,
                          int blocks);

#endif
