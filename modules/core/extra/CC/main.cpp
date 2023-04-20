#include <iostream>

extern "C" {
// C function from before
int add(int, int);
}

int add_num(int x, int y) {
    int z = add(x, y);
    return z;
}

int main() {

    int sum = add_num(4, 13);

    std::cout << "result = " << sum << std::endl;
    return 0;
}
