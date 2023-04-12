#include "../../include/core/datatable.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    /*
     * for now specific columns must be in the order they appear in the file
     * being read in
     */
    mtpk::DataTable dt;
    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>
        result = dt.readCSV("../../data/forestfires.csv",
                            {"month", "day", "temp", "wind"});
    // Print the column headers
    for (const auto &header : result.first) {
        std::cout << header << "\t";
    }
    std::cout << std::endl;

    // Print the data rows
    for (const auto &row : result.second) {
        for (const auto &value : row) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
    int num_columns = result.first.size();
    int num_rows = result.second.size();

    // Print the dimensions
    // std::cout << "[" << numColumns << " x " << numRows << "]" << endl;

    std::cout << "[" << num_rows << " rows"
              << " x " << num_columns << " columns"
              << "]\n\n";

    return 0;
}
