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

//#include "../../include/struct/datatable.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::map<std::string, std::string>>
    csv_read(std::string filename,
             std::vector<std::string> selected_columns = {}) {
    std::ifstream file(filename);
    std::vector<std::map<std::string, std::string>> data;

    if (file) {
        // Read header line
        std::string line;
        std::getline(file, line);
        std::istringstream header(line);
        std::vector<std::string> column_names;
        std::string name;
        while (std::getline(header, name, ',')) {
            // If no columns are selected or the column is selected, add it
            // to the column names
            if (selected_columns.empty() ||
                std::find(selected_columns.begin(), selected_columns.end(),
                          name) != selected_columns.end()) {
                column_names.push_back(name);
                // std::cout<<name<<std::endl;
            }
        }

        // Read data lines
        while (std::getline(file, line)) {
            std::istringstream record(line);
            std::map<std::string, std::string> row;
            for (const auto &column_name : column_names) {
                std::string value;
                std::getline(record, value, ',');
                row[column_name] = value;
                // std::cout<<row[column_name]<<std::endl;
            }
            data.push_back(row);
        }
    }

    return data;
}

void display(const std::vector<std::map<std::string, std::string>> &data) {
    if (data.empty()) {
        std::cout << "Empty DataTable" << std::endl;
        return;
    }

    // Get the list of column names
    std::vector<std::string> column_names;
    std::map<std::string, size_t> column_widths;
    for (const auto &row : data) {
        for (const auto &pair : row) {
            if (std::find(column_names.begin(), column_names.end(),
                          pair.first) == column_names.end()) {
                column_names.push_back(pair.first);
                column_widths[pair.first] = pair.first.size() + 2;
            }
            if (pair.second.size() + 2 > column_widths[pair.first]) {
                column_widths[pair.first] = pair.second.size() + 2;
            }
        }
    }

    // Print the data
    std::cout << std::left;
    std::cout << std::setw(4) << "";
    for (const auto &name : column_names) {
        std::cout << std::setw(column_widths[name]) << name;
    }
    std::cout << std::endl;

    int num_rows = data.size();
    int start_row = 0;
    int end_row = num_rows - 1;
    if (num_rows > 10) {
        end_row = 4;
        for (int i = start_row; i <= end_row; i++) {
            std::cout << std::setw(4) << i;
            for (const auto &name : column_names) {
                if (data[i].count(name)) {
                    std::cout << std::setw(column_widths[name])
                              << data[i].at(name);
                } else {
                    std::cout << std::setw(column_widths[name]) << "";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "... " << num_rows - 10 << " rows omitted ..."
                  << std::endl;
        start_row = num_rows - 5;
        end_row = num_rows - 1;
    }

    for (int i = start_row; i <= end_row; i++) {
        std::cout << std::setw(4) << i;
        for (const auto &name : column_names) {
            if (data[i].count(name)) {
                std::cout << std::setw(column_widths[name])
                          << data[i].at(name);
            } else {
                std::cout << std::setw(column_widths[name]) << "";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "[" << num_rows << " rows"
              << " x " << column_names.size() << " columns"
              << "]\n\n";
}

int main() {
    // mtpk::Datatable dt;
    std::vector<std::map<std::string, std::string>> frame =
        csv_read("../../data/forestfires.csv");

    // std::vector<std::map<std::string, std::string>> frame2 =
    //    csv_read("../../data/school_scores.csv");
    // Print dataframe
    display(frame);
    // display(frame2);

    return 0;
}
