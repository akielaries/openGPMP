# Download and install GoogleTest


include(FetchContent)

find_package(GTest REQUIRED)

# check if installation is present
#if(NOT GTEST_FOUND)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    #endif()

#FetchContent_MakeAvailable(googletest)


# source files that will be tested 
set(TEST_SOURCES
    ../modules/arithmetic/arith.cpp
    ../modules/calculus/deriv.cpp
    ../modules/nt/cipher.cpp
    ../modules/nt/rc4.cpp
    ../modules/nt/primes.cpp

)

# test files
set(TEST_FILES
    arith/t_arith.cpp
    calc/t_calc.cpp
    nt/t_cipher.cpp
    nt/t_rc4.cpp
    nt/t_primes.cpp
)

# create executable
add_executable(
    test_openMTPK 
    ${TEST_SOURCES}
    ${TEST_FILES}
)

# enable testing
enable_testing()

# link the libraries together with the test binary
target_link_libraries(
    test_openMTPK 
    GTest::gtest_main 
    pthread

)

include(GoogleTest)
gtest_discover_tests(test_openMTPK)

# Add a custom target for running the tests
add_custom_target(check COMMAND test_openMTPK)

