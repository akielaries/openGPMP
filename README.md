![](https://raw.githubusercontent.com/akielaries/openMTPK/139970427fb9092a12ccc87e736186b32316d46f/docs/openMTPK.svg)
--------------------------------------------------------------------------------

![Version](https://img.shields.io/github/v/release/akielaries/openMTPK?color=%23BF40BF)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/openMTPK&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/github/license/akielaries/openMTPK?color=23228B22)](https://github.com/akielaries/openMTPK/blob/main/LICENSE)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&utm_medium=referral&utm_content=akielaries/openMTPK&utm_campaign=Badge_Coverage)
![clones](https://raw.githubusercontent.com/akielaries/openMTPK/traffic/traffic-openMTPK/clones.svg)
[![PyPi](https://img.shields.io/pypi/v/openmtpk.svg)](https://pypi.python.org/pypi/openmtpk)
[![Py](https://github.com/akielaries/openMTPK/actions/workflows/openmtpk.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)

# Overview
**openMTPK** is an open-source (intended) mathematics package written in C++ with a primary
focus on Numbery Theory and Cryptographic algorithms, Linear Algebra, and Machine/Deep learning concepts
as well as a range of language API's. openMTPK aims to provide options for pre-built functions, models, etc.
along with modularity for user freedom.
Look in the [samples](https://github.com/akielaries/openMTPK/tree/main/samples) folder for examples 
on how to use some of openMTPK's functionalities. 


# Installation
openMTPK C++ & Python is tested on the following:
| OS    | Architecture | Status |
|-------|--------------|--------|
OSX Monterey 12.6.3 | x86 | [![darwin](https://github.com/akielaries/openMTPK/actions/workflows/build_osx.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | 
RasPi OS | ARMv6/v7 | [![cppRPi](https://github.com/akielaries/openMTPK/actions/workflows/cpp_rpi.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
| bullseye 11.6 | ARMv6        | [![arm6CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV6cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      | 
| ubuntu 22.10 | ARMv7        | [![arm7CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV7cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      | 
| ubuntu 22.10 | ARMv8        | [![arm8CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV8cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      | [![arm8Py](https://github.com/akielaries/openMTPK/actions/workflows/ARMV8py.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      |
| ubuntu 22.10 | RISCV64      | [![riscCPP](https://github.com/akielaries/openMTPK/actions/workflows/RISCVcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      | [![riscPy](https://github.com/akielaries/openMTPK/actions/workflows/RISCVpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)      |
| ubuntu 22.10 | S390X        | [![s390xCPP](https://github.com/akielaries/openMTPK/actions/workflows/S390Xcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)     | [![s390xPy](https://github.com/akielaries/openMTPK/actions/workflows/S390Xpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)     |
| ubuntu 22.10 | PPC64LE      | [![ppc64leCPP](https://github.com/akielaries/openMTPK/actions/workflows/PPC64LEcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![ppc64lePy](https://github.com/akielaries/openMTPK/actions/workflows/PPC64LEpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
> **Note** Testing on Apple specific hardware (M1, M2) is in progress. 

## Python
To install the Python interface, use the pip package manager and run the following, `pip install
openmtpk`. Additional hardware support is available with [SWIG](https://github.com/swig/swig) as a dependency for the pip 
installation.

## Build from source
* Linux/OSX
* CMake >=v3.24 (build from source for latest version)
* C++20
* g++12

```
# clone repo
$ git clone git@github.com:akielaries/openMTPK.git
$ cd openMTPK
# create build dir
$ mkdir build && cd build
# create necessary objects and static library
$ cmake -S ..
$ make
# install necessary headers and library in correct directories
$ sudo make install
```

> **Note**
> Keep the build directory for easy uninstallation. This process asumes your 
> STDLIB path is /usr/local/lib, where most 3rd-party libs are located if not, 
> run the following:

```
$ LD_LIBRARY_PATH=/usr/local/lib
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
$ cd scripts && ./all.sh
```

To uninstall files related to openMTPK, simply run the following:

```
# enter the build dir from installation
$ cd build
$ sudo make uninstall
```

## Modules

During early stages, modules will be developed in breadth while focusing on depth
in later stages of the `PRE-V1.0.0` phase. The modules below are all in progress.

1. Arithmetic
2. Calculus
   - Differential
3. Linear Algebra
   - Vector Operations
   - Matrix Operations
4. Machine/Deep Learning
   - Regression
   - Cross-Validation
   - K-Nearest Neighbors
   - Neural Networks
   - Classifiers
5. Number Theory
   - Primes
   - Cryptography
6. Topology/Complex
   - Dynamical Systems
   - Topology
   - Spline

For more details view the project [documentation](https://akielaries.github.io/openMTPK/).


# Examples

View the simple examples on how to use some of the modules in different languages [here](https://github.com/akielaries/openMTPK/tree/main/samples).

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

```cpp
#include <iostream>
#include <string>
// include the number theory module header
#include <openMTPK/number_theory.hpp>

int main() {
    // declare CIPHER class obj
    mtpk::Cipher cc;

    /* CAESAR CIPHER */
    std::string text0 = "Plaintext";
    int shift_key_0 = 5;
    std::string hashtext_0 = cc.caesar(text0, shift_key_0);
    std::cout << "Hashtext0 = " << hashtext_0 << std::endl;

    /* TESTING MONOALPHABETIC SUBSTITUION KEYWORD CIPHER */
    std::string shift_key_2 = "Computer";
    std::string text2 = "Password";
    // encode the plaintext
    std::string encoded_text = cc.keyword_encode(shift_key_2);
    // call the cipher function
    std::string hashtext_2 = cc.keyword(text2 , encoded_text);

    std::cout << "Hashtext2 = " << hashtext_2 << std::endl;

    return 0;
}
```


A Python example showing the same functionalities.

```python
#!/usr/bin/python3
# import the Number Theory module
from openmtpk import nt

c = Cipher()
ciphertext_0 = c.caesar('Plaintext', 5)
print(ciphertext_0)

ciphertext_1 = c.caesar('ATTACKATONCE', 4)
print(ciphertext_1)

text = "Password"
shift = "Computer"
encoded_text = c.keyword_encode(shift);
hashtext = c.keyword(text, encoded_text);
print(hashtext)
```

