![img](https://github.com/akielaries/RM-pkg/blob/main/docs/openMTPK.svg)
--------------------------------------------------------------------------------

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/openMTPK&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/github/license/akielaries/openMTPK?color=23228B22)](https://github.com/akielaries/openMTPK/blob/main/LICENSE)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&utm_medium=referral&utm_content=akielaries/openMTPK&utm_campaign=Badge_Coverage)

# Overview 
**openMTPK** is an open-source (intended) mathematics package written in C++ with a primary
focus on Numbery Theory and Cryptographic algorithms, Linear Algebra, and Machine/Deep learning concepts
as well as a range of language API's for integration with pre-existing projects.
openMTPK is originally inspired from undergraduate coursework and work done on [vpaSTRM](https://github.com/akielaries/vpaSTRM). 
The project welcomes contributors and is in need of mathematics focused/interested programmers
comfortable in C and C++. If interested see 
[here](https://github.com/akielaries/openMTPK/blob/main/CONTRIBUTING.md)!

The goal is to make a reusable mathematics library allowing users to call 
within their own projects. Some of the implementations seen in the package were first prototypes in 
Wolfram Mathetmatica, then translated to C++ for the package.
Look in the [drivers](https://github.com/akielaries/openMTPK/tree/main/drivers) folder for examples 
on using these tools in your own project. 

## API Bindings
As development progresses language bindings will be polished. More languages
such as Julia and MATLAB will be explored in the future.
Language |  Status |
---------|------|
C++17/g++12(core)  | [![cppbuild](https://github.com/akielaries/openMTPK/actions/workflows/build.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
Python v3.x    | [![Py](https://github.com/akielaries/openMTPK/actions/workflows/python.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)|
OCaml v4.13.1  | ![OCaml](https://badgen.net/badge/OCaml/Unstable/yellow?icon=github)|
R v4.2.2       | ![R](https://badgen.net/badge/R/Unstable/yellow?icon=github)|
Julia v1.8.3   | ![Julia](https://badgen.net/badge/Julia%20API/In%20Progress/red?icon=github) |

## Modules
Module | Build Status | 
-------|--------------|
Arithmetic          | [![Arith](https://github.com/akielaries/openMTPK/actions/workflows/arith.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | 
Calculus            | [![Calc](https://github.com/akielaries/openMTPK/actions/workflows/calc.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | 
Linear Algebra      | [![linalg](https://github.com/akielaries/openMTPK/actions/workflows/linalg.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | 
Machine/Deep Learning | [![lin-reg](https://github.com/akielaries/openMTPK/actions/workflows/ml_dl.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
Number Theory       | [![num-theory](https://github.com/akielaries/openMTPK/actions/workflows/numtheory.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | 
Topology/Complex    | ![In Progress](https://badgen.net/badge/TM/In%20Progress/yellow?icon=github) | 

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
[here](https://github.com/akielaries/openMTPK-docs/blob/main/src/openMTPK_paper.pdf)

# Examples
All examples are in the [drivers](https://github.com/akielaries/openMTPK/tree/main/drivers) folder
```
# clone the repo and enter
$ git clone git@github.com:akielaries/openMTPK.git 
$ cd openMTPK

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
#include <string>
#include <openMTPK/number_theory/cipher.hpp>

int main() {
    // declare CIPHER class obj
    Cipher cc;
    
    /* CAESAR CIPHER */
    std::string text0 = "Plaintext";
    int shift_key_0 = 5;
    std::string hashtext_0 = cc.C_cipher(text0, shift_key_0);
    std::cout << "Hashtext0 = " << hashtext_0 << std::endl;
    
    /* TESTING MONOALPHABETIC SUBSTITUION KEYWORD CIPHER */
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
A Python example showing the same functionalities.
```python
#!/usr/bin/python3.10
from openMTPK import Cipher

c = Cipher()
cipertext_0 = c.C_cipher('Plaintext', 5)
print(ciphertext_0)

ciphertext_1 = c.C_cipher('ATTACKATONCE', 4)
print(ciphertext_1)

text = "Password"
shift = "Computer"
encoded_text = c.KC_encode(shift);
hashtext = c.KC_cipher(text, encoded_text);
print(hashtext)
```

# Installation
Requirements are loose and mostly tied to what openMTPK was tested and used on.
* Linux/OSX
* CMake
* g++
```
# clone repo
$ git clone git@github.com:akielaries/openMTPK.git
$ cd oepnMTPK
# create build dir
$ mkdir build && cd build
# create necessary objects and static library
$ cmake ..
$ make
# install necessary headers and library in correct directories
$ sudo make install
```
To test the installation build some of the example drivers in the projects 
[samples](https://github.com/akielaries/openMTPK/tree/main/samples) directory.
```
# compile yourself
$ cd samples
$ g++ cipher.cpp -lopenMTPK -o cipher
$ g++ arith.cpp -lopenMTPK -o arith
# script to test all modules and their drivers
# using the projects root makefile
$ make arith
$ make num-theory
...
```

