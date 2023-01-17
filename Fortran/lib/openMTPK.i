/* CORE openMTPK PYTHON API SWIG INTERFACE FILE */

/* FIGURE OUT CLASS TEMPLATES FOR ARITHMETIC CLASS */
%module openMTPK
%include "std_string.i"
%include "stdint.i"


%{
    #include "../../include/arithmetic/arith_ops.hpp"
%}

%include "../../include/arithmetic/arith_ops.hpp"

//%include "cpointer.i"

//%pointer_functions(int64_t, int64_t_ptr)


