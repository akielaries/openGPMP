/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
/**
 * @file _gpu_mtx.cpp
 * @brief OpenCL-based GPU acceleration
 */
#include "../../include/linalg/_gpu_mtx.h"
#include <chrono>
#include <iostream>
#include <math.h>
#include <random>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <vector>

// using deprecated functions from OpenCL
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_TARGET_OPENCL_VERSION 300

// if system is Apple, use this header
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)
#define PRINT_LINE(title) printf("\n========== %s ==========\n", title);

#define MAX_SOURCE_SIZE (0x100000)

// Helper function to check for OpenCL errors
void checkError(cl_int status, const char *errorMsg) {
    if (status != CL_SUCCESS) {
        std::cout << errorMsg << std::endl;
        exit(1);
    }
}

void gpu_mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C) {
    // Matrix dimensions
    const int N = A.size();
    const int M = A[0].size();

    // Input matrices
    std::vector<int> flat_A(N * M);
    std::vector<int> flat_B(N * M);
    std::vector<int> flat_C(N * M, 0);

    // Flatten input matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            flat_A[i * M + j] = A[i][j];
            flat_B[i * M + j] = B[i][j];
        }
    }
    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // Load the kernel source code
    FILE *file = fopen("_gpu_mtx_kernel.c", "r");
    if (!file) {
        std::cout << "Failed to load kernel." << std::endl;
        return;
    }
    char *source_str = (char *)malloc(MAX_SOURCE_SIZE);
    size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, file);
    fclose(file);

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;

    cl_int status = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    status |= clGetDeviceIDs(platform_id,
                             CL_DEVICE_TYPE_GPU,
                             1,
                             &device_id,
                             &ret_num_devices);
    checkError(status, "Error getting platform and device information.");

    // Create an OpenCL context
    cl_context context =
        clCreateContext(NULL, 1, &device_id, NULL, NULL, &status);
    checkError(status, "Error creating context.");

    // Create a command queue
    cl_command_queue command_queue =
        clCreateCommandQueue(context, device_id, 0, &status);
    checkError(status, "Error creating command queue.");

    // Create memory buffers on the device for each matrix
    cl_mem mem_obj_A = clCreateBuffer(context,
                                      CL_MEM_READ_ONLY,
                                      N * M * sizeof(int),
                                      NULL,
                                      &status);
    cl_mem mem_obj_B = clCreateBuffer(context,
                                      CL_MEM_READ_ONLY,
                                      N * M * sizeof(int),
                                      NULL,
                                      &status);
    cl_mem mem_obj_C = clCreateBuffer(context,
                                      CL_MEM_WRITE_ONLY,
                                      N * M * sizeof(int),
                                      NULL,
                                      &status);

    // Write matrices A and B to the device memory
    status = clEnqueueWriteBuffer(command_queue,
                                  mem_obj_A,
                                  CL_TRUE,
                                  0,
                                  N * M * sizeof(int),
                                  flat_A.data(),
                                  0,
                                  NULL,
                                  NULL);
    status |= clEnqueueWriteBuffer(command_queue,
                                   mem_obj_B,
                                   CL_TRUE,
                                   0,
                                   N * M * sizeof(int),
                                   flat_B.data(),
                                   0,
                                   NULL,
                                   NULL);
    checkError(status, "Error writing matrices to device memory.");

    // Create a program from the kernel source code
    cl_program program = clCreateProgramWithSource(context,
                                                   1,
                                                   (const char **)&source_str,
                                                   (const size_t *)&source_size,
                                                   &status);
    checkError(status, "Error creating program.");

    // Build the program
    status = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    checkError(status, "Error building program.");

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "gpu_mtx_add", &status);
    checkError(status, "Error creating kernel.");

    // Set the arguments of the kernel
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mem_obj_A);
    status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mem_obj_B);
    status |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&mem_obj_C);
    checkError(status, "Error setting kernel arguments.");

    // Define the global and local workgroup sizes
    size_t global_work_size[2] = {N, M};
    size_t local_work_size[2] = {1, 1};

    // Enqueue the kernel for execution
    status = clEnqueueNDRangeKernel(command_queue,
                                    kernel,
                                    2,
                                    NULL,
                                    global_work_size,
                                    local_work_size,
                                    0,
                                    NULL,
                                    NULL);
    checkError(status, "Error enqueueing kernel.");

    // Read the result from the device memory
    status = clEnqueueReadBuffer(command_queue,
                                 mem_obj_C,
                                 CL_TRUE,
                                 0,
                                 N * M * sizeof(int),
                                 flat_C.data(),
                                 0,
                                 NULL,
                                 NULL);
    checkError(status, "Error reading result from device memory.");
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();
    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    // Populate the output matrix C
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            C[i][j] = flat_C[i * M + j];
        }
    }

    // Cleanup
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(mem_obj_A);
    clReleaseMemObject(mem_obj_B);
    clReleaseMemObject(mem_obj_C);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    free(source_str);
}

int main() {
    int matrixSize = 8192;
    // std::vector<std::vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // std::vector<std::vector<int>> B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    // std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size()));
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> C(matrixSize, std::vector<int>(matrixSize));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();

    gpu_mtx_add(A, B, C);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    // Print the result matrix
    /*
    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Result matrix:\n";
    for (const auto &row : C) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }*/

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    return 0;
}
