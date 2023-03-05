#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // for std::find

std::vector<std::map<std::string, std::string>> read_csv(std::string filename, std::vector<std::string> selected_columns) {
    std::vector<std::map<std::string, std::string>> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return data;
    }

    // Read the first line and determine the column indices
    std::string line;
    std::getline(file, line);
    std::istringstream ss(line);
    std::vector<std::string> all_columns;
    std::string field;
    while (std::getline(ss, field, ',')) {
        all_columns.push_back(field);
    }

    std::vector<int> column_indices;
    for (const auto& column : selected_columns) {
        auto it = std::find(all_columns.begin(), all_columns.end(), column);
        if (it == all_columns.end()) {
            std::cerr << "Column not found: " << column << std::endl;
            return data;
        }
        column_indices.push_back(std::distance(all_columns.begin(), it));
    }

    // Read the data
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::map<std::string, std::string> row;
        int index = 0;
        while (std::getline(ss, field, ',')) {
            if (std::find(column_indices.begin(), column_indices.end(), index) != column_indices.end()) {
                row[all_columns[index]] = field;
            }
            index++;
        }
        data.push_back(row);
    }

    return data;
}


int main() {
    std::vector<std::string> columns = {"year", "GPA"};
    std::vector<std::string> selected_columns = {"year"};
    std::vector<std::map<std::string, std::string>> data =
        read_csv("../../data/school_scores.csv", selected_columns);
    // Print the data
    int i = 0;
    for (const auto &row : data) {
        std::cout << i << "\t";
        for (const auto &column : selected_columns) {
            std::cout << row.at(column) << "\t";
        }
        std::cout << std::endl;
        i++;
    }

    return 0;
}

