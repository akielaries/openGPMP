<p align="center">
  <img src="https://raw.githubusercontent.com/akielaries/openGPMP/main/docs/openGPMP_logo_med.png" />
</p>

![Version](https://img.shields.io/github/v/release/akielaries/openGPMP?color=%23BF40BF)
[![PyPi](https://img.shields.io/pypi/v/pygpmp.svg)](https://pypi.python.org/pypi/pygpmp)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cccab2412bac4217827559131efea8ee)](https://www.codacy.com/gh/akielaries/openGPMP/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=akielaries/openGPMP&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/github/license/akielaries/openGPMP?color=23228B22)](https://github.com/akielaries/openGPMP/blob/main/LICENSE)
[![codecov](https://codecov.io/gh/akielaries/openGPMP/branch/main/graph/badge.svg?token=KJBGLP8DYJ)](https://codecov.io/gh/akielaries/openGPMP)
![clones](https://raw.githubusercontent.com/akielaries/openGPMP/traffic/traffic-openGPMP/clones.svg)
[![openGPMP](https://github.com/akielaries/openGPMP/actions/workflows/opengpmp.yml/badge.svg)](https://github.com/akielaries/openGPMP/actions/)
![](https://tokei.rs/b1/github/akielaries/openGPMP)


# Overview
**openGPMP** is an open-source, multi-threaded, mathematics package written in C++, C, Fortran and Assembly with 
no runtime dependencies. The primary focus in Number Theory and Cryptographic algorithms, Linear Algebra, Calculus, 
Statistics, and Machine Learning concepts, and more. openGPMP aims to serve as a warehouse and one-stop shop for 
mathematical operations. Additional acceleration methods are featured for optional use and installation via OpenCL 
and CUDA. By default, SIMD intrinsics will be used for the supported platforms.

Look in the [samples](https://github.com/akielaries/openGPMP/tree/main/samples) folder for examples 
on how to use some of openGPMP's functionalities and the in-depth [documentation](https://akielaries.github.io/openGPMP/).

# Installation
## C++ (source)
### Requirements
* Linux/OSX
* CMake v3.18+ (build from source for latest version)
* C++20
* gcc, g++, gfortran v12+ (clang, clang++, and flang are being tested)

### Build
Clone the repository or download the codebase from a release:

```
# clone repo
$ git clone git@github.com:akielaries/openGPMP.git
$ cd openGPMP
```

Create a build directory and configure with CMake:
```
$ mkdir build && cd build
$ cmake -S ../
```
* Additional CMake options include:
    * `-DBUILD_TESTS=ON`
    * `-DCMAKE_C_COMPILER=/path/to/C/compiler`
    * `-DCMAKE_CXX_COMPILER=/path/to/CPP/compiler`
    * `-DCMAKE_FC_COMPILER=/path/to/Fortran/compiler`

> **Note** For now, OSX requires GCC for compilation

Install the compiled static library and headers:
```
$ make
$ sudo make install
```

> **Note**
> Keep the build directory for easy uninstallation.

## Python (pygpmp)
To install the Python interface, use the pip package manager and run the following, `pip install
pygpmp`. Additional hardware support is available with [SWIG](https://github.com/swig/swig) as a dependency for the pip
installation.

### From source
Building the Python pip wheel from source is easy as well. Run the following:
```
# install dependencies
$ pip install -r requirements.txt
# create CMake files in py_build dir
$ cmake -B py_build -DBUILD_PYGPMP=ON
# install
$ pip install .
```

## Julia (gpmp.jl)
> **Note** In progress
The Julia interface is built with the help of [wrapit](https://github.com/grasph/wrapit).

## tinygpmp
> **Note** In progress
[`tinygpmp`](/tinygpmp) targets low-voltage, resource-constrained devices and is currently aiming to support
AVR series MCUs, STM32 chips, and other embedded devices.

tinygpmp can be built using the following CMake options:
```
    * `-DTINYGPMP_AVR=ON` ***todo***
    * `-DTINYGPMP_ARM32=ON` ***todo***
    * `-DTINYGPMP_DYN=ON` ***todo***
    * `-DTINYGPMP_STAT=ON` ***todo***
```
# Uninstall
To uninstall files related to openGPMP, simply run the following:

```
# enter the build dir from installation
$ cd build
$ sudo make uninstall
```

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
8. Statistics
9. Optimization

For more details view the project [documentation](https://akielaries.github.io/openGPMP/).


# Examples

View the simple examples on how to use some of the modules in different languages [here](https://github.com/akielaries/openGPMP/tree/main/samples).

```
# clone the repo and enter the samples dir
$ git clone git@github.com:akielaries/openGPMP.git 
$ cd samples
# compile an example and link against openGPMP
$ g++ cpp/linreg.cpp -lopenGPMP -o example
$ ./example
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
>>> print(text0)
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

# Why?
The rationale/why behind this project is mostly because I find high 
performance & numerical computing, low level programming, computational
mathematics, C, C++, Fortran, Assembly, Julia, etc, etc all interesting.
As far as usability and practicality, that may become more solidified 
with more contributors and time spent but I do aim to design and implement
the project with real-world usage as a focus...

