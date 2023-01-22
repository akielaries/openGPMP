![](https://raw.githubusercontent.com/akielaries/openMTPK/139970427fb9092a12ccc87e736186b32316d46f/docs/openMTPK.svg)
--------------------------------------------------------------------------------

![Version](https://img.shields.io/github/v/release/akielaries/openMTPK?color=%23BF40BF)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/openMTPK&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/github/license/akielaries/openMTPK?color=23228B22)](https://github.com/akielaries/openMTPK/blob/main/LICENSE)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openMTPK/dashboard?utm_source=github.com&utm_medium=referral&utm_content=akielaries/openMTPK&utm_campaign=Badge_Coverage)
![clones](https://raw.githubusercontent.com/akielaries/openMTPK/traffic/traffic-openMTPK/clones.svg)
[![PyPi](https://img.shields.io/pypi/v/openmtpk.svg)](https://pypi.python.org/pypi/openmtpk)
[![Py](https://github.com/akielaries/openMTPK/actions/workflows/pypi.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)
# Overview

**openMTPK** is an open-source (intended) mathematics package written in C++ with a primary
focus on Numbery Theory and Cryptographic algorithms, Linear Algebra, and Machine/Deep learning concepts
as well as a range of language API's for integration with pre-existing projects.
openMTPK is originally inspired from undergraduate coursework and work done on [vpaSTRM](https://github.com/akielaries/vpaSTRM). 
The project welcomes contributors and is in need of mathematics focused/interested programmers
comfortable in C and C++. If interested see 
[here](https://github.com/akielaries/openMTPK/blob/main/CONTRIBUTING.md)!

The goal is to make a reusable mathematics library allowing users to call 
within their own projects. A few of the implementations seen in the package were first prototypes in 
Wolfram Mathetmatica, then translated to C then C++ for the package.
Look in the [samples](https://github.com/akielaries/openMTPK/tree/main/samples) folder for examples 
on how to use some of openMTPK's functionalities. 

## APIs

As development progresses language bindings will be polished. More languages will be explored in the future.
The primary goal of creating bindings for other languages is to provide some level of abstraction from the
source C++ code. However, it also serves to integrate this package into pre-existing projects in perhaps 
different target languages. The focus on APIs early on was to start the process while the codebase was of 
manageable size allowing for modularity with new developments and injecting into the language binding 
simultaneously.

The tables below highlight the supported kernel/hardware families across the different
language bindings. By default openMTPK offers support for Linux and Darwin x86 machines,
Apple's M1 is yet to be tested. 

Language |  Linux x86 | Darwin x86 | RPi 3/4 ARMv8 |
---------|------------|------------|---------------|
C++20(core)  | [![linux](https://github.com/akielaries/openMTPK/actions/workflows/build_nix.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![darwin](https://github.com/akielaries/openMTPK/actions/workflows/build_osx.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![cppRPi](https://github.com/akielaries/openMTPK/actions/workflows/cpp_rpi.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
Python v3.x    | [![PyNix](https://github.com/akielaries/openMTPK/actions/workflows/py_nix.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)| [![PyDarwin](https://github.com/akielaries/openMTPK/actions/workflows/py_osx.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/)| [![RPi](https://github.com/akielaries/openMTPK/actions/workflows/py_rpi.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
R v4.2.2       | ![R](https://badgen.net/badge/R/Unstable/yellow?icon=github)| N/A | N/A | N/A |


openMTPK's core C++ package and Python are also tested on the following architectures using `ubuntu-latest` and `bullseye` for 
ARMV6. 

Architecture |  C++ | Python |
-------------|------|--------|
ARMV6		 | [![arm6CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV6cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![arm6Py](https://github.com/akielaries/openMTPK/actions/workflows/ARMV6py.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
ARMV7		 | [![arm7CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV7cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![arm6Py](https://github.com/akielaries/openMTPK/actions/workflows/ARMV7py.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
ARMV7		 | [![arm8CPP](https://github.com/akielaries/openMTPK/actions/workflows/ARMV8cpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![arm8Py](https://github.com/akielaries/openMTPK/actions/workflows/ARMV8py.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
RISCV64		 | [![riscCPP](https://github.com/akielaries/openMTPK/actions/workflows/RISCVcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![riscPy](https://github.com/akielaries/openMTPK/actions/workflows/RISCVpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
s390x		 | [![s390xCPP](https://github.com/akielaries/openMTPK/actions/workflows/S390Xcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![s390xPy](https://github.com/akielaries/openMTPK/actions/workflows/S390Xpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |
ppc64le		 | [![ppc64leCPP](https://github.com/akielaries/openMTPK/actions/workflows/PPC64LEcpp.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) | [![ppc64lePy](https://github.com/akielaries/openMTPK/actions/workflows/PPC64LEpy.yml/badge.svg)](https://github.com/akielaries/openMTPK/actions/) |

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

# Installation

Requirements are loose and mostly tied to what openMTPK was tested and used on.
The current installation does not allow for the building of the packages language
bindings, limiting use to the core c++ lib. See below on how to build the bindings 
from source if interested.

## Requirements

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
$ make arith
$ make num-theory
...
```

## Uninstall

To uninstall files related to openMTPK, simply run the following:

```
# enter the build dir from installation
$ cd build
$ sudo make uninstall
```

## Python

For the Python API of openMTPK simply install with pip.

```
$ pip install openmtpk
```

Run an example in the `samples/python` to verify installation.

```
$ python3 arithmetic.py
```

### Bindings (BETA)

> **Note** These instructions are specific for the OCaml, R, and Fortran. 

The binding process leverages the use of Swig, specifically the fork authored by *sethrj*
that makes use of the Fortran binding process. See [here](https://github.com/swig-fortran/swig).
Each API comes with a custom Makefile for compiling a wrapper for the respective language, but
does not take care of storing files in necessary filepaths needed by the compiler/interpreter. 

### Install Swig

```
# clone the fork of Swig
$ git clone git@github.com:swig-fortran/swig.git
$ cd swig/
# run autotools
$ ./autogen.sh
# install
$ make
$ make check
$ make install
```

### Install Bindings

Bindings are currently being tested for OCaml, R, and Fortran. Simply
enter any of the languages lib directories and run the following

```
$ cd <API_NAME>/lib
$ make run-swig
```

If you wish to use the generated bindings globally, move the necessary files to the path 
needed by the compiler/interpreter.

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
from openmtpk import Cipher

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
