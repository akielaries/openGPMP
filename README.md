# Overview 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/RM-pkg/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/RM-pkg&amp;utm_campaign=Badge_Grade)
![Codacy Analysis](https://github.com/akielaries/RM-pkg/actions/workflows/codacy.yml/badge.svg) 
![license](https://img.shields.io/github/license/akielaries/RM-pkg?color=%23228B22)

RM-pkg is a <ins>**R**</ins>eusable <ins>**M**</ins>athematics library written in C++ 
originally inspired from Python based coursework for CS 499 Contemporary Developments, 
Deep Learning, as well as work done on [vpaSTRM](https://github.com/akielaries/vpaSTRM). 
The project welcomes contributors and is in extreme need, if interested see 
[here](https://github.com/akielaries/RM-pkg/blob/main/CONTRIBUTING.md)!

The goal is to make a reusable mathematics library similar to the use of 
math.h allowing users to call within their own projects.
Starting with some implementations of basics of different mathematical topics 
like arithmetic, calculus, statistics, linear algebra, etc. in conjunction with more advanced 
algorithms seen in the blend of such topics, branches of Machine Learning, image processing 
and much more. Many of these implementations were first prototypes in Wolfram Mathetmatica, 
then converted to C++ code for the package.
Look in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) folder for examples 
on using these tools in your own project. 

# Modules
These modules are tested by compiling a test driver file with a main() function
against the source `.cpp` file of the respective module, running a suite of afl 
tools against the compiles binaries. To analyze for memory leaks, within the 
Makefile of the project, there are checks using valgrind, for unit testing
I made use of googletest (Google produces some fun OSS), there are suites of 
cases testing each module.


Module | Build Status | Unit Tests | Fuzzing |
-------|--------------|------------|---------|
Arithmetic          | ![Arith](https://github.com/akielaries/RM-pkg/actions/workflows/arith.yml/badge.svg)    | ![Arith](https://github.com/akielaries/RM-pkg/actions/workflows/t_arith.yml/badge.svg) | *Coming Soon* |
Calculus            | ![Calc](https://github.com/akielaries/RM-pkg/actions/workflows/calc.yml/badge.svg)      | *In Progress* | *Coming Soon* |
Linear Algebra      | ![lin-alg](https://github.com/akielaries/RM-pkg/actions/workflows/linalg.yml/badge.svg) | *In Progress* | *Coming Soon* |
Linear Regression   | ![lin-reg](https://github.com/akielaries/RM-pkg/actions/workflows/linreg.yml/badge.svg) | *In Progress* | *Coming Soon* |
Number Theory       | ![num-theory](https://github.com/akielaries/RM-pkg/actions/workflows/numtheory.yml/badge.svg) | *In Progress* | *In Progress* |

> :warning: *These modules will eventually be provided with their own documentation and references 
on the underlying functions used as well as background/history. As development progresses, modules 
are added, and documentation is updated/created, the existing modules be encapsulated by 'suites' 
and the modules within will hold relevance to the overarching suite. As this happens the READEME
will be trimmed down to what modules are shown and references to more in depth documentation on
said modules.*

## Arithmetic
Basic operations of addition, subtraction, multiplication, and division were implemented in a
way to accept `n` arguments of `n` types. Meaning calling any of the respective functions allows
numerous parameters to be passed in of various numeric data type. This acts as the basis for many
of the basic functionalities of this package.

## Calculus
### Differential
The derivative of a function of a real variable measures the sensitivity to change of the function value 
(output value) with respect to a change in its argument (input value). For example, the derivative of the 
position of a moving object with respect to time is the object's velocity: this measures how quickly the 
position of the object changes when time advances.

## Linear Algebra
### Vector Operations
#### Vector Addition
Two vectors of the same size can be added together by adding the corresponding elements, to form another 
vector of the same size, called the sum of the vectors. Vector addition is denoted by the symbol +. 
(Thus the symbol + is overloaded to mean scalar addition when scalars appear on its left- and right-hand 
sides, and vector addition when vectors appear on its left- and right-hand sides.)
#### Vector/Scalar Multiplication
Another operation is scalar multiplication or scalar-vector multiplication, in which a vector is multiplied 
by a scalar (i.e., number), which is done by multiplying every element of the vector by the scalar. Scalar 
multiplication is denoted by juxtaposition, typically with the scalar on the left.

## Number Theory
A branch of pure mathematics with applications in cryptography, phyics, others areas of computation, etc. 
that primarily deals with the study of integers, integer valued functions, prime numbers, as well as 
the attributes and properties made from integers and their functions. This topic of mathematics is quite
theoretical and is difficult to view the applications in a comprehensible sense. Beyond the basics of 
Number Theory, this module will also focus on encryption algorithms.

### Cryptography
#### Caesar Cipher
#### Monoalphabetic Substitution Keyword Cipher
#### Rivest Cipher 2 (RC2) Encryption Algorithm
#### Rivest Cipher 4 (RC4) Encryption Algorithm
A stream cipher algorithm created by Ron Rivest (creator of RSA) previously declared insecure. RC4 generates a pseudorandom 
stream of bits (a keystream). As with any stream cipher, these can be used for encryption by combining it with the plaintext 
using bitwise exclusive or; decryption is performed the same way (since exclusive or with given data is an involution). This 
is similar to the one-time pad, except that generated pseudorandom bits, rather than a prepared stream, are used.
To generate the keystream, the cipher makes use of a secret internal state which consists of two parts:

1. A permutation of all 256 possible bytes (denoted "S" below).
2. Two 8-bit index-pointers (denoted "i" and "j").
The permutation is initialized with a variable-length key, typically between 40 and 2048 bits, using the key-scheduling 
algorithm (KSA). Once this has been completed, the stream of bits is generated using the pseudo-random generation algorithm (PRGA).
### Rivest Cipher 5 (RC5) Encryption Algorithm
### Rivest Cipher 6 (RC6) Encryption Algorithm

## Deep Learning
### Linear Regression
A linear approach for modelling the relationship between a scalar response and one or more explanatory variables 
(also known as dependent and independent variables). In linear regression, the relationships are modeled using 
linear predictor functions whose unknown model parameters are estimated from the data. Such models are called linear models.

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

# Run Examples
So far I have only been able to create semi-working example using basic arithmetic operations, 
calculus operations such as simple derivatives as well as Linear-Regression. Within many of the
driver examples the use of `printf()` over `std::cout` is often used for easier and more readable 
displaying of our values. 
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

# compile + run the RC4 Encryption Algo example from the Number Theory Module
$ make num-theory

# to remove the generated binaries
$ make clean
```
As I progress through different mathematical operations I will provide more 
examples as driver files in drivers folder with some corresponding 
documentation. 

# Future
* fuzzing /num theory module
* test custom crypto algo 
* open src algos, interpolate?
* lateral development on this is ideal but for sanity stick to math related to school / work
