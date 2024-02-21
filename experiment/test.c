#include <stdio.h>

// Declare the assembly function as an external function
extern int asm_function(int a, int b, int c, int d);

int add (int a, int b, int c) {
    int d = 2;

    return asm_function(a, b, c, d);
}

int main() {
    int a = 5;
    int b = 7;
    int c = 10;
    //int result = asm_function(5, 7);
    int result = add(a, b, c);
    printf("Result: %d\n", result);
    return 0;
}

