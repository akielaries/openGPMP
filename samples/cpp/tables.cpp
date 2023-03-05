#include "../../include/struct/datatable.hpp"
#include <string>
#include <map>
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
