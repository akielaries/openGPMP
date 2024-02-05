/**
 * This file implements OpenCL matrix operation related kernel functions
 */

/**
 * add vectors using GPU
 */
__kernel void
gpu_mtx_add(__global const int *A, __global const int *B, __global int *C) {
    int i = get_global_id(0);
    int j = get_global_id(1);
    int index = i * get_global_size(1) + j;
    C[index] = A[index] + B[index];
}

__kernel void matrixMul(__global float *C,
                        __global float *A,
                        __global float *B,
                        int wA,
                        int wB) {

    int tx = get_global_id(0);
    int ty = get_global_id(1);

    // value stores the element that is
    // computed by the thread
    float value = 0;
    for (int k = 0; k < wA; ++k) {
        float elementA = A[ty * wA + k];
        float elementB = B[k * wB + tx];
        value += elementA * elementB;
    }

    // Write the matrix to device memory each
    // thread writes one element
    C[ty * wA + tx] = value;
}
