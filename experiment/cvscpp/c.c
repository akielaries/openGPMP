struct Arith {
    int (*add)(int, int);
    int (*sub)(int, int);
    int (*mul)(int, int);
};

int add(int n1, int n2) { 
    return n1 + n2;
}

int sub(int n1, int n2) {
    return n1 - n2; 
}

int mul(int n1, int n2) {
    return n1 * n2; 
}

int main() {
    struct Arith arith = {add, sub, mul};

    for (int i = 0; i < 2048; i++) {
        int resl = arith.add(i, i + i);
        int diff = arith.sub(i, i + i);
        int prod = arith.mul(i, i + i);
    }

    return 0;
}

