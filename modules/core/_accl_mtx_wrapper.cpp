#include <iostream>

extern "C" {
void accl_mtx_exec();
}

int main() {
    accl_mtx_exec();
    return 0;
}
