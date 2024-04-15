#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

class MyDataFrame {
  private:
    std::vector<int64_t> intColumns;
    std::vector<long double> doubleColumns;
    std::vector<std::string> stringColumns;

  public:
    MyDataFrame(const std::string &filename) {
        // Initialize the timer
        auto start = std::chrono::high_resolution_clock::now();

        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::string line;
        if (!getline(file, line)) {
            throw std::runtime_error("Empty file: " + filename);
        }

        std::stringstream header(line);
        std::vector<std::string> headerCols;
        std::string columnName;

        while (getline(header, columnName, ',')) {
            headerCols.push_back(columnName);
        }

        // Read data rows and determine column types
        while (getline(file, line)) {
            std::stringstream rowStream(line);
            std::string value;
            int columnIndex = 0;

            while (getline(rowStream, value, ',')) {
                if (columnIndex >= headerCols.size()) {
                    // Handle the case where the number of columns in the row
                    // exceeds the header
                    break;
                }

                if (headerCols[columnIndex] == "int_column") {
                    int64_t intValue = std::stoll(value);
                    intColumns.push_back(intValue);
                } else if (headerCols[columnIndex] == "double_column") {
                    long double doubleValue = std::stold(value);
                    doubleColumns.push_back(doubleValue);
                } else {
                    // Default to string if the column type is not recognized
                    stringColumns.push_back(value);
                }

                columnIndex++;
            }
        }

        file.close();

        // Stop the timer
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // Log the time taken for CSV reading
        std::cout << "Time taken for CSV reading: " << duration.count() << " ms"
                  << std::endl;

        // Log column types
        std::cout << "Column Types:" << std::endl;
        std::cout << "intColumns: " << intColumns.size() << " elements"
                  << std::endl;
        std::cout << "doubleColumns: " << doubleColumns.size() << " elements"
                  << std::endl;
        std::cout << "stringColumns: " << stringColumns.size() << " elements"
                  << std::endl;

        // Print the first 5 rows of the data
        std::cout << "First 5 rows of data:" << std::endl;
        printFirst5Rows();
    }

    // Helper method to print the first 5 rows of the data
    void printFirst5Rows() {
        size_t rowCount =
            std::min(std::min(std::min(intColumns.size(), doubleColumns.size()),
                              stringColumns.size()),
                     size_t(5));

        for (int i = 0; i < rowCount; ++i) {
            std::cout << "Row " << i + 1 << ": ";
            if (i < intColumns.size()) {
                std::cout << intColumns[i] << " ";
            }
            if (i < doubleColumns.size()) {
                std::cout << doubleColumns[i] << " ";
            }
            if (i < stringColumns.size()) {
                std::cout << stringColumns[i] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        MyDataFrame df("../data/1m.csv");
        // Perform additional operations on the columns as needed
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
