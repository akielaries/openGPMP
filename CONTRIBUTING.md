# Contributing
openGPMP welcomes any and all contributors! There are **many** ways to contribute 
to openGPMP. New implementations, updates to source code, documentations, language 
API, and much more. To submit a change simply fork the repository and begin the 
pull request process. Squash commits, clean up misc. files, etc. and submit a pull 
request to the openGPMP repository. 

Be sure to include a hash `#` prefixing your commit messages. For example `#EDITS:` 
or `#UPDATES:` are used to signaling commits that feature minor edits/updates. 
`#BUILD:` references anything to do with the openGPMP project's build system.
`#BUG:` references a bug fix commit, and `#FEAT` represents a new feature being 
added to the project. The prefixes, `#PATCH`, `#MINOR`, `#MAJOR`, are reserved 
for automated versioning/tagging of commits based on messages. This process still 
features a manual intervention by design meaning the maintainer of this project 
will be in charge of publishing versions.

# Needed Help
These are the current fixes, ideas, and implementations involved with openGPMP. 
Contributors are welcome to open a pull request, the maintainer 
([me](https://github.com/akielaries)), will take care of assuring passing tests 
and checks as far as github workflows.

0. At a glance openGPMP aims to feature fully functional Calculus, Linear Algebra, 
Number Theory, Machine Learning (and more) modules for modular and pre-built use.

1. The `Machine and Deep Learning Module` a continuous effort and I find is the 
most important and reusable module of the openGPMP project for programmers, 
students, researchers, etc. also meaning it requires the most help regarding 
implementations, tests, verifications, and any effort helping assure the accuracy 
of the implemented models. 
   * Proper implementation of various styles of Nerual Networks, Regression methods, 
   classifiers, optimizers, accelerators, and more. So far I implement
   the components of the Machine Learning module as I have time and as I familiarize 
   myself with a particular topic using some handy texts, papers, and other resources.. 
      * The ML module will heavily rely off of the Linear Algebra module as well as 
      statistical methods that could perhaps be included in its own `statistics` module.
   *  To prove the existing and future implemented models and methods provide some 
   use, benchmarking/comparisons against industry-grade and open-source projects 
   like **PyTorch**, **TensorFlow (including the Keras interface)**, and 
   **Sci-kit Learn** will prove beneficial. 

2. Perfecting the **Linux** and **OSX** installations with `CMake`. 
   
   * **Windows** is not currently on my agenda. Installation and support for Windows 
   systems is handed off to those who need it or if I have a plethora of spare time. 
   
   * `CMake` installation currently only works with **Linux**, issues arise on **OSX** 
   when it comes to the steps regarding GoogleTest.

3. Creating bindings for languages.
   
   * The stable `Python API` makes use of **SWIG** and **distutils** to wrap the source 
   C++ code into a shared library, making use of **Github Actions** to publish the 
   package to PyPI with support for just about all `Linux` distros and `OSX` versions 
   and platform architectures, see [here](https://pypi.org/project/pygpmp/#files). 
   If this process can be polished it is highly welcomed. 
   
   * Properly implementing, testing, and updating the unstable/inprogress APIs for `R`, 
   `OCaml`, and `Fortran`.  
     * This will require knowledge of the languages and openGPMP in order to create 
     samples for the respective languages in the [samples](https://github.com/akielaries/openGPMP/tree/main/samples) folder.
     
     * As of now partial working steps for doing this with **SWIG** is present in each 
     of the respective languages folders. 

4. Formalize openGPMP for real world applications.
   * Threading, acceleration, optimization, etc. This could include creating a 1-stop-shop 
   implementation using some sort of cross-platform library/framework/technique that enable 
   CPU and/or GPU exploitation just like popular libraries that are capable of handling 
   extremely large data sets (PyTorch, TensorFlow, etc.).
   * pthreads, openCL, openMP? A custom take at this could prove difficult to implement 
   and maintain. 

5. Updates to Documentation published with Doxygen to https://akielaries.github.io/openGPMP/. 
This is needed for both the C++ and Python uses while the former contains a decent amount already.

## 

# Bug fixes
* If you have a bug fix please submit a pull request with details highlighting what you are 
fixing, how you replicated it, and how you tested your fix. For fixes that include confidential 
information please feel free to send me an email [akiel@akiel.org](mailto:akiel@akiel.org)

# Code Style
openGPMP attempts to follow the neat [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) 
for naming while a custom clang-format file is used for tidying formatting. 



Hopefully these guidelines are clear enough for you to begin contributing to this project. 
As always email me akiel.aries@colorado.edu for questions.
