# Contributing

RM-pkg welcomes any and all contributors! There are **two** ways to contribute to RM-pkg
## Bug fixes
* If you have a bug fix please submit a pull request with details highlighting what you are fixing, how you 
replicated it, and how you tested your fix. 

## New Features
* If you have an idea on some mathematical algorithm that can be used in this package, please...
1. see if the idea already exists in one of the [modules](https://github.com/akielaries/RM-pkg/tree/main/modules) 
2. create/add to an existing modules code + the corresponding `.hpp` file in the [includes](https://github.com/akielaries/RM-pkg/tree/main/include)
directory.
3. create a driver with your `main()` function and store in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers)
directory.
4. confirm your implementations work correctly. 
5. if necessary add your example to the projects [Makefile](https://github.com/akielaries/RM-pkg/tree/main/Makefile) that shows 
different examples running. 
6. pretty up any miscsubmit pull request

## Goal
The **goal** is to incorporate different mathematical topics into modules. These modules will serve as 
*"abstract"* topics and code within them to then be reused by users and the package itself. Each modules 
code will have corresponding `main()` functions in the [drivers](https://github.com/akielaries/RM-pkg/tree/main/drivers) 
directory showing examples on how to implement said modules. 


* For example, a linear algebra module would contain a module named `LINALG` that could contain `.cpp` implementation files
with their corresponding headers in in the includes folder mentioned previously. The specific module directory can contain whatever
new implementation files or add to an existing file.
  * For example, if you have the idea to add operations on Vectors (addition, subtraction, multiplication, division) but see that 
  addition and subtraction are already implemented in a file called `la_basics.cpp` you would add your implementations into that file
  instead of creating a new one. 

Hopefully these guidelines are clear enough for you to begin contributing to this project. As always email me akiel@akiel.org for questions.
