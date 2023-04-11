Welcome to openMTPK's documentation.
===================================
**openMTPK** is a open-source mathematics package written in C++ with language 
bindings available for Fortran, OCaml, Python, and R. The goal is to 
make a reusable mathematics library covering an array of topics for an array of 
uses. 

Starting with some implementations of basics of different mathematical topics like 
Arithmetic, Calculus, Statistics, Linear Algebra, etc. in conjunction with more advanced
algorithms seen in the blend of such topics, branches of Machine Learning, Image 
Processing and much more. Some of the modules operate in a circular dependant way, 
for example arithmetic operations seen in linear algebra vector operations that can 
be seen in algorithms implemented in the deep learning module. 

Some of these implementations were first prototypes in Wolfram Mathetmatica, then 
converted to C++ code for the package. Look in the samples folder for examples on 
using these tools in your own project. This piece of documentation will highlight 
the modules in use, the mathematics/logic behind them, future developments, and 
more. 

This documentation primarily highlights how to use the source C++ API. Documentation
and usage for the Python API is in progress but there is some similarity/crossover
with usage for the source. The Python docs will likely be doxygen-based as well as
located on this site.

The published PyPI package for openMTPK can be 
seen [here](https://pypi.org/project/openmtpk/).

> **Note**
> This project is under active development.

Contents
--------
1. [Installation](Installation.md)
2. [Annotations](annotated.html)
3. [Usage](Examples.md)
4. [Modules](Modules.md)

