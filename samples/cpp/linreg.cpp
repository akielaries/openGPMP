/**
 * Simple test driver showing how to use simple linear regression on a 2-column
 * dataset. The current linear regression method is not capable of multiple
 * linear regression, to generate use of this implementation data sets must
 * either be two column in nature or users must disect data for a proper
 * key,value response
 *
 * @example reg.cpp
 */
#include <iostream>
//#include <openGPMP/ml/linreg.hpp>
#include "../../include/core/datatable.hpp"
#include "../../include/ml/linreg.hpp"
#include <stdio.h>

int main() {
    gpmp::ml::LinearRegression reg;
    gpmp::core::DataTable dt;
    // gpmp::core::DataTableStr result =
    // dt.csv_read("../../data/forestfires.csv",
    //                                               {"month", "day", "temp",
    //                                               "wind"});

    gpmp::core::DataTableStr result =
        dt.csv_read("../../data/school_scores.csv", {"Year", "GPA"});

    dt.display(result);
    std::vector<std::string> columns = {"Year", "GPA"};
    reg.get_input(result, columns);

    // declare Regression class object

    printf("LINEAR REGRESSION EXAMPLE ON YEAR/GPA DATA IN "
           "MATHEMATICS\n");

    // Printing the best fitting line
    reg.best_fit();

    /* CALCULATING PREDICTIONS */
    int v1 = 1995;
    double v1_v = reg.predict(v1);
    double v1_e = reg.error_in(v1);
    printf("Predicted value at %d   = %f\n", v1, v1_v);
    printf("Error value at %d       = %f\n\n", v1, v1_e);

    int v2 = 1997;
    double v2_v = reg.predict(v2);
    double v2_e = reg.error_in(v2);
    printf("Predicted value at %d   = %f\n", v2, v2_v);
    printf("Error value at %d       = %f\n\n", v2, v2_e);

    int v3 = 1999;
    double v3_v = reg.predict(v3);
    double v3_e = reg.error_in(v3);
    printf("Predicted value at %d   = %f\n", v3, v3_v);
    printf("Error value at %d       = %f\n\n", v3, v3_e);

    int v4 = 2001;
    double v4_v = reg.predict(v4);
    double v4_e = reg.error_in(v4);
    printf("Predicted value at %d   = %f\n", v4, v4_v);
    printf("Error value at %d       = %f\n\n", v4, v4_e);

    int v5 = 2003;
    double v5_v = reg.predict(v5);
    double v5_e = reg.error_in(v5);
    printf("Predicted value at %d   = %f\n", v5, v5_v);
    printf("Error value at %d       = %f\n\n", v5, v5_e);

    int v6 = 2005;
    double v6_v = reg.predict(v6);
    double v6_e = reg.error_in(v6);
    printf("Predicted value at %d   = %f\n", v6, v6_v);
    printf("Error value at %d       = %f\n\n", v6, v6_e);

    int v7 = 2006;
    double v7_v = reg.predict(v7);
    double v7_e = reg.error_in(v7);
    printf("Predicted value at %d   = %f\n", v7, v7_v);
    printf("Error value at %d       = %f\n\n", v7, v7_e);

    int v8 = 2007;
    double v8_v = reg.predict(v8);
    double v8_e = reg.error_in(v8);
    printf("Predicted value at %d   = %f\n", v8, v8_v);
    printf("Error value at %d       = %f\n\n", v8, v8_e);

    int v10 = 2016;
    double v10_v = reg.predict(v10);
    double v10_e = reg.error_in(v10);
    printf("Predicted value at %d   = %f\n", v10, v10_v);
    printf("Error value at %d       = %f\n\n", v10, v10_e);

    int v11 = 2017;
    double v11_v = reg.predict(v11);
    double v11_e = reg.error_in(v11);
    printf("Predicted value at %d   = %f\n", v11, v11_v);
    printf("Error value at %d       = %f\n\n", v11, v11_e);

    return 0;
}
