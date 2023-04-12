#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

pair<vector<string>, vector<vector<string>>>
readCSV(string filename, vector<string> columns = {}) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<string>> data;
    string line;

    // Get the header line and parse the column names
    getline(file, line);
    stringstream header(line);
    vector<string> headerColumns;
    string columnName;

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
            cerr << "Column not found: " << column << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Read in the data rows
    while (getline(file, line)) {
        vector<string> row;
        stringstream rowStream(line);
        string value;
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

int main() {
    /*
     * for now specific columns must be in the order they appear in the file
     * being read in
     */
    pair<vector<string>, vector<vector<string>>> result =
        readCSV("../../data/forestfires.csv", {"month", "day", "temp", "wind"});
    // Print the column headers
    for (const auto &header : result.first) {
        cout << header << "\t";
    }
    cout << endl;

    // Print the data rows
    for (const auto &row : result.second) {
        for (const auto &value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
    int num_columns = result.first.size();
    int num_rows = result.second.size();

    // Print the dimensions
    // cout << "[" << numColumns << " x " << numRows << "]" << endl;

    cout << "[" << num_rows << " rows"
         << " x " << num_columns << " columns"
         << "]\n\n";

    return 0;
}
