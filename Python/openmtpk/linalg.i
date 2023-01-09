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

%template(MatrixI) mtpk::Matrix<int>;
%template(MatrixD) mtpk::Matrix<double>;

%module openmtpk

