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
 * seen here : https://akielaries.github.io/openGPMP/ along with
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

#define MAX_ROWS 30
#define SHOW_ROWS 15

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gpmp {

namespace core {

/** @brief enum for representing different data types
 */
enum class DataType { Unknown, String, Integer, Double };

typedef std::pair<
    std::vector<std::string>,
    std::vector<std::vector<std::variant<int64_t, long double, std::string>>>>
    TableType;

/** @typedef alias for the pair type of strings
 */
typedef std::pair<std::vector<std::string>,
                  std::vector<std::vector<std::string>>>
    DataTableStr;
/** @typedef alias for pair type of 64 bit integers
 */
typedef std::pair<std::vector<int64_t>, std::vector<std::vector<int64_t>>>
    DataTableInt;
/** @typedef alias for pair type of long doubles
 */
typedef std::pair<std::vector<long double>,
                  std::vector<std::vector<long double>>>
    DataTableDouble;

class DataTable {
  private:
    // original DataTable object headers
    std::vector<std::string> headers_;
    // original DataTable object rows
    std::vector<std::vector<std::string>> rows_;
    // modified DataTable object headers
    std::vector<std::string> new_headers_;
    // vector to hold data
    std::vector<std::vector<std::string>> data_;

    // original DataTable data
    DataTableStr original_data_;

  public:
    DataTable() {
        // Initialize data_ and headers_ to empty vectors
        data_ = std::vector<std::vector<std::string>>();
        headers_ = std::vector<std::string>();
    }

    /**
     * @brief Reads a CSV file and returns a DataTableStr
     * parses CSV files and stores all data as strings
     * @param filename the path to the CSV file
     * @param columns optional vector of column names to read in, if empty all
     * columns will be read in
     * @return a DataTableStr containing the column names and data
     */
    DataTableStr csv_read(std::string filename,
                          std::vector<std::string> columns = {});

    /**
     * @brief Write DataTable to a CSV file
     */
    void csv_write();

    // TODO: TOML and JSON readers?
    /**
     * @brief Reads a TSV file and returns a DataTableStr
     * parses TSV files and stores all data as strings
     * @param filename the path to the TSV file
     * @param columns optional vector of column names to read in, if empty all
     * columns will be read in
     * @return a DataTableStr containing the column names and data
     */
    DataTableStr tsv_read(std::string filename,
                          std::vector<std::string> columns = {});

    /**
     * @brief Reads a JSON file and returns a DataTableStr
     * parses JSON files and stores all data as strings
     * @param filename the path to the JSON file
     * @param objs optional vector of JSON object names to read in, if empty all
     * objects will be read in
     * @return a DataTableStr containing the column names and data
     */
    DataTableStr json_read(std::string filename,
                           std::vector<std::string> objs = {});

    /**
     * @brief Extracts date and time components from a timestamp column
     * @param column_name The name of the timestamp column
     * @param extract_year If true, extract the year component
     * @param extract_month If true, extract the month component
     * @param extract_time If true, extract the time component
     * @return A new DataTableStr with extracted components
     */
    DataTableStr datetime(std::string column_name,
                          bool extract_year = true,
                          bool extract_month = true,
                          bool extract_time = false);

    /**
     * @brief Sorts the rows of the DataTable based on specified columns.
     * @param sort_columns A vector of column names to sort by.
     * @param ascending If true, sort in ascending order; otherwise, sort in
     * descending order, default is true.
     */
    void sort(const std::vector<std::string> &sort_columns,
              bool ascending = true);

    // customSort(const std::vector<std::string>& columnNames,
    // gpmp::core::DataTableStr& data);

    /**
     * @brief Groups the data by specified columns
     * @param group_by_columns The column names to group by
     * @return A vector of DataTableStr, each containing a group of rows
     */
    std::vector<DataTableStr>
    group_by(std::vector<std::string> group_by_columns);

    /**
     * @brief Gets the first element of each created group
     * @param groups Return type of `gpmp::core::DataTable.group()`
     * @return a DataTableStr
     */
    DataTableStr
    first(const std::vector<gpmp::core::DataTableStr> &groups) const;

    /**
     * @brief Prints some information about the DataTable
     */
    void describe();

    /**
     * @brief Converts DataTable column's rows to their native types.
     * Since the existing DataTable read/load related methods hone in
     * on the DataTableStr type, there must be a way to get those types
     * to their native formats.
     */
    TableType native_type(const std::vector<std::string> &skip_columns = {});

    DataType inferType(const std::vector<std::string> &column);

    /**
     * @brief Converts a DataTableStr to a DataTableInt
     * @param src The DataTableStr to convert
     * @return The converted DataTableInt
     * @note This function assumes that the input DataTableStr contains only
     * elements that can be converted to a 64-bit integer using std::stoi()
     * @TODO allow for specific columns to be converted
     * @TODO make use of ThreadPool
     */
    DataTableInt str_to_int(DataTableStr src);

    /**
     * @brief Converts a DataTableStr to a DataTableDouble
     * @param src A DataTableStr object to be converted
     * @return The converted DataTableDouble
     * @note The function assumes the input DataTableStr contains only valid
     * double type elements
     */
    DataTableDouble str_to_double(DataTableStr src);

    /**
     * @brief Sort a DataTable based on a specified column
     */

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
        // Get the number of columns and rows in the data
        int num_columns = data.first.size();
        int num_rows = data.second.size();
        int num_omitted_rows = 0;

        // Initialize max_column_widths with the lengths of column headers
        std::vector<int> max_column_widths(num_columns, 0);

        // Calculate the maximum width for each column based on column headers
        for (int i = 0; i < num_columns; i++) {
            max_column_widths[i] = data.first[i].length();
        }

        // Calculate the maximum width for each column based on data rows
        for (int i = 0; i < num_columns; i++) {
            for (const auto &row : data.second) {
                if (i < static_cast<int>(row.size())) {
                    max_column_widths[i] =
                        std::max(max_column_widths[i],
                                 static_cast<int>(row[i].length()));
                }
            }
        }

        // Set a larger width for the DateTime column (adjust the index as
        // needed later on)
        const int dateTimeColumnIndex = 0;
        // adjust as needed?
        max_column_widths[dateTimeColumnIndex] =
            std::max(max_column_widths[dateTimeColumnIndex], 0);

        // Print headers with right-aligned values
        std::cout << std::setw(7) << std::right << "Index"
                  << "  ";

        for (int i = 0; i < num_columns; i++) {
            std::cout << std::setw(max_column_widths[i]) << std::right
                      << data.first[i] << "  ";
        }
        std::cout << std::endl;

        int num_elements = data.second.size();
        if (!display_all && num_elements > MAX_ROWS) {
            for (int i = 0; i < SHOW_ROWS; i++) {
                // Prit index
                std::cout << std::setw(7) << std::right << i << "  ";
                // Print each row with right-aligned values
                for (int j = 0; j < num_columns; j++) {
                    if (j < static_cast<int>(data.second[i].size())) {
                        std::cout << std::setw(max_column_widths[j])
                                  << std::right << data.second[i][j] << "  ";
                    }
                }
                std::cout << std::endl;
            }
            num_omitted_rows = num_elements - MAX_ROWS;
            std::cout << "...\n";
            std::cout << "[" << num_omitted_rows << " rows omitted]\n";
            for (int i = num_elements - SHOW_ROWS; i < num_elements; i++) {
                std::cout << std::setw(7) << std::right << i << "  ";
                // Print each row with right-aligned values
                for (int j = 0; j < num_columns; j++) {
                    if (j < static_cast<int>(data.second[i].size())) {
                        std::cout << std::setw(max_column_widths[j])
                                  << std::right << data.second[i][j] << "  ";
                    }
                }
                std::cout << std::endl;
            }
        } else {
            // Print all rows with right-aligned values
            for (int i = 0; i < num_elements; i++) {

                // Print index
                std::cout << std::setw(7) << std::right << i << "  ";
                for (int j = 0; j < num_columns; j++) {
                    if (j < static_cast<int>(data.second[i].size())) {

                        // Print formatted row
                        std::cout << std::setw(max_column_widths[j])
                                  << std::right << data.second[i][j] << "  ";
                    }
                }
                std::cout << std::endl;
            }
        }

        // Print the number of rows and columns
        std::cout << "[" << num_rows << " rows"
                  << " x " << num_columns << " columns";
        std::cout << "]\n\n";
    }

    /**
     * @brief Overload function for display() defaults to displaying what is
     * currently stored in a DataTable object.
     * @param display_all Display all rows, defaults to false.
     */
    void display(bool display_all = false) {
        display(std::make_pair(headers_, data_), display_all);
    }
};

} // namespace core
} // namespace gpmp

#endif // DATATABLE_HPP
