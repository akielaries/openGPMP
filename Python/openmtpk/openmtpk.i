/* CORE openMTPK PYTHON API SWIG INTERFACE FILE */

/* FIGURE OUT CLASS TEMPLATES AND DEFININD SPECIFIC TYPES
 * FOR ARITHMETIC CLASS */
%module openmtpk
%include "std_string.i"
%include "linalg.i"

%{
    #include "../../include/arithmetic/arith_ops.hpp"

    #include "../../include/calculus/deriv.hpp"

    #include "../../include/ml/linreg.hpp"

    #include "../../include/nt/primes.hpp"
    #include "../../include/nt/rc4.hpp"
    #include "../../include/nt/cipher.hpp"
%}

%include "../../include/arithmetic/arith_ops.hpp"

%include "../../include/calculus/deriv.hpp"

%include "../../include/ml/linreg.hpp"

%include "../../include/nt/primes.hpp"
%include "../../include/nt/rc4.hpp"
%include "../../include/nt/cipher.hpp"

