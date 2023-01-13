/* Defining linear algebra methods/classes for python swig process
*/

%include "std_string.i"
%include <std_vector.i>
%nodefaultctor;

%{
    #include "../../include/linalg/matrix.hpp"
    using namespace mtpk;
%}

%include "../../include/linalg/matrix.hpp"

// rename operators
%rename(__add__) mtpk::Matrix::operator+;

// re-declare class templates specifying a datatype
%template(Matrix) mtpk::Matrix<double>;
%template(MatrixI) mtpk::Matrix<int>;

%naturalvar mtpk::mtx;

// re-declare struct templates specifying a datatype
%template(mtx) mtpk::mtx<double>;
//%template(mtxI) mtpk::mtx<int>;


%module linalg

