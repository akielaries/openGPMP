

/**
 * add vectors using GPU
 */
__kernel void add_vec_gpu(__global const int *a, __global const int *b,
                          __global int *res, const int len) {
    // current worker, each worker adds a element from A & B
    const int idx = get_global_id(0);
    // ensure number of workers created doesnt exceed elements of array
    // by checking its bounds
    if (idx < len) {
        res[idx] = a[idx] + b[idx];
    }
}

__kernel void matrixMul(__global float *C, __global float *A, __global float *B,
                        int wA, int wB) {

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

