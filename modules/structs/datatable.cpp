#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::map<std::string, std::string>>
    read_csv(std::string filename,
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
            }
            data.push_back(row);
        }
    }

    return data;
}

void print_dataframe(
    const std::vector<std::map<std::string, std::string>> &data) {
    if (data.empty()) {
        std::cout << "Empty dataframe" << std::endl;
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
    std::vector<std::map<std::string, std::string>> frame =
        read_csv("../../data/forestfires.csv");

    std::vector<std::map<std::string, std::string>> frame2 =
        read_csv("../../data/school_scores.csv");
    // Print dataframe
    print_dataframe(frame);
    print_dataframe(frame2);

    return 0;
}
