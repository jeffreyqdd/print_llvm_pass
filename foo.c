#include <stdio.h>

void print_hello() { printf("Hello, World\n"); }
int32_t plus1(int32_t a) { return a + 1; }
int64_t fibonacci(int64_t a) {
    if (a <= 1) {
        return a;
    }
    return fibonacci(a - 1) + fibonacci(a - 2);
}

int main() {
    print_hello();
    printf("fibonacci(2) = %lld\n", fibonacci(2));
    plus1(10);
    return 0;
}
