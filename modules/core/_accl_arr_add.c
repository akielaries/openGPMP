/* gpu */
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_TARGET_OPENCL_VERSION 300

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define ARRAY_SIZE 4096

void add_array(float *a, float *b, float *c) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
    }
}

const char *kernelSource = "__kernel void addArrays(__global float *a, "
                           "__global float *b, __global float *c, int n) {\n"
                           "    int gid = get_global_id(0);\n"
                           "    c[gid] = a[gid] + b[gid];\n"
                           "}\n";
int accl_arr_exec() {
    cl_int err;

    // Create OpenCL platform
    cl_platform_id platform;
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf("Error getting platform ID: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL device
    cl_device_id device;
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf("Error getting device ID: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("Error creating context: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL command queue
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
    if (err != CL_SUCCESS) {
        printf("Error creating command queue: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL program from kernel source
    cl_program program = clCreateProgramWithSource(
        context, 1, (const char **)&kernelSource, NULL, &err);
    if (err != CL_SUCCESS) {
        printf("Error creating program: %d\n", err);
        return EXIT_FAILURE;
    }

    // Build OpenCL program
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error building program: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "addArrays", &err);
    if (err != CL_SUCCESS) {
        printf("Error creating kernel: %d\n", err);
        return EXIT_FAILURE;
    }

    // Create OpenCL buffers for input and output arrays
    float *a = (float *)malloc(sizeof(float) * ARRAY_SIZE);
    float *b = (float *)malloc(sizeof(float) * ARRAY_SIZE);
    float *c = (float *)malloc(sizeof(float) * ARRAY_SIZE);
    cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                    sizeof(float) * ARRAY_SIZE, NULL, &err);
    cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                    sizeof(float) * ARRAY_SIZE, NULL, &err);
    cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                    sizeof(float) * ARRAY_SIZE, NULL, &err);

    // Initialize input arrays
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Write input arrays to OpenCL buffers
    err = clEnqueueWriteBuffer(queue, bufferA, CL_TRUE, 0,
                               sizeof(float) * ARRAY_SIZE, a, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error writing buffer A: %d\n", err);
        return EXIT_FAILURE;
    }
    err = clEnqueueWriteBuffer(queue, bufferB, CL_TRUE, 0,
                               sizeof(float) * ARRAY_SIZE, b, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error writing buffer B: %d\n", err);
        return EXIT_FAILURE;
    }

    // Set kernel arguments
    int n = ARRAY_SIZE;
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &n);
    if (err != CL_SUCCESS) {
        printf("Error setting kernel arguments: %d\n", err);
        return EXIT_FAILURE;
    }

    // Execute kernel
    size_t globalWorkSize[] = {ARRAY_SIZE};
    struct timeval start_gpu, end_gpu, start_cpu, end_cpu;
    double elapsed_time_gpu;
    gettimeofday(&start_gpu, NULL);

    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, globalWorkSize, NULL,
                                 0, NULL, NULL);
    gettimeofday(&end_gpu, NULL);
    elapsed_time_gpu = (end_gpu.tv_sec - start_gpu.tv_sec) +
                       (end_gpu.tv_usec - start_gpu.tv_usec) / 1000000.0;

    if (err != CL_SUCCESS) {
        printf("Error executing kernel: %d\n", err);
        return EXIT_FAILURE;
    }

    // Read output array from OpenCL buffer
    err = clEnqueueReadBuffer(queue, bufferC, CL_TRUE, 0,
                              sizeof(float) * ARRAY_SIZE, c, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error reading buffer C: %d\n", err);
        return EXIT_FAILURE;
    }

    // Print array a
    printf("ARRARY A: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");

    // Print array b
    printf("ARRAY B: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f ", b[i]);
    }
    printf("\n");

    // Print output array
    printf("ARRAY C: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f ", c[i]);
    }
    printf("\n");

    // Cleanup
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    free(a);
    free(b);
    free(c);

    float *d = (float *)malloc(sizeof(float) * ARRAY_SIZE);

    double elapsed_time_cpu;

    gettimeofday(&start_cpu, NULL);

    add_array(a, b, d);

    gettimeofday(&end_cpu, NULL);
    elapsed_time_cpu = (end_cpu.tv_sec - start_cpu.tv_sec) +
                       (end_cpu.tv_usec - start_cpu.tv_usec) / 1000000.0;

    printf("ARRAY D: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f ", d[i]);
    }
    printf("\n");

    free(d);

    // print CPU result
    printf("CPU: %f \n", elapsed_time_cpu);
    // print GPU result
    printf("GPU: %f \n", elapsed_time_gpu);

    return EXIT_SUCCESS;
}
