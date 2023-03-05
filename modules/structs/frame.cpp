#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::map<std::string, std::string>>
    read_csv(std::string filename, std::vector<std::string> columns);

std::vector<std::map<std::string, std::string>>
    read_csv(std::string filename, std::vector<std::string> columns) {
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
    std::map<std::string, int> column_indices;
    std::string field;
    int index = 0;
    while (std::getline(ss, field, ',')) {
        if (std::find(columns.begin(), columns.end(), field) !=
            columns.end()) {
            column_indices[field] = index;
        }
        index++;
    }

    // Read the data
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::map<std::string, std::string> row;
        index = 0;
        while (std::getline(ss, field, ',')) {
            if (column_indices.find(columns[index]) !=
                column_indices.end()) {
                row[columns[index]] = field;
            }
            index++;
        }
        data.push_back(row);
    }

    return data;
}

int main() {
    std::vector<std::string> columns = {"year", "GPA"};
    std::vector<std::map<std::string, std::string>> data =
        read_csv("../../data/school_scores.csv", columns);
    // Print the data
    int i = 0;
    for (const auto &row : data) {
        std::cout << i << "\t";
        for (const auto &column : columns) {
            std::cout << row.at(column) << "\t";
        }
        std::cout << std::endl;
        i++;
    }

    return 0;
}

