set(the_description "Calculus Module")

message("-- Including Calculus Module")

set(SOURCE_FILES
    differential.cpp

)
add_library(calculus OBJECT ${SOURCE_FILES})

