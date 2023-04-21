__kernel void addArrays(__global float *a, __global float *b, __global float *c,
                        int n) {
    int gid = get_global_id(0);
    c[gid] = a[gid] + b[gid];
}
