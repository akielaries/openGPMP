# Changelog

# v1.0.0-rc.1
See [new contributors](https://github.com/akielaries/openGPMP/graphs/contributors?from=2023-02-07&to=2023-05-09&type=c)
## What's Changed 
* **Project from openMTPK to openGPMP. Python API renamed from openmtpk to pygpmp**
* Documentation layout + additions
* `gpmp::accl` namespace introduced hardware acceleration methods using GPUs with the help of 
OpenCL and additional methods for CPU exploitation with Intel specific SIMD intrinsic functions. The
acceleration unit is an optional install with openGPMP with the use of `cmake`.
    * `gpmp::accl::GPU()` class features methods of GPU acceleration using OpenCL. This class will house
    methods seen in the mathematical openGPMP modules that are ideal for GPU computation. The GPU functions
    themselves will be written in `C` with wrapper methods for use in `C++` using `extern "C" {/* function definitions */}`
    making them available under the `gpmp::accl` namespace.
    * `gpmp::accl::SIMD()` class features accelerated functions seen in the core mathematical openGPMP
    modules ideal for wide register computations using Intel specific intrinsic functions.  

* `gpmp::core::ThreadPool()` class capable of spawning a specific number of threads or
the default `std::thread::hardware_concurrency()`.
    * view docs [here](https://akielaries.github.io/openGPMP/classgpmp_1_1ThreadPool.html)
    > **Note** This class is not yet used innately within openGPMP and is provided as a user utility for now.

* `gpmp::core::ThreadDispatch()` class that dispatches functions to the threadpool. 
    * view docs [here](https://akielaries.github.io/openGPMP/classgpmp_1_1ThreadDispatch.html)
* `gpmp::core::DataTable()` class capable of reading in CSV files storing them as a pair of 
vector strings. For now, the DataTable class features very limited functionality, reading in CSVs(entirely,
or specific columns), formatted displaying, and two conversion methods for the `string->int` & `string->double`.
    * Solves open enhancement [`#29 DataFrame/DataTable related functionality`](https://github.com/akielaries/openGPMP/issues/29)
    * view docs [here](https://akielaries.github.io/openGPMP/classgpmp_1_1core_1_1DataTable.html)
* `gpmp::core::TypeCast()` class featuring several methods to convert C++ `std::` specific data types
to C-compatible data types. This class is utilized for the C++ wrapping of the C-based acceleration methods.

* Created [`rolling`](https://github.com/akielaries/openGPMP/tree/rolling) branch that will update its commits 
from the [gpmp-bot](https://github.com/gpmp-bot) user on a nightly basis, using the `#NIGHTLY:` commit message 
prefix.
* Introduced updates to calculus module in numerical differentation methods. First, second, and third order derivatives methods 
of a given polynomial in a function at a given value. For example f(x) = x^2ln(x) = `x*x*log(x)`.
* Updates to unit tests and additions for the new classes introduced.
* Updates to namespaces, the core module containing the ThreadPool and DataTable related methods along with other miscellaneous
tools lies under the `gpmp::core` namespace. 
* Patches introduced for [`#27 OSX Build reaches dead state`](https://github.com/akielaries/openGPMP/issues/27)
    * This introduced additional testing and CICD work related to openGPMP on OSX.
* TODO


# v0.9.4
## What's Changed
* Division between code for internal functionality vs. what is available to the user.
* CI/CD pipeline updates
   * `clang-format` for linting/formatting C++ source code, `autopep8` for Python.
   * Python PyPI packaging edits.
   * Tag bump related commits will include a `#MAJOR`, `#MINOR`, or `#PATCH` prefix to the commit message.
   * Updates to certain directories run certain jobs.
* Continuous Machine Learning & Linear Algebra module updates. 
   * Stubbed out implementations for activation, regularization, optimization & model trainer methods, statistical helpers, random sorts + utilities. 
   * `Matrix` related methods are usable. More updates to come.
   * ML module is not currently usable aside from `Linear Regression` model on very select data sets.


# v0.7.0
## New Changes in v0.7.0
1. Updates to Primary and Secondary Multi-Layer Perceptron networks
2. Updates to Python API
3. Added support for Operating Systems, Kernels, Architectures, etc.
	* Added tested support beyond x86 processors
	* ARMV6, ARMV7, ARMV8, RISCV64, S390X, PPC64LE
	* Raspberry Pi 3 & 4 support
4. Fortran, OCaml, Go and Julia demoted to experimental APIs, focus remains on Python and now R bindings

### Next :
_______________
1. Fix CMake bugs for `OSX` installation. Issues with Googletest hangup 
2. Update Machine Learning Module with more techniques
3. Inject source code updates into APIs
4. Create formal check/test process for Raspberry Pi hardware


# v0.6.0
## New Changes in v0.6.0
1. Continued changes to Linear Algebra Module + samples
2. Continued updates to Python API, injecting new C++ source functionalities into the `setup.py` file used in packaging process for PyPI
	* Install with `pip install pygpmp==0.6.1`
3. Updates to the `gpmp` namespace. Wrapped more classes in the namespace, does not affect Python API
4. Changes/updates to datatypes to allow for maximum precision while also avoiding potential overflow as well as for conciseness
	> **Note** Some int and char types will be updated later on to ensure nothing breaks
	* `int`----------->`int64_t`
	* `long long`-->`int64_t`
	* `unsigned`---->`uint64_t`
	* `double`------->`long double`
	* `float`--------->`long double`
5. Adding `make uninstall` option for the project's build process with CMake. See the install/uninstall directions [here](https://github.com/akielaries/openGPMP#installation).


# v0.5.3
## What's Changed 
1. Updates to Linear Algebra Module and samples
	* See this [example](https://github.com/akielaries/openGPMP/blob/main/samples/cpp/linalg_ops.cpp) to view operations on matrices
	* More updates to samples as development continues
2. PyPI updates
	* Adjusting SWIG process to accommodate for template based classes and methods
	* pygpmp `0.5.14` release [here](https://pypi.org/project/pygpmp/0.5.13/)
3. Updated to CMake installation of source C++ code

### Next :
_______________
1. Create first of many Neural Network Models and Machine Learning techniques for the [ml](https://akielaries.github.io/openGPMP/ml_8hpp.html) module
	* Update the overarching `ml.hpp` header to make use of implemented models and techniques
	> **Note** So far the [Linear Regression](https://akielaries.github.io/openGPMP/linreg_8hpp.html) technique works on select two-column data
2. Progress on CPP->R & OCaml language binding process


# v0.5.2
## What's Changed 
> **Note** Do not expect much until _**v1.0.0**_

### Major Updates to Python PyPI packaging process. 
* Builds wheels for OSX and Linux platforms (Windows will not be supported)
* See all [supported platforms](https://pypi.org/project/pygpmp/0.5.1/#files).
  * Manually tested on _**Kali(latest), Ubuntu(latest)**_ & _**macOS Ventura 13.1 (latest)**_. Works for most OSX and Linux distro versions.
* New versions must be specified in the `setup.py` file and will be published to https://pypi.org/project/pygpmp/ on pushes to `MAIN`.
* Install with `pip install pygpmp`
* Tools available: 
  * Arithmetic based operations
  * Primes
  * RC4
  * Ciphers

### C++ source is currently supported on Linux based platforms.
* Bugs with googletest on OSX.


# v0.4.0
## What's Changed
* Created Python pip package for Python API. Install with `pip install pygpmp`
  * Functionality is limited to Primes, RC4, Ciphers, and part of the Arithmetic module
  * Fixes to template classes/methods cpp->python conversion


# v0.3.2
CMake installation make Googletest as a dependency.
* openGPMP tests must pass in order to build and install the static library
* TEST -> BUILD -> INSTALL


# v0.3.1
Minor Release with updates to CMake installation process.
* Headers are now installed in nested fashion with a parent-level header representing each module. For example:
  * Files in a module directory such as the `ml/` directory (linreg.hpp, logreg.hpp, mlp_network.hpp, etc.) will make up that modules header file([ml.hpp](https://github.com/akielaries/openGPMP/blob/main/include/ml.hpp)).
* Will include googletest workflow into CMake installation
  * `Build library -> Test library -> Install library` 


# v0.3
Formal documentation created with Doxygen deployed to github pages, see [here](https://akielaries.github.io/openGPMP). 
* Documentation updates within headers
* Linear Regression model testing
* Additional work and plans for Machine/Deep Learning module
  * Multi-Layer Perceptron, Linear Algebra Matrix, Scalar, and Vector manipulations + testing
  * Formal API installation processes
  * Automate API installations with Actions  

As always refer to the project [README](https://github.com/akielaries/openGPMP#installation).


# v0.2
Formal installation of source C++ API with CMake. See installation steps in the project [README](https://github.com/akielaries/openGPMP#installation).
* Linux is supported. 
* OSX testing is in progress.
* Working Python API, user installation mandatory.
* Unstable Fortran, OCaml, and R bindings.

**Future**
* Fixes + testing + formal installation of language bindings.
* Neural Networks, Classifiers

https://pygpmp-docs.readthedocs.io/en/latest/index.html


# v0.1
### Initial introduction beta release of openGPMP 
Open-source (intended) mathematics package written in C++ with a working Python API allowing for the use of algorithms and equations seen in many mathematical topics.
See the [README](https://github.com/akielaries/openGPMP/blob/main/README.md) for more details


#### Modules
Module | Features | Status | 
------------|--------------|-----------|
Arithmetic          | Operations, GCD, etc. | **Working** | 
Calculus              | Derivative at value |**Limited** | 
Linear Algebra   |Matrix Operations | **Limited** | 
Machine/Deep Learning | Linear Regression | **Limited** |
Number Theory       | Primes, Cryptography/Encryption | **Working** | 

Issues:
* No formal installation method 
* Test coverage
* OCaml & R bindings are unstable. 
  * C++->OCaml class translation
