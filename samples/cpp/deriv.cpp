/**
 * Test driver showing how to use different derivative-based
 * operations in openGPMP.
 *
 * @example deriv.cpp
 */
#include <openGPMP/calculus.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

int main() {
    std::cout << "DERIVATIVE EXAMPLE\n\n";

    // Example usage for the first polynomial
    gpmp::Differential *poly1 = new gpmp::Differential;
    poly1->add_term(3, 2);
    poly1->add_term(2, 1);
    poly1->add_term(1, 0);

    std::cout << "Original Polynomial 1: \n";
    poly1->display();

    gpmp::Differential derivative1 = poly1->power_rule();

    std::cout << "Derivative 1: \n";
    derivative1.display();

    delete poly1;

    // Example usage for the second polynomial
    gpmp::Differential *poly2 = new gpmp::Differential;
    poly2->add_term(3, 3);
    poly2->add_term(4, 2);
    poly2->add_term(6, 1);
    poly2->add_term(89, 1);

    std::cout << "Original Polynomial 2: \n";
    poly2->display();

    gpmp::Differential derivative2 = poly2->power_rule();

    std::cout << "Derivative 2: \n";
    derivative2.display();

    delete poly2;

    std::cout << "<------------>\n";

    double x_value = 2.0;
    double result = derivative2.eval(x_value);
    std::cout << "Derivative2 at x = " << x_value << ": " << result
              << std::endl;

    gpmp::Differential *poly3 = new gpmp::Differential;
    poly3->add_term(3, 3);
    poly3->add_term(-4, 2);
    poly3->add_term(22, 1);
    poly3->add_term(-89, 1);

    std::cout << "Original Polynomial 3: \n";
    poly3->display();

    gpmp::Differential derivative3 = poly3->power_rule().power_rule();
    std::cout << "Second derivative of Polynomial 3: \n";
    derivative3.display();

    delete poly3;

    std::cout << "<------------>\n";

    gpmp::Differential *poly4 = new gpmp::Differential;
    poly4->add_term(-3, 3);
    poly4->add_term(8, 2);
    poly4->add_term(-2, 1);
    poly4->add_term(1, 0);

    std::cout << "Original Polynomial 4: \n";
    poly4->display();

    double limitAtX = poly4->limit_at(2);
    std::cout << "Limit at x = 2: " << limitAtX << std::endl;

    double limitAtInfinity = poly4->limit_at_infinity();
    std::cout << "Limit as x approaches infinity: " << limitAtInfinity
              << std::endl;

    gpmp::Differential derivative4 = poly4->power_rule().power_rule();
    std::cout << "Second derivative of Polynomial 4: \n";
    derivative4.display();

    delete poly4;

    std::cout << "<------------>\n";

    gpmp::Differential base_func;
    base_func.add_term(4, 2);
    base_func.add_term(1, 0);

    gpmp::Differential base_deriv = base_func.chain_rule(base_func);

    gpmp::Differential outer_func;
    outer_func.add_term(1, 5);

    gpmp::Differential chain_result = outer_func.chain_rule(base_func);

    // Display the result
    std::cout << "Derivative of (4x^2 + 1)^5 is: ";
    chain_result.display();

    return 0;
}
