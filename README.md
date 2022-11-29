# Overview 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/RM-pkg/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/RM-pkg&amp;utm_campaign=Badge_Grade)
![Codacy Analysis](https://github.com/akielaries/RM-pkg/actions/workflows/codacy.yml/badge.svg) 
![license](https://img.shields.io/github/license/akielaries/RM-pkg?color=%23228B22)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/RM-pkg/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/RM-pkg&amp;utm_campaign=Badge_Coverage)

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

Module | Build Status | 
-------|--------------|
Arithmetic          | ![Arith](https://github.com/akielaries/RM-pkg/actions/workflows/arith.yml/badge.svg)    | 
Calculus            | ![Calc](https://github.com/akielaries/RM-pkg/actions/workflows/calc.yml/badge.svg)      | 
Linear Algebra      | ![lin-alg](https://github.com/akielaries/RM-pkg/actions/workflows/linalg.yml/badge.svg) | 
Linear Regression   | ![lin-reg](https://github.com/akielaries/RM-pkg/actions/workflows/linreg.yml/badge.svg) |
Number Theory       | ![num-theory](https://github.com/akielaries/RM-pkg/actions/workflows/numtheory.yml/badge.svg) | 

> :warning: *These modules will eventually be provided with their own documentation and references 
on the underlying functions used as well as background/history. As development progresses, modules 
are added, and documentation is updated/created, the existing modules will be encapsulated by 'suites' 
and the modules within will hold relevance to the overarching suite. As this happens the READEME
will be trimmed down to what modules are shown and references to more in depth documentation on
said modules.*

### Testing
RM-pkg makes use of a few methods of testing. Unit testing + fuzzing is done with the help of Google's 
[googletest](https://github.com/google/googletest) and [AFL](https://github.com/google/afl),
but mostly the up to date fuzzer [AFL++](https://github.com/AFLplusplus/AFLplusplus).

#### Unit Testing Coverage
Status |
-------|
![RM-pkg](https://github.com/akielaries/RM-pkg/actions/workflows/RM-pkg.yml/badge.svg) |
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

More documentation on the modules can be seen in the documentation I had made here: https://github.com/akielaries/RMdocs

# Examples
All examples are in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) folder
```
# clone the repo and enter
$ git clone git@github.com:akielaries/RM-pkg.git 
$ cd RM-pkg

# to run all examples 
$ ./all-modules.sh

# compile + run the arithmetic operation example using the provided Makefile
$ make arith

# compile + run derivative operations example 
$ make calculus

# compile + run the Linear-Regression example 
$ make lin-reg

# compile + run the RC4 Encryption Algo example from the Number Theory Module
$ make num-theory

# to remove the generated binaries
$ make clean-mods

# run unit tests and other checking methods
$ make run-tests

# clean up generated test files
$ make clean-tests
```

Example driver file for running Caesar Cipher & Mono-Alphabetic Substitution
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
