/* Defining linear algebra methods/classes for python swig process
*/

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%module linalg

%{
    #include "../../include/openGPMP/linalg/mtx.hpp"
    using namespace gpmp;
%}

%include "../../include/openGPMP/linalg/mtx.hpp"

