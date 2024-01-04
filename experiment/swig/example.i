%module example

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>
%include "carrays.i"

%{
#include "example.h"
%}

%array_functions(int,std_mtx_add)

%include "example.h"

