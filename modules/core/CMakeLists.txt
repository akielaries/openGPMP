set(the_description "Core Module")

message("-- Including Core Module")

set(SOURCE_FILES
    datatable.cpp
    utils.cpp
)

add_library(core OBJECT ${SOURCE_FILES})

