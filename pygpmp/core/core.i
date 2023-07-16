/* openGPMP Structures Module */

%module ml
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/struct/datatable.hpp"
    using namespace gpmp;
%}

%include "../../include/struct/datatable.hpp"

