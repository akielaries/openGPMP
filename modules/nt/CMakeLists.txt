set(the_description "Number Theory Module")

message("-- Including Number Theory Module")

set(SOURCE_FILES
    cipher.cpp
    factorization.cpp
    logarithms.cpp
    prime_gen.cpp
    prime_test.cpp
    redpike.cpp
    rc4.cpp
    rc5.cpp
    rc6.cpp
    random.cpp
)

if (SIMD_ISA STREQUAL "AVX2" OR SIMD_ISA STREQUAL "SSE")
    list(APPEND SOURCE_FILES
        sse_sieve_erat.S
    )  

endif()

add_library(nt OBJECT ${SOURCE_FILES})


