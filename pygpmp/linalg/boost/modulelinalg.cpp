#include <boost/bind/bind.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iterator>

#include "../../../include/linalg/mtx.hpp"

BOOST_PYTHON_MODULE(linalg) {
    // using namespace boost::python;

    boost::python::class_<gpmp::linalg::Mtx>("Mtx").def(
        "mtx_add",
        static_cast<void (
            gpmp::linalg::Mtx::
                *)(const int *A, const int *B, int *C, int rows, int cols)>(
            &gpmp::linalg::Mtx::mtx_add));
    //.def("mtx_add", static_cast<bool (gpmp::linalg::Mtx::*)(int,
    //double)>(&gpmp::linalg::Mtx::mtx_add)) .def("mtx_add", static_cast<bool
    //(gpmp::linalg::Mtx::*)(int, double, char)>(&gpmp::linalg::Mtx::mtx_add))
    //.def("mtx_add", static_cast<int (gpmp::linalg::Mtx::*)(int, int,
    //int)>(&gpmp::linalg::Mtx::mtx_add));
}
