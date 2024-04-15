# /*************************************************************************
# Root CMake file for the openGPMP project
# *************************************************************************/

cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

project(openGPMP LANGUAGES CXX C Fortran ASM)
set(PROJECT_VERSION "1.0")

include(CheckIncludeFileCXX)

# MAIN OPTIONS FOR BUILDING
# * -DBUILD_OPENGPMP: build source C++ API detecting available hardware accl
#   by default
# * -DBUILD_PYGPMP  : build Python API wrapper
# * -DBUILD_TINYGPMP: build tinygpmp subproject for embedded devices
# * -DBUILD_TESTS   : build C++ and FORTRAN unit tests

option(BUILD_OPENGPMP   "Build Source C++ API"  ON)     # ON BY DEFAULT
option(BUILD_TINYGPMP   "Build tinygpmp"        OFF)    # OFF BY DEFAULT
option(BUILD_PYGPMP     "Build Python API"      OFF)    # OFF BY DEFAULT
option(BUILD_TESTS      "Build Unit Test Suite" OFF)    # OFF BY DEFAULT

if(NOT BUILD_TINYGPMP AND NOT BUILD_PYGPMP)

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-unused-result -Wparentheses -Wsign-compare")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -Wall -Wextra -Wfloat-equal -Wcast-qual")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wunreachable-code -D __GPMP_CPP_API__")

    message(STATUS "Detecting ${CMAKE_CXX_COMPILER} macros")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -march=native -dM -E -
        RESULT_VARIABLE result
        # result output
        OUTPUT_VARIABLE compiler_output
        INPUT_FILE /dev/null  # Provide an empty input
    )
    message(STATUS "Detecting ${CMAKE_CXX_COMPILER} macros - done")

    # check if the command execution was successful
    if(result EQUAL 0)
        # check if string is in compiler output
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

endif()

if(BUILD_TINYGPMP)
    # this section should have some heirarchy to it. should make the default
    # 32-bit MCUs. should define macros for each option (src code will use 
    # this). should take in -mcpu and -march as params to then set for
    # arm g++ compiler flags. 
    # THERE AREN'T MANY THINGS FOR US TO RELY ON FOR DETECTING EMBEDDED
    # DEVICE INFO EASILY SO WE WILL RELY MOSTLY ON PASSED IN INFO AS FLAGS
    # TODO FIXME
    message(STATUS "Building tinygpmp")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__TINYGPMP__")

    option(TINYGPMP_AVR8  "Build for 8-bit AVR MCUs" OFF)
    option(TINYGPMP_AVR32 "Build for 32-bit AVR MCUs" OFF)
    option(TINYGPMP_STM8  "Build for 8-bit ARM M-Cortex MCUs" OFF)
    option(TINYGPMP_STM32 "Build for 32-bit ARM M-Cortex MCUs" OFF)

    if (TINYGPMP_AVR8 OR TINYGPMP_AVR32)
        set(CMAKE_CXX_COMPILER "avr-g++")
        if (TINYGPMP_AVR8)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__AVR8__")
        elseif(TINYGPMP_AVR32)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__AVR32__")
        endif()

    elseif (TINYGPMP_STM8 OR TINYGPMP_STM32)
        set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
        if (TINYGPMP_STM8)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STM8__")
        elseif(TINYGPMP_STM32)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STM32__")
        endif()
        
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
    endif()

endif()

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

#else()
elseif(NOT BUILD_PYGPMP OR NOT BUILD_TINYGPMP)

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
