/* File : example.i */
%module example

%include "std_string.i"
%{
#include "example.hpp"
%}
%include stl.i
/* Let's just grab the original header file here */
%include "example.hpp"
