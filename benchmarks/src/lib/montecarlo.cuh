/**
 * Monte Carlo GPU methods header
 */
#ifndef __MONTECARLO_CUH__
#define __MONTECARLO_CUH__

#define TRIALS_PER_THREAD 4096
#define BLOCKS 256
#define THREADS 256
#define PI 3.1415926535 // known value of pi

#include <cuda.h>
#include <curand_kernel.h>

/**
 * @brief Driver for CUDA Monte Carlo method
 * @param dev
 * @param devStates
 */
void run_gpu_monte_carlo(float *dev, curandState *devStates);

#endif
