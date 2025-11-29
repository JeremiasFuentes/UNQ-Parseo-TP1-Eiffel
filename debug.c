#include <stdbool.h>
#include <stdio.h>
#include "debug.h"

bool debug_print_tokens = false;

void print_token(const char *name, const char *lexeme) {
  if (debug_print_tokens) {
    printf("%-18s -> %s\n", name, lexeme);
  }
}