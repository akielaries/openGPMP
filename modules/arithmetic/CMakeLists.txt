set(the_description "Arithmetic Module")
message("-- Including Arithmetic Module")

set(SOURCE_FILES
    arith.cpp
)

add_library(arithmetic OBJECT ${SOURCE_FILES})


