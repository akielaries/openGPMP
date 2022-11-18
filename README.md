![BuildTest](https://github.com/akielaries/RM-pkg/actions/workflows/build.yml/badge.svg)
![Arith](https://github.com/akielaries/RM-pkg/actions/workflows/arith.yml/badge.svg)
![Calc](https://github.com/akielaries/RM-pkg/actions/workflows/calc.yml/badge.svg)
![lin-reg](https://github.com/akielaries/RM-pkg/actions/workflows/linreg.yml/badge.svg)

# Overview (Work In Progress)
RM-pkg is a <ins>**R**</ins>eusable <ins>**M**</ins>athematics library written in C++ 
originally inspired from Python based coursework for CS 499 Contemporary Developments, 
Deep Learning, as well as work done on [vpaSTRM](https://github.com/akielaries/vpaSTRM). 
The project welcomes contributes and is in extreme need, if interested see 
[here](https://github.com/akielaries/RM-pkg/blob/main/CONTRIBUTING.md)!

The goal is to make a reusable mathematics library similar to the use of 
math.h allowing users to call within their own projects.
Starting with some implementations of basics of different mathematical topics 
like arithmetic, calculus, statistics, linear algebra, etc. in conjunction with more advanced 
algorithms seen in the blend of such topics, branches of Machine Learning, image processing 
and much more. 
Look in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) folder for examples 
on using these tools in your own project. 

# Run Examples
So far I have only been able to create semi-working example using basic arithmetic operations, 
calculus operations such as simple derivatives as well as Linear-Regression.
All examples are in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) folder
```
# clone the repo and enter
$ git clone git@github.com:akielaries/RM-pkg.git 
$ cd RM-pkg

# to run all examples 
$ ./test.sh

# compile + run the arithmetic operation example using the provided Makefile
$ make arith

# compile + run derivative operations example 
$ make calculus

# compile + run the Linear-Regression example 
$ make lin-reg

# to remove the generated binaries
$ make clean
```
As I progress through different mathematical operations I will provide more 
examples as driver files in drivers folder with some corresponding 
documentation. 

# Modules
## Arithmetic
Basic operations of addition, subtraction, multiplication, and division were implemented in a
way to accept `n` arguments of `n` types. Meaning calling any of the respective functions allows
numerous parameters to be passed in of various numeric data type. This acts as the basis for many
of the basic functionalities of this package.

## Calculus
## Statistics
## Linear Algebra
### Vector Operations

## Deep Learning
### Cross Validation
A resampling technique, the idea of this method is to train our model by utilizing 
the subsets of our data set then proceeding to evaluate + compare against the original.
Essentially, use some part(s) of the data set for training, other part(s) for testing.

#### K-Fold Cross Validation
Split our data into a `k` number of subsets also called folds, and perform
training/learning on the subsets leaving one `(k - 1)` for the final evaluation of 
the trained model. The method involves iterating `k` number of times using a different
fold each time for testing against.


.......
