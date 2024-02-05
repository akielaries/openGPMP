set(the_description "Optimization Module")

message("-- Including Optimization Module")

set(SOURCE_FILES
    function.cpp
)

add_library(optim OBJECT ${SOURCE_FILES})

