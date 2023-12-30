<p align="center">
  <img src="https://raw.githubusercontent.com/akielaries/openGPMP/v1.0.0-rc.1/docs/openGPMP_logo_med.png" />
</p>

![Version](https://img.shields.io/github/v/release/akielaries/openGPMP?color=%23BF40BF)
[![PyPi](https://img.shields.io/pypi/v/pygpmp.svg)](https://pypi.python.org/pypi/pygpmp)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openGPMP/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/openGPMP&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/github/license/akielaries/openGPMP?color=23228B22)](https://github.com/akielaries/openGPMP/blob/main/LICENSE)
[![codecov](https://codecov.io/gh/akielaries/openGPMP/branch/main/graph/badge.svg?token=KJBGLP8DYJ)](https://codecov.io/gh/akielaries/openGPMP)
![clones](https://raw.githubusercontent.com/akielaries/openGPMP/traffic/traffic-openGPMP/clones.svg)
[![openGPMP](https://github.com/akielaries/openGPMP/actions/workflows/opengpmp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)

# Overview
**openGPMP** is an open-source, multi-threaded, mathematics package written in C++, C, and Fortran with no runtime dependencies. 
The primary focus in Number Theory and Cryptographic algorithms, Linear Algebra, Calculus, Statistics, and Machine 
Learning concepts, and more. openGPMP aims to serve as a warehouse and one-stop shop for mathematical operations. Additional 
acceleration methods are featured for optional use and installation via OpenCL and CUDA. By default, SIMD intrinsics will be 
used for the supported platforms.

Look in the [samples](https://github.com/akielaries/openGPMP/tree/main/samples) folder for examples 
on how to use some of openGPMP's functionalities. 

# Installation
openGPMP C++ & Python is tested on the following:
| OS    | Architecture | Status |
|-------|--------------|--------|
OSX Monterey 12.6.3 | x86 | [![darwin](https://github.com/akielaries/openGPMP/actions/workflows/build_osx.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/) | 
RasPi OS | ARMv6/v7 | [![cppRPi](https://github.com/akielaries/openGPMP/actions/workflows/cpp_rpi.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/) |
| bullseye 11.6 | ARMv6        | [![arm6CPP](https://github.com/akielaries/openGPMP/actions/workflows/ARMV6cpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      | 
| ubuntu 22.10 | ARMv7        | [![arm7CPP](https://github.com/akielaries/openGPMP/actions/workflows/ARMV7cpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      | 
| ubuntu 22.10 | ARMv8        | [![arm8CPP](https://github.com/akielaries/openGPMP/actions/workflows/ARMV8cpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      | [![arm8Py](https://github.com/akielaries/openGPMP/actions/workflows/ARMV8py.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      |
| ubuntu 22.10 | RISCV64      | [![riscCPP](https://github.com/akielaries/openGPMP/actions/workflows/RISCVcpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      | [![riscPy](https://github.com/akielaries/openGPMP/actions/workflows/RISCVpy.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)      |
| ubuntu 22.10 | S390X        | [![s390xCPP](https://github.com/akielaries/openGPMP/actions/workflows/S390Xcpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)     | [![s390xPy](https://github.com/akielaries/openGPMP/actions/workflows/S390Xpy.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)     |
| ubuntu 22.10 | PPC64LE      | [![ppc64leCPP](https://github.com/akielaries/openGPMP/actions/workflows/PPC64LEcpp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/) | [![ppc64lePy](https://github.com/akielaries/openGPMP/actions/workflows/PPC64LEpy.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/) |
ubuntu 22.10  | Intel GPU | [![INTELGPU](https://github.com/akielaries/openGPMP/actions/workflows/intel_opencl.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)  |
ubuntu 18.04  | Nvidia GPU (CUDA) | [![NVIDIACUDA](https://github.com/akielaries/openGPMP/actions/workflows/CUDA.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)  |
ubuntu 18.04  | Nvidia GPU (OpenCL) | [![NVIDIAOPENCL](https://github.com/akielaries/openGPMP/actions/workflows/nvid_opencl.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)  |
> **Note** Testing on Apple specific hardware (M1, M2) is in progress. 

## Python
To install the Python interface, use the pip package manager and run the following, `pip install
pygpmp`. Additional hardware support is available with [SWIG](https://github.com/swig/swig) as a dependency for the pip 
installation.

## Build from source
### Requirements
* Linux/OSX
* CMake v3.18+ (build from source for latest version)
* C++20
* gcc, g++, gfortran v12+ (other C, C++, and Fortran compilers are being tested)

```
# clone repo
$ git clone git@github.com:akielaries/openGPMP.git
$ cd openGPMP
# create build dir
$ mkdir build && cd build
# create necessary objects and static library
$ cmake -S ../
# on OSX
$ cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc-12 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-12 -S ../
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
[samples](https://github.com/akielaries/openGPMP/tree/main/samples) directory.

```
# compile yourself
$ cd samples/cpp
$ g++ cipher.cpp -lopenGPMP -o cipher
$ g++ arith.cpp -lopenGPMP -o arith
# script to test all modules and their drivers
# using the projects root makefile
$ cd scripts && ./all.sh
```

To uninstall files related to openGPMP, simply run the following:

```
# enter the build dir from installation
$ cd build
$ sudo make uninstall
```
## tinygpmp
[`tinygpmp`](/tinygpmp) targets low-voltage, resource-constrained devices and is currently aiming to support
AVR series MCUs, STM32 chips, and other embedded devices.

## Modules

During early stages, modules will be developed in breadth while focusing on depth
in later stages of the `PRE-V1.0.0` phase. The modules below are all in progress.

0. Core (utilities & common interfaces)
1. Arithmetic
2. Calculus
3. Discrete Mathematics
4. Linear Algebra
5. Machine/Deep Learning
6. Number Theory
7. Complex

For more details view the project [documentation](https://akielaries.github.io/openGPMP/).


# Examples

View the simple examples on how to use some of the modules in different languages [here](https://github.com/akielaries/openGPMP/tree/main/samples).

```
# clone the repo and enter
$ git clone git@github.com:akielaries/openGPMP.git 
$ cd openGPMP/scripts

# to run all examples 
$ ./all.sh

# to remove the generated binaries
$ cd ../ && make clean-mods

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
#include <openGPMP/nt.hpp>

int main() {
    // declare CIPHER class obj
    gpmp::Cipher cc;

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
>>> from pygpmp import nt
>>> c = nt.Cipher()
>>> text0 = c.caesar('Plaintext', 5)
>>> print(ciphertext_0)
Uqfnsyjcy
>>> 
>>> text1 = c.caesar('ATTACKATONCE', 4)
>>> print(text1)
EXXEGOEXSRGI
>>> 
>>> text = "Password"
>>> shift = "Computer"
>>> encoded_text = c.keyword_encode(shift);
>>> hashtext = c.keyword(text, encoded_text);
>>> print(hashtext)
JCNNWILP
```

