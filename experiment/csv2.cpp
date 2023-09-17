#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono> // for timing

// For mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void handle_error(const char* msg);
const char* map_file(const char* fname, size_t& length);
void csv_read(const char* fname, std::vector<std::string>& csvLines, std::vector<std::vector<std::string>>& columns);
void displayCSVData(const std::vector<std::string>& csvLines);

static uintmax_t wc(char const *fname)
{
    static const auto BUFFER_SIZE = 16*1024;
    int fd = open(fname, O_RDONLY);
    if(fd == -1)
        handle_error("open");

    /* Advise the kernel of our access pattern.  */
    posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL

    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;

    while(size_t bytes_read = read(fd, buf, BUFFER_SIZE))
    {
        if(bytes_read == (size_t)-1)
            handle_error("read failed");
        if (!bytes_read)
            break;

        for(char *p = buf; (p = (char*) memchr(p, '\n', (buf + bytes_read) - p)); ++p)
            ++lines;
    }

    return lines;
}

int main()
{
    const char* file = "../data/1m.csv";
    //const char* file = "../data/Tetuan_power_consumption.csv";

    std::vector<std::string> csvLines;
    std::vector<std::vector<std::string>> columns;
    // Timing variables
    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing
    csv_read(file, csvLines, columns);

    auto end_time = std::chrono::high_resolution_clock::now(); // End timing
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Time to read and store CSV data: " << elapsed_time.count() << " ms\n";

    // Display the CSV data
  //  displayCSVData(csvLines);

    return 0;
}

void handle_error(const char* msg) {
    perror(msg);
    exit(255);
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

void csv_read(const char* fname, std::vector<std::string>& csvLines, std::vector<std::vector<std::string>>& columns)
{
    size_t length;
    auto csvData = map_file(fname, length);
    auto endOfFile = csvData + length;

    // Count the number of lines in the CSV file and calculate the number of columns
    uintmax_t numLines = wc(fname); // Use the optimized line-counting function

    if (numLines == 0)
    {
        std::cerr << "Error: Empty file or unable to count lines." << std::endl;
        return;
    }

    size_t numColumns = 0;

    for (auto currentPos = csvData; currentPos && currentPos != endOfFile; ++currentPos)
    {
        if (*currentPos == '\n')
        {
            numColumns = std::count(csvData, currentPos, ',') + 1;
            columns.resize(numColumns);
            break; // Stop counting columns after the first line
        }
    }

    // Preallocate memory for csvLines and columns
    csvLines.reserve(numLines);
    for (auto& col : columns)
    {
        col.reserve(numLines);
    }

    const char* lineStart = csvData;
    auto currentPos = csvData;

    for (; currentPos && currentPos != endOfFile; ++currentPos)
    {
        if (*currentPos == ',' || *currentPos == '\n')
        {
            csvLines.emplace_back(lineStart, currentPos - lineStart);

            // Split the line into columns
            size_t columnIndex = 0;
            const char* columnStart = lineStart;
            for (; columnStart != currentPos; ++columnStart)
            {
                if (*columnStart == ',')
                {
                    std::string value(columnStart + 1, currentPos - columnStart - 1);

                    try {
                        // Try converting to integer
                        int64_t int_value = std::stoll(value);
                        columns[columnIndex++].emplace_back(std::to_string(int_value));
                    } catch (const std::invalid_argument &) {
                        try {
                            // Try converting to double
                            long double double_value = std::stold(value);
                            columns[columnIndex++].emplace_back(std::to_string(double_value));
                        } catch (const std::invalid_argument &) {
                            // Conversion failed, treat as a string
                            columns[columnIndex++].emplace_back(std::move(value));
                        }
                    }
                }
            }

            lineStart = currentPos + 1;
        }
    }
}

void displayCSVData(const std::vector<std::string>& csvLines)
{
    // Implement your logic to print or process the CSV data here
    for (const auto& line : csvLines)
    {
        std::cout << "CSV Line: " << line << "\n";
    }
}

