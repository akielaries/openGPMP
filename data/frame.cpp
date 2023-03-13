/**
 * Lets test out an existing dataframe utility for cpp
 */

#include <DataFrame/DataFrame.h>

// the DataFrame lib by Hossein Moein
using namespace hmdf;
using StrDataFrame = StdDataFrame<std::string>;

int main() {
    StrDataFrame test;

    test.read("forestfires.csv", io_format::csv2);




    return 0;
}

