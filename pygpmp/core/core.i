/* openGPMP Structures Module */

%module core
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/openGPMP/core/datatable.hpp"
    #include "../../include/openGPMP/core/utils.hpp"
    //#include "../../include/core/threads.hpp"
    using namespace gpmp;
%}

%include "../../include/openGPMP/core/datatable.hpp"
%include "../../include/openGPMP/core/utils.hpp"
//%include "../../include/core/threads.hpp"

