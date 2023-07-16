# Benchmarks (TODO)
The term benchmarks really means documented comparisons in this case.
This folder aims to show comparisons in openGPMP's Machine Learning
related methods againsts Scikit-learn's pre-built modules, as well as
speed/effeciency on diverse datasets. Other methods of testing will be
implemented along the way.

Benchmarks performed on Intel SkyLake CPU

Linear Algebra Module: 
Matrix Addition 8192 elements

openGPMP: ~430ms
Armadillo: ~1000ms
Eigen: ~1950ms

