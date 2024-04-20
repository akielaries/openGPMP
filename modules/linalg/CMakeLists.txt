set(the_description "Linear Algebra Module")

message("-- Including Linear Algebra Module")

option(BUILD_GPU_OPENCL "Build OpenCL Linear Algebra Extension" OFF)

set(SOURCE_FILES
    mtx.cpp
    mtx_routines.f90
    mtx_arr_f90.cpp
    linsys_routines.f90
    mtx_naive.cpp
    linsys.cpp
    eigen.cpp
    tensor.cpp
    svd.cpp
    vector_naive.cpp
    igemm_arr.cpp

    sgemm_arr.cpp
    
    dgemm_arr.cpp
)

# Add files depending on the detected SIMD ISA
if (SIMD_ISA STREQUAL "AVX2")
    list(APPEND SOURCE_FILES
        avx/mtx_avx2_arr_i8.cpp
        avx/mtx_avx2_arr_i16.cpp
        avx/mtx_avx2_arr_i32.cpp
        avx/mtx_avx2_arr_f32.cpp
        avx/mtx_avx2_arr_f64.cpp

        avx/mtx_avx2_vec_i32.cpp
        avx/mtx_avx2_vec_f32.cpp
        avx/mtx_avx2_vec_f64.cpp

        avx/vector_avx2_i8.cpp
        avx/vector_avx2_i16.cpp
        avx/vector_avx2_i32.cpp
        avx/vector_avx2_f64.cpp

        #dgemm_kernel_sse.cpp
        sse/dgemm_kernel_4x4_sse.S
    )
elseif (SIMD_ISA STREQUAL "ARM_NEON")
    list(APPEND SOURCE_FILES
        arm/mtx_arm_vec_i32.cpp
        arm/mtx_arm_vec_f32.cpp

        arm/vector_arm_i32.cpp
        arm/vector_arm_f64.cpp
    )

elseif (SIMD_ISA STREQUAL "SSE")
    list(APPEND SOURCE_FILES

        sse/mtx_sse2_arr_i8.cpp
        sse/mtx_sse2_arr_i16.cpp
        sse/mtx_sse2_arr_i32.cpp
        sse/mtx_sse2_arr_f32.cpp
        sse/mtx_sse2_arr_f64.cpp

        sse/mtx_sse2_vec_i32.cpp
        sse/mtx_sse2_vec_f32.cpp
        sse/mtx_sse2_vec_f64.cpp

        sse/dgemm_kernel_4x4_sse.S
    )

else (
    list(APPEND SOURCE_FILES
        dgemm_kernel.cpp
    )

)
endif()

# compile OpenCL GPU accelerators into openGPMP binary written
# in C with C++ wrapper
if (BUILD_GPU_OPENCL)
    message("--   [EXT] : Building OpenCL GPU Extension")
    list(APPEND SOURCE_FILES
        gpu/_gpu_mtx_add.c
        gpu/_gpu_mtx_add_wrapper.cpp
    )
endif()

add_library(linalg OBJECT ${SOURCE_FILES})

