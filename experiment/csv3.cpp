#include "../include/core/datatable.hpp"
#include "../include/core/utils.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono> // for timing

// For mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void handle_error(const char* msg);
const char* map_file(const char* fname, size_t& length);

//using DataTableStr = std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>;


//gpmp::core::DataTableStr csv_read(const char* fname, const std::vector<std::string>& columns);

int main()
{
    const char* file = "../data/1m.csv";
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> data;
    gpmp::core::DataTable dt;

    // Timing variables
    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing

    // Use the efficient CSV reader
    gpmp::core::DataTableStr result = dt.csv_read(file, columns);


    auto end_time = std::chrono::high_resolution_clock::now(); // End timing
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Time to read and store CSV data using efficient method: " << elapsed_time.count() << " ms\n";

    // Access result.columns and result.data as needed
    // result.first is columns, and result.second is data

    dt.display(result);

    return 0;
}

const char* map_file(const char* fname, size_t& length)
{
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // Obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO: Close fd at some point in time, call munmap(...)
    return addr;
}
gpmp::core::DataTableStr gpmp::core::DataTable::csv_read(
    std::string filename, std::vector<std::string> columns) {

    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        // Handle file open error
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    char *file_data = static_cast<char*>(mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0));

    if (file_data == MAP_FAILED) {
        // Handle memory mapping error
        perror("Error mapping file to memory");
        close(fd);
        exit(EXIT_FAILURE);
    }

    std::stringstream file_stream(file_data);
    std::vector<std::vector<std::string>> data;
    std::string line;

    // Get the header line and parse the column names
    getline(file_stream, line);
    std::stringstream header(line);
    std::vector<std::string> header_cols;
    std::string columnName;

    while (getline(header, columnName, ',')) {
        header_cols.push_back(columnName);
    }

    // If no columns are specified, read in all columns
    if (columns.empty()) {
        columns = header_cols;
    }

    // Check if specified columns exist in the header
    for (const auto &column : columns) {
        if (std::find(header_cols.begin(), header_cols.end(), column) ==
            header_cols.end()) {
            // Handle column not found error
            perror(("Column: " + column + " not found").c_str());
            munmap(file_data, size);
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // Read in the data rows
    while (getline(file_stream, line)) {
        std::vector<std::string> row;
        std::stringstream rowStream(line);
        std::string value;
        int columnIndex = 0;

        while (getline(rowStream, value, ',')) {
            // If column is specified, only read in specified columns
            if (std::find(columns.begin(), columns.end(),
                          header_cols[columnIndex]) != columns.end()) {
                row.push_back(value);
            }

            columnIndex++;
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    // populate headers_ class variable
    headers_ = columns;
    // populate data_ class variable
    data_ = data;

    munmap(file_data, size);
    close(fd);

    return std::make_pair(headers_, data_);
}

void handle_error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

