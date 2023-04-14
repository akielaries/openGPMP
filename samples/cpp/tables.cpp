/**
 * Test driver showing how to use openMTPK's DataTable core utility class.
 *
 * @todo: TODO
 *
 * @example tables.cpp
 */

#include "../../include/struct/datatable.hpp"
#include <map>
#include <string>
#include <vector>

int main() {
    mtpk::Datatable dt;
    std::vector<std::map<std::string, std::string>> frame =
        dt.csv_read("../../data/forestfires.csv");

    std::vector<std::map<std::string, std::string>> frame2 =
        dt.csv_read("../../data/school_scores.csv");
    // Print dataframe
    dt.display(frame);
    dt.display(frame2);

    return 0;
}
