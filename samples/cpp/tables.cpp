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
    // gpmp::core::DataTableStr result =
    //    dt.csv_read("../../data/forestfires.csv",
    //                {"month", "day", "temp", "wind"});
    gpmp::core::DataTableStr result = dt.csv_read(
        "../../data/Tetuan_power_consumption.csv",
        {"DateTime", "general diffuse flows", "Zone 1 Power Consumption"});

    std::cout << "FULL DATASET: \n";
    dt.display(result);

    // date_time accepts options to extract year, month, and time specifically
    // another way to call is date_time("col",true, true, true) - gets all
    // fields
    gpmp::core::DataTableStr date_time_result = dt.date_time("DateTime");
    std::cout << "TIMESTAMPS: \n";
    dt.display(date_time_result);

    std::vector<std::string> group_by_columns = {"Year", "Month"};
    std::cout << "GROUPS: \n";
    // group rows based on year/month
    std::vector<gpmp::core::DataTableStr> groups =
        dt.group_by(group_by_columns);

    // get first element of each group
    gpmp::core::DataTableStr first_element = dt.first(groups);
    dt.display(first_element);

    gpmp::core::DataTable dt2;

    gpmp::core::DataTableStr result2 =
        dt2.csv_read("../../data/forestfires.csv",
                     {"month", "day", "temp", "wind"});

    dt2.display(result2);
    // gpmp::core::DataTableStr date_time_result2 = dt2.date_time("month",
    // false, true, false); dt2.display(date_time_result2);
    std::vector<std::string> group_by_columns2 = {"month"};
    std::cout << "GROUPS: \n";
    // group rows based on year/month
    std::vector<gpmp::core::DataTableStr> groups2 =
        dt2.group_by(group_by_columns2);

    // get first element of each group
    gpmp::core::DataTableStr first_element2 = dt2.first(groups2);
    dt2.display(first_element2);

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
