set(the_description "Statistics Module")

message("-- Including Statistics Module")

set(SOURCE_FILES
    describe.cpp
    probdist.cpp
    hypothesis.cpp
    resampling.cpp
    cdfs.cpp
    pdfs.cpp
)

add_library(stats OBJECT ${SOURCE_FILES})

