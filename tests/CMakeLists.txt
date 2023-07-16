# Download and install GoogleTest
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    message("-- Googletest not found, installing...")
    # GoogleTest not found, download and install it
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )
    FetchContent_MakeAvailable(googletest)
    
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()
    
    # Set GTest variables after downloading and installing
    set(GTest_INCLUDE_DIRS ${googletest_SOURCE_DIR}/include)
    set(GTest_LIBRARIES gtest_main)
else()
    message("-- Googletest found")
endif()




set(CPP_SOURCES
    ../modules/arithmetic/arith.cpp
    ../modules/calculus/differential.cpp
    ../modules/linalg/mtx.cpp
    ../modules/nt/cipher.cpp
    ../modules/nt/rc4.cpp
    ../modules/nt/prime_test.cpp
    ../modules/nt/prime_gen.cpp
    ../modules/nt/factorization.cpp
    ../modules/nt/logarithms.cpp
)

# C++ test files
set(CPP_TEST_FILES
    arith/t_arith.cpp
    calc/t_calc.cpp
    linalg/t_matrix.cpp
    nt/t_cipher.cpp
    nt/t_rc4.cpp
    nt/t_primes.cpp
    nt/t_factorization.cpp
    nt/t_logarithms.cpp
    core/t_threadpool.cpp
)

set(FORTRAN_SOURCES
    ../modules/linalg/mtx.f90
)

# Fortran test file
set(FORTRAN_TEST_FILE
    linalg/t_mtx.f90
)

# create separate executables for C++ and Fortran tests
add_executable(
    test_openGPMP_cpp
    ${CPP_SOURCES}
    ${CPP_TEST_FILES}
)

add_executable(
    test_openGPMP_fortran
    ${FORTRAN_SOURCES}
    ${FORTRAN_TEST_FILE}
)

target_link_libraries(
    test_openGPMP_cpp
    GTest::gtest_main 
    pthread
)
target_link_libraries(
    test_openGPMP_fortran
    GTest::gtest_main
    pthread
)


include(GoogleTest)
gtest_discover_tests(test_openGPMP_cpp)

# Add a custom target for running the tests
add_custom_target(RUN_CPP_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --bold "[Running C++ Unit Tests]"
    COMMAND test_openGPMP_cpp
)

add_custom_target(RUN_FORTRAN_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta --bold "[Running Fortran Unit Tests]"
    COMMAND test_openGPMP_fortran
)

add_dependencies(RUN_CPP_TESTS test_openGPMP_cpp)
add_dependencies(RUN_CPP_TESTS test_openGPMP_fortran)

