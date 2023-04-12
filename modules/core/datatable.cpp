#include "../../include/core/datatable.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

mtpk::DataTableStr mtpk::DataTable::csv_read(std::string filename,
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
            std::cerr << "Column not found: " << column << std::endl;
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
            if (find(columns.begin(), columns.end(),
                     headerColumns[columnIndex]) != columns.end()) {
                row.push_back(value);
            }

            columnIndex++;
        }

        if (row.size() > 0) {
            data.push_back(row);
        }
    }

    file.close();
    return make_pair(columns, data);
}

mtpk::DataTableInt mtpk::DataTable::str_to_int(mtpk::DataTableStr src) {
    mtpk::DataTableInt dest;

    for (const auto &v : src.first) {
        if (std::regex_match(
                v, std::regex("\\d+"))) { // check if v contains only digits
            dest.first.push_back(std::stoi(v));
        }
    }
    for (const auto &vv : src.second) {
        std::vector<int64_t> new_vec;
        for (const auto &v : vv) {
            if (std::regex_match(
                    v, std::regex("\\d+"))) { // check if v contains only digits
                new_vec.push_back(std::stoi(v));
            }
        }
        dest.second.push_back(new_vec);
    }
    return dest;
}

mtpk::DataTableDouble mtpk::DataTable::str_to_double(mtpk::DataTableStr src) {
    mtpk::DataTableDouble dest;

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
