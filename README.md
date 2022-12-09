# Overview 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/RM-pkg/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/RM-pkg&amp;utm_campaign=Badge_Grade)
![Codacy Analysis](https://github.com/akielaries/RM-pkg/actions/workflows/codacy.yml/badge.svg) 
![license](https://img.shields.io/github/license/akielaries/RM-pkg?color=%23228B22)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/RM-pkg/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/RM-pkg&amp;utm_campaign=Badge_Coverage)

RM-pkg is a <ins>**R**</ins>eusable <ins>**M**</ins>athematics library written in C++ 
originally inspired from Python based coursework for CS 499 Contemporary Developments, 
Deep Learning, as well as work done on [vpaSTRM](https://github.com/akielaries/vpaSTRM). 
The project welcomes contributors and is in need of mathematics focused/interested programmers
comfortable in C and C++. If interested see 
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

# Programming Language API Bindings
The goal of this project is to also develop as unilaterally as possible, so as I develop the modules
for RM-pkg, the programming language bindings will come along with it. Perhaps other languages will
be explored.
Language | Tool | Status |
---------|------|--------|
Python   | Swig |![PyBuild](https://github.com/akielaries/RM-pkg/actions/workflows/python.yml/badge.svg)|
Julia    | TBD  | TBD    |

# Modules

Module | Build Status | 
-------|--------------|
Arithmetic          | ![Arith](https://github.com/akielaries/RM-pkg/actions/workflows/arith.yml/badge.svg)    | 
Calculus            | ![Calc](https://github.com/akielaries/RM-pkg/actions/workflows/calc.yml/badge.svg)      | 
Linear Algebra      | ![lin-alg](https://github.com/akielaries/RM-pkg/actions/workflows/linalg.yml/badge.svg) | 
Machine/Deep Learning | ![lin-reg](https://github.com/akielaries/RM-pkg/actions/workflows/ml_dl.yml/badge.svg) |
Number Theory       | ![num-theory](https://github.com/akielaries/RM-pkg/actions/workflows/numtheory.yml/badge.svg) | 
Topology/Complex    | ![complex](https://github.com/akielaries/RM-pkg/actions/workflows/complex.yml/badge.svg) | 

### Testing
RM-pkg makes use of a few methods of testing. Unit testing + fuzzing is done with the help of Google's 
[googletest](https://github.com/google/googletest) and [AFL](https://github.com/google/afl),
but mostly the up to date fuzzer [AFL++](https://github.com/AFLplusplus/AFLplusplus).

#### Unit Testing Coverage
Status |
-------|
![RM-pkg](https://github.com/akielaries/RM-pkg/actions/workflows/codecov.yml/badge.svg) |
![img](https://codecov.io/gh/akielaries/RM-pkg/branch/main/graphs/sunburst.svg?token=KJBGLP8DYJ) |

#### Fuzzing
*Coming Soon...*

#### Details
1. Arithmetic
2. Calculus
   - Differential
   - Integral
3. Linear Algebra
   - Vector Operations
   - Matrix Operations
4. Machine/Deep Learning
   - Linear Regression
   - Cross-Validation
   - K-Nearest Neighbors
5. Number Theory
   - Primes
   - Cryptography

More documentation on the modules can be seen in the research-formatted LaTeX paper I had made 
[here](https://github.com/akielaries/RMdocs/blob/main/src/RM-pkg_paper.pdf)

# Examples
All examples are in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) folder
```
# clone the repo and enter
$ git clone git@github.com:akielaries/RM-pkg.git 
$ cd RM-pkg

# to run all examples 
$ ./all.sh

# to remove the generated binaries
$ make clean-mods

# run unit tests and other checking methods
$ make run-tests

# clean up generated test files
$ make clean-tests
```

Example C++ driver file for running Caesar Cipher & Mono-Alphabetic Substitution
Keyword cipher:
``` cpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <RM-pkg/number_theory/cipher.hpp>

int main() {
    // declare CIPHER class obj
    CIPHER cc;
    
    /* TESTING CAESAR CIPHER */
    std::string text0 = "Plaintext";
    int shift_key_0 = 5;
    std::string hashtext_0 = cc.C_cipher(text0, shift_key_0);
    std::cout << "Hashtext0 = " << hashtext_0 << std::endl;
    
    std::string text1 = "ATTACKATONCE";
    int shift_key_1 = 4;
    std::string hashtext_1 = cc.C_cipher(text1, shift_key_1);
    std::cout << "Hashtext1 = " << hashtext_1 << std::endl; 

    /* TESTING MONOALPHABETIC SUBSTITUION KEYWORD CIPHER */
    std::cout << "\nMONOALPHABETIC SUBSTITUION KEYWORD CIPHER EXAMPLE\n\n";

    std::string shift_key_2 = "Computer";
    std::string text2 = "Password";
    // encode the plaintext
    std::string encoded_text = cc.KC_encode(shift_key_2);
    // call the cipher function
    std::string hashtext_2 = cc.KC_cipher(text2 , encoded_text);
    
    std::cout << "Hashtext2 = " << hashtext_2 << std::endl;

    return 0;
}
```
As I progress through different mathematical operations I will provide more 
examples as driver files in drivers folder with some corresponding 
documentation. 

# Installation
## Dependencies
The use of `libxbgi` graphics library is seen in some modules of this project for
visualization of different mathematical algorithms such as Mandelbrot Fractal Sets.
To install this library simply run the dependencies.sh shell script
```
./dependencies.sh
```

For now there is not much use of this package unless you wanted to include the 
definition + implementation files in your own project with a little modification.
The use of Makefiles + shell scripts to compile modules, tests, clean generated files,
and more for development purposes. When the package reaches a *publishable state*, I 
will create an installation process with CMake compiling the source files into a clean
object for your standard directories with callable headers in `usr/include`. Since I 
use Linux as my main development environment, installation instructions will make the 
assumption you are using the same. Builds/tests for OSX will also be in development in
later stages.

# Future
* fuzzing /num theory module
* test custom crypto algo 
* open src algos, interpolate?
* lateral development on this is ideal but for sanity stick to math related to school / work
