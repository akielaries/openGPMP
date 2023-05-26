#include <iostream>

extern "C" {
int accl_arr_exec();
}

int main() {
    accl_arr_exec();

    return 0;
}
