#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
//#include <openGPMP/core/datatable.hpp>
#include "../../include/core/datatable.hpp"
#include <regex>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

int main() {
    /*
     * for now specific columns must be in the order they appear in the file
     * being read in
     */
    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();
    gpmp::core::DataTable dt;

    // of type std::pair<std::vector<std::string>,
    //         std::vector<std::vector<std::string>>>
    gpmp::core::DataTableStr result =
        dt.csv_read("../../data/forestfires.csv",
                    {"month", "day", "temp", "wind"});
    // print result
    dt.display(result);

    // gpmp::DataTable dt_b;

    /* of type std::pair<std::vector<std::string>,
     *         std::vector<std::vector<std::string>>>
     */
    // read in a file of 1 million lines
    // gpmp::DataTableStr result_b = dt_b.csv_read("../../data/1m.csv",
    // {"Num"});

    /* of type std::pair<std::vector<int64_t>,
     *         std::vector<std::vector<int64_t>>>
     * convert DataTableStr to DataTableInt
     */
    // gpmp::DataTableInt result_int = dt_b.str_to_int(result_b);

    // dt_b.display(result_int);

    // time the time taken to perform the DataTable methods
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
