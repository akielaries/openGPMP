set(the_description "Linear Algebra Module")

message("-- Including Linear Algebra Module")

option(BUILD_GPU_OPENCL "Build OpenCL Linear Algebra Extension" OFF)

set(SOURCE_FILES
    lao.cpp
    mtx_routines.f90
    mtx.cpp
    linsys.f90
)

# compile OpenCL GPU accelerators into openGPMP binary written
# in C with C++ wrapper
if (BUILD_GPU_OPENCL)
    message("--   [EXT] : Building OpenCL GPU Extension")
    list(APPEND SOURCE_FILES
        _gpu_mtx_add.c
        _gpu_mtx_add_wrapper.cpp
    )
endif()

add_library(linalg OBJECT ${SOURCE_FILES})

