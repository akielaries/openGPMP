set(the_description "Number Theory Module")

message("-- Including Number Theory Module")
message("--   [NOTE] : Relies on Arithmetic Module")

set(SOURCE_FILES
    cipher.cpp
    factorization.cpp
    logarithms.cpp
    prime_gen.cpp
    prime_test.cpp
    rc4.cpp
    random.cpp
)


add_library(nt OBJECT ${SOURCE_FILES})


