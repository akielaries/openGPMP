#include <boost/python.hpp>

struct X {
    bool f(int a) {
        return true;
    }

    bool f(int a, double b) {
        return true;
    }

    bool f(int a, double b, char c) {
        return true;
    }

    int f(int a, int b, int c) {
        return a + b + c;
    };
};

BOOST_PYTHON_MODULE(example) {
    using namespace boost::python;

    class_<X>("X")
        .def("f", static_cast<bool (X::*)(int)>(&X::f))
        .def("f", static_cast<bool (X::*)(int, double)>(&X::f))
        .def("f", static_cast<bool (X::*)(int, double, char)>(&X::f))
        .def("f", static_cast<int (X::*)(int, int, int)>(&X::f));
}
