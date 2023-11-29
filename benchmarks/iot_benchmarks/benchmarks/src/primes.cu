#include <ctime>
#include <cuda_runtime.h>
#include <iostream>
#include <random>
#include <vector>

__device__ uint32_t mod_mul(uint32_t a, uint32_t b, uint32_t m) {
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

__device__ uint32_t mod_pow(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t res = 1;

    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = mod_mul(res, a, m);
        }
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

__device__ bool witness(uint32_t n, uint32_t d, uint32_t a, uint32_t s) {
    uint32_t x = mod_pow(a, d, n);

    if (x == 1 || x == n - 1) {
        return false;
    }

    for (uint32_t r = 1; r < s; r++) {
        x = mod_mul(x, x, n);
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

    for (int i = 0; i < iters; i++) {
        uint32_t a = rand() % (num - 3) + 2;
        if (witness(num, d, a, s)) {
            output[idx] = false;
            return;
        }
    }
    output[idx] = true;
}

int main() {
    std::vector<uint32_t> nums = {
        1000000007, // A large 32-bit integer PRIME
        2147483647, // The largest 32-bit signed integer PRIME
        97,         // A PRIME number
        123456789,  // Another large 32-bit integer
        19,         // A PRIME number
        42,         // Just a random number
        31,         // A PRIME number
        987654321,  // Yet another large 32-bit integer
        37,         // A PRIME number
        123,        // Just another number
        17,         // A PRIME number
        999999999,  // And another large 32-bit integer
        23,         // A PRIME number
        777777777,  // Large 32-bit integer
        13,         // A PRIME number
        234567890,  // Large 32-bit integer
        11,         // A PRIME number
        987654321,  // Repeating value for demonstration
        7,          // A PRIME number
        8675309,    // Another large 32-bit integer
        709,        // A PRIME number
        5381,       // A PRIME number
        52711,      // A PRIME number
        167449,     // A PRIME number
        648391,     // A PRIME number
        1128889,    // A PRIME number
        2269733,    // A PRIME number
        3042161,    // A PRIME number
        4535189,    // A PRIME number
        7474967,    // A PRIME number
        9737333,    // A PRIME number
        14161729,   // A PRIME number
        17624813,   // A PRIME number
        19734581,   // A PRIME number
        23391799,   // A PRIME number
        29499439,   // A PRIME number
        37139213    // A PRIME number
    };

    int n = nums.size();
    int iters = 10;

    // Allocate device memory for input and output arrays
    uint32_t *d_input;
    bool *d_output;
    cudaMalloc((void **)&d_input, n * sizeof(uint32_t));
    cudaMalloc((void **)&d_output, n * sizeof(bool));

    // Copy input data to device
    cudaMemcpy(d_input,
               nums.data(),
               n * sizeof(uint32_t),
               cudaMemcpyHostToDevice);

    // Launch a separate thread for each element in the array
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
    miller_rabin_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_input,
                                                            d_output,
                                                            iters);

    // Copy the results back to the host
    bool *results = new bool[n];
    cudaMemcpy(results, d_output, n * sizeof(bool), cudaMemcpyDeviceToHost);

    // Clean up
    cudaFree(d_input);
    cudaFree(d_output);
    delete[] results;

    return 0;
}
