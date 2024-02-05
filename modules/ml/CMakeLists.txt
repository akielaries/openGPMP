set(the_description "Machine Learning Module")

message("-- Including Machine Learning Module")
message("--   [NOTE] : Relies on Linear Algebra Module")

set(SOURCE_FILES
    encoder.cpp
    bayes_clf.cpp
    linreg.cpp
    mlp_network.cpp
    kohonen_net.cpp
    knn.cpp
    kfold.cpp
)

add_library(ml OBJECT ${SOURCE_FILES})

