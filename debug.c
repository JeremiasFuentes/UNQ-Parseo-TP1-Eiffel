#include <stdbool.h>
#include <stdio.h>
#include "debug.h"

bool debug_print_tokens = false;
bool debug_print_env_actions = false;

void print_token(const char *name, const char *lexeme) {
  if (debug_print_tokens) {
    printf("%-18s -> %s\n", name, lexeme);
  }
}

void print_env_action(const char *action, const char *detail) {
  if (debug_print_env_actions) {
    printf("%-12s -> %s\n", action, detail);
  }
}