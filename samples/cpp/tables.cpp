#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <openGPMP/core/datatable.hpp>
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

    // DataTableStr is of type std::pair<std::vector<std::string>,
    gpmp::core::DataTableStr result = dt.csv_read("../../data/1m.csv");

    //  display() takes a DataTableStr or default to displaying the current obj
    dt.display(result);

    // time the time taken to perform the DataTable methods
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "\nTime elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
