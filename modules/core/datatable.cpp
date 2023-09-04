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
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// TODO : optimize these methods, CSV reader using threads? loop unrolling?,
// etc? conversion functions to be quicker,
gpmp::core::DataTableStr
gpmp::core::DataTable::csv_read(std::string filename,
                                std::vector<std::string> columns) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<std::string>> data;
    std::string line;

    // Get the header line and parse the column names
    getline(file, line);
    std::stringstream header(line);
    std::vector<std::string> headerColumns;
    std::string columnName;

    while (getline(header, columnName, ',')) {
        headerColumns.push_back(columnName);
    }

    // If no columns are specified, read in all columns
    if (columns.empty()) {
        columns = headerColumns;
    }

    // Check if specified columns exist in the header
    for (const auto &column : columns) {
        if (find(headerColumns.begin(), headerColumns.end(), column) ==
            headerColumns.end()) {
            std::cerr << "Column " << column << " not found!\n";
            exit(EXIT_FAILURE);
        }
    }

    // Read in the data rows
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream rowStream(line);
        std::string value;
        int columnIndex = 0;

        while (getline(rowStream, value, ',')) {
            // If column is specified, only read in specified columns
            if (find(columns.begin(),
                     columns.end(),
                     headerColumns[columnIndex]) != columns.end()) {
                row.push_back(value);
            }

            columnIndex++;
        }

        if (row.size() > 0) {
            data.push_back(row);
        }
    }
    headers = headerColumns;

    file.close();
    return make_pair(columns, data);
}

void gpmp::core::DataTable::to_datetime(const std::string &new_column_name,
                                        const std::string &source_column_name) {
    // Find the index of the source column
    int source_index = -1;
    for (int i = 0; i < data_[0].size(); ++i) {
        if (data_[0][i] == source_column_name) {
            source_index = i;
            break;
        }
    }

    // Check if the source column exists
    if (source_index == -1) {
        std::cerr << "Source column not found: " << source_column_name
                  << std::endl;
        return;
    }

    // Iterate through the data and convert to datetime
    for (int i = 1; i < data_.size(); ++i) {
        std::string datetime_str = data_[i][source_index];
        // Convert the string to a datetime object (you can use your preferred
        // datetime library) Then replace the source column with the new
        // datetime column
        data_[i][source_index] =
            datetime_str;                    // Replace with the datetime object
        data_[0].push_back(new_column_name); // Add the new column name
    }
}

std::string
gpmp::core::DataTable::extract_month(const std::string &new_column_name,
                                     const std::string &source_column_name) {
    // Find the index of the source column in the headers
    int source_index = -1;
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == source_column_name) {
            source_index = i;
            break;
        }
    }

    // Check if the source column was found
    if (source_index == -1) {
        std::cerr << "Source column not found: " << source_column_name
                  << std::endl;
        return "";
    }

    // Create a new DataTable with the added month column
    gpmp::core::DataTable new_table;

    // Copy the headers
    new_table.headers = headers; // Copy the headers to the new DataTable
    new_table.headers.push_back(new_column_name); // Add the new column name

    // Iterate through the data and extract the month
    for (int i = 0; i < data_.size(); ++i) {
        if (data_[i].size() <= source_index) {
            std::cerr << "Row " << i
                      << " doesn't have enough columns for source column: "
                      << source_column_name << std::endl;
            continue; // Skip this row
        }

        std::string datetime_str = data_[i][source_index];

        // Assuming datetime_str is in the format "YYYY-MM-DD HH:MM:SS"
        std::tm timeinfo = {};
        std::istringstream ss(datetime_str);
        ss >> std::get_time(&timeinfo, "%m/%d/%Y %H:%M");

        if (ss.fail()) {
            std::cerr << "Failed to parse datetime: " << datetime_str
                      << std::endl;
            continue;
        }

        // Extract the month
        int month = timeinfo.tm_mon + 1; // tm_mon is 0-based

        // Add the month value to the new column in the new DataTable
        new_table.data_.push_back({std::to_string(month)});
    }

    // Replace the current instance with the new DataTable
    *this = new_table;

    // std::cout << ;

    return new_column_name;
}

void gpmp::core::DataTable::extract_year(
    const std::string &new_column_name,
    const std::string &source_column_name) {
    // Find the index of the source column in the headers
    int source_index = -1;
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == source_column_name) {
            source_index = i;
            break;
        }
    }

    // Check if the source column was found
    if (source_index == -1) {
        std::cerr << "Source column not found: " << source_column_name
                  << std::endl;
        return;
    }

    // Add the new column name for the year to the headers
    headers.push_back(new_column_name);

    // Iterate through the data and extract the year
    for (int i = 0; i < data_.size(); ++i) {
        if (data_[i].size() <= source_index) {
            std::cerr << "Row " << i
                      << " doesn't have enough columns for source column: "
                      << source_column_name << std::endl;
            continue; // Skip this row
        }

        std::string datetime_str = data_[i][source_index];

        // Assuming datetime_str is in the format "YYYY-MM-DD HH:MM:SS"
        std::tm timeinfo = {};
        std::istringstream ss(datetime_str);
        ss >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

        if (ss.fail()) {
            std::cerr << "Failed to parse datetime: " << datetime_str
                      << std::endl;
            continue;
        }

        // Extract the year
        int year = timeinfo.tm_year + 1900; // tm_year is years since 1900

        // Add the year value to the new column in the current DataTable
        data_[i].push_back(std::to_string(year));
    }
}
// Function to parse a datetime string and extract Year and Month
void parse_datetime(const std::string &datetime,
                    std::string &year,
                    std::string &month) {
    // Assuming the datetime format is "MM/DD/YYYY HH:MM" (you might need to
    // adjust this)
    std::istringstream ss(datetime);
    std::string datePart;
    std::getline(ss, datePart, ' '); // Get the date part (MM/DD/YYYY)

    std::istringstream dateStream(datePart);
    std::getline(dateStream, month, '/');
    std::getline(dateStream, month, '/');
    std::getline(dateStream, year, '/');
}

gpmp::core::DataTableStr
gpmp::core::DataTable::groupby_sum(const std::string &groupby_column1,
                                   const std::string &groupby_column2,
                                   const std::string &sum_column) {

    // Create a new DataTableStr to store the grouped data
    gpmp::core::DataTableStr grouped_data;

    // Copy the headers to the new DataTableStr
    grouped_data.first = {"Year", "Month", sum_column};

    // Initialize a map to store the grouped sum for each month
    std::map<std::pair<std::string, std::string>, double> group_sum;

    // Iterate through the data and calculate the sum for each group
    for (int i = 1; i < data_.size();
         ++i) { // Start from index 1 to skip the header row
        if (data_[i].size() <= 0) {
            continue; // Skip empty rows
        }

        std::string datetime =
            data_[i][0]; // Assuming DateTime is in the first column
        double value = 0.0;

        for (int j = 1; j < headers.size(); ++j) {
            if (headers[j] == sum_column) {
                // Convert the value to double
                value = std::stod(data_[i][j]);
                break;
            }
        }

        // Parse the DateTime to extract Year and Month
        std::string year, month;
        parse_datetime(datetime, year, month);

        // Use a pair of Year and Month as the key
        std::pair<std::string, std::string> group_key(year, month);

        // Add the value to the sum for this group
        group_sum[group_key] += value;
    }

    // Iterate through the map and add the grouped data to the new DataTableStr
    for (const auto &pair : group_sum) {
        // Create a new row for the grouped data
        std::vector<std::string> row;

        // Add the group values to the row
        row.push_back(pair.first.first);  // Year
        row.push_back(pair.first.second); // Month

        // Add the sum value to the row
        row.push_back(std::to_string(pair.second));

        // Add the row to the new DataTableStr
        grouped_data.second.push_back(row);
    }

    return grouped_data;
}

gpmp::core::DataTableInt
gpmp::core::DataTable::str_to_int(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableInt dest;

    for (const auto &v : src.first) {
        // check if v contains only digits
        if (std::regex_match(v, std::regex("\\d+"))) {
            dest.first.push_back(std::stoi(v));
        }
    }
    for (const auto &vv : src.second) {
        std::vector<int64_t> new_vec;
        for (const auto &v : vv) {
            // check if v contains only digits
            if (std::regex_match(v, std::regex("\\d+"))) {
                new_vec.push_back(std::stoi(v));
            }
        }
        dest.second.push_back(new_vec);
    }
    return dest;
}

gpmp::core::DataTableDouble
gpmp::core::DataTable::str_to_double(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableDouble dest;

    for (const auto &v : src.first) {
        if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
            dest.first.push_back(std::stold(v));
        }
    }

    for (const auto &vv : src.second) {
        std::vector<long double> new_vec;
        for (const auto &v : vv) {
            if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
                new_vec.push_back(std::stold(v));
            }
        }
        dest.second.push_back(new_vec);
    }

    return dest;
}
