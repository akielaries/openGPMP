__kernel void add_arr_gpu(__global float *a, __global float *b,
                          __global float *c, int n) {

    int gid = get_global_id(0);
    c[gid] = a[gid] + b[gid];
}

/**
 * add vectors using GPU
 */
__kernel void add_vec_gpu(__global const int *a, __global const int *b,
                          __global int *res, const int len) {
    const int idx = get_global_id(0);
    if (idx < len) {
        res[idx] = a[idx] + b[idx];
    }
}
