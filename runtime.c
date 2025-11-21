#include <stdio.h>
#include "value.h"
#include "runtime.h"

void runtime_print(Value v) {
    switch (v.type) {
        case TYPE_INT:
            printf("%d\n", v.i);
            break;
        // case TYPE_BOOL:
        //     printf("%s\n", v.b ? "true" : "false");
        //     break;
        case TYPE_STRING:
            printf("%s\n", v.s);
            break;
        case TYPE_VOID:
            printf("(void)\n");
            break;
    }
}

void runtime_error(const char *msg) {
    fprintf(stderr, "Runtime error: %s\n", msg);
}
