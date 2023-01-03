# Download and install GoogleTest
include(ExternalProject)
ExternalProject_Add(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           main
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)

# TESTS
add_executable(test_openMTPK arith/t_arith.cpp)

# use googletest
add_dependencies(test_openMTPK gtest)
include_directories(${source_dir}/include)
target_link_libraries(test_openMTPK openMTPK gtest gtest_main pthread)

#target_link_libraries(test_openMTPK ${binary_dir}/libgtest_main.a)


enable_testing()

add_test(NAME    test_openMTPK
         COMMAND test_openMTPK)



