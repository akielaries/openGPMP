/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * The datatable class similar to the Pandas Dataframe, R data.table, etc
 * with many more limitations.
 */
#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mtpk {

// alias for the pair type of strings
typedef std::pair<std::vector<std::string>,
                  std::vector<std::vector<std::string>>>
    DataTableStr;
// alias for pair type of 64 bit integers
typedef std::pair<std::vector<int64_t>, std::vector<std::vector<int64_t>>>
    DataTableInt;

// alias for pair type of long doubles
typedef std::pair<std::vector<long double>,
                  std::vector<std::vector<long double>>>
    DataTableDouble;

class DataTable {
  public:
    /**
     * @brief Reads a CSV file and returns a DataTableStr.
     * parses CSV files and stores all data as strings
     * @param filename the path to the CSV file
     * @param columns optional vector of column names to read in, if empty all
     * columns will be read in
     * @return a DataTableStr containing the column names and data
     */
    DataTableStr csv_read(std::string filename,
                          std::vector<std::string> columns = {});

    // TODO: TOML and JSON readers?

    // converts a type DataTableStr to DataTableInt
    /**
     * @brief Converts a DataTableStr to a DataTableInt
     * @param src The DataTableStr to convert
     * @return The converted DataTableInt
     * @note This function assumes that the input DataTableStr contains only
     * elements that can be converted to a 64-bit integer using std::stoi().
     * @TODO allow for specific columns to be converted
     * @TODO make use of ThreadPool
     */
    DataTableInt str_to_int(DataTableStr src);

    /**
     * @brief Converts a DataTableStr to a DataTableDouble
     * @param src A DataTableStr object to be converted.
     * @return The converted DataTableDouble.
     * @note The function assumes the input DataTableStr contains only valid
     * double type elements
     */
    DataTableDouble str_to_double(DataTableStr src);

    /**
     * @brief Displays a DataTable of type T with the option to display all or a
     * subset of rows
     * @tparam T The type of the DataTable to be displayed
     * @param data A pair of vectors representing the header and data rows of
     * the DataTable
     * @param display_all A flag indicating whether to display all rows or just
     * a subset
     */
    template <typename T>
    void display(std::pair<std::vector<T>, std::vector<std::vector<T>>> data,
                 bool display_all = false) {
        int num_columns = data.first.size();
        int num_rows = data.second.size();
        int num_omitted_rows = 0;

        for (const auto &header : data.first) {
            std::cout << header << "\t";
        }
        std::cout << std::endl;

        int num_elements = data.second.size();
        if (!display_all && num_elements > 10) {
            for (int i = 0; i < 5; i++) {
                for (const auto &value : data.second[i]) {
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
            num_omitted_rows = num_elements - 10;
            std::cout << "...\n";
            std::cout << "[" << num_omitted_rows << " rows omitted]\n";
            for (int i = num_elements - 5; i < num_elements; i++) {
                for (const auto &value : data.second[i]) {
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
        } 
        else {
            for (const auto &row : data.second) {
                for (const auto &value : row) {
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
        }

        std::cout << "[" << num_rows << " rows"
                  << " x " << num_columns << " columns";
        std::cout << "]\n\n";
    }
};

} // namespace mtpk

#endif // DATATABLE_HPP
