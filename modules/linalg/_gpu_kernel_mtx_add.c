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
