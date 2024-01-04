#include "../lib/primes.cuh"
#include <ctime>
#include <curand_kernel.h>
#include <iostream>
#include <random>
#include <vector>

__device__ uint32_t gpu_mod_mul(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return res;
}

__device__ uint32_t gpu_mod_pow(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t res = 1;

    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = gpu_mod_mul(res, a, m);
        }
        a = gpu_mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

__device__ bool gpu_witness(uint32_t n, uint32_t d, uint32_t a, uint32_t s) {
    uint32_t x = gpu_mod_pow(a, d, n);

    if (x == 1 || x == n - 1) {
        return false;
    }

    for (uint32_t r = 1; r < s; r++) {
        x = gpu_mod_mul(x, x, n);
        if (x == n - 1) {
            return false;
        }
    }
    return true;
}

__global__ void
miller_rabin_kernel(const uint32_t *input, bool *output, int iters) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    uint32_t num = input[idx];
    uint32_t d = num - 1, s = 0;

    if (num < 2) {
        output[idx] = false;
        return;
    }
    if (num == 2 || num == 3) {
        output[idx] = true;
        return;
    }
    if (num % 2 == 0) {
        output[idx] = false;
        return;
    }

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    curandState state;
    curand_init(clock64(), idx, 0, &state);

    for (int i = 0; i < iters; i++) {
        uint32_t a = curand(&state) % (num - 3) + 2;
        if (gpu_witness(num, d, a, s)) {
            output[idx] = false;
            return;
        }
    }

    output[idx] = true;
}

void run_gpu_miller_rabin(const uint32_t *input,
                          bool *output,
                          int iters,
                          int threads,
                          int blocks) {

    miller_rabin_kernel<<<blocks, threads>>>(input, output, iters);
}
