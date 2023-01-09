/* CORE openMTPK PYTHON API SWIG INTERFACE FILE */

/* FIGURE OUT CLASS TEMPLATES AND DEFININD SPECIFIC TYPES
 * FOR ARITHMETIC CLASS */
%module openmtpk
%include "std_string.i"
%include "linalg.i"
%{
    #include "../../include/arithmetic/arith_ops.hpp"

    #include "../../include/calculus/deriv.hpp"

    #include "../../include/linalg/vectors.hpp"

    #include "../../include/ml/bayes_network.hpp"
    #include "../../include/ml/k-foldCV.hpp"
    #include "../../include/ml/linreg.hpp"
    #include "../../include/ml/nearest_neighbor.hpp"

    #include "../../include/number_theory/primes.hpp"
    #include "../../include/number_theory/rc4.hpp"
    #include "../../include/number_theory/cipher.hpp"
%}

%include "../../include/arithmetic/arith_ops.hpp"

%include "../../include/calculus/deriv.hpp"

%include "../../include/linalg/vectors.hpp"

%include "../../include/ml/bayes_network.hpp"
%include "../../include/ml/k-foldCV.hpp"
%include "../../include/ml/linreg.hpp"
%include "../../include/ml/nearest_neighbor.hpp"

%include "../../include/number_theory/primes.hpp"
%include "../../include/number_theory/rc4.hpp"
%include "../../include/number_theory/cipher.hpp"


