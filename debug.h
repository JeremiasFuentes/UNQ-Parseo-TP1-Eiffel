#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

extern bool debug_print_tokens;

void print_token(const char *name, const char *lexeme);

#endif