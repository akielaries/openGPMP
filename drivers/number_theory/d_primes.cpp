/*
 * Driver for showing how to use the core basic and elementary functionalities
 * of the Number Theory module
 *
 */
#include "../../include/number_theory/primes.hpp"
#include <iostream>

int main() {
    std::cout << "BASIC NUMBER THEORY OPERATIONS\n" << std::endl;
    // declare primality class object
    Primality p;

    std::cout << "<--------- IS IT PRIME? --------->\n";
    int a = 9;
    // check if an integer is prime or not
    bool is_it = p.is_prime(a);

    std::cout << a << " is prime? : ";
    is_it ? std::cout << "true\n" : 
        std::cout << "false\n" << std::endl;

    int b = 2;
    bool is_it2 = p.is_prime(b);

    std::cout << b << " is prime? : ";
    is_it2? std::cout << "true\n" : 
            std::cout << "false\n" << std::endl;
    std::cout << "\n";

    std::cout << "<--------- MILLER-RABIN METHOD --------->\n";
    int min_num = 1;
    // display the prime numbers smaller than a given value
    int max_num = 100;
    // number of iterations
    int iters = 4;
    /*
     * calculate the solution, the method doesn't return a value, 
     * prints the values
     */
    p.miller_rabin(iters, min_num, max_num);
    p.miller_rabin(iters, 25, 50);
    p.miller_rabin(iters, 30, 3000);

    std::cout << "\n";
    
    std::cout << "<--------- CARMICHAEL NUMBERS --------->\n";
    int cm_test = 500;
    bool carm_num = p.carmichael_num(cm_test);

    int cm_test1 = 561;
    bool carm_num1 = p.carmichael_num(cm_test1);

    int cm_test2 = 1105;
    bool carm_num2 = p.carmichael_num(cm_test2);
    
    std::cout << cm_test << " is a carmichael number : ";
    carm_num? std::cout << "true\n" :
            std::cout << "false\n";

    std::cout << cm_test1 << " is a carmichael number : ";
    carm_num1? std::cout << "true\n" :
            std::cout << "false\n";

    std::cout << cm_test2 << " is a carmichael number : ";
    carm_num2? std::cout << "true\n" :
            std::cout << "false\n";

    std::cout << "\n";


    std::cout << "\n";
    return 0;
}

