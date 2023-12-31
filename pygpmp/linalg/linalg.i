/* Defining linear algebra methods/classes for python swig process
*/

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%nodefaultctor;

%module linalg


%{
    #include "../../include/linalg/mtx.hpp"
    // #include "../../include/linalg/mtx_tmpl.hpp"
    using namespace gpmp;
%}

%include "../../include/linalg/mtx.hpp"
/*%include "../../include/linalg/mtx_tmpl.hpp"

// rename operators
%rename(__add__) gpmp::Matrix::operator+;

// re-declare class templates specifying a datatype
%template(Matrix) gpmp::Matrix<double>;
%template(MatrixI) gpmp::Matrix<int>;

%naturalvar gpmp::mtx;

// re-declare struct templates specifying a datatype
%template(mtx) gpmp::mtx<double>;
//%template(mtxI) gpmp::mtx<int>;
*/

