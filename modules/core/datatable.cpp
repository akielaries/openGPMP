#include "../../include/core/datatable.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>
mtpk::DataTable::readCSV(std::string filename,
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
