#include "stdio.h"

void __trace_call(char *func_name) { fprintf(stderr, "llvm: calling function: %s(", func_name); }

void __trace_i64(int64_t n) { fprintf(stderr, "%lld, ", n); }
void __trace_i32(int32_t n) { fprintf(stderr, "%d, ", n); }
void __trace_i16(int16_t n) { fprintf(stderr, "%d, ", n); }
void __trace_i8(int8_t n) { fprintf(stderr, "%d, ", n); }

void __trace_char(char n) { fprintf(stderr, "%c, ", n); }
void __trace_str(char *n) {
    if (n == NULL) {
        fprintf(stderr, "NULL, ");
        return;
    }

    int cnt = 0;
    for (const char *p = n; *p; p++) {
        if (cnt > 10) {
            fprintf(stderr, "..., ");
            break;
        }
        if (*p == '\n') {
            fprintf(stderr, "\\n");
        } else {
            fprintf(stderr, "%c", *p);
        }
        cnt++;
    }
    fprintf(stderr, ", ");
}

void __trace_any() { fprintf(stderr, "any, "); }
void __trace_end() { fprintf(stderr, ")\n"); }
