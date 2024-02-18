include(FetchContent)

find_package(GTest QUIET)

message(STATUS "Detecting GoogleTest")
if(NOT GTest_FOUND)
    message(STATUS "GoogleTest not found")
    message(STATUS "Fetching GoogleTest")
    # If GoogleTest is not found, fetch and build it
    include(FetchContent)
    FetchContent_Declare(
        googletest
        #URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        URL https://github.com/google/googletest/archive/b75ecf1bed2fcd416b66c86cb6fe79122abf132e.zip
    )
    FetchContent_MakeAvailable(googletest)
    message(STATUS "Fetching GoogleTest - done")

else()
    message(STATUS "GoogleTest found")
endif()

message(STATUS "Detecting GoogleTest - done")

# Define the libraries you want to test
set(LIBRARIES_TO_TEST
    arithmetic
    calculus
    disct
    linalg
    core
    ml
    nt
    optim
    stats
)

# C++ test files
set(CPP_TEST_FILES
    arith/t_arith.cpp
    calc/t_calc.cpp
    core/t_threadpool.cpp
    disct/t_graphs.cpp
    linalg/t_eigen.cpp
    linalg/t_linsys.cpp
    
    linalg/t_matrix_vector_i32.cpp
    linalg/t_matrix_vector_f64.cpp

    linalg/t_matrix_arr_i8.cpp
    linalg/t_matrix_arr_i16.cpp
    linalg/t_matrix_arr_i32.cpp
    linalg/t_matrix_arr_f64.cpp
    
    linalg/t_vector_vector_f64.cpp
    linalg/t_vector_vector_i8.cpp
    linalg/t_vector_vector_i32.cpp

    linalg/t_vector_vector_naive.cpp
    linalg/t_matrix_arr_naive.cpp

    nt/t_cipher.cpp
    nt/t_rc4.cpp
    nt/t_primes.cpp
    nt/t_factorization.cpp
    nt/t_logarithms.cpp
    nt/t_random.cpp
    optim/t_function.cpp
    optim/t_quasi.cpp
    stats/t_describe.cpp
    stats/t_probdist.cpp
)

# Fortran source files to be tested
set(FORTRAN_SOURCES
    ../modules/linalg/mtx_routines.f90
)

# Fortran test file
set(FORTRAN_TEST_FILES
    linalg/t_mtx.f90
)

# create separate executables for C++ and Fortran tests
add_executable(
    test_openGPMP_cpp
    ${CPP_TEST_FILES}
)

add_executable(
    test_openGPMP_fortran
    ${FORTRAN_TEST_FILES}
)

foreach(library ${LIBRARIES_TO_TEST})
    target_link_libraries(test_openGPMP_cpp ${library})
    target_link_libraries(test_openGPMP_fortran ${library})

    target_compile_options(${library} PRIVATE --coverage -fprofile-arcs -ftest-coverage -fPIC)

endforeach()

target_compile_options(
    test_openGPMP_cpp
    PRIVATE
    --coverage
    -fprofile-arcs
    -ftest-coverage
    -fPIC
)

target_compile_options(
    test_openGPMP_fortran 
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
    --coverage
    -fprofile-arcs
    -ftest-coverage
    -fPIC
)

include(GoogleTest)
gtest_discover_tests(test_openGPMP_cpp)

# Add a custom target for running the tests
add_custom_target(RUN_CPP_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --bold "[Running C++ Unit Tests]"
    COMMAND test_openGPMP_cpp
)
message(STATUS "Detecting lcov")

# Find lcov
find_program(LCOV lcov)
option(BUILD_COV "Generate coverage reports" OFF)

if(LCOV)
    if(BUILD_COV)
    add_custom_command(TARGET RUN_CPP_TESTS POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan --bold "[Generating Coverage Reports]"
        COMMAND lcov --directory .. --capture --output-file lcov.info --rc geninfo_unexecuted_blocks=1 #--ignore-errors mismatch,mismatch
        COMMAND lcov --remove lcov.info "*c++*" "*11*" "*/googletest/*" "*/gtest*" "/usr/*" "/src" "/build" -o lcov.info --ignore-errors unused
        COMMAND mv lcov.info ../../.coverage
    )
    endif()
else()
    message(STATUS "lcov not found. Coverage reports will not be generated")
endif()

message(STATUS "Detecting lcov - done")

add_custom_target(RUN_FORTRAN_TESTS
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green "[==========]"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta --bold "[Running Fortran Unit Tests]"
    COMMAND test_openGPMP_fortran
)

add_dependencies(RUN_CPP_TESTS test_openGPMP_cpp)
add_dependencies(RUN_FORTRAN_TESTS test_openGPMP_fortran)
