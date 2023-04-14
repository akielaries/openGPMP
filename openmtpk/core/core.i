/* openMTPK Structures Module */

%module ml
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/struct/datatable.hpp"
    using namespace mtpk;
%}

%include "../../include/struct/datatable.hpp"

