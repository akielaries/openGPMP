set(the_description "Number Theory Module")

set(SOURCE_FILES
    cipher.cpp
    factorization.cpp
    logarithms.cpp
    prime_gen.cpp
    prime_test.cpp
    rc4.cpp
)


add_library(nt OBJECT ${SOURCE_FILES})


