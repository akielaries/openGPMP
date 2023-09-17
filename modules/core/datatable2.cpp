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
#include "../../include/core/datatable.hpp"
#include "../../include/core/utils.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <typeinfo>
#include <unordered_set>
#include <variant>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <cstring>
#include <mutex>
#include <cstdint>

/** Logger class object*/
static gpmp::core::Logger _log_;

// create method to create datatable from scratch? insert, drop, etc?

// Function to check if a string is an integer
bool is_int(const std::string &str) {
    // TODO : determine type of int based on length of largest val?
    return std::regex_match(str, std::regex(R"(-?\d+)"));
}

// Function to check if a string is a double
bool is_double(const std::string &str) {
    return std::regex_match(str, std::regex(R"(-?\d+\.\d+)"));
}

void handle_error(const char* msg) {
    perror(msg);
    exit(255);
}

const char* map_file(const char* fname, size_t& length)
{
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // Obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO: Close fd at some point in time, call munmap(...)
    return addr;
}

// TODO : optimize these methods, CSV reader using threads? loop unrolling?,
// etc? conversion functions to be quicker,
gpmp::core::TableType
gpmp::core::DataTable::csv_read(std::string filename, std::vector<std::string> columns) {
    std::ifstream file(filename);
    file.rdbuf()->pubsetbuf(nullptr, 0);  // Disable buffering


    if (!file.is_open()) {
        _log_.log(ERROR, "Unable to open file: " + filename + ".");
        throw std::runtime_error("Unable to open file: " + filename + ".");
    }

    gpmp::core::MixedType data;
    std::string line;

    // Read the header line once and parse the column names
    if (!getline(file, line)) {
        _log_.log(ERROR, "Empty file: " + filename + ".");
        throw std::runtime_error("Empty file: " + filename + ".");
    }

    std::stringstream header(line);
    std::vector<std::string> header_cols;
    std::string column_name;

    while (getline(header, column_name, ',')) {
        header_cols.emplace_back(column_name);
    }

    // If no columns are specified, read in all columns
    if (columns.empty()) {
        columns = header_cols;
    }

    // Check if specified columns exist in the header
    for (const auto &column : columns) {
        if (std::find(header_cols.begin(), header_cols.end(), column) == header_cols.end()) {
            _log_.log(ERROR, "Column: " + column + " not found");
            throw std::runtime_error("Column: " + column + " not found");
        }
    }

    // Reuse row_vector for each row to reduce memory overhead
    std::vector<std::variant<int64_t, long double, std::string>> row_vector;

    while (getline(file, line)) {
        std::stringstream rowStream(line);
        std::string value;
        int columnIndex = 0;

        while (getline(rowStream, value, ',')) {
            if (std::find(columns.begin(), columns.end(), header_cols[columnIndex]) != columns.end()) {
                // Check if the value contains exactly 1 decimal point
                size_t decimalPointCount = std::count(value.begin(), value.end(), '.');
                if (decimalPointCount == 1) {
                    try {
                        long double double_value = std::stold(value);
                        row_vector.emplace_back(double_value);
                    } catch (const std::invalid_argument &) {
                        row_vector.emplace_back(value);
                    }
                } else if ((value.find_first_not_of("0123456789-") == std::string::npos) &&
                           (std::count(value.begin(), value.end(), '-') <= 1)) {
                    try {
                        int64_t int_value = std::stoll(value);
                        row_vector.emplace_back(int_value);
                    } catch (const std::invalid_argument &) {
                        row_vector.emplace_back(value);
                    }
                } else {
                    row_vector.emplace_back(value);
                }
            }
            columnIndex++;
        }
        
        if (!row_vector.empty()) {
            data.emplace_back(row_vector);
            row_vector.clear();
        }
    }

    file.close();

    // Populate headers_ class variable
    headers_ = columns;
    // Populate data_ class variable
    data_ = data;

    return make_pair(columns, data);
}

// The main DataTable display method
// TODO : edit this display method to read in the first 15 and last 15 by
// default. if display_all = true then fetch all rows
void gpmp::core::DataTable::display(const gpmp::core::TableType &data,
                                    bool display_all) {
    int num_columns = data.first.size();
    int num_rows = data.second.size();
    int num_omitted_rows = 0;

    std::vector<int> max_column_widths(num_columns, 0);

    // Calculate the maximum width for each column based on column headers
    for (int i = 0; i < num_columns; i++) {
        max_column_widths[i] = data.first[i].length();
    }

    // Calculate the maximum width for each column based on data rows
    for (int i = 0; i < num_columns; i++) {
        for (const auto &row : data.second) {
            if (i < static_cast<int>(row.size())) {
                std::visit(
                    [&max_column_widths, &i](const auto &cellValue) {
                        using T = std::decay_t<decltype(cellValue)>;
                        if constexpr (std::is_same_v<T, std::string>) {
                            max_column_widths[i] =
                                std::max(max_column_widths[i],
                                         static_cast<int>(cellValue.length()));
                        } else if constexpr (std::is_integral_v<T> ||
                                             std::is_floating_point_v<T>) {
                            max_column_widths[i] = std::max(
                                max_column_widths[i],
                                static_cast<int>(
                                    std::to_string(cellValue).length()));
                        }
                    },
                    row[i]);
            }
        }
    }

    const int dateTimeColumnIndex = 0;
    max_column_widths[dateTimeColumnIndex] =
        std::max(max_column_widths[dateTimeColumnIndex], 0);

    // Define a function to print a row
    auto printRow = [&data, &max_column_widths, num_columns](int row_index) {
        std::cout << std::setw(7) << std::right << row_index << "  ";

        for (int j = 0; j < num_columns; j++) {
            if (j < static_cast<int>(data.second[row_index].size())) {
                std::visit(
                    [&max_column_widths, &j](const auto &cellValue) {
                        using T = std::decay_t<decltype(cellValue)>;
                        if constexpr (std::is_same_v<T, double> ||
                                      std::is_same_v<T, long double>) {
                            // Convert the value to a string without trailing
                            // zeros
                            std::string cellValueStr =
                                std::to_string(cellValue);
                            cellValueStr.erase(
                                cellValueStr.find_last_not_of('0') + 1,
                                std::string::npos);
                            cellValueStr.erase(
                                cellValueStr.find_last_not_of('.') + 1,
                                std::string::npos);

                            std::cout << std::setw(max_column_widths[j])
                                      << std::right << cellValueStr << "  ";
                        } else {
                            std::cout << std::setw(max_column_widths[j])
                                      << std::right << cellValue << "  ";
                        }
                    },
                    data.second[row_index][j]);
            }
        }

        std::cout << std::endl;
    };

    // Print headers
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
            printRow(i);
        }
        num_omitted_rows = num_elements - MAX_ROWS;
        std::cout << "...\n";
        std::cout << "[" << num_omitted_rows << " rows omitted]\n";
        for (int i = num_elements - SHOW_ROWS; i < num_elements; i++) {
            printRow(i);
        }
    } else {
        // Print all rows
        for (int i = 0; i < num_elements; i++) {
            printRow(i);
        }
    }

    // Print the number of rows and columns
    std::cout << "[" << num_rows << " rows"
              << " x " << num_columns << " columns";
    std::cout << "]\n\n";
}

// Overload method for display(). Allows user to display the existing
// data in a DataTable object.
void gpmp::core::DataTable::display(bool display_all) {
    display(std::make_pair(headers_, data_), display_all);
}

gpmp::core::DataType
gpmp::core::DataTable::inferType(const std::vector<std::string> &column) {
    int integer_count = 0;
    int double_count = 0;
    int string_count = 0;

    for (const std::string &cell : column) {
        if (is_int(cell)) {
            integer_count++;
        } else if (is_double(cell)) {
            double_count++;
        } else {
            string_count++;
        }
    }

    _log_.log(INFO,
              "int/double/str: " + std::to_string(integer_count) + "/" +
                  std::to_string(double_count) + "/" +
                  std::to_string(string_count));

    if (integer_count > double_count) {
        return DataType::dt_int32;
    } else if (double_count > integer_count) {
        return DataType::dt_double;
    } else {
        return DataType::dt_str;
    }
}
std::string dt_to_str(gpmp::core::DataType type) {
    switch (type) {
    case gpmp::core::DataType::dt_int64:
        return "int64";
    case gpmp::core::DataType::dt_ldouble:
        return "long double";
    case gpmp::core::DataType::dt_str:
        return "std::string";
    // TODO : Add more cases if needed
    default:
        return "Unknown";
    }
}

gpmp::core::TableType gpmp::core::DataTable::native_type(
    const std::vector<std::string> &skip_columns) {
    gpmp::core::TableType mixed_data;
    std::cout << "HEADERS:" << headers_.size() << std::endl;
    std::cout << "ROWS:" << data_.size() << std::endl;

    // Traverse column headers, skipping specified columns
    for (const std::string &header : headers_) {

        if (std::find(skip_columns.begin(), skip_columns.end(), header) !=
            skip_columns.end()) {
            continue; // Skip this column
        }

        std::cout << header << " ";
        // push column headers into mixed_data var
        mixed_data.first.emplace_back(header);
    }

    std::cout << std::endl;

    // Traverse rows, skip rows of the specified columns
    for (size_t col = 0; col < headers_.size(); ++col) {
        if (std::find(skip_columns.begin(),
                      skip_columns.end(),
                      headers_[col]) != skip_columns.end()) {
            continue; // Skip this column
        }
        _log_.log(INFO, "Column: " + headers_[col]);

        // Collect data for this column
        std::vector<std::string> column_data;
        for (const std::vector<std::variant<int64_t, long double, std::string>>
                 &row : data_) {
            column_data.emplace_back(
                std::get<std::string>(row[col])); // Convert variant to string
        }

        std::vector<std::variant<int64_t, long double, std::string>>
            converted_data;

        // Call inferType on the column's data
        gpmp::core::DataType column_type = inferType(column_data);

        _log_.log(INFO, "Using type: " + dt_to_str(column_type));

        // Check type and convert rows
        if (column_type == gpmp::core::DataType::dt_int32) {
            std::cout << "INT\n";
            for (const std::string &cell : column_data) {
                converted_data.emplace_back(std::stoi(cell));
            }
        } else if (column_type == gpmp::core::DataType::dt_double) {
            std::cout << "DOUBLE\n";
            for (const std::string &cell : column_data) {
                converted_data.emplace_back(std::stod(cell));
            }
        } else {
            std::cout << "STRING\n";
            for (const std::string &cell : column_data) {
                converted_data.emplace_back(cell);
            }
        }
        // push rows into the mixed_data var
        mixed_data.second.emplace_back(converted_data);
    }

    /*std::cout << "Mixed Data:" << std::endl;
    for (const std::string &header : mixed_data.first) {
        std::cout << header << " ";
    }
    std::cout << std::endl;

    for (const auto &row : mixed_data.second) {
        for (const auto &cell : row) {
            if (std::holds_alternative<int64_t>(cell)) {
                std::cout << std::get<int64_t>(cell) << " ";
            } else if (std::holds_alternative<long double>(cell)) {
                std::cout << std::get<long double>(cell) << " ";
            } else if (std::holds_alternative<std::string>(cell)) {
                std::cout << std::get<std::string>(cell) << " ";
            }
        }
        std::cout << std::endl;
    }*/

    return mixed_data;
}

// Extracts date/time information from given column
// TODO: add additional options for detecting/converting date/time columns
// to numeric formats
/*
gpmp::core::DataTableStr
gpmp::core::DataTable::datetime(std::string column_name,
                                bool extract_year,
                                bool extract_month,
                                bool extract_time) {
    // Find the index of the specified column
    auto column_iter = std::find(headers_.begin(), headers_.end(), column_name);
    if (column_iter == headers_.end()) {
        _log_.log(ERROR, "Column: " + column_name + " node found");
        exit(EXIT_FAILURE);
    }
    int column_index = std::distance(headers_.begin(), column_iter);

    // Extract components from each row
    std::vector<std::string> new_headers = headers_;
    std::vector<std::vector<std::string>> new_data;

    // Iterate and populate the additional columns
    for (size_t row_index = 0; row_index < data_.size(); ++row_index) {
        std::vector<std::string> row = data_[row_index];
        // If column row is not found
        if (row.size() <= static_cast<size_t>(column_index)) {
            _log_.log(ERROR, "Column: " + column_name + " not found");

            exit(EXIT_FAILURE);
        }

        std::string timestamp = row[column_index];
        std::string year, month, time;

        // Create a new row with extracted components
        std::vector<std::string> new_row;

        // Extract year, month, and time components
        if (extract_year) {
            year = timestamp.substr(timestamp.find_last_of('/') + 1, 4);
            new_row.emplace_back(year);
        }
        if (extract_month) {
            month = timestamp.substr(0, timestamp.find_first_of('/'));
            new_row.emplace_back(month);
        }
        if (extract_time) {
            time = timestamp.substr(timestamp.find(' ') + 1);
            new_row.emplace_back(time);
        }

        // append original row data
        new_row.insert(new_row.end(), row.begin(), row.end());
        // add new rows
        new_data.emplace_back(new_row);
    }

    // Create new headers based on the extracted components
    if (extract_month)
        new_headers.insert(new_headers.begin(), "Month");
    if (extract_year)
        new_headers.insert(new_headers.begin(), "Year");
    if (extract_time)
        new_headers.insert(new_headers.begin(), "Time");

    // set class car data_ to hold rows/lines
    data_ = new_data;
    // set class var modified headers to new headers
    // new_headers_ = new_headers;
    headers_ = new_headers;

    return std::make_pair(new_headers, new_data);
}

// Sort specified columns, by default in asending order
void gpmp::core::DataTable::sort(const std::vector<std::string> &sort_columns,
                                 bool ascending) {
    // Extract the column indices to be sorted by from the original data
    std::vector<size_t> column_indices;
    for (const std::string &column : sort_columns) {
        auto iter = std::find(headers_.begin(), headers_.end(), column);
        if (iter != headers_.end()) {
            size_t index = std::distance(headers_.begin(), iter);
            column_indices.emplace_back(index);
        }
    }

    // Sort the data based on the specified columns
    std::stable_sort(data_.begin(),
                     data_.end(),
                     [&](const std::vector<std::string> &row1,
                         const std::vector<std::string> &row2) {
                         for (size_t index : column_indices) {
                             if (row1[index] != row2[index]) {
                                 if (ascending) {
                                     return row1[index] < row2[index];
                                 } else {
                                     return row1[index] > row2[index];
                                 }
                             }
                         }
                         // Rows are equal, nothing to sort
                         return false;
                     });
}

// Group rows by specific columns
std::vector<gpmp::core::DataTableStr>
gpmp::core::DataTable::group_by(std::vector<std::string> group_by_columns) {
    // Find the indices of the specified group by columns
    std::vector<int> group_by_indices;

    // Traverse group column names
    for (const std::string &column_name : group_by_columns) {
        std::cout << "Searching for column: " << column_name << std::endl;

        // Find start/end and match column name
        auto column_iter =
            std::find(headers_.begin(), headers_.end(), column_name);

        // If no columns
        if (column_iter == headers_.end()) {
            _log_.log(ERROR, "Column: " + column_name + " not found");
            exit(EXIT_FAILURE);
        }
        // column index set to distance from start of first col to nexter iter
        int column_index = std::distance(headers_.begin(), column_iter);
        // add column index to group
        group_by_indices.emplace_back(column_index);
    }

    // Group the data based on the specified columns using a vector
    std::vector<std::pair<std::vector<std::string>, gpmp::core::DataTableStr>>
        groups;

    // Traverse row/line data
    for (const std::vector<std::string> &row : data_) {
        // store group key for each row
        std::vector<std::string> group_key;
        // Fill group key from specified group column names
        for (int index : group_by_indices) {
            group_key.emplace_back(row[index]);
        }

        // Check if the group already exists
        auto group_iter = std::find_if(
            groups.begin(),
            groups.end(),
            [&group_key](const std::pair<std::vector<std::string>,
                                         gpmp::core::DataTableStr> &group) {
                return group.first == group_key;
            });
        // If the group DNE create a new one to add to groups vector
        if (group_iter == groups.end()) {
            // Create a new group
            groups.emplace_back(
                {group_key, gpmp::core::DataTableStr(headers_, {})});
            group_iter = groups.end() - 1;
        }
        // Add current row to group
        group_iter->second.second.emplace_back(row);
    }

    // Extract the grouped data into a vector
    std::vector<gpmp::core::DataTableStr> grouped_data;
    // Iterate over sorted groups to push onto result vector
    for (const auto &group : groups) {
        grouped_data.emplace_back(group.second);
    }

    // Return final DataTableStr type
    return grouped_data;
}

// Get first element of each created group
gpmp::core::DataTableStr gpmp::core::DataTable::first(
    const std::vector<gpmp::core::DataTableStr> &groups) const {
    if (groups.empty()) {
        // Handle the case when there are no groups
        return std::make_pair(std::vector<std::string>(),
                              std::vector<std::vector<std::string>>());
    }

    std::vector<std::vector<std::string>> first_rows;

    for (const gpmp::core::DataTableStr &group : groups) {
        if (!group.second.empty()) {
            first_rows.emplace_back(
                group.second[0]); // Get the first row of each group
        }
    }

    if (!first_rows.empty()) {
        // Assuming all groups have the same headers as the first group
        return std::make_pair(groups[0].first, first_rows);
    } else {
        // Handle the case when there are no first rows found.
        return std::make_pair(groups[0].first,
                              std::vector<std::vector<std::string>>());
    }
}
*/

void gpmp::core::DataTable::info() {
    // Calculate memory usage for each column and keep track of data type
    std::vector<double> column_memory_usages(headers_.size(), 0.0);
    std::vector<std::string> column_data_types(headers_.size());
    double total_memory_usage_kb = 0.0;

    // Calculate memory usage in bytes for the entire table
    size_t memory_usage_bytes = sizeof(headers_);
    for (const auto &row : data_) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (std::holds_alternative<int64_t>(row[i])) {
                memory_usage_bytes += sizeof(int64_t);
                column_memory_usages[i] +=
                    static_cast<double>(sizeof(int64_t)) / 1024.0;
                column_data_types[i] = "int64_t";
            } else if (std::holds_alternative<long double>(row[i])) {
                memory_usage_bytes += sizeof(long double);
                column_memory_usages[i] +=
                    static_cast<double>(sizeof(long double)) / 1024.0;
                column_data_types[i] = "long double";
            } else if (std::holds_alternative<std::string>(row[i])) {
                memory_usage_bytes += std::get<std::string>(row[i]).capacity();
                column_memory_usages[i] +=
                    static_cast<double>(
                        std::get<std::string>(row[i]).capacity()) /
                    1024.0;
                column_data_types[i] = "std::string";
            }
        }
    }

    // Convert total memory usage to KB
    total_memory_usage_kb = static_cast<double>(memory_usage_bytes) / 1024.0;

    // Find the maximum column name length
    size_t max_column_name_length = 0;
    for (const std::string &column : headers_) {
        max_column_name_length =
            std::max(max_column_name_length, column.length());
    }

    // Find the maximum data type length
    size_t max_data_type_length = 0;
    for (const std::string &data_type : column_data_types) {
        max_data_type_length =
            std::max(max_data_type_length, data_type.length());
    }

    // Set the column width for formatting
    int column_width = static_cast<int>(std::max(max_column_name_length,
                                                 max_data_type_length)) +
                       2; // Add extra padding

    // Print header
    std::cout << std::left << std::setw(column_width) << "Column"
              << std::setw(column_width) << "Type" << std::setw(column_width)
              << "Memory Usage (KB)" << std::endl;

    // Print data
    for (size_t i = 0; i < headers_.size(); ++i) {
        std::cout << std::left << std::setw(column_width) << headers_[i]
                  << std::setw(column_width) << column_data_types[i]
                  << std::setw(column_width) << std::fixed
                  << std::setprecision(2) << column_memory_usages[i]
                  << std::endl;
    }

    // Print total table memory usage
    std::cout << "\nTotal Memory Usage: " << std::fixed << std::setprecision(2)
              << total_memory_usage_kb << " KB" << std::endl;
}

// Prints some basic information about a DataTable object
gpmp::core::DataTableInt
gpmp::core::DataTable::str_to_int(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableInt dest;

    for (const auto &v : src.first) {
        // check if v contains only digits
        if (std::regex_match(v, std::regex("\\d+"))) {
            dest.first.emplace_back(std::stoi(v));
        }
    }
    for (const auto &vv : src.second) {
        std::vector<int64_t> new_vec;
        for (const auto &v : vv) {
            // check if v contains only digits
            if (std::regex_match(v, std::regex("\\d+"))) {
                new_vec.emplace_back(std::stoi(v));
            }
        }
        dest.second.emplace_back(new_vec);
    }
    return dest;
}

gpmp::core::DataTableDouble
gpmp::core::DataTable::str_to_double(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableDouble dest;

    for (const auto &v : src.first) {
        if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
            dest.first.emplace_back(std::stold(v));
        }
    }

    for (const auto &vv : src.second) {
        std::vector<long double> new_vec;
        for (const auto &v : vv) {
            if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
                new_vec.emplace_back(std::stold(v));
            }
        }
        dest.second.emplace_back(new_vec);
    }

    return dest;
}
