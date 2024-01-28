#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
// #include <openGPMP/core/datatable.hpp>
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

    // DataTableStr is of type std::pair<std::vector<std::string>,
    //                                   std::vector<std::vector<std::string>>>
    // gpmp::core::DataTableStr result = dt.csv_read(
    // gpmp::core::TableType result = dt.csv_read(
    //"../../data/forestfires.csv",
    // {"temp", "RH", "wind"});
    //    "../../data/Tetuan_power_consumption.csv",
    //    {"DateTime", "general diffuse flows", "Zone 1 Power Consumption"});

    // gpmp::core::TableType result = dt.csv_read("../../data/1m.csv");
    gpmp::core::DataTableStr result = dt.csv_read("../../data/1m.csv");

    // std::cout << "FULL DATASET: \n";
    //  display() takes a DataTableStr or default to displaying the current obj
    dt.display(result);
    // dt.info();

    // date_time accepts options to extract year, month, and time specifically
    // another way to call is date_time("col",true, true, true) - gets all
    // fields
    // gpmp::core::DataTableStr date_time_result = dt.datetime("DateTime");
    // std::cout << "TIMESTAMPS: \n";
    /*dt.display(date_time_result);

    std::vector<std::string> group_by_columns = {"Year", "Month"};
    std::cout << "GROUPS: \n";
    // group rows based on year/month
    std::vector<gpmp::core::DataTableStr> groups =
        dt.group_by(group_by_columns);

    // get first element of each group
    gpmp::core::DataTableStr first_element = dt.first(groups);
    dt.display(first_element);
  */
    // Second DataTable object
    //    gpmp::core::DataTable dt2;

    //    gpmp::core::TableType result2 =
    //        dt2.csv_read("../../data/forestfires.csv",
    //{"month", "day", "temp", "wind"});
    //                     {"temp", "RH", "wind"});

    //    dt2.display(result2);
    //    dt2.info();
    /*  // std::vector<std::string> sort_cols = {"month", "day"};
      std::cout << "SORT: \n";
      // sort based on the specified columns
      // dt2.sort(sort_cols);
      // dt2.display();
      std::cout << "DESCRIBE: \n";
      // prints some basic info about our DataTable object
      // dt2.describe();
      std::cout << "GROUPS2: \n";
      std::vector<std::string> group_by_columns2 = {"month"};
      // group rows based on month/day
      // std::vector<gpmp::core::DataTableStr> groups2 =
      // dt2.group_by(group_by_columns2);
      std::cout << "NATIVE TYPES: \n";
      std::vector<std::string> new_cols = {"temp", "wind"};
      std::vector<std::string> skip_cols = {"temp"};
      // convert a DataTable objects data to its native types, can exclude
      columns gpmp::core::TableType new_table = dt2.native_type(skip_cols);

      // get first element of each group
      // gpmp::core::DataTableStr first_element2 = dt2.first(groups2);
      // dt2.display(first_element2);
  */
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

    std::cout << "\nTime elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
