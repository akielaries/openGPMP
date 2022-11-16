/*
 * definitions for basic arithmetic operations 
 */

#ifndef RMARITH_H
#define RMARITH_H
#include <vector>
#include <stdio.h>


class arith {

    public:
        // arith();
        template<typename T>
        inline T rm_sum(T t);

        template<typename T, typename... Ts>
        inline auto rm_sum(T t, Ts... ts);



};

#endif

