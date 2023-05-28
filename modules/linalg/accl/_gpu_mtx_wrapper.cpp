#include <iostream>

extern "C" {
int accl_mtx_exec();
}

int main() {
    accl_mtx_exec();
    return 0;
}
