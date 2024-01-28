#include "../lib/montecarlo.cuh"
#include <cuda.h>
#include <curand_kernel.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void gpu_monte_carlo(float *estimate, curandState *states) {
    unsigned int thread_id = threadIdx.x + blockDim.x * blockIdx.x;
    int points_in_circle = 0;
    float x, y;
    // Initialize CURAND
    curand_init(1234, thread_id, 0, &states[thread_id]);

    for (int i = 0; i < TRIALS_PER_THREAD; i++) {
        x = curand_uniform(&states[thread_id]);
        y = curand_uniform(&states[thread_id]);
        points_in_circle +=
            (x * x + y * y <= 1.0f); // count if x & y is in the circle.
    }
    estimate[thread_id] = 4.0f * points_in_circle /
                          (float)TRIALS_PER_THREAD; // return estimate of pi
}

float host_monte_carlo(long trials) {
    float x, y;
    long points_in_circle = 0;
    for (long i = 0; i < trials; i++) {
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;
        points_in_circle += (x * x + y * y <= 1.0f);
    }
    return 4.0f * points_in_circle / trials;
}

void run_gpu_monte_carlo(float *dev, curandState *devStates) {

    gpu_monte_carlo<<<BLOCKS, THREADS>>>(dev, devStates);
}
