# Download and install GoogleTest


include(FetchContent)

#find_package(GTest REQUIRED)

# check if installation is present
#if(NOT GTEST_FOUND)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    #endif()

#FetchContent_MakeAvailable(googletest)

# TODO this could be made dynamic some how?
# source files that will be tested
set(CPP_SOURCES
    ../modules/arithmetic/arith.cpp
    ../modules/calculus/differential.cpp
    ../modules/core/datatable.cpp
    ../modules/core/utils.cpp
    ../modules/disct/graphs.cpp
    ../modules/linalg/mtx.cpp
    ../modules/ml/bayes_clf.cpp
    ../modules/ml/encoder.cpp
    ../modules/ml/mlp_network.cpp
    ../modules/nt/cipher.cpp
    ../modules/nt/rc4.cpp
    ../modules/nt/prime_test.cpp
    ../modules/nt/prime_gen.cpp
    ../modules/nt/factorization.cpp
    ../modules/nt/logarithms.cpp
    ../modules/nt/random.cpp
    ../modules/stats/describe.cpp
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
    nt/t_random.cpp
    core/t_threadpool.cpp
    disct/t_graphs.cpp
)

# Fortran source files to be tested
set(FORTRAN_SOURCES
    ../modules/linalg/mtx_routines.f90
)

# Fortran test file
set(FORTRAN_TEST_FILE
    linalg/t_mtx.f90
)

# create separate executables for C++ and Fortran tests
add_executable(
    test_openGPMP_cpp
    ${FORTRAN_SOURCES}
    ${CPP_SOURCES}
    ${CPP_TEST_FILES}
)

add_executable(
    test_openGPMP_fortran
    ${FORTRAN_SOURCES}
    ${FORTRAN_TEST_FILE}
)

target_compile_options(
    test_openGPMP_cpp
    PRIVATE
    --coverage
    -fprofile-arcs
    -ftest-coverage
    -fPIC
)

target_link_libraries(
    test_openGPMP_cpp
    GTest::gtest_main 
    pthread
    --coverage
    -fprofile-arcs
    -ftest-coverage
    -fPIC
)

target_link_libraries(
    test_openGPMP_fortran
    GTest::gtest_main
    pthread
    -lgfortran
)


include(GoogleTest)
gtest_discover_tests(test_openGPMP_cpp)

# Add a custom target for running the tests
add_custom_target(RUN_CPP_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --bold "[Running C++ Unit Tests]"
    COMMAND test_openGPMP_cpp
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --bold "[Generating Coverage Reports]"
    COMMAND lcov --directory . --capture --output-file lcov.info# --ignore-errors mismatch
    COMMAND lcov --remove lcov.info "*11*" "*/googletest/*" "*tests*" "/usr/*" "/src" "/build" -o lcov.info --ignore-errors unused
    #COMMAND mv lcov.info ../../.coverage

)

add_custom_target(RUN_FORTRAN_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta --bold "[Running Fortran Unit Tests]"
    COMMAND test_openGPMP_fortran
)

add_dependencies(RUN_CPP_TESTS test_openGPMP_cpp)
add_dependencies(RUN_FORTRAN_TESTS test_openGPMP_fortran)
