# openMTPK Julia API
> **Warning**
> This binding is currently in progress and will feature a formal 
> installation method most likely with a package manager.

The Julia API for openMTPK leverages the very handy tool 
[wrapit](https://github.com/grasph/wrapit) by 
[Philippe Gras](https://github.com/grasph) that automatically creates
a binding for Julia from C++ given some configuration. The process 
currently makes use of a custom `Makefile` to build the API.


# Usage
Julia is not inherently an Object-Oriented Programming Language,
however, the source C++ code makes use of namespaces and classes.
In openMTPK, each Class of and its encapsulated method are housed
in an overarching namespace `mtpk`. Thus to use methods of a given
class use this syntax:
```
    mtpk!<Class Name>
```

So for the class `Basics` that houses the method `greatest_power()`
we would call it with:
```
    obj = openMTPK.mtpk!Basics()
    res = greatest_power(obj, 3, 5)
```
Notice how we pass in the class "object" as a parameter to the `greatest_power()`
method. Note, I use the term object lightly as Julia does not follow OOP style but
we force this since the source C++ code does. 


### Currently
1. Issues regarding latency between the compiled shared library and the Julia
interface.
2. No formal installation process. 


