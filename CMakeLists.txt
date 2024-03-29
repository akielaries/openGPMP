#/************************************************************************* 
# *                                  
# *  Project               
# *                         _____ _____  __  __ _____
# *                        / ____|  __ \|  \/  |  __ \
# *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
# * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
# *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
# * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
# *      | |
# *      |_|
# *
# *
# * Copyright (C) Akiel Aries, <akiel@akiel.org>.
# *
# * This software is licensed as described in the file LICENSE, which
# * you should have received as part of this distribution. The terms
# * among other details are referenced in the official documentation
# * seen here : https://akielaries.github.io/openGPMP/ along with 
# * important files seen in this project.
# *
# * You may opt to use, copy, modify, merge, publish, distribute 
# * and/or sell copies of the Software, and permit persons to whom 
# * the Software is furnished to do so, under the terms of the 
# * LICENSE file. As this is an Open Source effort, all implementations
# * must be of the same methodology.
# * 
# *
# * This software is distributed on an "AS IS" basis, WITHOUT 
# * WARRANTY OF ANY KIND, either express or implied.
# *
# ************************************************************************/

cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-unused-result -Wparentheses -Wsign-compare")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -Wall -Wextra -Wfloat-equal -Wcast-qual")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wunreachable-code -D __GPMP_CPP_API__")

project(openGPMP LANGUAGES CXX C Fortran ASM)
set(PROJECT_VERSION "1.0")

include(CheckIncludeFileCXX)

message(STATUS "Detecting ${CMAKE_CXX_COMPILER} macros")
execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -march=native -dM -E -
    RESULT_VARIABLE result
    OUTPUT_VARIABLE compiler_output
    INPUT_FILE /dev/null  # Provide an empty input
)
message(STATUS "Detecting ${CMAKE_CXX_COMPILER} macros - done")

# check if the command execution was successful
if(result EQUAL 0)
    string(FIND "${compiler_output}" "#define __ARM_NEON 1" arm_neon_index)
    string(FIND "${compiler_output}" "#define __AVX2__ 1" avx2_index)
    string(FIND "${compiler_output}" "#define __SSE__ 1" sse_index)
    string(FIND "${compiler_output}" "#define __MMX__ 1" mmx_index)

    message(STATUS "Detecting available SIMD ISAs")
    
    # order of magnitude for INTRINS:
    # ARM NEON is only available extension on ARM procs
    # AVX2 is the highest order support and x86 procs supporting this will 
    # also support SSE2, SSE, MMX, and the others that came before it

    if(arm_neon_index GREATER -1)
        message(STATUS "SIMD ISA : ARM NEON supported")
        set(SIMD_ISA "ARM_NEON")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GPMP_ARM_NEON__")
        check_include_file_cxx("arm_neon.h" HEADER_EXISTS)

    elseif(avx2_index GREATER -1)
        message(STATUS "SIMD ISA : AVX2 is supported")
        set(SIMD_ISA "AVX2")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GPMP_AVX2__")
        check_include_file_cxx("immintrin.h" HEADER_EXISTS)

    elseif(sse_index GREATER -1)
        message(STATUS "SIMD ISA : SSE is supported")
        set(SIMD_ISA "SSE")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GPMP_SSE__")
        check_include_file_cxx("emmintrin.h" HEADER_EXISTS)
        check_include_file_cxx("smmintrin.h" HEADER_EXISTS)

    elseif(mmx_index GREATER -1)
        message(STATUS "SIMD ISA : MMX is supported")
        set(SIMD_ISA "MMX")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__GPMP_MMX__")
        check_include_file_cxx("mmintrin.h" HEADER_EXISTS)

    else()
        message(STATUS "No supported SIMD ISA")
    endif()

    message(STATUS "Detecting available SIMD ISAs - done")
else()
    message(STATUS "Command failed with error code ${result}")
endif()

# compile with native microarchitecture
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

# Set build type if not specified
set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

    
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
set(CMAKE_Fortran_FLAGS "-O0")

include(GNUInstallDirs)

option(BUILD_ARITH "[!] Build Arithmetic Module" ON)

############################################################
# Run Tests
############################################################
#find_package(GTest REQUIRED)

option(BUILD_TESTS "Build Unit Test Suite" OFF)
option(BUILD_PYGPMP "Build Python API" OFF)

if(BUILD_PYGPMP)
    message(STATUS "Building Python API")

    # Set the path to your Python interpreter
    set(PYTHON_EXECUTABLE "/usr/bin/python3")

    # Set the path to your Python project
    set(PYTHON_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

    # Run the Python command to build the Python API
    execute_process(
        COMMAND ${PYTHON_EXECUTABLE} setup.py build_ext --inplace sdist bdist_wheel --plat-name=native
        WORKING_DIRECTORY ${PYTHON_PROJECT_DIR}
        RESULT_VARIABLE PYTHON_BUILD_RESULT
    )

    if(PYTHON_BUILD_RESULT)
        message(FATAL_ERROR "Failed to build Python API")
    else()
        message(STATUS "Python API built successfully")
    endif()

else()
    message(STATUS "Building source C++ API")

    ############################################################
    # Create a library
    ############################################################

    # Add the module directories
    add_subdirectory(modules/arithmetic)
    add_subdirectory(modules/calculus)
    add_subdirectory(modules/disct)
    add_subdirectory(modules/linalg)
    add_subdirectory(modules/core)
    add_subdirectory(modules/ml)
    add_subdirectory(modules/nt)
    add_subdirectory(modules/optim)
    add_subdirectory(modules/stats)

    add_library(${PROJECT_NAME} STATIC
      $<TARGET_OBJECTS:arithmetic>
      $<TARGET_OBJECTS:calculus>
      $<TARGET_OBJECTS:disct>
      $<TARGET_OBJECTS:linalg>
      $<TARGET_OBJECTS:core>
      $<TARGET_OBJECTS:ml>
      $<TARGET_OBJECTS:nt>
      $<TARGET_OBJECTS:optim>
      $<TARGET_OBJECTS:stats>
    )

    # include directory for openGPMP
    target_include_directories(${PROJECT_NAME} PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE modules
    )

    set_target_properties(${PROJECT_NAME} 
        PROPERTIES VERSION ${PROJECT_VERSION}
    )

    install(TARGETS ${PROJECT_NAME} EXPORT openGPMPConfig 
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    # install include directory to /usr/local/include/openGPMP
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openGPMP"
    )

    install(EXPORT openGPMPConfig DESTINATION share/openGPMP/cmake)

    export(TARGETS ${PROJECT_NAME} FILE openGPMPConfig.cmake)

    if (BUILD_TESTS)
        message(STATUS "Including tests")

        enable_testing()

        add_subdirectory(tests)

        # run C++ and Fortran unit tests
        add_dependencies(${PROJECT_NAME} RUN_CPP_TESTS)
        add_dependencies(${PROJECT_NAME} RUN_FORTRAN_TESTS) 
    endif()

    # uninstall target
    if(NOT TARGET uninstall)
      configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

      add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
    endif()

endif()
