set(the_description "Machine Learning Module")

set(SOURCE_FILES
    linreg.cpp
    mlp_network.cpp
)

add_library(ml OBJECT ${SOURCE_FILES})

