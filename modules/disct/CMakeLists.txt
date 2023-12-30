set(the_description "Discrete Mathematics Module")

message("-- Including Discrete Mathematics Module")

set(SOURCE_FILES
    graphs.cpp
)


add_library(disct OBJECT ${SOURCE_FILES})


