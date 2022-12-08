/* SWIG Interface file */

/* %module = sepcifies a module to use, 
will include headers within */

%module arithmetic
%inline%{
    /* MODULE HEADER FILE */
    #include "../../include/arithmetic/arith.hpp"
    /*
    class Arith {
        public:
            template<typename T>
            inline T add(T t) {
                return t;
            }
            template<typename T, typename... Ts>
            inline auto add(T t, Ts... ts) {
                return t + add(ts...);
            }
    };
    */
%}

/* EXPLICITLY list functions and variables to include */
#include "../../include/arithmetic/arith.hpp"
template<typename T>
extern inline T add(T t) {
    return t;
}
template<typename T, typename... Ts>
extern inline auto add(T t, Ts... ts) {
    return t + add(ts...);
}

%template(i_add) add<int>;
%template(d_add) Arith.add<double>;

%template(add_a) add<int>;
%template(add_b) add<double>;

