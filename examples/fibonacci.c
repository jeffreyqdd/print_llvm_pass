#include <stdio.h>

int parse_user_input() {
    int value;
    printf("Enter an integer: ");
    scanf("%d", &value);
    return value;
}

int64_t fibonacci(int64_t a) {
    if (a <= 1) {
        return a;
    }
    return fibonacci(a - 1) + fibonacci(a - 2);
}

int main() {
    int result = parse_user_input();
    printf("fibonacci(%d) = %lld\n", result, fibonacci(result));
    return 0;
}
