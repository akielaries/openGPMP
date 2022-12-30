Installation
=====
Requirements are loose and mostly tied to what openMTPK was tested and used on.
The current installation does not allow for the building of the packages language
bindings, limiting use to the core c++ lib. See below on how to build the bindings 
from source if interested.

## Requirements
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
> **Note**
> This process asumes your STDLIB path is /usr/local/lib, where most 3rd-party 
> libs are located if not, run the following:
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
## Dependencies
> **Warning**
> At the moment these dependencies do not apply to the current release. 

The goal of openMTPK is to have as little dependencies as possible without re-inventing 
the wheel too much while performing speedy computations. Other than C and C++ standard 
libraries the 3rd-party dependencies that are used are deemed necessary for many of the
packages functionalities. openMTPK makes use of a few open source cross-platform 
compatible packages and libraries in the cases of threading for performance, graphics 
libraries, and packages for testing and fuzzing.

* openMP: Open Multi-Processing is useful for simple threading when needed.
For loops that don't make complex calls can be encosed in a `#pragma omp parallel for 
{}` declaration.

* openCL: Open Computing Language is another useful threading API that allows for
more customized parallelization techniques.

* openGL: Open Graphics Library used for hardware-accelerated rendering. API
makes use of interaction with a machines Graphics Processing Unit (GPU) allowing 
for quick rendering of modules that make use.

* libXbgi: Borland Graphics Interface reiteration. Provides a useful graphics API
to get started with visualizing mathematical algorithms.

## Tools
* Gtest: Used for unit testing. Within the projects development Makefile,
there are option to run the tests for the modules in this package. This is done by 
compiling a driver file that runs the methods referenced in each module, the source 
module file itself, and then the gtest based test driver file for said module. Some 
modules are harder to test than others but for the most part simply checking the 
expected output against the computed output does all the checking that is needed.

* AFL and AFL++: AFL is a fuzzing tool built by Google but now deprecated.
AFL++ is an open source community effort forked from AFL offering the same 
functionalities but much better. Advertised as better mutations, more speed, and 
better instrumentation. Fuzzing comes in handy for generating random inputs for your 
program and analyzing the outputs Analyzing crashes, unique or not, proves valuable 
for implementing strong and secure code.

The code below is an example on how testing on the arithmetic module was done.
```c++
    #include <openMTPK/arithmetic/arith.hpp>
    #include <gtest/gtest.h>
    namespace {
        arith ar;
        // test case, test name
        TEST(arith_test, add_positive) {
            EXPECT_EQ(46094, ar.rm_add(93, 106, 3551, 42344));
            EXPECT_EQ(6.85, ar.rm_add(1.25, 1.85, 2.75, 1));
        }
        // multiplication (product) testing
        TEST(arith_test, mult_positive) {
            EXPECT_EQ(240, ar.rm_mult(10, 8, 3));
            EXPECT_EQ(6.359375, ar.rm_mult(1.25, 1.85, 2.75, 1));
        }
        // subtraction
        TEST(arith_test, sub_positive) {
            EXPECT_EQ(5, ar.rm_sub(10, 8, 3));
            EXPECT_EQ(1, ar.rm_sub(1.25, 1.85, 2.75));
        }
   }

```
