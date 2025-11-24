#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void rt_print(Value v) {
    switch (v.type) {
    case VAL_INT:
        printf("%ld\n", v.as.i);
        break;
    case VAL_BOOL:
        printf("%s\n", v.as.b ? "True" : "False");
        break;
    case VAL_STRING:
        printf("%s\n", v.as.s ? v.as.s : "");
        break;
    }
}

void rt_runtime_error(int line, const char *fmt, ...) {
    va_list args;
    fprintf(stderr, "Runtime/Semantic error: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (line > 0) {
        fprintf(stderr, " (line %d)", line);
    }
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}
