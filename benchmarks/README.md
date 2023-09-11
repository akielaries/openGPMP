# Benchmarks (TODO)
This folder aims to show comparisons in openGPMP's methods vs more populare
and widely used packages accomlishing similar tasks. Machine Learning
related methods againsts Scikit-learn's pre-built modules, as well as
speed/effeciency on diverse datasets. Linear Algebra related methods will
be compared against Armadillo and Eigen. NTL for Number Theory methods and 
ther methods of testing will be implemented along the way.

Benchmarks performed on Intel SkyLake CPU

Linear Algebra Module: 
Matrix Addition 8192 elements

openGPMP: ~430ms
Armadillo: ~1000ms
Eigen: ~1950ms

