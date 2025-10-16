#include "stdio.h"

void __trace_call(char *func_name) { printf("llvm: calling function: %s(", func_name); }

void __trace_i64(int64_t n) { printf("%lld, ", n); }
void __trace_i32(int32_t n) { printf("%d, ", n); }
void __trace_i16(int16_t n) { printf("%d, ", n); }
void __trace_i8(int8_t n) { printf("%d, ", n); }

void __trace_char(char n) { printf("%c, ", n); }
void __trace_str(char *n) {
    for (const char *p = n; *p; p++) {
        if (*p == '\n') {
            printf("\\n");
        } else {
            putchar(*p);
        }
    }
    printf(", ");
}

void __trace_any() { printf("any, "); }
void __trace_end() { printf(")\n"); }
// void __trace_bool(int8_t n) { printf("%s, ", n ? "true" : "false"); }
// void __trace_int64(int64_t n) { printf("%d, ", n); }