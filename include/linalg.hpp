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
 * seen here : https://akielaries.github.io/openMTPK/ along with
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
 * @file
 *
 * @brief openMTPK LINEAR ALGEBRA MODULE
 *
 * @details This file serves as the core header for the Linear Algebra
 * module. This header includes Vector/Matrix related operations. Also
 * with additional support for GPU utilization through CUDA (Nvidia
 * hardward support) and OpenCL (OSX & Linux system support):
 *
 *  @note Some topics in Linear Algebra overlap and/or heavily
 * influence algorithms seen in Machine Learning
 */
#ifndef LINALG_HPP
#define LINALG_HPP

/**
 * @brief \b Matrix \b Operations
 * @details Encompasses Matrix and Scalar operations
 */
#define MATRIX
#include "linalg/matrix.hpp"
/*****************************************************************************/

/*****************************************************************************/
/**
 * @brief \b CUDA \b Matrix \b Operations
 * @details CUDA GPU accelerated Matrix functions
 */
#define CUDA_MATRIX
#if defined(__linux__)
    #ifdef __NVCC__
        #include "linalg/_cuda_mtx.cuh"
    #endif
#endif

/**
 * @brief \b OpenCL \b Matrix \b Operations
 * @details OpenCL GPU accelerated Matrix functions
 */
#if defined(__linux__) || defined(__APPLE__)
    #ifndef __NVCC__
        #include "linalg/_gpu_mtx.h"
        #include "linalg/_gpu_mtx_wrapper.hpp"
    #endif
#endif

/**
 * @brief \b Intel \b CPU \b Matrix \b SIMD \b Operations
 * @details Intel based intrinsic functions
 */
#define INTEL_SIMD
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)
    #include "linalg/_simd_intel_mtx.hpp"
#endif

/**
 * @brief \b ARM \b CPU \b Matrix \b SIMD \b Operations
 * @details ARM based intrinsic functions
 */
#define ARM_SIMD
#if defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                      \
    defined(__ARM_ARCH) || defined(__aarch64__)
    #include "linalg/_simd_arm_mtx.hpp"
#endif

#endif
