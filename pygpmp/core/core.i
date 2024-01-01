/* openGPMP Structures Module */

%module core
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/core/datatable.hpp"
    #include "../../include/core/utils.hpp"
    #include "../../include/core/threads.hpp"
    using namespace gpmp;
%}

%include "../../include/core/datatable.hpp"
%include "../../include/core/utils.hpp"
%include "../../include/core/threads.hpp"

