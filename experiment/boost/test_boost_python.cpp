#include <boost/bind/bind.hpp> // Include bind/bind.hpp explicitly
#include <boost/python.hpp>
#include <iterator>

// Use boost::placeholders explicitly
using namespace boost::placeholders;

char const *greet() {
    return "Hello, Boost.Python!";
}

BOOST_PYTHON_MODULE(libtest_boost_python) {
    using namespace boost::python;
    def("greet", greet);
}
