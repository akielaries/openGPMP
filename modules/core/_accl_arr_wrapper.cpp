#include <iostream>

extern "C" {
void accl_arr_exec();
}

int main() {
    accl_arr_exec();

    return 0;
}
