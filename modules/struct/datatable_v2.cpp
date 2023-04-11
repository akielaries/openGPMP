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

class DataTable {
  public:
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
                // If no columns are selected or the column is selected,
                // add it to the column names
                if (selected_columns.empty() ||
                    std::find(selected_columns.begin(), selected_columns.end(),
                              name) != selected_columns.end()) {
                    column_names.push_back(name);
                }
            }

            // Read data lines
            std::string record_str;
            while (std::getline(file, record_str)) {
                std::istringstream record(record_str);
                std::vector<std::pair<std::string, std::string>> row_pairs;
                std::string value;
                int i = 0;
                while (std::getline(record, value, ',')) {
                    if (i < column_names.size()) {
                        row_pairs.push_back(
                            std::make_pair(column_names[i], value));
                    }
                    i++;
                }
                std::map<std::string, std::string> row(row_pairs.begin(),
                                                       row_pairs.end());
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

        // Get the list of column names in the order they appear in the CSV
        std::vector<std::string> column_names;
        std::map<std::string, size_t> column_widths;
        const auto &first_row = data[0];
        for (const auto &pair : first_row) {
            column_names.push_back(pair.first);
            column_widths[pair.first] = pair.first.size() + 2;
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
};

int main() {
    DataTable dt;
    std::vector<std::string> selected_columns = {"DC", "X", "Y", "area"};
    std::string filename = "../../data/forestfires.csv";

    std::vector<std::map<std::string, std::string>> frame =
        dt.csv_read(filename);

    // std::vector<std::map<std::string, std::string>> frame2 =
    //    csv_read("../../data/school_scores.csv");
    // Print dataframe
    dt.display(frame);
    // display(frame2);

    return 0;
}
