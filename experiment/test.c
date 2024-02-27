#include <stdio.h>

// Declare the assembly function as an external function
extern int asm_function(int a,
                        int b,
                        int c,
                        int d,
                        int e,
                        int f,
                        int g,
                        int h,
                        int i,
                        int j,
                        int k,
                        double l);

int add(int a, int b, int c) {

    // performs:
    //
    // a + b + c - d - e + f + g - h + i - j + k

    int d = 2, e = 11, f = 33, g = 22, h = 4, i = 39, j = 18, k = 9;

    double l = 1.23;

    return asm_function(a, b, c, d, e, f, g, h, i, j, k, l);
}

int main() {
    int a = 5;
    int b = 7;
    int c = 10;
    // int result = asm_function(5, 7);
    int result = add(a, b, c);
    printf("Result: %d\n", result);
    return 0;
}
