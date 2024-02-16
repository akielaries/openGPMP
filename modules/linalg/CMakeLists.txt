set(the_description "Linear Algebra Module")

message("-- Including Linear Algebra Module")

option(BUILD_GPU_OPENCL "Build OpenCL Linear Algebra Extension" OFF)

set(SOURCE_FILES
    mtx_routines.f90
    linsys_routines.f90
    mtx.cpp
    linsys.cpp
    eigen.cpp
    tensor.cpp
    svd.cpp
    vector_naive.cpp
)

# Add files depending on the detected SIMD ISA
if (SIMD_ISA STREQUAL "AVX2")
    list(APPEND SOURCE_FILES
        mtx_avx2_i32.cpp

        vector_avx2_i8.cpp
        vector_avx2_i16.cpp
        vector_avx2_i32.cpp
        vector_avx2_f64.cpp
    )
elseif (SIMD_ISA STREQUAL "ARM_NEON")
    list(APPEND SOURCE_FILES
        vector_arm_i32.cpp
        vector_arm_f64.cpp
    )
endif()

# compile OpenCL GPU accelerators into openGPMP binary written
# in C with C++ wrapper
if (BUILD_GPU_OPENCL)
    message("--   [EXT] : Building OpenCL GPU Extension")
    list(APPEND SOURCE_FILES
        plat/_gpu_mtx_add.c
        plat/_gpu_mtx_add_wrapper.cpp
    )
endif()

add_library(linalg OBJECT ${SOURCE_FILES})

